#include "ShaderProgram.h"
#include "Utilities/Log.h"

namespace S3DGE
{
	namespace Graphics
	{
		ShaderProgram::ShaderProgram(const char* vertex, const char* fragment)
			: m_Vertex(vertex), m_Fragment(fragment)
		{
			m_ProgramID = Load();
		}

		ShaderProgram::~ShaderProgram()
		{
			glDeleteProgram(m_ProgramID);
		}

		uint ShaderProgram::Load()
		{
			int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			std::string vertexSource = FileIO::ReadFromFile(m_Vertex).c_str();
			if (vertexSource == "")
			{
				LOG_ERROR("Cannot find vertex shader source");
				return -1;
			}
			const char* vSource = vertexSource.c_str();
			glShaderSource(vertexShader, 1, &vSource, NULL);
			if (!Compile(vertexShader))
				return -1;

			int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			std::string fragmentSource = FileIO::ReadFromFile(m_Fragment).c_str();
			if (fragmentSource == "")
			{
				LOG_ERROR("Cannot find fragment shader source");
				return -1;
			}
			const char* fSource = fragmentSource.c_str();
			glShaderSource(fragmentShader, 1, &fSource, NULL);
			if (!Compile(fragmentShader))
				return -1;

			int program = glCreateProgram();

			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			//// Perform the linking process
			//glLinkProgram(program);

			//// Check the status
			//int linkStatus;
			//glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
			//if (linkStatus == GL_FALSE)
			//{
			//	LOG_ERROR("Shader program linking failed.");
			//	return -1;
			//}

			return program;
		}

		bool ShaderProgram::Compile(int shader)
		{
			// Compile the shader
			glCompileShader(shader);

			// Check the compilation status and report any errors
			int shaderStatus;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderStatus);

			// If the shader failed to compile, display the info log and quit out
			if (shaderStatus == GL_FALSE)
			{
				GLint infoLogLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

				char *strInfoLog = new char[infoLogLength + 1];
				glGetShaderInfoLog(shader, infoLogLength, 0, strInfoLog);

				LOG_ERROR("shader compilation failed: ", strInfoLog);
				delete[] strInfoLog;
				glDeleteShader(shader);
				return false;
			}

			return true;
		}

		void ShaderProgram::Enable()
		{
			glUseProgram(m_ProgramID);
		}

		void ShaderProgram::Disable()
		{
			glUseProgram(0);
		}

		void ShaderProgram::SetUniform1f(const char* name, float value)
		{
			glUniform1f(glGetUniformLocation(m_ProgramID, name), value);
		}

		void ShaderProgram::SetUniform2f(const char* name, Maths::vec2f value)
		{
			glUniform2f(glGetUniformLocation(m_ProgramID, name), value.x, value.y);
		}

		void ShaderProgram::SetUniform3f(const char* name, Maths::vec3f value)
		{
			glUniform3f(glGetUniformLocation(m_ProgramID, name), value.x, value.y, value.z);
		}

		void ShaderProgram::SetUniform4f(const char* name, Maths::vec4f value)
		{
			glUniform4f(glGetUniformLocation(m_ProgramID, name), value.x, value.y, value.z, value.w);
		}

		void ShaderProgram::SetUniform1i(const char* name, int value)
		{
			glUniform1i(glGetUniformLocation(m_ProgramID, name), value);
		}
	}
}