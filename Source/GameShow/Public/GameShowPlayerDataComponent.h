#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameShowPlayerDataComponent.generated.h"

// Blueprint implemented data component
UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESHOW_API UGameShowPlayerDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool EditMode;

	UPROPERTY(BlueprintReadWrite, Replicated)
	FString PlayerIdentifier;

protected:
	// UFUNCTION()
	// void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;
};
