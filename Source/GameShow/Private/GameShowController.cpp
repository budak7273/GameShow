#include "GameShowController.h"

#include "FGDSSharedTypes.h"
#include "Logging/StructuredLog.h"

FFGServerErrorResponse UGameShowController::Handler_Sammi(const FString& JsonInput) const
{
	UE_LOGFMT(LogTemp, Log, "SammiHandler called with input: {0}", JsonInput);

	return FFGServerErrorResponse::Ok();
}
