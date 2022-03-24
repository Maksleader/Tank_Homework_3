// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "TankPawn.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpwanPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpwanPoint");
	ProjectileSpwanPoint->SetupAttachment(Mesh);
	


}

void ACannon::Fire()
{
	if (!bReadyToFire)
	{
		return;
	}

	if (CurrentAmmunition > 0)
	{
		switch (Type)
		{
		case Ecannon::FireProjectile:
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Puf-Puf")));
			break;
		case Ecannon::FireTrace:
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("Pif-Pif")));
			break;

		case Ecannon::AutomaticCannon:

			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Tra-Tra")));
			break;
		}
		bReadyToFire = false;
		/*if (Type == Ecannon::AutomaticCannon)
		{
			GetWorld()->GetTimerManager().SetTimer(ReLoadTImerHandle, FTimerDelegate::CreateUObject(this, &ACannon::IsReadyToFire), 1 / FireRate, true);
			
		}*/
		

			GetWorld()->GetTimerManager().SetTimer(ReLoadTImerHandle, FTimerDelegate::CreateUObject(this, &ACannon::IsReadyToFire), 1 / FireRate, true);
			
		
		
		GEngine->AddOnScreenDebugMessage(12, 10, FColor::Green, FString::Printf(TEXT("Ammunition= % f/ %f"), CurrentAmmunition, MaxAmmunition));
		
	}

	else if (CurrentAmmunition == 0)
	{
		Reload();
	}
}

void ACannon::FireSpecial()
{
	if (!bReadyToFire)
	{
		return;
	}
	if (CurrentSpecialAmmunition > 0)
	{

		switch (Type)
		{
		case Ecannon::FireProjectile:
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Puf")));
			break;
		case Ecannon::FireTrace:
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Pif")));
			break;
		}

		bReadyToFire = false;
		GetWorld()->GetTimerManager().SetTimer(ReLoadTImerHandle, FTimerDelegate::CreateUObject(this, &ACannon::IsReadyToFire), 1 / FireRate, false);

		CurrentSpecialAmmunition -=1;
		GEngine->AddOnScreenDebugMessage(13, 10, FColor::Green, FString::Printf(TEXT("Ammunition= % f/ %f"), CurrentSpecialAmmunition, MaxSpecialAmmunition));
		
	}
	

	else if (CurrentSpecialAmmunition == 0)
	{
		SpecialWeaponReload();
	}



}



void ACannon::IsReadyToFire()
{
	Fire();
	
	CurrentNumberOfShots--;
	
	bReadyToFire = true;
	if (CurrentNumberOfShots == 0)
	{
		CurrentAmmunition--;
		GetWorldTimerManager().ClearTimer(ReLoadTImerHandle);
		CurrentNumberOfShots=NumberOfShots;
		
	}

	
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACannon::Reload()
{
	CurrentAmmunition = MaxAmmunition;
	
	
	

}

void ACannon::SpecialWeaponReload()
{

	CurrentSpecialAmmunition = MaxSpecialAmmunition;

	

}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(1236, 10, FColor::Green, FString::Printf(TEXT("Time= %f "), GetWorld()->GetTimerManager().GetTimerElapsed(ReLoadTImerHandle)));
}

