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
IMPLEMENT_GLOBAL_SHADER(FEdgeDetectionShader, "/Plugins/EdgeDetection/EdgeDetection.usf", "MainPS", SF_Pixel);
IMPLEMENT_GLOBAL_SHADER(FNormalDepthTextureMergingShader, "/Plugins/EdgeDetection/NormalDepthTextureMerging.usf", "MainPS", SF_Pixel);

void DetectEdges(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs, const FIntRect& Viewport, const FGlobalShaderMap* GlobalShaderMap, const FScreenPassTexture& NormalDepthTexture)
{
	const FScreenPassTexture SceneColorTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);
	
	FEdgeDetectionShader::FParameters* Parameters = GraphBuilder.AllocParameters<FEdgeDetectionShader::FParameters>();
	Parameters->SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);;
	Parameters->WorldNormalTexture = NormalDepthTexture.Texture;
	Parameters->WorldNormalTextureSampler = TStaticSamplerState<SF_Bilinear>::GetRHI();
	Parameters->SceneColorTexture = SceneColorTexture.Texture;
	Parameters->View = View.ViewUniformBuffer;
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);
	
	TShaderMapRef<FEdgeDetectionShader> PixelShader(GlobalShaderMap);
	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Edge detection pass")), PixelShader, Parameters, Viewport);
}

FScreenPassTexture MergeNormalAndDepthTextures(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs, const FIntRect& Viewport, const FGlobalShaderMap* GlobalShaderMap)
{
	const FScreenPassTexture WorldNormalsTexture((*Inputs.SceneTextures)->GBufferATexture, Viewport);
	const FScreenPassTexture DepthTexture((*Inputs.SceneTextures)->SceneDepthTexture, Viewport);
	
	FRDGTextureDesc Descriptor = FRDGTextureDesc::Create2D(Viewport.Size(), PF_A32B32G32R32F, FClearValueBinding::None, TexCreate_RenderTargetable | TexCreate_ShaderResource);
	FRDGTextureRef NormalDepthRenderTexture = GraphBuilder.CreateTexture(Descriptor, TEXT("NormalDepthRenderTexture"));
	
	FNormalDepthTextureMergingShader::FParameters* Parameters = GraphBuilder.AllocParameters<FNormalDepthTextureMergingShader::FParameters>();
	Parameters->SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	Parameters->WorldNormalTexture = WorldNormalsTexture.Texture;
	Parameters->DepthTexture = DepthTexture.Texture;
	Parameters->View = View.ViewUniformBuffer;
	Parameters->RenderTargets[0] = FRenderTargetBinding(NormalDepthRenderTexture, ERenderTargetLoadAction::EClear);
	
	TShaderMapRef<FNormalDepthTextureMergingShader> PixelShader(GlobalShaderMap);
	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Normal depth texture merging")), PixelShader, Parameters, Viewport);

	return FScreenPassTexture(NormalDepthRenderTexture, Viewport);
}

EdgeDetectionExtension::EdgeDetectionExtension(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister)
{
}

void EdgeDetectionExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	
	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	
	RDG_GPU_STAT_SCOPE(GraphBuilder, EdgeDetection); 
	RDG_EVENT_SCOPE(GraphBuilder, "Edge detection");

	const FScreenPassTexture NormalDepthTexture = MergeNormalAndDepthTextures(GraphBuilder, View, Inputs, Viewport, GlobalShaderMap);
	DetectEdges(GraphBuilder, View, Inputs, Viewport, GlobalShaderMap, NormalDepthTexture);
}