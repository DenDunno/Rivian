#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "EdgeDetectionExtension.h"
#include "EdgeDetectionSubsystem.generated.h"

UCLASS()
class RIVIAN_API UEdgeDetectionSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

private:
	TSharedPtr<class EdgeDetectionExtension> CustomSceneViewExtension;
};