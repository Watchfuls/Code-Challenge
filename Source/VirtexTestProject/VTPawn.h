////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  VTPawn.h
//
// Copyright Gregory Hallam 2021
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VTDirections.h"
#include "VTPawn.generated.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AVTPawn
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS()
class VIRTEXTESTPROJECT_API AVTPawn : public APawn
{
	GENERATED_BODY()
	
public:
	AVTPawn();

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	EVTDirection ActionPressed;
	
	//How far the pawn should move when a direction is pressed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MovementDistance;
	
	virtual void Tick(float DeltaTime) override;
	
	FVector MovePawn(EVTDirection NewDir, FVector NewLoc = FVector::ZeroVector);

protected:

	virtual void BeginPlay() override;
};
