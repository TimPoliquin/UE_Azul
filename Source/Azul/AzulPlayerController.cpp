// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AzulPlayerController.h"

AAzulPlayerController::AAzulPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::GrabHand;
}
