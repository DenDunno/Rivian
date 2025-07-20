#pragma once
#include "Modules/ModuleManager.h"

class FEdgeDetectionModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};