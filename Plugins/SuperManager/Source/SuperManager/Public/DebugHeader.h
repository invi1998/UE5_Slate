#pragma once

inline void PrintDebug(const FString& InString, const FColor& InColor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, InColor, InString);
	}
}

inline void PrintLog(const FString& InString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *InString);
}
