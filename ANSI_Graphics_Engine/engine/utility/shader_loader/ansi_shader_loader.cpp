#include "ansi_shader_loader.h"

#include "core/log/ansi_log.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	enum class ShaderType {
		Vertex,
		Fragment,
	};

	bool ShaderLoader::Load(const std::string & filePath, unsigned & shaderId)
	{
		AN_CHECK_LOG(shaderId = glCreateProgram());

		unsigned vsId{ 0 }, fsId{ 0 };
		std::string vsSource, fsSource;

		AN_CHECK(ParseShader(filePath, vsSource, fsSource));
		AN_CHECK(CompileShader(GL_VERTEX_SHADER, vsSource, vsId));
		AN_CHECK(CompileShader(GL_FRAGMENT_SHADER, fsSource, fsId));

		GL_CHECK(glAttachShader(shaderId, vsId));
		GL_CHECK(glAttachShader(shaderId, fsId));
		GL_CHECK(glLinkProgram(shaderId));
		GL_CHECK(glValidateProgram(shaderId));

		GL_CHECK(glDeleteShader(vsId));
		GL_CHECK(glDeleteShader(fsId));

		return true;
	}

	bool ShaderLoader::ParseShader(const std::string & filePath, std::string & vsSource, std::string & fsSource)
	{
		std::ifstream stream(filePath);
		std::string line;
		std::stringstream streams[2];
		ShaderType type{ ShaderType::Vertex };

		AN_CHECK_LOG_M(stream.good(), L"잘못된 Shader 파일 경로: " + Converter::ToUnicode(filePath));
		while (getline(stream, line))
		{
			if (line.find("shader_vertex") != std::string::npos) { type = ShaderType::Vertex; }
			else if (line.find("shader_fragment") != std::string::npos) { type = ShaderType::Fragment; }
			else { streams[static_cast<unsigned>(type)] << line << '\n'; }
		}

		vsSource = streams[static_cast<unsigned>(ShaderType::Vertex)].str();
		fsSource = streams[static_cast<unsigned>(ShaderType::Fragment)].str();

		return true;
	}

	bool ShaderLoader::CompileShader(unsigned type, const std::string & source, unsigned & shaderId)
	{
		AN_CHECK_LOG(shaderId = glCreateShader(type));
		const char * src{ source.c_str() };
		GL_ERROR_LOG(glShaderSource(shaderId, 1, &src, nullptr));
		GL_ERROR_LOG(glCompileShader(shaderId));

		int result{ 0 };
		GL_ERROR_LOG(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length{ 0 };
			GL_ERROR_LOG(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));
			char * message{ new char[length] };

			GL_ERROR_LOG(glGetShaderInfoLog(shaderId, length, &length, message));
			Core::GetLog()->WriteSpace(L"Failed:");
			Core::GetLog()->WriteSpace((type == GL_VERTEX_SHADER) ? L"Vertex" : L"Fragment");
			Core::GetLog()->WriteLine(L"shader compilation.");
			Core::GetLog()->WriteLine(Converter::ToUnicode(message));

			delete[] message;
			GL_ERROR_LOG(glDeleteShader(shaderId));
			return false;
		}

		return true;
	}

}
