// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NBCPlayerState.h"
#include "Net/UnrealNetwork.h"


ANBCPlayerState::ANBCPlayerState()
	: PlayerName(TEXT("Anonymous"))
	, CurrentTryCount(0)
	, MaxTryCount(3)
{
	bReplicates = true;
}

void ANBCPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANBCPlayerState, PlayerName);
	DOREPLIFETIME(ANBCPlayerState, CurrentTryCount);
	DOREPLIFETIME(ANBCPlayerState, MaxTryCount);
} 

FString ANBCPlayerState::GetPlayerInfo()
{
	FString PlayerInfoString = FString::Printf(TEXT("%s < %d / %d >"), *PlayerName, CurrentTryCount, MaxTryCount);
	return PlayerInfoString;
}