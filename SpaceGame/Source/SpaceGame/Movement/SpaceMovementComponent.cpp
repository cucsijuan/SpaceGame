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

void USpaceMovementComponent::ApplyYawRotation(float DeltaTime, float SteeringThrow)
{
	SteeringThrow = FMath::Clamp(SteeringThrow, -1.f, 1.f);

	float DeltaDegrees = MaxYawAcceleration * DeltaTime * SteeringThrow;

	if (DeltaDegrees == 0.f && YawVelocity != 0)
	{
		float AbsBrakeForce = YawBrakeForce * DeltaTime;
		YawVelocity += YawVelocity > 0 ? -AbsBrakeForce : AbsBrakeForce;

		if (FMath::IsNearlyZero(YawVelocity, 0.2f))
		{
			YawVelocity = 0.f;
		}
	}
	else
	{
		YawVelocity += DeltaDegrees;

		if (FMath::Abs(YawVelocity) > MaxYawVelocity)
		{
			if (YawVelocity > 0)
			{
				YawVelocity = MaxYawVelocity;
			}
			else
			{
				YawVelocity = -MaxYawVelocity;
			}
		}
	}

	FQuat RotationDelta(GetOwner()->GetActorUpVector(), FMath::DegreesToRadians(YawVelocity));

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
	PitchThrow = FMath::Clamp(PitchThrow, -1.f, 1.f);

	float DeltaDegrees = MaxPitchAcceleration * DeltaTime * PitchThrow;

	if (DeltaDegrees == 0.f && PitchVelocity != 0)
	{
		float AbsBrakeForce = PitchBrakeForce * DeltaTime;
		PitchVelocity += PitchVelocity > 0 ? -AbsBrakeForce : AbsBrakeForce;

		if (FMath::IsNearlyZero(PitchVelocity, 0.2f))
		{
			PitchVelocity = 0.f;
		}
	}
	else
	{
		PitchVelocity += DeltaDegrees;

		if (FMath::Abs(PitchVelocity) > MaxPitchVelocity)
		{
			if (PitchVelocity > 0)
			{
				PitchVelocity = MaxPitchVelocity;
			}
			else
			{
				PitchVelocity = -MaxPitchVelocity;
			}
		}
	}

	FQuat RotationDelta(GetOwner()->GetActorRightVector(), FMath::DegreesToRadians(PitchVelocity));

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
	InRollThrow = FMath::Clamp(InRollThrow, -1.f, 1.f);
	
	float DeltaDegrees = MaxRollAcceleration * DeltaTime * InRollThrow;

	if (DeltaDegrees == 0.f && RollVelocity != 0)
	{
		float AbsBrakeForce = RollBrakeForce * DeltaTime;
		RollVelocity += RollVelocity > 0 ? -AbsBrakeForce : AbsBrakeForce;

		if (FMath::IsNearlyZero(RollVelocity, 0.2f))
		{
			RollVelocity = 0.f;
		}
	}
	else
	{
		RollVelocity += DeltaDegrees;

		if (FMath::Abs(RollVelocity) > MaxRollVelocity)
		{
			if (RollVelocity > 0)
			{
				RollVelocity = MaxRollVelocity;
			}
			else
			{
				RollVelocity = -MaxRollVelocity;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("RollVel: %f"), RollVelocity);
	
	FQuat RotationDelta(GetOwner()->GetActorForwardVector(), FMath::DegreesToRadians(RollVelocity));

	Velocity = RotationDelta.RotateVector(Velocity);

	FHitResult  Hit;

	GetOwner()->AddActorWorldRotation(RotationDelta, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		GetOwner()->AddActorWorldRotation(RotationDelta.Inverse());
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

	ApplyYawRotation(Move.DeltaTime, Move.SteeringThrow);

	ApplyPitchRotation(Move.DeltaTime, Move.PitchThrow);

	ApplyRollRotation(Move.DeltaTime, Move.RollThrow);

	UpdateLocationFromVelocity(Move.DeltaTime);
}

FVector USpaceMovementComponent::GetAirResistance()
{
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

float USpaceMovementComponent::GetRotationDrag(float RotationVelocity)
{
	return -FMath::Square(RotationVelocity) * RotationDragCoefficient;
}

FVector USpaceMovementComponent::GetRollingResistance()
{
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100;

	float NormalForce = Mass * AccelerationDueToGravity;

	return -Velocity.GetSafeNormal() * RollingResistanceCoefficient * NormalForce;
}

float USpaceMovementComponent::GetFloatRollingResistance()
{
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100; //TODO: change this to a parameter and this function should be called get brake thrusters or somenthing like that

	float NormalForce = Mass * AccelerationDueToGravity;

	UE_LOG(LogTemp, Warning, TEXT("%d"), -RollingResistanceCoefficient * NormalForce);

	return -RollingResistanceCoefficient * NormalForce;
}
