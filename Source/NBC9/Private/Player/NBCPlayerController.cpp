// NBCPlayerController.cpp


#include "Player/NBCPlayerController.h"
#include "Player/NBCPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Game/NBCGameModeBase.h"
#include "UI/NBCChatInput.h"
#include "EngineUtils.h"
#include "Net/UnrealNetwork.h"
#include "NBC9.h"


void ANBCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//로컬 컨트롤러 아니면 무시
	if (IsLocalController() == false)
	{
		return;
	}



	//UI입력 설정
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	//채팅 UI 생성
	if (IsValid(ChatInputClass) == true)
	{
		ChatInputInstance = CreateWidget<UNBCChatInput>(this, ChatInputClass);
		if (IsValid(ChatInputInstance) == true)
		{
			ChatInputInstance->AddToViewport();
		}
	}

	//알림 UI 생성
	if (IsValid(NotificationWidgetClass) == true)
	{
		NotificationWidgetInstance = CreateWidget<UUserWidget>(this, NotificationWidgetClass);
		if (IsValid(NotificationWidgetInstance) == true)
		{
			NotificationWidgetInstance->AddToViewport();
		}
	}
}

void ANBCPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANBCPlayerController, NotificationText);
}

//채팅 메세지 설정
void ANBCPlayerController::SetChatMessage(const FString& InputMessage)
{
	ChatMessage = InputMessage;

	if (IsLocalController())
	{
		ANBCPlayerState* PS = GetPlayerState<ANBCPlayerState>();
		if (IsValid(PS) == true)
		{
			FString CombinedMessageString = PS->GetPlayerInfo() + TEXT(" : ") + InputMessage;

			ServerRPCPrintMessage(CombinedMessageString);
		}
	}
}

//체팅 메세지 출력
void ANBCPlayerController::PrintMessage(const FString& InputMessage)
{
	if (IsLocalController() == true && IsValid(ChatInputInstance) == true)
	{
		ChatInputInstance->AddChatMessage(InputMessage);
		return;
	}

	NBCUtilLibrary::PrintString(this, InputMessage, 10.f);
}

//클라이언트 채팅 RPC
void ANBCPlayerController::ClientRPCPrintMessage_Implementation(const FString& InputMessage)
{
	PrintMessage(InputMessage);
}

//서버 채팅 RPC, 각 클라이언트의 메세치 출력 호출
void ANBCPlayerController::ServerRPCPrintMessage_Implementation(const FString& InputMessage)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ANBCGameModeBase* NBCGM = Cast<ANBCGameModeBase>(GM);
		if (IsValid(NBCGM) == true)
		{
			NBCGM->PrintMessage(this, InputMessage);
		}
	}
}
