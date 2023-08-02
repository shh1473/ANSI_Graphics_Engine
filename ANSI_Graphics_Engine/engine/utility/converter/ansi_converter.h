#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_type.h"

namespace AN
{
	class Converter
	{
	public:
		static std::wstring ToUnicode(const std::string & string);
		static std::wstring ToUnicode(const char * c_str);
		static std::wstring ToUnicode(const unsigned char * c_str);

		static std::string ToAscii(const std::wstring & string);
		static std::string ToAscii(const wchar_t * w_str);

		static std::wstring TinyXMLErrorToString(int error);

		static glm::quat EulerToQuat(const glm::vec3 & rotation, EulerOrder order);

	private:
		explicit Converter() = delete;

	};

}
