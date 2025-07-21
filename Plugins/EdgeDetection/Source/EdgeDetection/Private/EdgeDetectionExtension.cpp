#include "EdgeDetectionExtension.h"

#include "PixelShaderUtils.h"
#include "RenderGraphEvent.h"
#include "SceneRenderTargetParameters.h"
#include "SceneTexturesConfig.h"
#include "CoreMinimal.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "SceneRendering.h"
#include "Runtime/Renderer/Internal/PostProcess/PostProcessInputs.h"

IMPLEMENT_GLOBAL_SHADER(FCustomShader, "/Plugins/EdgeDetection/EdgeDetection.usf", "MainPS", SF_Pixel);

EdgeDetectionExtension::EdgeDetectionExtension(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister)
{
}

void EdgeDetectionExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	
	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	// Requires RHI
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	
	RDG_GPU_STAT_SCOPE(GraphBuilder, ColourExtract); // Unreal Insights
	RDG_EVENT_SCOPE(GraphBuilder,  "Colour Extract"); // RenderDoc
	
	// Without the helper function
	// This is to get the base colour without shading
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	// This is colour with shading and shadows
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);
	
	FCustomShader::FParameters* Parameters = GraphBuilder.AllocParameters<FCustomShader::FParameters>();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	Parameters->SceneTextures = SceneTextures;
	Parameters->View = View.ViewUniformBuffer;
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);
	
	TShaderMapRef<FCustomShader> PixelShader(GlobalShaderMap);
	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Colour Extract Pass")), PixelShader, Parameters, Viewport);
}