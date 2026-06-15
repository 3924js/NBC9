// NBCGameStateBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NBCGameStateBase.generated.h"

UCLASS()
class NBC9_API ANBCGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLogin(const FString& InNameString = FString(TEXT("Anonymous")));

};
