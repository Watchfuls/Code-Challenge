////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  VTPlayerController.h
//
// Copyright Gregory Hallam 2021
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VTDirections.h"
#include "VTPlayerController.generated.h"

DECLARE_DELEGATE_OneParam(FVTInputDelegate, EVTDirection);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AVTPlayerController
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS()
class VIRTEXTESTPROJECT_API AVTPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	AVTPlayerController();

	virtual void SetupInputComponent() override;

	UPROPERTY(Replicated, BlueprintReadWrite)
	FVector PawnLocation;

private:

	void OnActionPressed();

	void MoveOnLocalClient(EVTDirection Direction);

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveOnServer(FVector NewLoc);

	EVTDirection CurrentDirection;

	//I've left this is as it might be useful for debugging at a later point, and so could surrounded by #if WITH_EDITOR
	int32 ActionPressed;
};