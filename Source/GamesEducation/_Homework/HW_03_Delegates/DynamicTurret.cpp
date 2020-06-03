// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicTurret.h"

#include "ToolContextInterfaces.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "GamesEducation/GamesEducationProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "HW_03_GameMode.h"

// Sets default values
ADynamicTurret::ADynamicTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** Setup defaults */
	Health = 3.f;
	bAlive = true;
	Score = 10;

	/**
	 * Create and configure components
	 */
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->SetBoxExtent(FVector(50.f));
	CollisionComp->SetCollisionProfileName(TEXT("PhysicsActor"));
	SetRootComponent(CollisionComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetupAttachment(CollisionComp);

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("RouteComp"));
	SplineComp->SetupAttachment(CollisionComp);

	MovementComp = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("MovementComp"));
	MovementComp->BehaviourType = EInterpToBehaviourType::PingPong;
	MovementComp->Duration = 1.f;
}

// Called when the game starts or when spawned
void ADynamicTurret::BeginPlay()
{
	Super::BeginPlay();

	// Register Turret hit delegate 
	CollisionComp->OnComponentHit.AddDynamic(this, &ADynamicTurret::OnHit);

	SetupMovementRoute();

	CurrentPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Register current Turret in the Game Mode
	AHW_03_GameMode* CurrentGameMode = Cast<AHW_03_GameMode>(GetWorld()->GetAuthGameMode());
	if (CurrentGameMode)
	{
		CurrentGameMode->AddTurret(this);
	}
}



// Called every frame
void ADynamicTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LookOnTarget();
}

//----------------------------------------------------------------------------------------------------------------------
// Setup Movement Route
//----------------------------------------------------------------------------------------------------------------------
void ADynamicTurret::SetupMovementRoute() const
{
	for (int32 i = 0; i < SplineComp->GetNumberOfSplinePoints(); ++i)
	{
		const FVector PointLocation = SplineComp->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		MovementComp->ControlPoints.Add(FInterpControlPoint(PointLocation, true));
		
		ULog::Vector(PointLocation, LO_Both);
	}

	MovementComp->FinaliseControlPoints();
}

//----------------------------------------------------------------------------------------------------------------------
// The Turret Looks on the Player
//----------------------------------------------------------------------------------------------------------------------
void ADynamicTurret::LookOnTarget() const
{
	if (bAlive)
	{
		MeshComp->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(MeshComp->GetComponentLocation(), CurrentPlayer->GetActorLocation()));
	}
}

//----------------------------------------------------------------------------------------------------------------------
// On Turret Hit
//----------------------------------------------------------------------------------------------------------------------
void ADynamicTurret::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// If Hit By Projectile
	if (OtherActor->IsA(AGamesEducationProjectile::StaticClass()))
	{
		Damage(OtherActor);

		OtherActor->Destroy();
	}
}

//----------------------------------------------------------------------------------------------------------------------
// Takes Damage
//----------------------------------------------------------------------------------------------------------------------
void ADynamicTurret::Damage(AActor* OtherActor)
{
	if (!bAlive)
		return;

	// Decrease Health and checking for the Death condition
	Health--;
	if (Health <= 0)
	{
		Death();
	}

	// Broadcast OnDamage Delegate and set a new Duration (movement speed)
	if (OnDamage.IsBound())
	{
		const FVector TurretOffset = OnDamage.Execute(this);

		if (bAlive)
		{
			MovementComp->ApplyWorldOffset(TurretOffset, true);
		}	
	}
}

//----------------------------------------------------------------------------------------------------------------------
// The Turret Death
//----------------------------------------------------------------------------------------------------------------------
void ADynamicTurret::Death()
{
	bAlive = false;
	CollisionComp->SetSimulatePhysics(true);

	if (OnDeath.IsBound())
	{
		OnDeath.Broadcast(this);
	}
}


