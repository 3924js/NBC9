//NBCGameModeBase.cpp


#include "Game/NBCGameModeBase.h"
#include "Game/NBCGameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Player/NBCPawn.h"
#include "Player/NBCPlayerState.h"
#include "Player/NBCPlayerController.h"
#include "EngineUtils.h"

void ANBCGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//랜덤 목표 숫자 생성
	TargetNumber = CreateTargetNumber();
	UE_LOG(LogTemp, Warning, TEXT("TargetNum - %s"), *TargetNumber);
}

//입력 메세지 출력
void ANBCGameModeBase::PrintMessage(ANBCPlayerController* Player, const FString& InputNumber)
{
	FString ChatMessageString = InputNumber;
	int Index = InputNumber.Len() - 3;
	FString GuessNumberString = InputNumber.RightChop(Index);
	if (IsInputValid(GuessNumberString) == true)
	{
		FString CheckResultString = CheckResult(GuessNumberString);
		IncreaseTryCount(Player);
		for (TActorIterator<ANBCPlayerController> Iterator(GetWorld()); Iterator; ++Iterator)
		{
			ANBCPlayerController* PC = *Iterator;
			if (IsValid(PC) == true)
			{
				FString CombinedMessageString = InputNumber + TEXT(" -> ") + CheckResultString;
				PC->ClientRPCPrintMessage(CombinedMessageString);

				//스트라이크 갯수로 게임오버 확인
				int32 StrikeCount = FCString::Atoi(*CheckResultString.Left(1));
				CheckGameOver(Player, StrikeCount);
			}
		}
	}
	else
	{
		for (TActorIterator<ANBCPlayerController> Iterator(GetWorld()); Iterator; ++Iterator)
		{
			ANBCPlayerController* PC = *Iterator;
			if (IsValid(PC) == true)
			{
				PC->ClientRPCPrintMessage(InputNumber);
			}
		}
	}
}

//플레이어 시도 횟수 증가
void ANBCGameModeBase::IncreaseTryCount(ANBCPlayerController* Player)
{
	ANBCPlayerState* PS = Player->GetPlayerState<ANBCPlayerState>();
	if (IsValid(PS) == true)
	{
		PS->CurrentTryCount++;
	}
}

//플레이어 접속 관리
void ANBCGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	//플레이어 목록에 추가
	ANBCPlayerController* PC = Cast<ANBCPlayerController>(NewPlayer);
	if (IsValid(PC))
	{
		PC->NotificationText = FText::FromString(TEXT("Connected to the game server."));

		Controllers.Add(PC);

		ANBCPlayerState* PS = PC->GetPlayerState<ANBCPlayerState>();
		if (IsValid(PS))
		{
			PS->PlayerName = TEXT("Player") + FString::FromInt(Controllers.Num());

			ANBCGameStateBase* GS = GetGameState<ANBCGameStateBase>();

			if (IsValid(GS))
			{
				GS->MulticastRPCBroadcastLogin(PS->PlayerName);
			}
		}
	}
}

//게임용 랜덤 숫자 문자열 생성
FString ANBCGameModeBase::CreateTargetNumber()
{
	//숫자 배열 생성
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; ++i)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	Numbers = Numbers.FilterByPredicate([](int32 Num) { return Num > 0; });

	//랜덤 3개 숫자 골라서 문자열에 삽입
	FString Result;
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}

	return Result;
}

//입력 검사
bool ANBCGameModeBase::IsInputValid(const FString& InNumberString)
{
	bool bCanPlay = false;

	do {
		
		//길이 3 아니면 실패
		if (InNumberString.Len() != 3)
		{
			break;
		}

		//숫자 아니거나 0이면 실패
		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (bIsUnique == false)
		{
			break;
		}

		//해당 안되면 정상 입력
		bCanPlay = true;

	} while (false);

	return bCanPlay;
}

//결과 확인
FString ANBCGameModeBase::CheckResult(const FString& InputNumber)
{
	//스트라이크, 볼 갯수 확인
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		//위치랑 숫자까지 같으면 스트라이크
		if (TargetNumber[i] == InputNumber[i])
		{
			StrikeCount++;
		}
		//같은숫자에 자리만 다르면 볼
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InputNumber[i]);
			if (TargetNumber.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	//결과 문자로 반환
	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}


void ANBCGameModeBase::ResetGame()
{
	TargetNumber = CreateTargetNumber();

	for (const auto& PC : Controllers)
	{
		ANBCPlayerState* PS = PC->GetPlayerState<ANBCPlayerState>();
		if (IsValid(PS) == true)
		{
			PS->CurrentTryCount = 0;
		}
	}
}

void ANBCGameModeBase::CheckGameOver(ANBCPlayerController* Player, int StrikeCount)
{
	if (StrikeCount >= 3)
	{
		ANBCPlayerState* PS = Player->GetPlayerState<ANBCPlayerState>();
		for (const auto& PC : Controllers)
		{
			if (IsValid(PS) == true)
			{
				FString CombinedMessage = PS->PlayerName + TEXT(" has won the game!");
				PC->NotificationText = FText::FromString(CombinedMessage);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& PC : Controllers)
		{
			ANBCPlayerState* PS = PC->GetPlayerState<ANBCPlayerState>();
			if (IsValid(PS) == true)
			{
				if (PS->CurrentTryCount < PS->MaxTryCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}

		if (true == bIsDraw)
		{
			for (const auto& PC : Controllers)
			{
				PC->NotificationText = FText::FromString(TEXT("Draw!"));

				ResetGame();
			}
		}
	}
}