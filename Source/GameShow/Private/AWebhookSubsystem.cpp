#include "AWebhookSubsystem.h"

#include "Runtime/Launch/Resources/Version.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "FGServerAPIManager.h"
#include "FGServerSubsystem.h"
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

void AWebhookSubsystem::SammiHandler(FString JsonInput)
{
	UE_LOG(LogTemp, Log, TEXT("SammiHandler called with input: %s"), *JsonInput);
}

void AWebhookSubsystem::RegisterRoute(UFGServerAPIManager *Manager, const char *Name) {
	auto Handler = FFGRequestHandlerRegistration();
	Handler.HandlerObject = this;
	Handler.HandlerFunction = this->FindFunction(Name);
	Handler.FunctionName = FName(Name);
	Handler.PrivilegeLevel = EPrivilegeLevel::None;
	Manager->mRegisteredHandlers.Add(FString(Name), Handler);
}

void AWebhookSubsystem::InitializeFunctions() {
	const auto World = this->GetWorld();
	if (World == nullptr)
		return;

	const auto GameInstance = World->GetGameInstance();
	if (GameInstance == nullptr)
		return;

	const auto Subsystem = GameInstance->GetSubsystem<UFGServerSubsystem>();
	if (Subsystem == nullptr)
		return;

	const auto ServerAPIManager = Subsystem->GetServerAPIManager();
	if (ServerAPIManager == nullptr)
		return;

	this->RegisterRoute(ServerAPIManager, "SammiHandler");
}