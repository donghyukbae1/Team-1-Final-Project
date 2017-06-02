// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerRun.h"
#include "PlayerRunner.h"
#include "Pickup.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


// Sets default values
APlayerRunner::APlayerRunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Dont let pawn rotations be affected by controller. Must be above Camera Components
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Character movement settings
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.0f;

	//Mouse Rates
	OrbitRate = 45.0f;
	PitchRate = 45.0f;

	//Create Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//Create Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

}

// Called when the game starts or when spawned
void APlayerRunner::BeginPlay()
{
	Super::BeginPlay();

	IntPower = 200.0f;
	MaxSpeed = GetCharacterMovement()->GetMaxSpeed();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Character Loaded"));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Max Speed: ") + FString::SanitizeFloat(MaxSpeed));
	}
}

// Called every frame
void APlayerRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, TEXT("Internal Power: ") + FString::SanitizeFloat(IntPower));
	}

	Velocity = GetVelocity().Size();

	if (Velocity != 0)
	{
		IntPower -= 1 * (Velocity / MaxSpeed) * GetWorld()->DeltaTimeSeconds;
	}
}

// Called to bind functionality to input
void APlayerRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Bind movement keys
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerRunner::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerRunner::MoveRight);

	PlayerInputComponent->BindAction("Collect", IE_Pressed, this, &APlayerRunner::CollectPickups);

	//Bind mouse inputs
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	//Bind Power keys
	PlayerInputComponent->BindAction("AddPower", IE_Pressed, this, &APlayerRunner::AddPower);
	PlayerInputComponent->BindAction("SubPower", IE_Pressed, this, &APlayerRunner::SubPower);
}

void APlayerRunner::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerRunner::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerRunner::CameraOrbit(float Value)
{
	AddControllerYawInput(Value * OrbitRate * GetWorld()->GetDeltaSeconds());
}

void APlayerRunner::CameraPitch(float Value)
{
	AddControllerPitchInput(Value * PitchRate * GetWorld()->GetDeltaSeconds());
}

void APlayerRunner::AddPower()
{
	IntPower++;
}

void APlayerRunner::SubPower()
{
	if (IntPower > 0)
	{
		IntPower--;
		if (IntPower < 0)
		{
			IntPower = 0;
		}
	}
}

void APlayerRunner::CollectPickups()
{
	//Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);
	// For each Actor we collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
	// Cast the Actor to APickup
		APickup* const TestPickup = Cast<APickup>(CollectedActors[iCollected]);
	// If the cast is successful and the pickup is valid and active
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsActive())
		{
			// call the pickups WasCollected function
			TestPickup->WasCollected();
			// Deactivate the pickup
			TestPickup->SetActive(false);
		}
	}
}