// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerRunner.generated.h"

UCLASS()
class POWERRUN_API APlayerRunner : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;

public:
	// Sets default values for this character's properties
	APlayerRunner();

	//Mouse Rates
	float OrbitRate;
	float PitchRate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Power")
	void AddPower();

	UFUNCTION(BlueprintCallable, Category = "Power")
	void SubPower();

	/** Returns CollectionSphere subobject */
	FORCEINLINE class USphereComponent* GetSphereComponent() const { return CollectionSphere;  }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Movement functions
	void MoveForward(float Value);
	void MoveRight(float Value);

	//Mouse Controls
	void CameraOrbit(float Value);
	void CameraPitch(float Value);

	/** Called when we press a key to collect any pickups inside the CollectionSphere*/
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void CollectPickups();

private:
	//Internal Power
	float IntPower;

	float Velocity;
	float MaxSpeed;
	
};
