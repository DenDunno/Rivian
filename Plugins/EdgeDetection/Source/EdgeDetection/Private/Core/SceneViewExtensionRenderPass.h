#pragma once
#include "CoreMinimal.h"
#include "SceneViewExtension.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "IRenderPass.h"
#include <vector>

class SceneViewExtensionRenderPass : public FSceneViewExtensionBase
{
public:
	SceneViewExtensionRenderPass(const FAutoRegister& AutoRegister);
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;

private:
	std::vector<std::unique_ptr<IRenderPass>> passes_;
};