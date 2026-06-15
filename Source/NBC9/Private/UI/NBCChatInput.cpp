// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NBCChatInput.h"
#include "Player/NBCPlayerController.h"
#include "Components/EditableTextBox.h"

//생성시 바인드
void UNBCChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChatBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		ChatBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

//소멸시 언바인드
void UNBCChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (ChatBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		ChatBox->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

//텍스트 입력시 채팅 메세지 입력 후 입력 텍스트 초기화
void UNBCChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ANBCPlayerController* OwningNBCPlayerController = Cast<ANBCPlayerController>(OwningPlayerController);
			if (IsValid(OwningNBCPlayerController) == true)
			{
				OwningNBCPlayerController->SetChatMessage(Text.ToString());
				ChatBox->SetText(FText());
			}
		}
	}
}