// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlane.h"
#include "MyPlaneController.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyPlane::StaticClass();
	PlayerControllerClass = AMyPlaneController::StaticClass();
}
