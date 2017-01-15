/*
===========================================================================
Common.h

Aggregates all the basic components of the engine in a single header file.
This file is included by the main header S3DGE.h
===========================================================================
*/

#pragma once

#define _USE_MATH_DEFINES
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

#include "Platforms/KeyCodes.h"

#include "Graphics/Window.h"
#include "Graphics/Layer.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Graphics/Renderables/Sprite.h"
#include "Graphics/Renderables/Label.h"
#include "Graphics/Textures/TextureManager.h"
#include "Graphics/Fonts/FontManager.h"
#include "Graphics/GraphicsManager.h"

#include "Audio/SoundManager.h"

#include "Internal/DeleteMacros.h"

#include "Utilities/Converters.h"
#include "Utilities/Timers/Timer.h"
#include "Utilities/RGN.h"