// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerRunner.h"
#include "Pickup.generated.h"

UCLASS()
class POWERRUN_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// root component for Pickup
	UPROPERTY(EditAnywhere)
		USceneComponent* PickupRoot;

	// mesh component for Pickup
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;

	// box component for Pickup
	UPROPERTY(EditAnywhere)
		UBoxComponent* PickupBox;

	// one of two conditions to pick up
	bool bIsInPickupBox;

	// PlayerRunner object who is assigned the playercharacter so the second condition can be accessed
	UPROPERTY(EditAnywhere)
	APlayerRunner* Player;

	// weight of the pickup item
	float PickupWeight;

	// activates on trigger enter
	UFUNCTION()
	void OnEnterPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// activates on trigger exit
	UFUNCTION()
	void OnExitPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Activates item and utilizes its unique functionality on the Player
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	virtual void Activate(AActor* OtherActor);

	// assigns player character to PlayerRunner variable
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void GetPlayer(AActor* OtherActor);

	FString PickupName;
	
};
