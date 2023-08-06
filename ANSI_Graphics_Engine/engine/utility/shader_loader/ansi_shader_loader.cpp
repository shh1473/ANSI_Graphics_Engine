#include "ansi_shader_loader.h"

#include "core/log/ansi_log.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	bool ShaderLoader::Load(const std::string & filePath, unsigned & shaderId)
	{
		AN_CHECK_LOG(shaderId = glCreateProgram());

		unsigned shaderTypeIndex{ 0 };
		std::vector<unsigned> ids(3, 0);
		std::vector<std::string> sources(3, "");

		AN_CHECK(ParseShader(filePath, sources));

		/* === Vertex === */
		shaderTypeIndex = static_cast<unsigned>(ShaderType::Vertex);
		AN_CHECK(CompileShader(GL_VERTEX_SHADER, sources[shaderTypeIndex], ids[shaderTypeIndex]));
		GL_CHECK(glAttachShader(shaderId, ids[shaderTypeIndex]));

		/* === Geometry === */
		shaderTypeIndex = static_cast<unsigned>(ShaderType::Geometry);
		if (sources[shaderTypeIndex] != "") {
			AN_CHECK(CompileShader(GL_GEOMETRY_SHADER, sources[shaderTypeIndex], ids[shaderTypeIndex]));
			GL_CHECK(glAttachShader(shaderId, ids[shaderTypeIndex]));
		}

		/* === Fragment === */
		shaderTypeIndex = static_cast<unsigned>(ShaderType::Fragment);
		AN_CHECK(CompileShader(GL_FRAGMENT_SHADER, sources[shaderTypeIndex], ids[shaderTypeIndex]));
		GL_CHECK(glAttachShader(shaderId, ids[shaderTypeIndex]));

		GL_CHECK(glLinkProgram(shaderId));
		GL_CHECK(glValidateProgram(shaderId));

		for (unsigned i{ 0 }; i < ids.size(); ++i)
		{
			if (ids[i] != 0) { GL_CHECK(glDeleteShader(ids[i])); }
		}

		return true;
	}

	bool ShaderLoader::ParseShader(const std::string & filePath, std::vector<std::string> & sources)
	{
		std::ifstream fileStream(filePath);
		std::string line;
		std::stringstream shaderStreams[3];
		ShaderType type{ ShaderType::Vertex };

		AN_CHECK_LOG_M(fileStream.good(), L"잘못된 Shader 파일 경로: " + Converter::ToUnicode(filePath));
		while (getline(fileStream, line))
		{
			if (line.find("shader_vertex") != std::string::npos) { type = ShaderType::Vertex; }
			else if (line.find("shader_geometry") != std::string::npos) { type = ShaderType::Geometry; }
			else if (line.find("shader_fragment") != std::string::npos) { type = ShaderType::Fragment; }
			else { shaderStreams[static_cast<unsigned>(type)] << line << '\n'; }
		}

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			sources[i] =shaderStreams[i].str();
		}

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
			Core::GetLog()->WriteSpace((type == GL_VERTEX_SHADER) ? L"Vertex" : L"Fragment");
			Core::GetLog()->WriteLine(L"Shader compilation has failed:");
			Core::GetLog()->WriteLine(Converter::ToUnicode(message));

			delete[] message;
			GL_ERROR_LOG(glDeleteShader(shaderId));

			return false;
		}

		return true;
	}

}
