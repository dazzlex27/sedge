/*
===========================================================================
Light.h

Defines a class that describes light sources.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Math/Vector3.h"
#include "Graphics/Structures/Color.h"
#include "Math/Size2D.h"

namespace s3dge
{
	enum LightType
	{
		Unknown,
		Ambient,
		Directional,
		Point,
		Spot
	};

	class Light
	{
	private:
		cstring _name;
		LightType _type;
		Vector3 _position;
		Vector3 _direction;
		Vector3 _up;
		float _attenuationConst;
		float _attenuationLinear;
		float _attenuationQuadratic;
		Color _colorAmbient;
		Color _colorDiffuse;
		Color _colorSpecular;
		float _innerConeAngle;
		float _outerConeAngle;
		Size2D _size;
	};
}