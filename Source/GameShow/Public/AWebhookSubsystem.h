#pragma once


#include "GameShow.h"
#include "UGameShowController.h"
#include "Subsystem/ModSubsystem.h"
#include "FactoryDedicatedServer/Public/Networking/FGServerAPIManager.h"
#include "AWebhookSubsystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAMESHOW_API AWebhookSubsystem : public AModSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void InitializeFunctions();
	
	UFUNCTION(BlueprintCallable)
	void SendJsonToWebhook(FString JsonString);

	UPROPERTY()
	UGameShowController *Controller;
};

