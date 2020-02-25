// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGBaseWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEGAME_API USGBaseWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGBaseWeaponComponent();

	virtual void InitWeaponComponent();

	virtual void CustomTick(float DeltaTime);

protected:
	class ASGBaseWeapon* OwningWeapon;

	virtual void BeginPlay() override;
		
};
