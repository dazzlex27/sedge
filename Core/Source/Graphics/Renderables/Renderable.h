/*
===========================================================================
Renderable.h

Declares the Renderable class, which is the base class for all elements that can be drawn to the screen.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Math/Matrix4.h"

namespace s3dge
{
	class Renderable
	{
	protected:
		Matrix4 ModelMatrix;

	public:
		Renderable(const Matrix4& modelMatrix = Matrix4::GetIdentity()) 
			: ModelMatrix(modelMatrix) { }

		virtual void Draw() const = 0;
	};
}