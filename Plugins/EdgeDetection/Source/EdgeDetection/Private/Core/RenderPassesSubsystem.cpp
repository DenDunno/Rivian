#include "RenderPassesSubsystem.h"
#include "SceneViewExtensionRenderPass.h"
#include "SceneViewExtension.h"

void URenderPassesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Subsystem INITIALIZED"));
	Super::Initialize(Collection);

	CustomSceneViewExtension = FSceneViewExtensions::NewExtension<SceneViewExtensionRenderPass>();
}

void URenderPassesSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Subsystem DEINITIALIZED"));
	Super::Deinitialize();

	CustomSceneViewExtension.Reset();
	CustomSceneViewExtension = nullptr;
}