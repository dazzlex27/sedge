/*
===========================================================================
OpenGLBindings.h

Implements GraphicsAPI functions for OpenGL.
This should be the only place where GL/glew.h is included!
===========================================================================
*/

#pragma once

#include "GraphicsAPI.h"
#include "GraphicsAPIEnumConverter.h"
#include "System/Log.h"
#include <GL/glew.h>
#include <string>
#include "System/ImageUtils.h"

using namespace s3dge;

uint VAO;

#ifdef S3_DEBUG
#ifdef _WIN32
#include <Windows.h>
#else
#define APIENTRY _stdcall
#endif

void APIENTRY openglCallbackFunction(
	GLenum source,
	GLenum type,
	GLuint ID,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);
#endif

typedef GraphicsAPIEnumConverter EnumConverter;

void GraphicsAPI::GenBuffers(const uint n, ID*const buffers)
{
	glGenBuffers(n, buffers);
}

void GraphicsAPI::DeleteBuffers(const uint n, ID*const buffers)
{
	glDeleteBuffers(n, buffers);
}

void GraphicsAPI::BindBuffer(const BufferTarget target, const ID id)
{
	glBindBuffer(EnumConverter::GetBufferTarget(target), id);
}

void GraphicsAPI::SetBufferData(const BufferTarget target, const uint bufferSize, const void* bufferData, const DrawingMode hint)
{
	glBufferData(EnumConverter::GetBufferTarget(target), bufferSize, bufferData, EnumConverter::GetDrawingModeValue(hint));
}

void* GraphicsAPI::MapBufferForWriting(const BufferTarget target)
{
	return glMapBuffer(EnumConverter::GetBufferTarget(target), GL_WRITE_ONLY);
}

void GraphicsAPI::UnmapBuffer(const BufferTarget target)
{
	glUnmapBuffer(EnumConverter::GetBufferTarget(target));
}

void GraphicsAPI::EnableVertexAttributeArray(const uint index)
{
	glEnableVertexAttribArray(index);
}

void GraphicsAPI::VertexAttributePointer(const uint index, const int size, const int type, const int normalized, const int stride, const void * const offset)
{
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void GraphicsAPI::DrawArrays(const PrimitiveType primitiveType, const int first, const uint count)
{
	glDrawArrays(EnumConverter::GetPrimitiveType(primitiveType), first, count);
}

void GraphicsAPI::DrawElements(const PrimitiveType primitiveType, const uint count, const ValueType type, const void*const elements)
{
	glDrawElements(EnumConverter::GetPrimitiveType(primitiveType), count, EnumConverter::GetValueType(type), elements);
}

void GraphicsAPI::DrawTrianglesIndexed(const uint elementCount)
{
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
}

void GraphicsAPI::GenTextures(const uint n, ID*const textures)
{
	glGenTextures(n, textures);
}

void GraphicsAPI::DeleteTextures(const uint n, ID*const textures)
{
	glDeleteTextures(n, textures);
}

void GraphicsAPI::BindTexture(const TextureTarget target, const ID id)
{
	glBindTexture(EnumConverter::GetTextureTarget(target), id);
}

void GraphicsAPI::LoadTex2DImage(const int level, const ColorCode internalFormat, const int width, const int height, const int border, const ColorCode format, const ValueType valueType, const void * const pixels)
{
	glTexImage2D(GL_TEXTURE_2D, level, EnumConverter::GetColorCode(internalFormat), width, height, border, EnumConverter::GetColorCode(format), EnumConverter::GetValueType(valueType), pixels);
}

void GraphicsAPI::LoadCubemapImage(const uint num, const int level, const ColorCode internalFormat, const int width, const int height, const int border, const ColorCode format, const ValueType valueType, const void * const pixels)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + num, level, EnumConverter::GetColorCode(internalFormat), width, height, border, EnumConverter::GetColorCode(format), EnumConverter::GetValueType(valueType), pixels);
}

void GraphicsAPI::GenerateMipmap(const TextureTarget target)
{
	glGenerateMipmap(EnumConverter::GetTextureTarget(target));
}

void GraphicsAPI::ActivateTexture(const uint num)
{
	glActiveTexture(GL_TEXTURE0 + num);
}

void GraphicsAPI::SetTextureWrapMode(const TextureTarget target, const TextureWrap wrap, const TextureWrapMode wrapMode)
{
	glTexParameteri(EnumConverter::GetTextureTarget(target), EnumConverter::GetTextureWrap(wrap), EnumConverter::GetTextureWrapMode(wrapMode));
}

void GraphicsAPI::SetTextureFilterMode(const TextureTarget target, const TextureFilter filter, const TextureFilterMode mode)
{
	glTexParameteri(EnumConverter::GetTextureTarget(target), EnumConverter::GetTextureFilter(filter), EnumConverter::GetTextureFilterMode(mode));
}

void GraphicsAPI::GenFramebuffers(const uint n, ID*const buffers)
{
	glGenFramebuffers(n, buffers);
}

void GraphicsAPI::DeleteFramebuffers(const uint n, ID*const buffers)
{
	glDeleteFramebuffers(n, buffers);
}

void GraphicsAPI::BindFramebuffer(const ID bufferID)
{
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
}

const bool GraphicsAPI::IsFramebufferComplete(const ID bufferID)
{
	BindFramebuffer(bufferID);
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void GraphicsAPI::AttachTextureToFramebuffer(const ID textureID)
{

}

const ID GraphicsAPI::CreateShaderProgram()
{
	return glCreateProgram();
}

void GraphicsAPI::LinkShaderProgram(const ID programID)
{
	glLinkProgram(programID);
}

void GraphicsAPI::ValidateShaderProgram(const ID programID)
{
	glValidateProgram(programID);
}

void GraphicsAPI::DeleteShaderProgram(const ID programID)
{
	glDeleteProgram(programID);
}

void GraphicsAPI::DeleteShader(const ID shaderID)
{
	glDeleteShader(shaderID);
}

const ID GraphicsAPI::CreateShader(const ShaderTarget target)
{
	return glCreateShader(EnumConverter::GetShaderTarget(target));
}

void GraphicsAPI::AttachShader(const ID programID, const ID shaderID)
{
	glAttachShader(programID, shaderID);
}

void GraphicsAPI::DetachShader(const ID programID, const ID shaderID)
{
	glDetachShader(programID, shaderID);
}

const bool GraphicsAPI::CompileShader(const ID shaderID)
{
	glCompileShader(shaderID);

	int shaderStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderStatus);

	return shaderStatus == GL_TRUE;
}

char* GraphicsAPI::GetShaderInfoLog(const ID shaderID)
{
	GLint infoLogLength;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* strInfoLog = new char[infoLogLength + 1];
	glGetShaderInfoLog(shaderID, infoLogLength, 0, strInfoLog);

	return strInfoLog;
}

void GraphicsAPI::BindShaderProgram(const ID programID)
{
	glUseProgram(programID);
}

void GraphicsAPI::LoadShaderSource(const ID shaderID, const char*const source)
{
	glShaderSource(shaderID, 1, &source, NULL);
}

const int GraphicsAPI::GetUniformLocation(const ID programID, const char*const name)
{
	return glGetUniformLocation(programID, name);
}

void GraphicsAPI::SetUniformMatrix4(const int location, const int count, const bool transpose, const float*const values)
{
	glUniformMatrix4fv(location, 1, transpose, values);
}

void GraphicsAPI::SetUniform1f(const int location, const float value)
{
	glUniform1f(location, value);
}

void GraphicsAPI::SetUniform2f(const int location, const float value1, const float value2)
{
	glUniform2f(location, value1, value2);
}

void GraphicsAPI::SetUniform3f(const int location, const float value1, const float value2, const float value3)
{
	glUniform3f(location, value1, value2, value3);
}

void GraphicsAPI::SetUniform4f(const int location, const float value1, const float value2, const float value3, const float value4)
{
	glUniform4f(location, value1, value2, value3, value4);
}

void GraphicsAPI::SetUniform1i(const int location, const int value)
{
	glUniform1i(location, value);
}

void GraphicsAPI::SetUniform1iv(const int location, const int count, const int*const values)
{
	glUniform1iv(location, count, values);
}

const bool GraphicsAPI::Initialize()
{
	int result = glewInit();

	if (result != GLEW_OK)
		return false;

#ifdef S3_DEBUG
	// Enable the debug callback
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
#endif

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glFrontFace(GL_CCW);

	// global VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	ImageUtils::SetFlipVertically(true);

	return true;
}

void GraphicsAPI::Dispose()
{
	glBindVertexArray(VAO);
	glDeleteVertexArrays(1, &VAO);
}

void GraphicsAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GraphicsAPI::SetViewPort(const int x, const int y, const int width, const int height)
{
	glViewport(x, y, width, height);
}

void GraphicsAPI::EnableDepthMask()
{
	glDepthMask(GL_TRUE);
}

void GraphicsAPI::DisableDepthMask()
{
	glDepthMask(GL_FALSE);
}

void GraphicsAPI::SetDepthMask(const bool useMask)
{
	if (useMask)
		EnableDepthMask();
	else
		DisableDepthMask();
}

void GraphicsAPI::EnableFaceCulling()
{
	glEnable(GL_CULL_FACE);
}

void GraphicsAPI::DisableFaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void GraphicsAPI::SetFaceCulling(const bool cullFaces)
{
	if (cullFaces)
		EnableFaceCulling();
	else
		DisableFaceCulling();
}

void GraphicsAPI::EnableBlending()
{
	glEnable(GL_BLEND);
}

void GraphicsAPI::DisableBlending()
{
	glDisable(GL_BLEND);
}

void GraphicsAPI::SetBlending(const bool blend)
{
	if (blend)
		EnableBlending();
	else
		DisableBlending();
}

void GraphicsAPI::SetStandartBlending()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsAPI::EnableDepthTesting()
{
	glEnable(GL_DEPTH_TEST);
}

void GraphicsAPI::DisableDepthTesting()
{
	glDisable(GL_DEPTH_TEST);
}

void GraphicsAPI::SetDepthTesting(const bool testDepth)
{
	if (testDepth)
		EnableDepthTesting();
	else
		DisableDepthTesting();
}

void GraphicsAPI::SetWindingOrder(const WindingOrder order)
{
	glFrontFace(EnumConverter::GetWindingOrder(order));
}

char* GraphicsAPI::GetVersion()
{
	return (char*)glGetString(GL_VERSION);
}

char* GraphicsAPI::GetRenderingDevice()
{
	return (char*)glGetString(GL_RENDERER);
}

char* GraphicsAPI::GetExtensions()
{
	return (char*)glGetString(GL_EXTENSIONS);
}

// ============================================================================
// Enum converters
// ============================================================================

const int EnumConverter::GetDrawingModeValue(const DrawingMode drawingMode)
{
	switch (drawingMode)
	{
	case Dynamic:
		return GL_DYNAMIC_DRAW;
	case Static:
		return GL_STATIC_DRAW;
	case Stream:
		return GL_STREAM_DRAW;
	default:
		return 0;
	}
}

const int EnumConverter::GetBufferTarget(const BufferTarget target)
{
	switch (target)
	{
	case Element:
		return GL_ELEMENT_ARRAY_BUFFER;
	case Array:
		return GL_ARRAY_BUFFER;
	default:
		return 0;
	}
}

const int EnumConverter::GetTextureTarget(const TextureTarget target)
{
	switch (target)
	{
	case Tex2D:
		return GL_TEXTURE_2D;
	case TexCube:
		return GL_TEXTURE_CUBE_MAP;
	default:
		return 0;
	}
}

const int EnumConverter::GetTextureWrap(const TextureWrap wrap)
{
	switch (wrap)
	{
	case WrapS:
		return GL_TEXTURE_WRAP_S;
	case WrapT:
		return GL_TEXTURE_WRAP_T;
	case WrapR:
		return GL_TEXTURE_WRAP_R;
	default:
		return 0;
	}
}

const int EnumConverter::GetTextureWrapMode(const TextureWrapMode mode)
{
	switch (mode)
	{
	case Repeat:
		return GL_REPEAT;
	case MirroredRepeat:
		return GL_MIRRORED_REPEAT;
	case ClampToBorder:
		return GL_CLAMP_TO_BORDER;
	case ClampToEdge:
		return GL_CLAMP_TO_EDGE;
	default:
		return 0;
	}
}

const int EnumConverter::GetTextureFilter(const TextureFilter filter)
{
	switch (filter)
	{
	case Min:
		return GL_TEXTURE_MIN_FILTER;
	case Mag:
		return GL_TEXTURE_MAG_FILTER;
	default:
		return 0;
	}
}

const int EnumConverter::GetTextureFilterMode(const TextureFilterMode filterMode)
{
	switch (filterMode)
	{
	case Nearest:
		return GL_NEAREST;
	case Linear:
		return GL_LINEAR;
	case NearestMipmapNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	case NearestMipmapLinear:
		return GL_NEAREST_MIPMAP_LINEAR;
	case LinearMipmapNearest:
		return GL_LINEAR_MIPMAP_NEAREST;
	case LinearMipmapLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		return 0;
	}
}

const int EnumConverter::GetShaderTarget(const ShaderTarget target)
{
	switch (target)
	{
	case Vertex:
		return GL_VERTEX_SHADER;
	case Fragment:
		return GL_FRAGMENT_SHADER;
	default:
		return 0;
	}
}

const int EnumConverter::GetColorCode(const ColorCode code)
{
	switch (code)
	{
	case Mono:
		return GL_LUMINANCE;
	case Rgb:
		return GL_RGB;
	case Rgba:
		return GL_RGBA;
	default:
		return 0;
	}
}

const int EnumConverter::GetPrimitiveType(const PrimitiveType type)
{
	switch (type)
	{
	case Triangles:
		return GL_TRIANGLES;
	case Lines:
		return GL_LINES;
	case Points:
		return GL_POINTS;
	case LineStrips:
		return GL_LINE_STRIP;
	case Quads:
		return GL_QUADS;
	case LineLoops:
		return GL_LINE_LOOP;
	case QuadStrips:
		return GL_QUAD_STRIP;
	case Polygons:
		return GL_POLYGON;
	default:
		return 0;
	}
}

const int EnumConverter::GetValueType(const ValueType type)
{
	switch (type)
	{
	case UnsginedShort:
		return GL_UNSIGNED_SHORT;
	case UnsignedInt:
		return GL_UNSIGNED_INT;
	case UnsignedByte:
		return GL_UNSIGNED_BYTE;
	default:
		return 0;
	}
}

const int EnumConverter::GetWindingOrder(const WindingOrder order)
{
	switch (order)
	{
	case Clockwise:
		return GL_CW;
	case CounterClockwise:
		return GL_CCW;
	default:
		return 0;
	}
}

#ifdef S3_DEBUG

void APIENTRY openglCallbackFunction(
	GLenum source,
	GLenum type,
	GLuint ID,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (ID == 131169 || ID == 131185 || ID == 131218 || ID == 131204) return;

	(void)source; (void)type; (void)ID;
	(void)severity; (void)length; (void)userParam;

	GLchar* errTpText;
	GLchar* srcText;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:				srcText = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		srcText = "window system"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	srcText = "shader compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:		srcText = "third party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:		srcText = "application"; break;
	case GL_DEBUG_SOURCE_OTHER:				srcText = "other"; break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               errTpText = "error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: errTpText = "deprecated behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  errTpText = "undefined behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         errTpText = "portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         errTpText = "performance"; break;
	case GL_DEBUG_TYPE_MARKER:              errTpText = "marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          errTpText = "push group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           errTpText = "pop group"; break;
	case GL_DEBUG_TYPE_OTHER:               errTpText = "other"; break;
	}

	s3dge::LOG_OPENGL_ISSUE("(source - ", srcText, ", type - ", errTpText, ")\nmessage - ", message);
	if (severity == GL_DEBUG_SEVERITY_HIGH)
		abort();
}

#endif