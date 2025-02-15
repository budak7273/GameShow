#include "AWebhookSubsystem.h"

#include "Runtime/Launch/Resources/Version.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Config/WebhookStruct.h"

void AWebhookSubsystem::SendJsonToWebhook(FString JsonString) {
	FWebhookStruct config = FWebhookStruct::GetActiveConfig(this);
				
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetURL(config.WebhookURL);
	HttpRequest->SetContentAsString(JsonString);

	//UE_LOGFMT(LogGameShow, Log, "JSON Payload: {JsonString}", JsonString);

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
