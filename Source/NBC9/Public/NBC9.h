// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//프로젝트 유틸 함수
class NBCUtilLibrary
{
public:
	//간단 메세지 출력 함수
	static void PrintString(const AActor* MyActor, const FString& InString, float InTimeToDisplay = 1.f, FColor InColor = FColor::Cyan)
	{
		if (IsValid(GEngine) == true && IsValid(MyActor) == true)
		{
			if (MyActor->GetNetMode() == NM_Client || MyActor->GetNetMode() == NM_ListenServer)
			{
				GEngine->AddOnScreenDebugMessage(-1, InTimeToDisplay, InColor, InString);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *InString);
			}
		}
	}
	
	//넷모드 확인 함수
	static FString GetNetMode(const AActor* MyActor)
	{
		FString NetModeString = TEXT("None");

		if (IsValid(MyActor) == true)
		{
			ENetMode NetMode = MyActor->GetNetMode();
			if (NetMode == NM_Client)
			{
				NetModeString = TEXT("Client");
			}
			else
			{
				if (NetMode == NM_Standalone)
				{
					NetModeString = TEXT("StandAlone");
				}
				else
				{
					NetModeString = TEXT("Server");
				}
			}
		}
		return NetModeString;
	}

	//넷 롤 확인
	static FString GetRole(const AActor* InActor)
	{
		FString RoleString = TEXT("None");

		if (IsValid(InActor) == true)
		{
			FString LocalRoleString = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), InActor->GetLocalRole());
			FString RemoteRoleString = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), InActor->GetRemoteRole());

			RoleString = FString::Printf(TEXT("%s / %s"), *LocalRoleString, *RemoteRoleString);
		}

		return RoleString;
	}
};
