// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"

#include "TimeControlComponent.generated.h"


UCLASS( ClassGroup=(Custom))
class GAMESEDUCATION_API UTimeControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Is time effect active */
	bool bTimeEffectActive;

	/** Start Time Effect */
	void TimeEffectBegin(float Impact);
	
public:	

	/** Time Effect Length in seconds (Slow down or Speed up) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float TimeEffectLength;

	/** Time Slow Down Impact in percent (0.5 - means 50%) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float TimeDownImpact;

	/** Time Speed Up Impact in percent (1.5 - means 150%) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float TimeUpImpact;

	void Init(UInputComponent* InputComp);
	
	/**
	 * Begin slow down time
	 */
	UFUNCTION(BlueprintCallable)
	void OnTimeDownBegin();

	/**
	* Begin speed up time
	*/
	UFUNCTION(BlueprintCallable)
    void OnTimeUpBegin();

	/**
	 * End slow down time
	 */
	UFUNCTION(BlueprintCallable)
	void OnTimeEffectEnd();
		
};

template <typename ComponentT = UTimeControlComponent, typename OwnerT = UObject>
ComponentT* CreateComponentWithInput(
	OwnerT* OwningObject,
	UInputComponent* InputComp = nullptr
)
{
	if (OwningObject && InputComp)
	{
		ComponentT* Obj = NewObject<ComponentT>(OwningObject);
		Obj->Init(InputComp);
		return Obj;
	}
	return nullptr;
}