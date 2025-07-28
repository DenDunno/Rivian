#include "CelShadingRenderPass.h"
#include "PixelShaderUtils.h"
#include "SceneRenderTargetParameters.h"

IMPLEMENT_GLOBAL_SHADER(FGCelShadingShader, "/Plugins/EdgeDetection/CelShading.usf", "MainPS", SF_Pixel);

CelShadingRenderPass::CelShadingRenderPass(const UCelShadingSettings* Settings): settings_(Settings)
{
}

bool CelShadingRenderPass::Enabled() { return settings_->Enabled; }

void CelShadingRenderPass::Execute(FRDGBuilder& GraphBuilder, const FSceneView& View,
	const FPostProcessingInputs& Inputs, const FIntRect& Viewport, const FGlobalShaderMap* GlobalShaderMap)
{
	const FScreenPassTexture SceneColorTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);
	const FScreenPassTexture BaseColorTexture((*Inputs.SceneTextures)->GBufferCTexture, Viewport);
	const FScreenPassTexture DepthTexture((*Inputs.SceneTextures)->SceneDepthTexture, Viewport);
	
	FGCelShadingShader::FParameters* Parameters = GraphBuilder.AllocParameters<FGCelShadingShader::FParameters>();
	Parameters->SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);;
	Parameters->SceneColorTexture = SceneColorTexture.Texture;
	Parameters->BaseColorTexture = BaseColorTexture.Texture;
	Parameters->DepthTexture = DepthTexture.Texture;
	Parameters->ShadowBias = settings_->ShadowBias;
	Parameters->ShadowContrast = settings_->ShadowContrast;
	Parameters->TintShadow = settings_->TintShadow;
	Parameters->TintHighlight = settings_->TintHighlight;
	Parameters->Brightness = settings_->Brightness;
	Parameters->View = View.ViewUniformBuffer;
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);
	
	TShaderMapRef<FGCelShadingShader> PixelShader(GlobalShaderMap);
	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Cel shading")), PixelShader, Parameters, Viewport);
}