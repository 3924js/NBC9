// NBCChatInput.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NBCChatInput.generated.h"

class UEditableTextBox;
class UScrollBox;
class UTextBlock;

UCLASS()
class NBC9_API UNBCChatInput : public UUserWidget
{
	GENERATED_BODY()
public:
	//컴포넌트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ChatBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> TextHistoryScrollBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextHistory;

	TArray<FString> TextList;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void AddChatMessage(const FString& Message);

protected:
	//메세지 입력
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

private:
	void RefreshTextHistory();

	static constexpr int32 MaxTextLineCount = 20;

};
