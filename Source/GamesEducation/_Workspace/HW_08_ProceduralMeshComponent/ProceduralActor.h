// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralActor.generated.h"

class UProceduralMeshComponent;

UENUM(BlueprintType)
enum class EProceduralMesh : uint8
{
	EPM_Cube UMETA(DisplayName = "Cube"),
	EPM_Triangle UMETA(DisplayName = "Triangle"),
	EPM_Star UMETA(DisplayName = "Star")
};

UCLASS()
class GAMESEDUCATION_API AProceduralActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralActor();

	virtual void OnConstruction(const FTransform& Transform) override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProceduralMesh MeshType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProceduralMeshComponent* CustomMesh;

	/** The vertices of the mesh */
	TArray<FVector> Vertices;

	/** The triangles of the mesh */
	TArray<int32> Triangles;

	/** Creates a triangle that connects the given vertices */
	void AddTriangle(int32 V1, int32 V2, int32 V3);

	void GenerateCubeMesh();

	void GenerateTetrahedronMesh();

	void GenerateStarMesh();

};
