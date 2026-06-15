// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NBCPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NBC9_API ANBCPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ANBCPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetPlayerInfo();

	//플레이어 명
	UPROPERTY(Replicated)
	FString PlayerName;
	//현재 시도 횟수
	UPROPERTY(Replicated)
	int32 CurrentTryCount;
	//최대 시도 횟수
	UPROPERTY(Replicated)
	int32 MaxTryCount;


};
