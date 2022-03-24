#include "Tank_Pawn_PlayerController.h"
#include "DrawDebugHelpers.h"

void ATank_Pawn_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATank_Pawn_PlayerController::OnmoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATank_Pawn_PlayerController::RotateRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATank_Pawn_PlayerController::Fire);
	InputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATank_Pawn_PlayerController::FireSpecial);
	bShowMouseCursor = true;
	

}

void ATank_Pawn_PlayerController::OnmoveForward(float Scale)
{
	if(PlayerTank)
	PlayerTank->MoveForward(Scale);
}

void ATank_Pawn_PlayerController::RotateRight(float Scale)
{
	if (PlayerTank)
		PlayerTank->RotateRight(Scale);
}

void ATank_Pawn_PlayerController::Fire()
{
	if (PlayerTank)
		PlayerTank->Fire();
}

void ATank_Pawn_PlayerController::FireSpecial()
{
	if (PlayerTank)
		PlayerTank->FireSpecial();
}

void ATank_Pawn_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = CastChecked<ATankPawn>(GetPawn());
}

void ATank_Pawn_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FVector MouseDirection; 

	DeprojectMousePositionToWorld(MousePosition, MouseDirection);
	auto Z = FMath::Abs(PlayerTank->GetActorLocation().Z - MousePosition.Z);
	MousePosition =MousePosition- MouseDirection * Z / MouseDirection.Z;
	
}
