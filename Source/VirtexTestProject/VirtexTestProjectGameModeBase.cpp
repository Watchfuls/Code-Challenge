////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VirtexTestProjectGameModeBase.cpp 
// 
// Copyright Gregory Hallam 2021
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "VirtexTestProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// THIS WAS NEVER USED BUT I THOUGHT I SHOULD INCLUDE IT ANYWAY

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpawnPlayerControllerCommon
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//This is essentially the same as usual, but from here I can specify the spawn position to check collisions. This is 100% not the right way to go about things and I'm sure there's much easier ways to specify multiple spawn locations, 
//but sometimes in coding you don't always have the optimal method available, to your knowledge, and within time constraints it's your prerogative to get something in that works, and is intended to be fixed or optimized at a later
//day, or by asking someone for assistance!

APlayerController* AVirtexTestProjectGameModeBase::SpawnPlayerControllerCommon(ENetRole InRemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation, TSubclassOf<APlayerController> InPlayerControllerClass)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save player controllers into a map
	SpawnInfo.bDeferConstruction = true;

	FVector NewSpawnLocation = SpawnLocation;
	bool	bSafeSpawnFound = false;
	bool	bConflictingSpawn = false;
	
	while (bSafeSpawnFound == false)
	{
		bConflictingSpawn = false;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* Controller = Cast<APlayerController>(Iterator->Get());
			if (Controller != nullptr)
			{
				if (Controller->GetSpawnLocation() == SpawnLocation)
				{
					bConflictingSpawn = true;
					NewSpawnLocation += FVector(0.0f, 100.0f, 0.0f);
					break;
				}
			}
		}
		if (bConflictingSpawn == false)
		{
			bSafeSpawnFound = true;
		}
	}
	
	APlayerController* NewPC = GetWorld()->SpawnActor<APlayerController>(InPlayerControllerClass, NewSpawnLocation, SpawnRotation, SpawnInfo);

	if (NewPC)
	{
		if (InRemoteRole == ROLE_SimulatedProxy)
		{
			// This is a local player because it has no authority/autonomous remote role
			NewPC->SetAsLocalPlayerController();
		}

		UGameplayStatics::FinishSpawningActor(NewPC, FTransform(SpawnRotation, SpawnLocation));
	}

	return NewPC;
}