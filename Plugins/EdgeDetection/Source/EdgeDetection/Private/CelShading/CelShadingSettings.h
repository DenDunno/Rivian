#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CelShadingSettings.generated.h"

UCLASS(config=Game, defaultconfig, meta=(DisplayName="Cel shading settings"))
class EDGEDETECTION_API UCelShadingSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere) bool Enabled = true;
	UPROPERTY(config, EditAnywhere) float ShadowBias = 0.5;
	UPROPERTY(config, EditAnywhere) float ShadowContrast = 50;
	UPROPERTY(config, EditAnywhere) float Brightness = 3;
	UPROPERTY(config, EditAnywhere) FLinearColor TintShadow = FLinearColor::Gray;
	UPROPERTY(config, EditAnywhere) FLinearColor TintHighlight = FLinearColor::White;
};