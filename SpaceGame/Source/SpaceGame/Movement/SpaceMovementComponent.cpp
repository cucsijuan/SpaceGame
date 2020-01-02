// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMovementComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"

// Sets default values for this component's properties
USpaceMovementComponent::USpaceMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USpaceMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USpaceMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwnerRole() == ROLE_AutonomousProxy || GetOwner()->GetRemoteRole() == ROLE_SimulatedProxy)
	{
		LastMove = CreateMove(DeltaTime);
		SimulateMove(LastMove);
	}
}

FGoKartMove USpaceMovementComponent::CreateMove(float DeltaTime)
{
	FGoKartMove Move;
	Move.DeltaTime = DeltaTime;
	Move.SteeringThrow = SteeringThrow;
	Move.PitchThrow = PitchThrow;
	Move.RollThrow = RollThrow;
	Move.Throttle = Throttle;
	Move.Time = GetOwner()->GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	return Move;
}

void USpaceMovementComponent::ApplyRotation(float DeltaTime, float SteeringThrow)
{
	float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = DeltaLocation / MinTurningRadius * SteeringThrow;

	FQuat RotationDelta(GetOwner()->GetActorUpVector(), RotationAngle);

	Velocity = RotationDelta.RotateVector(Velocity);

	FHitResult  Hit;

	GetOwner()->AddActorWorldRotation(RotationDelta, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		GetOwner()->AddActorWorldRotation(RotationDelta * -1);
	}
}

void USpaceMovementComponent::ApplyPitchRotation(float DeltaTime, float PitchThrow)
{
	float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = DeltaLocation / MinTurningRadius * PitchThrow;

	FQuat RotationDelta(GetOwner()->GetActorRightVector(), RotationAngle);

	Velocity = RotationDelta.RotateVector(Velocity);

	FHitResult  Hit;

	GetOwner()->AddActorWorldRotation(RotationDelta, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		GetOwner()->AddActorWorldRotation(RotationDelta * -1);
	}
}


void USpaceMovementComponent::ApplyRollRotation(float DeltaTime, float InRollThrow)
{
	float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = DeltaLocation / MinTurningRadius * InRollThrow;

	FQuat RotationDelta(GetOwner()->GetActorForwardVector(), RotationAngle);

	Velocity = RotationDelta.RotateVector(Velocity);

	FHitResult  Hit;

	GetOwner()->AddActorWorldRotation(RotationDelta, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		GetOwner()->AddActorWorldRotation(RotationDelta * -1);
	}
}

void USpaceMovementComponent::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;

	FHitResult  Hit;

	GetOwner()->AddActorWorldOffset(Translation, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

void USpaceMovementComponent::SimulateMove(const FGoKartMove& Move)
{
	FVector Force = MaxDrivingForce * Move.Throttle * GetOwner()->GetActorForwardVector();

	Force += GetAirResistance();

	Force += GetRollingResistance();

	FVector Acceleration = Force / Mass;

	Velocity += Acceleration * Move.DeltaTime;

	ApplyRotation(Move.DeltaTime, Move.SteeringThrow);

	ApplyPitchRotation(Move.DeltaTime, Move.PitchThrow);

	ApplyRollRotation(Move.DeltaTime, Move.RollThrow);

	UpdateLocationFromVelocity(Move.DeltaTime);
}

FVector USpaceMovementComponent::GetAirResistance()
{
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

FVector USpaceMovementComponent::GetRollingResistance()
{
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100;

	float NormalForce = Mass * AccelerationDueToGravity;

	return -Velocity.GetSafeNormal() * RollingResistanceCoefficient * NormalForce;
}
