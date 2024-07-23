#pragma once

#include "SceneViewExtension.h"
#include "ScreenPass.h"


class CHANGETRANSLUCENCY_API FChangeTranslucencySceneViewExtension : public FSceneViewExtensionBase
{
public:
	FChangeTranslucencySceneViewExtension(const FAutoRegister& AutoRegister);

	FScreenPassTextureViewportParameters GetTextureViewParameters(const FScreenPassTextureViewport& InViewport);
	
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};

	virtual void PrePostProcessPass_RenderThread(
		FRDGBuilder& GraphBuilder,
		const FSceneView& View,
		const FPostProcessingInputs& Inputs) override;
};
