#pragma once
#include "Modules/ModuleManager.h"

class FRenderPassesModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};