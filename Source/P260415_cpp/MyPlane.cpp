// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlane.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"

#include "Rocket.h"

// Sets default values
AMyPlane::AMyPlane()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(40.0f, 44.2f, 12.4f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Assets/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));

	Left->SetupAttachment(Body);
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/Assets/SM_P38_Propeller.SM_P38_Propeller'"));

	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(37.1f, -21.4f, 0.5f));
	Right->SetRelativeLocation(FVector(37.1f, 21.4f, 0.5f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Body);
	Arrow->SetRelativeLocation(FVector(200.f, 0, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Body);
	SpringArm->SocketOffset = FVector(0, 0, 33.33f);
	SpringArm->TargetArmLength = 120.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT(
		"Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 5000;
	BoostValue = 0.5f;

}

// Called when the game starts or when spawned
void AMyPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Left->AddRelativeRotation(FRotator(0, 0, DeltaTime * 4800.0f));
	Right->AddRelativeRotation(FRotator(0, 0, DeltaTime * 4800.0f));
	AddMovementInput(GetActorForwardVector(), BoostValue);
}

// Called to bind functionality to input
void AMyPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	/*PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPlane::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPlane::Roll);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMyPlane::Fire);
	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Pressed, this, &AMyPlane::Boost);
	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Released, this, &AMyPlane::UnBoost);*/

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &AMyPlane::Rotate);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPlane::Fire);
		UIC->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPlane::Boost);
		UIC->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPlane::UnBoost);
	}

}

void AMyPlane::Rotate(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Rotate"));

	FVector2D Rot = Value.Get<FVector2D>();
	Rot = Rot * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 50.0f;

	AddActorLocalRotation(FRotator(Rot.Y,0,Rot.X));
}

void AMyPlane::Fire()
{
	GetWorld()->SpawnActor<ARocket>(RocketTemplate, Arrow->K2_GetComponentToWorld());
}

void AMyPlane::Boost()
{
	BoostValue = 1.0f;
}

void AMyPlane::UnBoost()
{
	BoostValue = 0.5;
}

