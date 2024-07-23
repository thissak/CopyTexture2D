// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeTranslucencySceneViewExtension.h"
#include "Subsystems/EngineSubsystem.h"
#include "TranslucencyEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CHANGETRANSLUCENCY_API UTranslucencyEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:

private:
	TSharedPtr<FChangeTranslucencySceneViewExtension, ESPMode::ThreadSafe> ChangeTranslucencySceneViewExtension;
};
