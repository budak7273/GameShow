#pragma once

#include "GameShow.h"
#include "Subsystem/ModSubsystem.h"
#include "FactoryDedicatedServer/Public/FGServerSubsystem.h"
#include "FactoryDedicatedServer/Public/Networking/FGServerAPIManager.h"
#include "AWebhookSubsystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAMESHOW_API AWebhookSubsystem : public AModSubsystem
{
	GENERATED_BODY()
public:

	virtual void PostInitialize();
	
	UFUNCTION(BlueprintCallable)
	void SendJsonToWebhook(FString JsonString);

	UFUNCTION(BlueprintCallable)
	void SammiHandler(FString JsonInput);

private:	
	void RegisterRoute(UFGServerAPIManager *Manager, const char *Name);
};
