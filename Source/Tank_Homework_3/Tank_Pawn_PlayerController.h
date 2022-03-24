// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include <Tank_Homework_3/TankPawn.h>
#include "Tank_Pawn_PlayerController.generated.h"


/**
 * 
 */
UCLASS()
class TANK_HOMEWORK_3_API ATank_Pawn_PlayerController : public APlayerController
{
	GENERATED_BODY()

	

protected:

	void OnmoveForward(float Scale);
	void RotateRight(float Scale);
	void Fire();
	void FireSpecial();
	virtual void BeginPlay() override;
	
public:
	
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePosition() { return MousePosition; };
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	ATankPawn* PlayerTank;
	FVector MousePosition;

};