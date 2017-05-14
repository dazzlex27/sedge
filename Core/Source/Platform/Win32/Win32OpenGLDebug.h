/*
===========================================================================
OpenGLDebug.h

Contains callback function for debugging OpenGL errors.
This file is included by the target platform's window implementation.
===========================================================================
*/

#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include "System/Log.h"

void APIENTRY openglCallbackFunction(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	(void)source; (void)type; (void)id;
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

	s3dge::LOG_OPENGL_ISSUE("\nsource = ", srcText, "\ntype = ", errTpText, "\nmessage = ", message);
	if (severity == GL_DEBUG_SEVERITY_HIGH) 
		abort();
}