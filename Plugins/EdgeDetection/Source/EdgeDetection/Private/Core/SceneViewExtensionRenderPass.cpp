#include "SceneViewExtensionRenderPass.h"
#include "CoreMinimal.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "SceneRendering.h"
#include "CelShading/CelShadingRenderPass.h"
#include "EdgeDetection/EdgeDetectionRenderPass.h"

SceneViewExtensionRenderPass::SceneViewExtensionRenderPass(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister)
{
	passes_.emplace_back(std::make_unique<CelShadingRenderPass>(GetDefault<UCelShadingSettings>()));
	passes_.emplace_back(std::make_unique<EdgeDetectionRenderPass>(GetDefault<UEdgeDetectionSettings>()));
}

void SceneViewExtensionRenderPass::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	
	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	for (const auto& Pass : passes_)
	{
		if (Pass->Enabled())
		{
			Pass->Execute(GraphBuilder, View, Inputs, Viewport, GlobalShaderMap);
		}
	}
}