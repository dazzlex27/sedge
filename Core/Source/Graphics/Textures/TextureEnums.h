#pragma once

namespace s3dge
{
	enum TextureWrapMode
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder
	};

	enum TextureFilterMode
	{
		Nearest = 0,
		Linear = 1,
		NearestMipmapNearest = 2,
		LinearMipmapNearest = 3,
		NearestMipmapLinear = 4,
		LinearMipmapLinear = 5
	};

	enum TextureTarget
	{
		Tex2D,
		Cube
	};

	enum TextureFilter
	{
		Min,
		Mag
	};

	enum TextureWrap
	{
		WrapS,
		WrapT,
		WrapR
	};

	enum TextureType
	{
		Diffuse,
		Specular
	};

	enum ColorCode
	{
		Mono,
		Rgb,
		Rgba
	};
}