#include "EdgeDetectionModule.h"
#include "Interfaces/IPluginManager.h"
#define LOCTEXT_NAMESPACE "FEdgeDetectionModule"

void FEdgeDetectionModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("EDGE DETECTION MODULE STARTUP"));
	FString PluginShaderDirectory = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("EdgeDetection"))->GetBaseDir(), TEXT("Shaders"));

	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/Plugins/EdgeDetection")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/Plugins/EdgeDetection"), PluginShaderDirectory);
	}
}

void FEdgeDetectionModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("EDGE DETECTION MODULE SHUTDOWN"));
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FEdgeDetectionModule, EdgeDetection)