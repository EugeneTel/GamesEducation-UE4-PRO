// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GamesEducationProjectile.h"

#include "GamesEducationCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DestructibleActor.h"
#include "DestructibleComponent.h"
#include "_Workspace/HW_03_Delegates/IDamage.h"

void AGamesEducationProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Hit result notification
	if (HitActor)
	{
		AGamesEducationCharacter::NotifyHitEnemy.Broadcast(HitActor);
	}
	else
	{
		AGamesEducationCharacter::NotifyShootMiss.Broadcast();
	}

	Super::EndPlay(EndPlayReason);
}

AGamesEducationProjectile::AGamesEducationProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGamesEducationProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGamesEducationProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == nullptr || OtherActor == this)
		return;

	// Try to apply Destruction
	ADestructibleActor* DestructibleActor = Cast<ADestructibleActor>(OtherActor);
	if (DestructibleActor)
	{
		DestructibleActor->GetDestructibleComponent()->ApplyDamage(100.f, DestructibleActor->GetActorLocation(), Hit.Normal, 0.f);
		OtherComp->AddImpulseAtLocation(GetVelocity() * 5.0f, GetActorLocation());
	}
	
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	// Try to Apply Damage to the Actor
	if (OtherActor->GetClass()->ImplementsInterface(UIDamage::StaticClass()))
	{
		Cast<IIDamage>(OtherActor)->OnDamageReceived().Broadcast(10.f);
		HitActor = OtherActor;
		Destroy();
	}
}
