// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h" 	
#include "Engine/EngineTypes.h"
#include "Cannon.generated.h"

UENUM(BlueprintType)
enum class Ecannon :uint8
{
	FireProjectile=0 UMETA(DisplayName="Use Projectile"),
	FireTrace=1 UMETA(DisplayName="Use Trace"),
	AutomaticCannon=2 UMETA(DisplayName="Use Automatic Cannon")
};

UCLASS()
class TANK_HOMEWORK_3_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpwanPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float FireDamege = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float MaxAmmunition=10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float CurrentAmmunition=10;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float MaxSpecialAmmunition=2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float CurrentSpecialAmmunition=2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	Ecannon Type = Ecannon::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float NumberOfShots=1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float CurrentNumberOfShots = 1;

	

	
	
	bool bReadyToFire = true;

	void Fire();
	void FireSpecial();
    void IsReadyToFire();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;  
	void Reload();
	void SpecialWeaponReload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	
	float TempNumberOfShots = NumberOfShots;
	FTimerHandle ReLoadTImerHandle;
};
