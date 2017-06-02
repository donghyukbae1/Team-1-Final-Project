// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerRun.h"
#include "Pickup.h"
#include "PlayerRunner.h"
#include "BatteryPickup.h"
#include "Engine.h"


// assigns unique weight and powerlevel to battery
ABatteryPickup::ABatteryPickup() : APickup()
{
	PickupName = "Battery";
	PickupWeight = 5.0f;
	PowerLevel = 25.0f;

}

// adds power to player character, remove itself from existance
void ABatteryPickup::Activate(AActor* OtherActor)
{
	if (GEngine)
	{
		Player = Cast<APlayerRunner>(OtherActor);
		if (Player)
		{
			Player->AddToCurrentPower(PowerLevel);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Activating Battery: +") + FString::SanitizeFloat(PowerLevel) + TEXT(" Internal Power"));
		}
	}
	
}
