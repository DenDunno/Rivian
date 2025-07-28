#pragma once
#include "EdgeDetectionSettings.h"
#include "SceneTexturesConfig.h"
#include "Core/IRenderPass.h"

class EdgeDetectionRenderPass : public IRenderPass
{
public:
	EdgeDetectionRenderPass(const UEdgeDetectionSettings* Settings);
	virtual bool Enabled() override;
	virtual void Execute(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs,
		const FIntRect& Viewport, const FGlobalShaderMap* GlobalShaderMap) override;
private:
	const UEdgeDetectionSettings* settings_;
};

class FEdgeDetectionShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FEdgeDetectionShader)
	SHADER_USE_PARAMETER_STRUCT(FEdgeDetectionShader, FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, CompressedGBuffer)
		SHADER_PARAMETER_SAMPLER(SamplerState,	CompressedGBufferSampler)
		SHADER_PARAMETER(float, EdgeSize)
		SHADER_PARAMETER(float, Threshold)
		SHADER_PARAMETER(float, Feather)
		SHADER_PARAMETER(int, ShowEdgesOnly)
		SHADER_PARAMETER(FLinearColor, EdgeColor)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureShaderParameters, SceneTextures)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};

class FGBufferCompressingShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FGBufferCompressingShader)
	SHADER_USE_PARAMETER_STRUCT(FGBufferCompressingShader, FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, DepthTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, WorldNormalTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, BaseColorTexture)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureShaderParameters, SceneTextures)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};