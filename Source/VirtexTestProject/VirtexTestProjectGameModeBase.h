////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VirtexTestProjectGameModeBase.h 
// 
// Copyright Gregory Hallam 2021
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <GameFramework/PlayerController.h>
#include "VirtexTestProjectGameModeBase.generated.h"

UCLASS()
class VIRTEXTESTPROJECT_API AVirtexTestProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:

	virtual APlayerController* SpawnPlayerControllerCommon(ENetRole InRemoteRole, FVector const& SpawnLocations, FRotator const& SpawnRotation, TSubclassOf<APlayerController> InPlayerControllerClass) final;
	
};
