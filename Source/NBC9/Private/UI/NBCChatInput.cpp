// NBCChatInput.cpp


#include "UI/NBCChatInput.h"
#include "Player/NBCPlayerController.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

//생성시 바인드
void UNBCChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ChatBox) == true && ChatBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		ChatBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

//소멸시 언바인드
void UNBCChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(ChatBox) == true && ChatBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		ChatBox->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

//채팅 메세지 기록용 UI에 추가
void UNBCChatInput::AddChatMessage(const FString& Message)
{
	TextList.Add(Message);

	while (TextList.Num() > MaxTextLineCount)
	{
		TextList.RemoveAt(0);
	}

	RefreshTextHistory();
}

//텍스트 입력시 채팅 메세지 입력 후 입력 텍스트 초기화
void UNBCChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		const FString InputString = Text.ToString();
		if (InputString.IsEmpty() == true)
		{
			return;
		}

		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ANBCPlayerController* OwningNBCPlayerController = Cast<ANBCPlayerController>(OwningPlayerController);
			if (IsValid(OwningNBCPlayerController) == true)
			{
				OwningNBCPlayerController->SetChatMessage(InputString);
				if (IsValid(ChatBox) == true)
				{
					ChatBox->SetText(FText());
				}
			}
		}
	}
}

//채팅 내역 업데이트
void UNBCChatInput::RefreshTextHistory()
{
	if (IsValid(TextHistory) == false)
	{
		return;
	}

	FString CombinedText;
	for (const FString& Line : TextList)
	{
		if (CombinedText.IsEmpty() == false)
		{
			CombinedText += LINE_TERMINATOR;
		}

		CombinedText += Line;
	}

	TextHistory->SetText(FText::FromString(CombinedText));

	if (IsValid(TextHistoryScrollBox) == true)
	{
		TextHistoryScrollBox->ScrollToEnd();
	}
}
