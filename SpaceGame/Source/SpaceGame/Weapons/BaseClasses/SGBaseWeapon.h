// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGBaseWeapon.generated.h"

UCLASS()
class SPACEGAME_API ASGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASGBaseWeapon();

	virtual void RegisterComponent(class USGBaseWeaponComponent* WeaponComponent);

protected:
	TArray<class USGBaseWeaponComponent*> WeaponComponents;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
