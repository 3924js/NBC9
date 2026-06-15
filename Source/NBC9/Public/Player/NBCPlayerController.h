// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NBCPlayerController.generated.h"

class UNBCChatInput;

UCLASS()
class NBC9_API ANBCPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	//
	void SetChatMessage(const FString& InputMessage);

	void PrintMessage(const FString& InputMessage);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintMessage(const FString& InputMessage);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintMessage(const FString& InputMessage);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	//채팅 위젯
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNBCChatInput> ChatInputClass;

	UPROPERTY()
	TObjectPtr<UNBCChatInput> ChatInputInstance;

	//채팅 메세지
	FString ChatMessage;

	//알림 위젯
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationWidgetInstance;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;
	
};
