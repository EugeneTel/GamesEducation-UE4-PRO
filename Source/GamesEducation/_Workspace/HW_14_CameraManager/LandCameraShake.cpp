// Fill out your copyright notice in the Description page of Project Settings.


#include "LandCameraShake.h"

ULandCameraShake::ULandCameraShake()
{
    OscillationDuration = 0.15f;

    // Blend time
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(-1.5f, -3.f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(15.f, 20.f);
    
    RotOscillation.Yaw.Amplitude = FMath::RandRange(.5f, 1.f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(3.f, 6.f);
}
