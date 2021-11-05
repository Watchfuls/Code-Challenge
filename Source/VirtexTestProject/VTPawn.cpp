////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  VTPawn.cpp
//
// Copyright Gregory Hallam 2021
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "VTPawn.h"
#include "Net/UnrealNetwork.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Log
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DECLARE_LOG_CATEGORY_CLASS(VTPawnLog, All, All);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AVTPawn::AVTPawn()
{
	MovementDistance = 10.0f;
	ActionPressed = EVTDirection::NONE;

	PrimaryActorTick.bCanEverTick = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Begin Play
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AVTPawn::BeginPlay()
{
	// This function is no longer needed and can be removed.
	Super::BeginPlay();	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tick
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AVTPawn::Tick(float DeltaTime)
{
	// This function is no longer needed and can be removed.
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MovePawn
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FVector AVTPawn::MovePawn(EVTDirection NewDir, FVector NewLoc)
{
	check(NewDir == EVTDirection::NONE || NewLoc == FVector::ZeroVector);

	FVector PawnLocation = GetActorLocation();

	if (NewDir != EVTDirection::NONE)
	{
		if (NewDir == EVTDirection::UP)
		{
			PawnLocation += FVector(0.0f, 0.0f, MovementDistance);
		}
		else if (NewDir == EVTDirection::DOWN)
		{
			PawnLocation += FVector(0.0f, 0.0f, -MovementDistance);
		}
		else if (NewDir == EVTDirection::LEFT)
		{
			PawnLocation += FVector(0.0f, -MovementDistance, 0.0f);
		}
		else if (NewDir == EVTDirection::RIGHT)
		{
			PawnLocation += FVector(0.0f, MovementDistance, 0.0f);
		}
		SetActorLocation(PawnLocation);

		//This is for the functionality of keeping a record of the last pressed direction for the sake VP_VTPawn BP event graph. If I wanted to employ a nice log it would be better to put this in the player controller
		//though going for the simplest method it would still only log it on the local clients and not the server without some kind of replication, as I removed that information.

		ActionPressed = NewDir;
	}
	else
	{
		if (NewLoc != FVector::ZeroVector)
		{
			PawnLocation == NewLoc;
			SetActorLocation(NewLoc);

		}
	}

	//check(PawnLocation == GetActorLocation());
	if (GetNetMode() == NM_DedicatedServer)
	{
		UE_LOG(VTPawnLog, Log, TEXT("MovedPlayer %d on server to %s"), GetController()->GetUniqueID(), *GetActorLocation().ToCompactString());
	}
	// It might be more efficient to not return the actual location and just retrun 000 when we are on server, because we don't need the location value to be retuned.

	return PawnLocation;
};