#pragma once

#include "IImageWrapper.h"
#include "GamesEducationHelpers.Generated.h"

UENUM(BlueprintType)
enum class EJoyImageFormats : uint8
{
    JPG		UMETA(DisplayName="JPG        "),
    PNG		UMETA(DisplayName="PNG        "),
    BMP		UMETA(DisplayName="BMP        "),
    ICO		UMETA(DisplayName="ICO        "),
    EXR		UMETA(DisplayName="EXR        "),
    ICNS	UMETA(DisplayName="ICNS        ")
};

static EImageFormat GetJoyImageFormat(EJoyImageFormats JoyFormat)
{
    switch(JoyFormat)
    {
    case EJoyImageFormats::JPG : return EImageFormat::JPEG;
    case EJoyImageFormats::PNG : return EImageFormat::PNG;
    case EJoyImageFormats::BMP : return EImageFormat::BMP;
    case EJoyImageFormats::ICO : return EImageFormat::ICO;
    case EJoyImageFormats::EXR : return EImageFormat::EXR;
    case EJoyImageFormats::ICNS : return EImageFormat::ICNS;
    }
    
    return EImageFormat::JPEG;
}
