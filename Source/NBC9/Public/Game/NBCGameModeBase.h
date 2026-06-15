//NBCGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/NBCPlayerController.h"
#include "NBCGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NBC9_API ANBCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void PrintMessage(ANBCPlayerController* Player, const FString& InputMessage);

	virtual void OnPostLogin(AController* NewPlayer) override;

	FString CreateTargetNumber();

	bool IsInputValid(const FString& InputNumber);

	FString CheckResult(const FString& InputNumber);

	void IncreaseTryCount(ANBCPlayerController* InChattingPlayerController);

	void ResetGame();

	void CheckGameOver(ANBCPlayerController* Player, int StrikeCount);
private:
	//목표숫자
	FString TargetNumber;
	//참여 컨트롤러 목록
	TArray<TObjectPtr<ANBCPlayerController>> Controllers;
};
