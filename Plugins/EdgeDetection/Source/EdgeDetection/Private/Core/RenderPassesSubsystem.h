#pragma once
#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "RenderPassesSubsystem.generated.h"

UCLASS()
class URenderPassesSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	TSharedPtr<class SceneViewExtensionRenderPass> CustomSceneViewExtension;
};