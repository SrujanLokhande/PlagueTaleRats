// Copyright Srujan Lokhande 2024


#include "PlagueTaleCameraShake.h"

UPlagueTaleCameraShake::UPlagueTaleCameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(2.0f, 5.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(20.0f, 30.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(2.0f, 5.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(20.0f, 30.0f);
}
