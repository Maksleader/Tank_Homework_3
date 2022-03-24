// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include <Tank_Homework_3/Cannon.h>
#include "TankPawn.generated.h"




UCLASS(BluePrintable)
class TANK_HOMEWORK_3_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent *BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* TankBody;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* TankTurret;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* ArmComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
	float MoveSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
	float RotationSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
	float ForwardInterpolationKey = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
	float RotationInterpolationKey = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Speed")
	float TurretRotationInterpolationKey = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	TSubclassOf<ACannon>CannonClass;

	ACannon* Cannon;

	FTimerHandle TimerHandle;

	UFUNCTION()
	void MoveForward(float Scale);
	void RotateRight(float Scale);
	void Fire();
	void FireSpecial();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetupCannon();
	                                                                                                     
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveTank(float DeltaTime);
	void RotateTank(float DeltaTime);
	void CanonRotation(float DelataTime);

	float ForwardScaleValue = 0;
	float RightScaleValue = 0;
	float CurrentRightScaleValue = 0;
	float CurrentForwardScaleValue = 0;

	UPROPERTY()
	class ATank_Pawn_PlayerController* TankPlayerController;

};
