////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VTDirections.h
// 
// Copyright Gregory Hallam 2021
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coreminimal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EVTDirections
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UENUM()
enum class EVTDirection : uint8
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//In case of printing
//FString GetEnumAsString(EVTDirection EnumValue);