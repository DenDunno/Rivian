#pragma once
#include "CoreMinimal.h"
#include "SceneViewExtension.h"
#include "DataDrivenShaderPlatformInfo.h"

class EdgeDetectionExtension : public FSceneViewExtensionBase
{
public:
	EdgeDetectionExtension(const FAutoRegister& AutoRegister);
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
};