// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NBCChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class NBC9_API UNBCChatInput : public UUserWidget
{
	GENERATED_BODY()
public:
	//컴포넌트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ChatBox;


	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	//메세지 입력
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

};
