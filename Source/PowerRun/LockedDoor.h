// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LockedDoor.generated.h"

UCLASS()
class POWERRUN_API ALockedDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockedDoor();

	UFUNCTION(BlueprintCallable, Category = 'OpenDoor');
	void setOpen(bool isOpen);

	UFUNCTION(BlueprintNativeEvent)
	bool isOpen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
