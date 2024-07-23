// Fill out your copyright notice in the Description page of Project Settings.


#include "TranslucencyEngineSubsystem.h"

void UTranslucencyEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("TranslucencyEngineSybsystem is Initialized!"));
	ChangeTranslucencySceneViewExtension = FSceneViewExtensions::NewExtension<FChangeTranslucencySceneViewExtension>();
}
