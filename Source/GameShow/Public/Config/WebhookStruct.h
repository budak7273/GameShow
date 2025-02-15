#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigManager.h"
#include "Engine/Engine.h"
#include "WebhookStruct.generated.h"

/* Struct generated from Mod Configuration Asset '/GameShow/Config/Webhook' */
USTRUCT(BlueprintType)
struct FWebhookStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    FString WebhookURL{};

    /* Retrieves active configuration value and returns object of this struct containing it */
    static FWebhookStruct GetActiveConfig(UObject* WorldContext) {
        FWebhookStruct ConfigStruct{};
        FConfigId ConfigId{"GameShow", ""};
        if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull)) {
            UConfigManager* ConfigManager = World->GetGameInstance()->GetSubsystem<UConfigManager>();
            ConfigManager->FillConfigurationStruct(ConfigId, FDynamicStructInfo{FWebhookStruct::StaticStruct(), &ConfigStruct});
        }
        return ConfigStruct;
    }
};

