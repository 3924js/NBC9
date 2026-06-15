// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NBCPawn.h"
#include "NBC9.h"

// Sets default values
ANBCPawn::ANBCPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANBCPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = NBCUtilLibrary::GetRole(this);
	FString CombinedString = FString::Printf(TEXT("New Pawn BeginPlay() %s [%s]"), *NBCUtilLibrary::GetNetMode(this), *NetRoleString);
	NBCUtilLibrary::PrintString(this, CombinedString, 10.f);

}

void ANBCPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = NBCUtilLibrary::GetRole(this);
	FString CombinedString = FString::Printf(TEXT("New Pawn PossessedBy() %s [%s]"), *NBCUtilLibrary::GetNetMode(this), *NetRoleString);
	NBCUtilLibrary::PrintString(this, CombinedString, 10.f);
}