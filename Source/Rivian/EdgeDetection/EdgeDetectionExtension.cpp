#include "EdgeDetectionExtension.h"

#include "ScreenPass.h"

EdgeDetectionExtension::EdgeDetectionExtension(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{
	UE_LOG(LogTemp, Warning, TEXT("SceneViewExtensionTemplate: Custom SceneViewExtension registered"));
}

void EdgeDetectionExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView,const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, InView, Inputs);
}
