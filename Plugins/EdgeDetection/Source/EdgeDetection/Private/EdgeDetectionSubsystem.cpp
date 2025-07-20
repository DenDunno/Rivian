#include "EdgeDetectionSubsystem.h"
#include "EdgeDetectionExtension.h"
#include "SceneViewExtension.h"

void UEdgeDetectionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Subsystem INITIALIZED"));
	Super::Initialize(Collection);

	CustomSceneViewExtension = FSceneViewExtensions::NewExtension<EdgeDetectionExtension>();
}

void UEdgeDetectionSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Subsystem DEINITIALIZED"));
	
	Super::Deinitialize();

	CustomSceneViewExtension.Reset();
	CustomSceneViewExtension = nullptr;
}