#include "RenderPassesModule.h"
#include "Interfaces/IPluginManager.h"
#define LOCTEXT_NAMESPACE "FEdgeDetectionModule"

void FRenderPassesModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("EDGE DETECTION MODULE STARTUP"));
	FString PluginShaderDirectory = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("EdgeDetection"))->GetBaseDir(), TEXT("Shaders"));

	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/Plugins/EdgeDetection")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/Plugins/EdgeDetection"), PluginShaderDirectory);
	}
}

void FRenderPassesModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("EDGE DETECTION MODULE SHUTDOWN"));
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FRenderPassesModule, EdgeDetection)