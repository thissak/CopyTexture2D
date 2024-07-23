#include "ChangeTranslucencyShader.h"

IMPLEMENT_SHADER_TYPE(, FChangeTranslucencyShader,
	TEXT("/VirtualShaderDir/ChangeTranclucencyShader.usf"), TEXT("MainPS"), SF_Pixel);