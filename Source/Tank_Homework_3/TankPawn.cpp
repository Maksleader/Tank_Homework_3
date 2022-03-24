// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Tank_Pawn_PlayerController.h"
#include "Tank_Homework_3.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>


// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	TankBody = CreateDefaultSubobject<UStaticMeshComponent>("TankBody");
	TankBody->SetupAttachment(RootComponent);

	TankTurret = CreateDefaultSubobject<UStaticMeshComponent>("TankTurret");
	TankTurret->SetupAttachment(TankBody);

	ArmComponent = CreateDefaultSubobject<USpringArmComponent>("ArmComponent");
	ArmComponent->SetupAttachment(RootComponent);
	ArmComponent->bDoCollisionTest = false;
	ArmComponent->bInheritPitch = false;
	ArmComponent->bInheritRoll = false;
	ArmComponent->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(ArmComponent);


}

void ATankPawn::MoveForward(float Scale)
{
	ForwardScaleValue = Scale;
}

void ATankPawn::RotateRight(float Scale)
{
	RightScaleValue = Scale;
}

void ATankPawn::Fire()
{
	if (Cannon)
	Cannon->Fire();


}
	


void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
		
	}
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<ATank_Pawn_PlayerController>(GetController());
	SetupCannon();
}

void ATankPawn::SetupCannon()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}

	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveTank(DeltaTime);
	RotateTank(DeltaTime);
	CanonRotation(DeltaTime);
	

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::MoveTank(float DeltaTime)
{
	CurrentForwardScaleValue = FMath::Lerp(CurrentForwardScaleValue, ForwardScaleValue, ForwardInterpolationKey);
	FVector currentlocatin = GetActorLocation();
	FVector forwardvector = GetActorForwardVector();
	FVector movePosition = currentlocatin + forwardvector * MoveSpeed * CurrentForwardScaleValue * DeltaTime;

	SetActorLocation(movePosition, false);
}

void ATankPawn::RotateTank(float DeltaTime)
{
	CurrentRightScaleValue = FMath::Lerp(CurrentRightScaleValue, RightScaleValue, RotationInterpolationKey);
	//UE_LOG(LogTank, Warning, TEXT("CurrentRightScaleValue=%f RightScalevalue=%f"), CurrentRightScaleValue, RightScaleValue);

	float yawrotation = RotationSpeed * CurrentRightScaleValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawrotation = currentRotation.Yaw + yawrotation;

	FRotator newRotation = FRotator(0, yawrotation, 0);
	SetActorRotation(newRotation);
}

void ATankPawn::CanonRotation(float DelataTime)
{
	if (!TankPlayerController)
	{
		return;
	}
	auto OldRotation = TankTurret->GetComponentRotation();

	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(TankTurret->GetComponentLocation(),TankPlayerController->GetMousePosition());
	
	TurretRotation.Roll = OldRotation.Roll;
	TurretRotation.Pitch=OldRotation.Pitch;

	
	TankTurret->SetWorldRotation(FMath::Lerp(OldRotation,TurretRotation, TurretRotationInterpolationKey));
		
}

