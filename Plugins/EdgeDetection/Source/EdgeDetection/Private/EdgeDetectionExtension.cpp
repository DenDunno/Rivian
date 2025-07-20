#include "EdgeDetectionExtension.h"

EdgeDetectionExtension::EdgeDetectionExtension(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister)
{
}

void EdgeDetectionExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
}
