// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerRun.h"
#include "Pickup.h"
#include "PlayerInventory.h"
#include "PlayerRunner.h"
#include "Engine.h"



// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupName = "";
	PickupWeight = 0.0f;

	// creates a component to be the root of the pickup Actor, sets it to rootcomponent
	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = PickupRoot;

	// creates a mesh for the Actor and attaches it to the rootcomponent
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));

	// create overlap trigger and call trigger function on enter
	PickupBox->bGenerateOverlapEvents = true;
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnEnterPickupBox);
	PickupBox->OnComponentEndOverlap.AddDynamic(this, &APickup::OnExitPickupBox);
	PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	PickupMesh->SetSimulatePhysics(true);

	bIsInPickupBox = false;
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, TEXT("b2") + FString::FromInt(bIsInPickupBox));

	if (GEngine)
	{
		if (Player)
		{
			// It will check that the two conditions are met in order to pick up an item
			if (bIsInPickupBox && Player->bPickingUpItem)
			{
				// Adds item to inventory
				Player->Inventory->AddToInventory(this);
			
			}
		}
	}
}

// Assigns the PlayerRunner to a variable so its public functions can be accessed
void APickup::GetPlayer(AActor* OtherActor)
{
	Player = Cast<APlayerRunner>(OtherActor);

}

// Assigns true to one condition, and assigns the entering Actor to variable
void APickup::OnEnterPickupBox(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bIsInPickupBox = true;
	GetPlayer(OtherActor);
	
}

// Returns the condition to false when the item is picked up or when player chooses not to pick it up and leaves
void APickup::OnExitPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsInPickupBox = false;
}

// function that gets overriden by pickup-specific activation functionality
void APickup::Activate(AActor* OtherActor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Nothing happened."));
	}

}






