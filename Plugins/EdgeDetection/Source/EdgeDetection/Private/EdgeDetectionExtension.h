#pragma once
#include "CoreMinimal.h"
#include "SceneViewExtension.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "ScreenPass.h"
#include "ShaderParameterStruct.h"

class EdgeDetectionExtension : public FSceneViewExtensionBase
{
public:
	EdgeDetectionExtension(const FAutoRegister& AutoRegister);
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
};

class FEdgeDetectionShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FEdgeDetectionShader)
	SHADER_USE_PARAMETER_STRUCT(FEdgeDetectionShader, FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, WorldNormalTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState,	WorldNormalTextureSampler)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureShaderParameters, SceneTextures)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};

class FNormalDepthTextureMergingShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FNormalDepthTextureMergingShader)
	SHADER_USE_PARAMETER_STRUCT(FNormalDepthTextureMergingShader, FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, DepthTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, WorldNormalTexture)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureShaderParameters, SceneTextures)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};