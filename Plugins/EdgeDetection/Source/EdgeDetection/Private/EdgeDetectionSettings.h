#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EdgeDetectionSettings.generated.h"

UCLASS(config=Game, defaultconfig, meta=(DisplayName="Edge detection settings"))
class EDGEDETECTION_API UEdgeDetectionSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere) bool Enabled = true;
	UPROPERTY(config, EditAnywhere) int ShowEdgesOnly = false;
	UPROPERTY(config, EditAnywhere) float EdgeSize = 1;
	UPROPERTY(config, EditAnywhere) float Threshold = 0.3;
	UPROPERTY(config, EditAnywhere) float Feather = 0.01;
	UPROPERTY(config, EditAnywhere) FLinearColor Color = FLinearColor::White;
};