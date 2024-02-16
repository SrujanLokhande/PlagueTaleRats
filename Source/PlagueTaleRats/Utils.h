#pragma once

#define LOG(X, Y) GEngine->AddOnScreenDebugMessage(X, 5.0f, FColor::Red, Y);
#define LogVariable(X, Y) UE_LOG(LogTemp, Warning, TEXT(X), Y);
