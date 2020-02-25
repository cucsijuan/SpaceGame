// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBaseWeaponComponent.h"
#include "SGBaseWeapon.h"

USGBaseWeaponComponent::USGBaseWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USGBaseWeaponComponent::InitWeaponComponent()
{
	OwningWeapon = Cast<ASGBaseWeapon>(GetOwner());
}

void USGBaseWeaponComponent::CustomTick(float DeltaTime)
{

}

void USGBaseWeaponComponent::BeginPlay()
{
	Super::BeginPlay();	
}
