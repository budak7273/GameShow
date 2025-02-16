#include "GameShowPlayerDataComponent.h"
#include "Net/UnrealNetwork.h"

void UGameShowPlayerDataComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	DOREPLIFETIME(UGameShowPlayerDataComponent, EditMode);
	DOREPLIFETIME(UGameShowPlayerDataComponent, PlayerIdentifier);
}
