#pragma once

#include "GameShow.h"
#include "Subsystem/ModSubsystem.h"
#include "AWebhookSubsystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAMESHOW_API AWebhookSubsystem : public AModSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SendJsonToWebhook(FString JsonString);

};
