// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorMaterialChange.generated.h"

class UCurveFloat;

UCLASS()
class GAMESEDUCATION_API AActorMaterialChange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorMaterialChange();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	/** A curve used for changing mesh color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* ColorCurve;

	/** Material instance will be change dynamically */
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMatInstance;

	/** Set mesh color */
	UFUNCTION(BlueprintCallable)
	void SetColor(const FLinearColor& NewColor) const;

	/** Generate random RGB and Alpha value for our Vector Parameter */
	UFUNCTION(BlueprintCallable)
	FLinearColor GetRandomColor() const;

	/** Get color from Curve */
	UFUNCTION(BlueprintCallable)
	FLinearColor GetCurveColor();

private:
	/** Curve length in seconds */
	float CurveLengthSeconds;

	/** Default random mesh color */
	FLinearColor RandomColor;

};
