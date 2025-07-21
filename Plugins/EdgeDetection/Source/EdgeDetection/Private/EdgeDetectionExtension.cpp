#include "EdgeDetectionExtension.h"

#include "PixelShaderUtils.h"
#include "RenderGraphEvent.h"
#include "SceneRenderTargetParameters.h"
#include "SceneTexturesConfig.h"
#include "CoreMinimal.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "SceneRendering.h"
#include "Runtime/Renderer/Internal/PostProcess/PostProcessInputs.h"

DECLARE_GPU_DRAWCALL_STAT(EdgeDetection);
IMPLEMENT_GLOBAL_SHADER(FCustomShader, "/Plugins/EdgeDetection/EdgeDetection.usf", "MainPS", SF_Pixel);

EdgeDetectionExtension::EdgeDetectionExtension(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister)
{
}

void EdgeDetectionExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	
	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	
	RDG_GPU_STAT_SCOPE(GraphBuilder, EdgeDetection); 
	RDG_EVENT_SCOPE(GraphBuilder, "Edge detection");
	
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	const FScreenPassTexture SceneColorTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);
	const FScreenPassTexture WorldNormalsTexture((*Inputs.SceneTextures)->GBufferATexture, Viewport);
	
	FCustomShader::FParameters* Parameters = GraphBuilder.AllocParameters<FCustomShader::FParameters>();
	Parameters->WorldNormalTexture = WorldNormalsTexture.Texture;
	Parameters->SceneColorTexture = SceneColorTexture.Texture;
	Parameters->SceneTextures = SceneTextures;
	Parameters->View = View.ViewUniformBuffer;
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);
	
	TShaderMapRef<FCustomShader> PixelShader(GlobalShaderMap);
	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Edge detection pass")), PixelShader, Parameters, Viewport);
}