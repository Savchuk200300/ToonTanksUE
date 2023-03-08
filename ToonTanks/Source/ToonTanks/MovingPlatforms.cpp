// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatforms.h"

// Sets default values
AMovingPlatforms::AMovingPlatforms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatforms::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatforms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}


void AMovingPlatforms::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);

	}
}
void AMovingPlatforms::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}
bool AMovingPlatforms::ShouldPlatformReturn() const
{
	return GetDistance() > MoveDistance;
}
float AMovingPlatforms::GetDistance() const
{
	float DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
	return DistanceMoved;
}
