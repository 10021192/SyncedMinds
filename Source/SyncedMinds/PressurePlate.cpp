// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	SetReplicateMovement(true);

	Activated = false;
	
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	
	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	TriggerMesh->SetupAttachment(RootComp);
	TriggerMesh->SetIsReplicated(true);
	
	auto TriggerMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT
		("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (TriggerMeshAsset.Succeeded())
	{
		TriggerMesh->SetStaticMesh(TriggerMeshAsset.Object);
		TriggerMesh->SetRelativeScale3D(FVector(1.04f, 1.54f, 0.45f));
		TriggerMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
	}
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT
		("/Game/The_Lost_Ruins/Meshes/SM_slab02.SM_slab02"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
		Mesh->SetRelativeLocation(FVector::ZeroVector);
	}
	
	Transporter = CreateDefaultSubobject<UTransporter>(TEXT("Transporter"));
	Transporter->MoveTime = 0.25f;
	Transporter->OwnerIsTriggerActor = true;
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerMesh->SetVisibility(false);
	TriggerMesh->SetCollisionProfileName(FName(TEXT("OverlapAll")));
	
	FVector Point1 = GetActorLocation();
	FVector Point2 = GetActorLocation() + FVector(0.0f, 0.0f, -10.0f);
	Transporter->SetPoints(Point1, Point2);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		TArray<AActor*> OverlappingActors;
		AActor* TriggerActor = nullptr;
		TriggerMesh->GetOverlappingActors(OverlappingActors);
	
		for (int ActorIdx = 0; ActorIdx < OverlappingActors.Num(); ++ActorIdx)
		{
			AActor* A = OverlappingActors[ActorIdx];
			if (A->ActorHasTag(TEXT("TriggerActor")))
			{
				TriggerActor = A;
				break;
			}
		}

		if (TriggerActor)
		{
			if (!Activated)
			{
				Activated = true;
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,
				//	TEXT("Activated"));
				OnActivated.Broadcast();
			}
		}
		else
		{
			if (Activated)
			{
				Activated = false;
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White,
				//	TEXT("Deactivated"));
				OnDeactivated.Broadcast();
			}
		}
	}
}