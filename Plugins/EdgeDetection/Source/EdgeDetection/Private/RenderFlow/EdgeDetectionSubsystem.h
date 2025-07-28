#pragma once
#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "EdgeDetectionSubsystem.generated.h"

UCLASS()
class UEdgeDetectionSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	TSharedPtr<class EdgeDetectionExtension> CustomSceneViewExtension;
};