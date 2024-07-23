// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChangeTranslucency.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FChangeTranslucencyModule"

void FChangeTranslucencyModule::StartupModule()
{
	FString BaseDir = IPluginManager::Get().FindPlugin("ChangeTranslucency")->GetBaseDir();
	FString PluginDir = FPaths::Combine(BaseDir, "/Shaders");
	UE_LOG(LogTemp, Log, TEXT("Plugin Base Directory: %s"), *PluginDir);
	AddShaderSourceDirectoryMapping("/VirtualShaderDir", PluginDir);
	
}

void FChangeTranslucencyModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FChangeTranslucencyModule, ChangeTranslucency)

