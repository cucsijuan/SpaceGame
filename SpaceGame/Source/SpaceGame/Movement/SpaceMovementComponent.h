// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_BODY()

	UPROPERTY()
	float Throttle;
	UPROPERTY()
	float SteeringThrow;
	UPROPERTY()
	float PitchThrow;
	UPROPERTY()
	float RollThrow;
	UPROPERTY()
	float DeltaTime;
	UPROPERTY()
	float Time;

	bool IsValid() const 
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEGAME_API USpaceMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceMovementComponent();

	UFUNCTION(BlueprintCallable)
	void SetVelocity(FVector InVelocity) { Velocity = InVelocity; }
	UFUNCTION(BlueprintCallable)
	FVector GetVelocity() { return Velocity; }

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float InThrottle) { Throttle = InThrottle; }

	UFUNCTION(BlueprintCallable)
	void SetSteeringThrow(float InSteeringThrow) { SteeringThrow = InSteeringThrow; }
	UFUNCTION(BlueprintCallable)
	float GetSteeringThrow() { return SteeringThrow; }

	UFUNCTION(BlueprintCallable)
	void SetPitchThrow(float InPitchThrow) { PitchThrow = InPitchThrow; }
	UFUNCTION(BlueprintCallable)
	float GetPitchThrow() { return PitchThrow; }

	UFUNCTION(BlueprintCallable)
	void SetRollThrow(float InRollThrow) { RollThrow = InRollThrow; }
	UFUNCTION(BlueprintCallable)
	float GetRollThrow() { return RollThrow; }

	FGoKartMove GetLastMove() { return LastMove; }

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// The mass of the ship (kg).
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	//Force applied to the Ship when the throttle is fully down (N).
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	//Max Forward Speed (M/s).
	UPROPERTY(EditAnywhere)
	float MaxDriveSpeed = 140.f;

	//Max Forward Speed (M/s).
	UPROPERTY(EditAnywhere)
	float MaxDriveAcceleration = 100.f;

	//Max Forward Speed (M/s).
	UPROPERTY(EditAnywhere)
	float DriveBreakForce = 60.f;

	//Max Roll acceleration of the ship (Deg/s).
	UPROPERTY(EditAnywhere)
	float MaxRollAcceleration = 2.5f;

	//Max Roll Velocity of the ship (Deg/s)
	UPROPERTY(EditAnywhere)
	float MaxRollVelocity = 5.f;

	//Te force applied to Break Roll when no input is applied (Deg/s)
	UPROPERTY(EditAnywhere)
	float RollBrakeForce = 3.f;

	//Max Pitch acceleration of the ship (Deg/s).
	UPROPERTY(EditAnywhere)
	float MaxPitchAcceleration = 2.5f;

	//Max Pitch Velocity of the ship (Deg/s)
	UPROPERTY(EditAnywhere)
	float MaxPitchVelocity = 5;

	//Te force applied to Break Pitch when no input is applied (Deg/s)
	UPROPERTY(EditAnywhere)
	float PitchBrakeForce = 3;

	//Max Pitch acceleration of the ship (Deg/s).
	UPROPERTY(EditAnywhere)
	float MaxYawAcceleration = 2.5f;

	//Max Yaw Velocity of the ship (Deg/s)
	UPROPERTY(EditAnywhere)
	float MaxYawVelocity = 5;

	//Te force applied to Break Yaw when no input is applied (Deg/s)
	UPROPERTY(EditAnywhere)
	float YawBrakeForce = 3;

	//Minimum radius of the ship turning at full lock (m).
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10;

	//Higher means more drag
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16;

	//Higher means more drag
	UPROPERTY(EditAnywhere)
	float RotationDragCoefficient = 16;

	//Higher means more rolling resistance
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = 0.015f;

	FVector Velocity = FVector::ZeroVector;

	float YawVelocity;

	float RollVelocity;

	float PitchVelocity;

	FGoKartMove LastMove;

	UPROPERTY()
	float Throttle;

	float SteeringThrow;

	float PitchThrow;

	float RollThrow;

	FGoKartMove CreateMove(float DeltaTime);

	FVector GetAirResistance();

	float GetRotationDrag(float RotationVelocity);

	FVector GetRollingResistance();

	float GetFloatRollingResistance();

	void UpdateLocationFromVelocity(float DeltaTime);

	void ApplyYawRotation(float DeltaTime, float SteeringThrow);
	void ApplyPitchRotation(float DeltaTime, float PitchThrow);
	void ApplyRollRotation(float DeltaTime, float InRollThrow);
	
};
