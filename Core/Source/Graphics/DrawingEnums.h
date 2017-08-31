#pragma once

namespace s3dge
{
	enum PrimitiveType
	{
		Points,
		Triangles,
		LineStrips,
		LineLoops,
		Lines,
		TriangleStrips,
		TriangleFans,
		QuadStrips,
		Quads,
		Polygons
	};

	enum ValueType
	{
		UnsignedInt,
		UnsginedShort,
		UnsignedByte
	};

	enum WindingOrder
	{
		Clockwise,
		CounterClockwise
	};
}