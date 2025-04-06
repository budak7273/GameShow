#include "AWebhookSubsystem.h"

#include "Runtime/Launch/Resources/Version.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "FGServerAPIManager.h"
#include "FGServerSubsystem.h"
#include "UGameShowController.h"
#include "Config/WebhookStruct.h"

void AWebhookSubsystem::SendJsonToWebhook(FString JsonString) {
	FWebhookStruct config = FWebhookStruct::GetActiveConfig(this);
				
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetURL(config.WebhookURL);
	HttpRequest->SetContentAsString(JsonString);

	UE_LOGFMT(LogGameShow, VeryVerbose, "JSON Payload: {JsonString}", JsonString);

	HttpRequest->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			UE_LOG(LogGameShow, Log, TEXT("Webhook response: %s"), *Response->GetContentAsString());
		}
		else
		{
			UE_LOG(LogGameShow, Error, TEXT("Failed to send data to webhook"));
		}
	});

	HttpRequest->ProcessRequest();
};

void AWebhookSubsystem::InitializeFunctions() {
	const auto World = this->GetWorld();
	this->Controller = NewObject<UGameShowController>();

	if (World == nullptr)
		return;

	UE_LOGFMT(LogGame, Display, "World found");
	
	const auto GameInstance = World->GetGameInstance();
	if (GameInstance == nullptr)
		return;

	UE_LOGFMT(LogGame, Display, "GameInstance found");
	
	const auto Subsystem = GameInstance->GetSubsystem<UFGServerSubsystem>();
	if (Subsystem == nullptr)
		return;

	UE_LOGFMT(LogGame, Display, "UFGServerSubsystem found");
	
	const auto ServerAPIManager = Subsystem->GetServerAPIManager();
	if (ServerAPIManager == nullptr)
		return;

	ServerAPIManager->RegisterRequestHandler(this->Controller);
	UE_LOGFMT(LogGame, Display, "Controller registration called");

}