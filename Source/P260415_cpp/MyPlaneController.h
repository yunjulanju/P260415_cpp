// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlaneController.generated.h"

class UInputMappingContext;
UCLASS()
class P260415_CPP_API AMyPlaneController : public APlayerController
{
	GENERATED_BODY()

public:

	AMyPlaneController();

	virtual void OnPossess(APawn* aPawn) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMapping;
	
};
