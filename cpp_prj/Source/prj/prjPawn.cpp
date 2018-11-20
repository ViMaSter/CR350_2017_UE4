// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "prjPawn.h"
#include "prjProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

#include "WebSocketBlueprintLibrary.h"

const FName AprjPawn::MoveForwardBinding("MoveForward");
const FName AprjPawn::MoveRightBinding("MoveRight");
const FName AprjPawn::FireForwardBinding("FireForward");
const FName AprjPawn::FireRightBinding("FireRight");

AprjPawn::AprjPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	// Websocket
	Hostname = "127.0.0.1";
	Port = 7000;
	UpdateFrequencyInSeconds = 1.0f;
}

void AprjPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}

void AprjPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	FireShot(FireDirection);
}

void AprjPawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<AprjProjectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AprjPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void AprjPawn::ShotTimerExpired()
{
	bCanFire = true;
}

void AprjPawn::BeginPlay()
{
	Super::BeginPlay();
	SetupWebsocket();
}

void AprjPawn::SetupWebsocket()
{
	FString URI = FString::Printf(TEXT("ws://%s:%d/"), *Hostname, Port);
	UE_LOG(LogWindows, Warning, TEXT("Attempting to connect to '%s'"), *URI);
	websocketContext = TWeakObjectPtr<UWebSocketBase>(UWebSocketBlueprintLibrary::Connect(URI));

	FScriptDelegate OnConnectDelegate;
	OnConnectDelegate.BindUFunction(this, "OnOpen");
	websocketContext->OnConnectComplete.Add(OnConnectDelegate);

	FScriptDelegate OnErrorDelegate;
	OnErrorDelegate.BindUFunction(this, "OnError");
	websocketContext->OnConnectError.Add(OnErrorDelegate);

	FScriptDelegate OnMessageDelegate;
	OnMessageDelegate.BindUFunction(this, "OnMessage");
	websocketContext->OnReceiveData.Add(OnMessageDelegate);
}

void AprjPawn::SendNetworkMessage(const FString& data) const
{
	if (!websocketContext.IsValid())
	{
		UE_LOG(LogWindows, Warning, TEXT("Attempting to send the following message without a valid connection: '%s'"), *data);
		return;
	}
	UE_LOG(LogWindows, Warning, TEXT("Sending websocket message: '%s'"), *data);
	websocketContext->SendText(data);
}

void AprjPawn::OnOpen()
{
	UE_LOG(LogWindows, Warning, TEXT("Successfully connected"));
	FTimerDynamicDelegate NetworkTickDelegate;
	NetworkTickDelegate.BindUFunction(this, "NetworkTick");
	GetWorld()->GetTimerManager().SetTimer(WebUpdateTimerHandle, NetworkTickDelegate, UpdateFrequencyInSeconds, true);
	SendNetworkMessage(FString(TEXT("{\"command\":\"createSession\",\"parameters\": {\"playerPositionX\":40,\"playerPositionY\":50,\"health\":60}}")));
}

void AprjPawn::OnError(const FString& errorMessage) const
{
	UE_LOG(LogWindows, Warning, TEXT("Error inside websocket connection: '%s'"), *errorMessage);

}

void AprjPawn::OnMessage(const FString& data) const
{
	UE_LOG(LogWindows, Warning, TEXT("Received websocket data: '%s'"), *data);

	// convert text to json object we can traverse
	FString tmpData = data;
	TSharedRef<TJsonReader<TCHAR>> Reader = FJsonStringReader::Create(MoveTemp(tmpData));

	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogWindows, Warning, TEXT("Unable to parse json: '%s'"), *data);
		return;
	}
}

void AprjPawn::NetworkTick() const
{
	UE_LOG(LogWindows, Warning, TEXT("Network tick"));
	const FVector currentLocation = GetActorLocation();
	SendNetworkMessage(
		FString::Printf(
			TEXT("{\"command\":\"updateSession\",\"sessionID\":0,\"parameters\": {\"playerPositionX\":%f,\"playerPositionY\":%f,\"health\":30}}"),
			currentLocation.X,
			currentLocation.Y
		)
	);
}

