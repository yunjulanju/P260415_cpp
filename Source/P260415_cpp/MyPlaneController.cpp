// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlaneController.h"
#include <EnhancedInputSubsystems.h>
#include "Kismet/GameplayStatics.h"

AMyPlaneController::AMyPlaneController()
{
      
}

void AMyPlaneController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);
    UE_LOG(LogTemp, Warning, TEXT("OnPossess "));

    if (IsLocalPlayerController())
    {
        UE_LOG(LogTemp, Warning, TEXT("LocalController "));

        if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
        {
            UE_LOG(LogTemp, Warning, TEXT("LocalPlayer "));

            if (UEnhancedInputLocalPlayerSubsystem* InputSystem =
                LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                UE_LOG(LogTemp, Warning, TEXT("InputSystem "));

                if (InputMapping)
                {
                    UE_LOG(LogTemp, Warning, TEXT("IMC "));
                    InputSystem->AddMappingContext(InputMapping, 1);
                }
            }
        }
    }
}
