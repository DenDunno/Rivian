#include "EdgeDetectionSubsystem.h"

void UEdgeDetectionSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	CustomSceneViewExtension = FSceneViewExtensions::NewExtension<EdgeDetectionExtension>();
}

void UEdgeDetectionSubsystem::Deinitialize()
{
	CustomSceneViewExtension.Reset();
	CustomSceneViewExtension = nullptr;
}