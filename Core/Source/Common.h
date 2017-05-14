/*
===========================================================================
Common.h

Aggregates all the basic components of the engine in a single header file.
This file is included by the main header S3DGE.h
===========================================================================
*/

#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"
#include "Math/Point2D.h"
#include "Math/Point3D.h"
#include "Math/Size2D.h"
#include "Math/Size3D.h"

#include "Platform/KeyCodes.h"
#include "Platform/Window.h"

#include "Graphics/Layer.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Graphics/Renderables/Sprite.h"
#include "Graphics/Renderables/Label.h"
#include "Graphics/Textures/TextureManager.h"
#include "Graphics/Fonts/FontManager.h"
#include "Graphics/GraphicsManager.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Renderables/Mesh.h"
#include "Graphics/Renderables/MeshFactory.h"
#include "Graphics/Renderables/LabelFactory.h"
#include "Graphics/Renderables/SpriteFactory.h"

#include "Logic/Objects/Scene.h"
#include "Logic/Objects/Entity.h"
#include "Logic/Cameras/FPSCamera.h"
#include "Logic/Cameras/TPSCamera.h"

#include "System/DeleteMacros.h"
#include "System/Timer.h"
#include "System/RNG.h"

#include "Audio/Sound.h"
#include "Audio/SoundManager.h"