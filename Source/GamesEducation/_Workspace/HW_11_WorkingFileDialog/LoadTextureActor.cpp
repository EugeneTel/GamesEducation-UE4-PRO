// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadTextureActor.h"
#include "GamesEducation/GamesEducationHelpers.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Widgets/SWindow.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Texture2D.h"
#include "Misc/FileHelper.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Log.h"

// Sets default values
ALoadTextureActor::ALoadTextureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ALoadTextureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALoadTextureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoadTextureActor::UploadTexture()
{
	ULog::Success("UploadTexture Called");

    // Open Window for choosing a file
    const FString DialogTitle = "Upload Texture";
    const FString DefaultPath = "C:\\";
    const FString FileTypes = "Image Files|*.jpg";
    TArray<FString> OutFileNames;

    OpenFileDialog(DialogTitle, DefaultPath, FileTypes, OutFileNames);

    if (OutFileNames.Num() <= 0)
        return;

    const FString FilePath = OutFileNames[0];
    ULog::Success(FilePath);

    // Load file and create a texture
    bool bFileLoaded;
    UTexture2D* NewTexture = LoadTextureFromFile(FilePath, EJoyImageFormats::JPG, bFileLoaded);

    if (!bFileLoaded)
    {
        ULog::Error("Texture can't be loaded!");
        return;
    }

    // Apply the texture
    if (ApplyTexture(NewTexture, StaticMesh))
    {
        ULog::Success("The texture successfully applied");
    }
}

void ALoadTextureActor::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes,
    TArray<FString>& OutFileNames)
{
    if (!GEngine || !GEngine->GameViewport)
    {
        ULog::Error("GEngine is not defined");
        return;
    }

    void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        // open file picker
        const uint32 SelectionFlag = 0;
        DesktopPlatform->OpenFileDialog(ParentWindowHandle, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutFileNames);     
    }
}

UTexture2D* ALoadTextureActor::LoadTextureFromFile(const FString& FullFilePath, const EJoyImageFormats ImageFormat, bool& IsValid)
{
    IsValid = false;
    UTexture2D* LoadedTexture = nullptr;

    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(GetJoyImageFormat(ImageFormat));

    // Load from file
    TArray<uint8> RawFileData;
    if (!FFileHelper::LoadFileToArray(RawFileData, * FullFilePath))
    {
        return nullptr;
    }

    // Create T2D
    if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
    {
        const TArray<uint8>* UncompressedBGRA = nullptr;
        if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
        {
            LoadedTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

            // Valid?
            if (!LoadedTexture)
            {
                return nullptr;
            }

            // Copy!
            void* TextureData = LoadedTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
            FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
            LoadedTexture->PlatformData->Mips[0].BulkData.Unlock();

            // Update!
            LoadedTexture->UpdateResource();
        }
    }

    // Success!
    IsValid = true;
    
    return LoadedTexture;
}

bool ALoadTextureActor::ApplyTexture(UTexture2D* NewTexture, UStaticMeshComponent* ApplyToComp)
{
    UMaterialInstanceDynamic* DynamicMatInstance = ApplyToComp->CreateAndSetMaterialInstanceDynamic(0);
    DynamicMatInstance->SetTextureParameterValue(FName("TextureParam"), NewTexture);
    

    return true;
}

