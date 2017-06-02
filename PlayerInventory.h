// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.h"
#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"

/** This is a new component of the Actor class. It is called in the PlayerRunner.h as a component type. */

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POWERRUN_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	// size of the inventory array (6)
	int InventorySize;

	// amount of objects in inventory
	int NumberOfItems;

	// inventory array that stores pointers to pickups
	UPROPERTY(EditAnywhere)
	APickup* InventoryArray[6];

	// Pointer to PlayerRunner to access its functions
	APlayerRunner* Player;

	//APickup* SpawnedItem;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SpawnPickup(APickup* PickupItem, FVector SpawnLocation, FRotator SpawnRotation);
	
	//TSubclassOf<class ABatteryPickup> BatteryPickupBlueprint;




public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// adds new pickup to inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddToInventory(APickup* PickupItem);

	// search inventory array by string itemname, return object with name if in inventory
	APickup* GetItemInInventory(int index);

	int FirstEmptySlot();

	// print out inventory, will eventually be moved to PlayerRunner so it can be bound to an input
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowInventory();

	// Use item, calls check, get and APickup::Activate()
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItemFromInventory(int index);

	// removes used or dropped items
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropFromInventory(int index);


};
