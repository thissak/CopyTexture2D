#include "ChangeTranslucencySceneViewExtension.h"
#include "ChangeTranslucencyShader.h"
#include "PixelShaderUtils.h"
#include "PostProcess/PostProcessing.h"

FChangeTranslucencySceneViewExtension::FChangeTranslucencySceneViewExtension(const FAutoRegister& AutoRegister)
	: FSceneViewExtensionBase(AutoRegister)
{
	UE_LOG(LogTemp, Warning, TEXT("FChangeTranslucencySceneViewExtension is Created!!"))
}

FScreenPassTextureViewportParameters FChangeTranslucencySceneViewExtension::GetTextureViewParameters(
	const FScreenPassTextureViewport& InViewport)
{
	const FVector2f Extent(InViewport.Extent);
	const FVector2f ViewportMin(InViewport.Rect.Min);
	const FVector2f ViewportMax(InViewport.Rect.Max);
	const FVector2f ViewportSize = ViewportMax - ViewportMin;

	FScreenPassTextureViewportParameters Parameters;

	if (!InViewport.IsEmpty())
	{
		Parameters.Extent = FVector2f(Extent);
		Parameters.ExtentInverse = FVector2f(1.0f / Extent.X, 1.0f / Extent.Y);
		Parameters.ScreenPosToViewportScale = FVector2f(0.5f, -0.5f) * ViewportSize;
		Parameters.ScreenPosToViewportBias = (0.5f * ViewportSize) + ViewportMin;
		Parameters.ViewportMin = InViewport.Rect.Min;
		Parameters.ViewportMax = InViewport.Rect.Max;
		Parameters.ViewportSize = ViewportSize;
		Parameters.ViewportSizeInverse = FVector2f(1.0f / ViewportSize.X, 1.0f / ViewportSize.Y);
		Parameters.UVViewportMin = ViewportMin * Parameters.ExtentInverse;
		Parameters.UVViewportMax = ViewportMax * Parameters.ExtentInverse;
		Parameters.UVViewportSize = Parameters.UVViewportMax - Parameters.UVViewportMin;
		Parameters.UVViewportSizeInverse = FVector2f(1.0f / Parameters.UVViewportSize.X, 1.0f / Parameters.UVViewportSize.Y);
		Parameters.UVViewportBilinearMin = Parameters.UVViewportMin + 0.5f * Parameters.ExtentInverse;
		Parameters.UVViewportBilinearMax = Parameters.UVViewportMax + 0.5f * Parameters.ExtentInverse;
	}
	return Parameters;
}

void FChangeTranslucencySceneViewExtension::PrePostProcessPass_RenderThread(
	FRDGBuilder& GraphBuilder,
	const FSceneView& View,
	const FPostProcessingInputs& Inputs)
{
	//UE_LOG(LogTemp, Warning, TEXT("PrePostProcessPass_RenderTread Start!!"))
	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	FRDGTextureRef OriginalTranslucencyTexture =
		Inputs.TranslucencyViewResourcesMap.Get(ETranslucencyPass::TPT_TranslucencyAfterDOF).ColorTexture.Target;
	FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	RDG_EVENT_SCOPE(GraphBuilder, "Change Translucency.AfterDof Texture");

	// viewport parameters
	const FScreenPassTextureViewport TranslucencyTextureViewport(OriginalTranslucencyTexture);
	const FScreenPassTextureViewportParameters SceneTextureViewportParams = GetTextureViewParameters(TranslucencyTextureViewport);
	auto MyViewport = TranslucencyTextureViewport.Rect;

	// render target
	FScreenPassRenderTarget ChangedTranslucencyTexture;
	ChangedTranslucencyTexture.Texture = GraphBuilder.CreateTexture(OriginalTranslucencyTexture->Desc,
		TEXT("changed Translucency color"));

	// shader setup
	TShaderMapRef<FChangeTranslucencyShader> ChangeTranslucencyShader(GlobalShaderMap);
	FChangeTranslucencyShader::FParameters* ShaderParams =
		GraphBuilder.AllocParameters<FChangeTranslucencyShader::FParameters>();
	ShaderParams->TranslucencyTexture = OriginalTranslucencyTexture;
	ShaderParams->InputSampler = TStaticSamplerState<SF_Point, AM_Clamp, AM_Clamp, AM_Clamp,AM_Clamp>::GetRHI();
	ShaderParams->RenderTargets[0] = ChangedTranslucencyTexture.GetRenderTargetBinding();
	ShaderParams->ViewParams = SceneTextureViewportParams;

	FPixelShaderUtils::AddFullscreenPass(
		GraphBuilder,
		GlobalShaderMap,
		FRDGEventName(TEXT("Change Translucency color")),
		ChangeTranslucencyShader,
		ShaderParams,
		Viewport);

	AddCopyTexturePass(GraphBuilder, ChangedTranslucencyTexture.Texture, OriginalTranslucencyTexture);
}
