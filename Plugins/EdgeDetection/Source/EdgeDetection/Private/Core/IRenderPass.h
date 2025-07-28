#pragma once
#include "PostProcess/PostProcessInputs.h"

class IRenderPass
{
public:
	virtual ~IRenderPass() = default;
	virtual bool Enabled() = 0;
	virtual void Execute(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs,
		const FIntRect& Viewport, const FGlobalShaderMap* GlobalShaderMap) = 0;
};
