// NBCPlayerState.cpp


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

//플레이어 시도 횟수
FString ANBCPlayerState::GetPlayerInfo()
{
	FString PlayerInfoString = FString::Printf(TEXT("%s < %d / %d >"), *PlayerName, CurrentTryCount, MaxTryCount);
	return PlayerInfoString;
}