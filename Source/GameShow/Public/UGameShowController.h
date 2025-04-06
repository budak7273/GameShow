#pragma once

#include "FGServerControllerBase.h"
#include "UGameShowController.generated.h"

class UFGUserSetting;
struct FFGServerJoinDataResponse;
class UFGServerSubsystem;

UCLASS()
class GAMESHOW_API UGameShowController : public UFGServerControllerBase
{
	GENERATED_BODY()

public:

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGServerErrorResponse Handler_Sammi(const FString& JsonInput) const;
};