#pragma once

#include "GameShow.h"
#include "Runtime/Launch/Resources/Version.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Subsystem/ModSubsystem.h"
#include "Config/WebhookStruct.h"

#include "AWebhookSubsystem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAMESHOW_API AWebhookSubsystem : public AModSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SendJsonToWebhook(UObject* WorldContext, FString JsonString)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		FWebhookStruct config = FWebhookStruct::GetActiveConfig(WorldContext);
		
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
				
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->SetVerb("POST");
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		HttpRequest->SetURL(config.WebhookURL);
		HttpRequest->SetContentAsString(JsonString);

		HttpRequest->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful)
			{
				UE_LOG(LogTemp, Log, TEXT("Webhook response: %s"), *Response->GetContentAsString());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to send data to webhook"));
			}
		});

		HttpRequest->ProcessRequest();
	};
};
