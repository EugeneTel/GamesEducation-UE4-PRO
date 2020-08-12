// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamesEducation/GamesEducationHelpers.h"
#include "LoadTextureActor.generated.h"

UCLASS()
class GAMESEDUCATION_API ALoadTextureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoadTextureActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UploadTexture();
	
	UFUNCTION(BlueprintCallable)
    void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);

	UFUNCTION(BlueprintCallable)
    UTexture2D* LoadTextureFromFile(const FString& FullFilePath, const EJoyImageFormats ImageFormat, bool& IsValid);

	UFUNCTION(BlueprintCallable)
	bool ApplyTexture(UTexture2D* NewTexture, UStaticMeshComponent* ApplyToComp);

};
