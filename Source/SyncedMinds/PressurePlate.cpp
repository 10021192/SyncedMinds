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
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerMesh->SetVisibility(false);
	TriggerMesh->SetCollisionProfileName(FName(TEXT("OverlapAll")));
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}