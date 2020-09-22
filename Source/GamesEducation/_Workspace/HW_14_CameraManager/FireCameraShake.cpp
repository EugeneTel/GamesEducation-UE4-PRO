// Fill out your copyright notice in the Description page of Project Settings.


#include "FireCameraShake.h"

UFireCameraShake::UFireCameraShake()
{
    OscillationDuration = 0.15f;

    // Blend time
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(1.5f, 3.f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(5.f, 10.f);
    
    RotOscillation.Yaw.Amplitude = FMath::RandRange(.3f, .6f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(3.f, 6.f);
}
