// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralActor.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AProceduralActor::AProceduralActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomMesh = CreateDefaultSubobject<UProceduralMeshComponent>("CustomMesh");
	SetRootComponent(CustomMesh);

	/* Controls whether the physics cooking should be done off the game thread.
	 * This should be used when collision geometry doesn't have to be immediately up to date
	 * (For example streaming in far away objects) */
	CustomMesh->bUseAsyncCooking = true;

	MeshType = EProceduralMesh::EPM_Cube;
}

void AProceduralActor::OnConstruction(const FTransform& Transform)
{
	switch (MeshType)
	{
		case EProceduralMesh::EPM_Cube:
			GenerateCubeMesh();
		break;
		case EProceduralMesh::EPM_Star:
			GenerateStarMesh();
		break;
		case EProceduralMesh::EPM_Triangle:
			GenerateTetrahedronMesh();
		break;
		default:
			GenerateCubeMesh();
		break;
	}
}

void AProceduralActor::AddTriangle(const int32 V1, const int32 V2, const int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}

void AProceduralActor::GenerateCubeMesh()
{
	// 6 sides on cube, 4 verts each (corners)

	// These are relative locations to the placed Actor in the world
	Vertices.Add(FVector(0.f, -100.f, 0.f)); // lower left - 0
	Vertices.Add(FVector(0.f, -100.f, 100.f)); // upper left - 1
	
	Vertices.Add(FVector(0.f, 100.f, 0.f)); // lower right - 2
	Vertices.Add(FVector(0.f, 100.f, 100.f)); // upper right - 3
	
	Vertices.Add(FVector(100.f, -100.f, 0.f)); // lower front left - 4
	Vertices.Add(FVector(100.f, -100.f, 100.f)); // upper front left - 5
	
	Vertices.Add(FVector(100.f, 100.f, 100.f)); // upper front right - 6
	Vertices.Add(FVector(100.f, 100.f, 0.f)); // lower front right - 7


	// Back face of cube
	AddTriangle(0, 2, 3);
	AddTriangle(3, 1, 0);

	// Left face of cube
	AddTriangle(0, 1, 4);
	AddTriangle(4, 1, 5);
	
	// Front face of cube
	AddTriangle(4, 5, 7);
	AddTriangle(7, 5, 6);
	
	// Right face of cube
	AddTriangle(7, 6, 3);
	AddTriangle(3, 2, 7);
	
	// Top face
	AddTriangle(1, 3, 5);
	AddTriangle(6, 5, 3);

	// Bottom face
	AddTriangle(2, 0, 4);
	AddTriangle(4, 7, 2);

	// Add Colors
	TArray<FLinearColor> VertexColors; 	/* Optional array of colors for each vertex. If supplied, must be same length as Vertices array.*/
	VertexColors.Add(FLinearColor(0.f, 0.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.5f, 1.f, 0.5f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 1.f));

	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(), true);
	
}

void AProceduralActor::GenerateTetrahedronMesh()
{
	// 4 sides on Tetrahedron, 3 verts each (corners)

	Vertices.Add(FVector(0.f, 0.f, 100.f)); // top - 0
	Vertices.Add(FVector(-50.f, 50.f, 0.f)); // lower front left - 1
	Vertices.Add(FVector(50.f, 50.f, 0.f)); // lower front right - 2
	Vertices.Add(FVector(0.f, -50.f, 0.f)); // back - 3

	// Front
	AddTriangle(0, 1, 2);
	
	// Left
	AddTriangle(1, 0, 3);

	// Right
	AddTriangle(0, 2, 3);

	// Bottom
	AddTriangle(2, 1, 3);

	// Add Colors
	TArray<FLinearColor> VertexColors; 	/* Optional array of colors for each vertex. If supplied, must be same length as Vertices array.*/
	VertexColors.Add(FLinearColor(0.f, 0.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	
	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(), true);
}

void AProceduralActor::GenerateStarMesh()
{
	// 4 sides on Star, 3 verts each (corners)

	Vertices.Add(FVector(0.f, 0.f, 100.f)); // 0
	Vertices.Add(FVector(-50.f, 0.f, 0.f)); // 1
	Vertices.Add(FVector(50.f, 0.f, 0.f)); // 2
	Vertices.Add(FVector(0.f, 0.f, 0.f)); // 3
	Vertices.Add(FVector(0.f, 0.f, -100.f)); // 4

	Vertices.Add(FVector(100.f, 0.f, 0.f)); // 5
	Vertices.Add(FVector(0.f, 0.f, -50.f)); // 6
	Vertices.Add(FVector(0.f, 0.f, 50.f)); // 7
	Vertices.Add(FVector(0.f, 0.f, -50.f)); // 8
	Vertices.Add(FVector(-100.f, 0.f, 0.f)); // 9

	AddTriangle(0, 1, 2);	// Up
	AddTriangle(1, 4, 2);	// Down
	AddTriangle(5, 7, 8);	// Right
	AddTriangle(9, 6, 7);	// Left

	// Add Colors
	TArray<FLinearColor> VertexColors; 	/* Optional array of colors for each vertex. If supplied, must be same length as Vertices array.*/
	
	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(), true);
	
}

