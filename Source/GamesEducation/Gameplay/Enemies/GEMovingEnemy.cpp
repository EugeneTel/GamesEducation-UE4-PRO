// Fill out your copyright notice in the Description page of Project Settings.


#include "GEMovingEnemy.h"

#include "GamesEducation/GamesEducationCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
#include "AITypes.h"
#include "AI/Navigation/NavigationTypes.h"
#include "Animation/AnimInstance.h"
#include "TimerManager.h"

AGEMovingEnemy::AGEMovingEnemy()
{
    AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
    AgroSphere->SetupAttachment(GetRootComponent());
    AgroSphere->SetSphereRadius(800.f);

    CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
    CombatSphere->SetupAttachment(GetRootComponent());
    CombatSphere->SetSphereRadius(100.f);

    MovementStatus = EEnemyMovementStatus::EMS_Idle;
}

void AGEMovingEnemy::BeginPlay()
{
    Super::BeginPlay();

    AIController = Cast<AAIController>(GetController());
    
    AnimInstance = GetMesh()->GetAnimInstance();
	
    AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AGEMovingEnemy::AgroSphereOnOverlapBegin);
    AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AGEMovingEnemy::AgroSphereOnOverlapEnd);

    CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &AGEMovingEnemy::CombatSphereOnOverlapBegin);
    CombatSphere->OnComponentEndOverlap.AddDynamic(this, &AGEMovingEnemy::CombatSphereOnOverlapEnd);
}

void AGEMovingEnemy::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    AGamesEducationCharacter* MainCharacter = Cast<AGamesEducationCharacter>(OtherActor);

    if (MainCharacter && IsAlive())
    {
        bOverlappingAgroSphere = true;
        AgroTarget = MainCharacter;
        MoveToTarget(MainCharacter);
    }
}

void AGEMovingEnemy::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AGamesEducationCharacter* MainCharacter = Cast<AGamesEducationCharacter>(OtherActor);

    if (MainCharacter)
    {
        AgroTarget = nullptr;
        bOverlappingAgroSphere = false;
        StopMovementToTarget();
    }
}

void AGEMovingEnemy::CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AGamesEducationCharacter* MainCharacter = Cast<AGamesEducationCharacter>(OtherActor);
    
    if (MainCharacter && IsAlive())
    {
        bOverlappingCombatSphere = true;
        CombatTarget = MainCharacter;
        AttackTarget(MainCharacter);
    }
}

void AGEMovingEnemy::CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AGamesEducationCharacter* MainCharacter = Cast<AGamesEducationCharacter>(OtherActor);
    
    if (MainCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("AGEMovingEnemy::CombatSphereOnOverlapEnd"));

        CombatTarget = nullptr;
        bOverlappingCombatSphere = false;
        StopAttacking();
    }
    
}

void AGEMovingEnemy::MoveToTarget(AGamesEducationCharacter* Target)
{
    if (!AIController || !IsAlive()) { return; }
	
    UE_LOG(LogTemp, Warning, TEXT("AGEMovingEnemy::MoveToTarget"));

    MovementStatus = EEnemyMovementStatus::EMS_MoveToTarget;

    FAIMoveRequest AIMoveRequest(Target);
    AIMoveRequest.SetAcceptanceRadius(30.f);

    FNavPathSharedPtr NavPathShared;

    AIController->MoveTo(AIMoveRequest, OUT &NavPathShared);

    // Draw Debug line
    if (bDebugMode && NavPathShared)
    {
        auto PathPoints = NavPathShared->GetPathPoints();

        FVector PreviousPoint = FVector(0, 0, 0);

        for (const auto PathPoint : PathPoints)
        {
            const auto EndPoint = PathPoint.Location;

            if (PreviousPoint.IsZero())
            {
                PreviousPoint = EndPoint;
                continue;
            }

            UKismetSystemLibrary::DrawDebugLine(GetWorld(), PreviousPoint, EndPoint, FLinearColor::Red, 5.f, 1.f);
            PreviousPoint = EndPoint;
        }
    }  
}
    
void AGEMovingEnemy::StopMovementToTarget()
{
    if (!AIController || MovementStatus != EEnemyMovementStatus::EMS_MoveToTarget)
        return;

    AIController->StopMovement();

    MovementStatus = EEnemyMovementStatus::EMS_Idle;
}

void AGEMovingEnemy::AttackTarget(AGamesEducationCharacter* Target)
{
    UE_LOG(LogTemp, Warning, TEXT("AGEMovingEnemy::AttackTarget:Start"));
    if (!CombatMontage || !AnimInstance || !IsAlive())
        return;

    bIsAttacking = true;
	   
    UE_LOG(LogTemp, Warning, TEXT("AGEMovingEnemy::AttackTarget"));

    AnimInstance->Montage_Play(CombatMontage, 1.3f);   
    AnimInstance->Montage_JumpToSection(FName("Attack_Left"));
}

void AGEMovingEnemy::StopAttacking()
{
    CombatTarget = nullptr;
    bIsAttacking = false;
    MovementStatus = EEnemyMovementStatus::EMS_MoveToTarget;

    if (bOverlappingAgroSphere && AgroTarget)
    {
        MoveToTarget(AgroTarget);
    }
}

void AGEMovingEnemy::AttackSectionEnd()
{
    if (!bIsAttacking)
    {
        UE_LOG(LogTemp, Warning, TEXT("AGEMovingEnemy::AttackSectionEnd"));

        AnimInstance->Montage_Stop(0.f, CombatMontage);

        if (bOverlappingAgroSphere && AgroTarget)
        {
            MoveToTarget(AgroTarget);
        }
    }
}

void AGEMovingEnemy::AttackComboEnd()
{
    if (!bIsAttacking)
    {
        UE_LOG(LogTemp, Warning, TEXT("AGEMovingEnemy::AttackSectionEnd"));
        
        AnimInstance->Montage_Stop(0.f, CombatMontage);

        if (bOverlappingAgroSphere && AgroTarget)
        {
            MoveToTarget(AgroTarget);
        }
    }
    else if (CombatTarget)
    {
        AttackTarget(CombatTarget);
    }
}
