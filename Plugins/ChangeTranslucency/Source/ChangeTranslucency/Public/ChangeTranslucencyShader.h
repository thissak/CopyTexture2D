#pragma once

#include "GlobalShader.h"
#include "ScreenPass.h"

BEGIN_SHADER_PARAMETER_STRUCT(FChangeTranShaderParameters,)
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, TranslucencyTexture)
	SHADER_PARAMETER_SAMPLER(SamplerState, InputSampler)
	SHADER_PARAMETER_STRUCT(FScreenPassTextureViewportParameters, ViewParams)
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class FChangeTranslucencyShader : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FChangeTranslucencyShader, Global, );
	using FParameters = FChangeTranShaderParameters;
	SHADER_USE_PARAMETER_STRUCT(FChangeTranslucencyShader, FGlobalShader);
};

