// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBaseWeapon.h"
#include "SGBaseWeaponComponent.h"

// Sets default values
ASGBaseWeapon::ASGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASGBaseWeapon::RegisterComponent(USGBaseWeaponComponent* WeaponComponent)
{
	WeaponComponents.Add(WeaponComponent);
}

void ASGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASGBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

