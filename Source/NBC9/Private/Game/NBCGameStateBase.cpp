// NBCGameStateBase.cpp

#include "Game/NBCGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/NBCPlayerController.h"

void ANBCGameStateBase::MulticastRPCBroadcastLogin_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			ANBCPlayerController* NBCPC = Cast<ANBCPlayerController>(PC);
			if (IsValid(NBCPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				NBCPC->PrintMessage(NotificationString);
			}
		}
	}
}