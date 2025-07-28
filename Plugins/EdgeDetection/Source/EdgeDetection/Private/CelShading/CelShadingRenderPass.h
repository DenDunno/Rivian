#pragma once
#include "CelShadingSettings.h"
#include "SceneTexturesConfig.h"
#include "Core/IRenderPass.h"

class CelShadingRenderPass : public IRenderPass
{
public:
	CelShadingRenderPass(const UCelShadingSettings* Settings);
	virtual bool Enabled() override;
	virtual void Execute(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs,
		const FIntRect& Viewport, const FGlobalShaderMap* GlobalShaderMap) override;
private:
	const UCelShadingSettings* settings_;
};

class FGCelShadingShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FGCelShadingShader)
	SHADER_USE_PARAMETER_STRUCT(FGCelShadingShader, FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, DepthTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, BaseColorTexture)
		SHADER_PARAMETER(float, ShadowBias)
		SHADER_PARAMETER(float, ShadowContrast)
		SHADER_PARAMETER(float, Brightness)
		SHADER_PARAMETER(FVector4f, TintShadow)
		SHADER_PARAMETER(FVector4f, TintHighlight)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureShaderParameters, SceneTextures)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};