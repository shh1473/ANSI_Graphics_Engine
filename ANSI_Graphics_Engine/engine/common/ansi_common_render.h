#pragma once

#include "common/ansi_common.h"

namespace AN
{

	constexpr unsigned TEXCOORD{ 1 << 0 };
	constexpr unsigned NORMAL{ 1 << 1 };

	constexpr unsigned MaximumTextureCount{ 8 };

	enum class TextureType
	{
		Two = GL_TEXTURE_2D,
		Three = GL_TEXTURE_3D,
		Cube = GL_TEXTURE_CUBE_MAP,
		TwoArray = GL_TEXTURE_2D_ARRAY,
	};

	enum class MSAA
	{
		None,
		Nicest = GL_NICEST,
		Fastest = GL_FASTEST,
		DontCare = GL_DONT_CARE,
	};

	enum class PrimitiveTopology
	{
		Points = GL_POINTS,
		Lines = GL_LINES,
		LineLoop = GL_LINE_LOOP,
		LineStrip = GL_LINE_STRIP,
		Triangles = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN,
		Patches = GL_PATCHES,
	};

	enum class CompareFunc
	{
		Always = GL_ALWAYS,
		Never = GL_NEVER,
		Equal = GL_EQUAL,
		NotEqual = GL_NOTEQUAL,
		Less = GL_LESS,
		LessEqual = GL_LEQUAL,
		Greater = GL_GREATER,
		GreaterEqual = GL_GEQUAL,
	};

	enum class StencilOp
	{
		Keep = GL_KEEP,
		Zero = GL_ZERO,
		Replace = GL_REPLACE,
		Incr = GL_INCR,
		IncrWrap = GL_INCR_WRAP,
		Decr = GL_DECR,
		DecrWrap = GL_DECR_WRAP,
		Invert = GL_INVERT,
	};

	enum class FillMode
	{
		Point = GL_POINT,
		Wireframe = GL_LINE,
		Solid = GL_FILL,
	};

	enum class CullMode
	{
		None,
		Front = GL_FRONT,
		Back = GL_BACK,
		FrontAndBack = GL_FRONT_AND_BACK,
	};

	enum class FrontFace
	{
		CW = GL_CW,
		CCW = GL_CCW,
	};

	enum class BlendFactor
	{
		One = GL_ONE,
		Zero = GL_ZERO,
		SrcColor = GL_SRC_COLOR,
		DstColor = GL_DST_COLOR,
		SrcAlpha = GL_SRC_ALPHA,
		DstAlpha = GL_DST_ALPHA,
		InvSrcColor = GL_ONE_MINUS_SRC_COLOR,
		InvDstColor = GL_ONE_MINUS_DST_COLOR,
		InvSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
		InvDstAlpha = GL_ONE_MINUS_DST_ALPHA,
	};

	enum class BlendOp
	{
		Add = GL_FUNC_ADD,
		Subtract = GL_FUNC_SUBTRACT,
		ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
		Min = GL_MIN,
		Max = GL_MAX,
	};

	const unsigned CameraTypeCount{ 2 };
	enum class CameraType
	{
		Camera,
		Light_Spot,
		Light_Point,
	};

	const unsigned RenderTypeCount{ 4 };
	enum class RenderType
	{
		Packing,
		Deferred,
		Forward,
		Compute,
	};

}
