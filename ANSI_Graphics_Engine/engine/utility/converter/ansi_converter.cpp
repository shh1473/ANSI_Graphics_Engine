#include "ansi_converter.h"

#include "tinyxml2/tinyxml2.h"
#include "core/ansi_core.h"
#include "core/log/ansi_log.h"

namespace AN
{
	std::wstring Converter::ToUnicode(const std::string & string)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(string);
	}

	std::wstring Converter::ToUnicode(const char * c_str)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(c_str);
	}

	std::wstring Converter::ToUnicode(const unsigned char * c_str)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(reinterpret_cast<const char *>(c_str));
	}

	std::string Converter::ToAscii(const std::wstring & string)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(string);
	}

	std::string Converter::ToAscii(const wchar_t * w_str)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(w_str);
	}

	std::wstring Converter::TinyXMLErrorToString(int error)
	{
		switch (error)
		{
			case tinyxml2::XML_NO_ATTRIBUTE:                   return L"XML_NO_ATTRIBUTE";
			case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:           return L"XML_WRONG_ATTRIBUTE_TYPE";
			case tinyxml2::XML_ERROR_FILE_NOT_FOUND:           return L"XML_ERROR_FILE_NOT_FOUND";
			case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED: return L"XML_ERROR_FILE_COULD_NOT_BE_OPENED";
			case tinyxml2::XML_ERROR_FILE_READ_ERROR:          return L"XML_ERROR_FILE_READ_ERROR";
			case tinyxml2::XML_ERROR_PARSING_ELEMENT:          return L"XML_ERROR_PARSING_ELEMENT";
			case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:        return L"XML_ERROR_PARSING_ATTRIBUTE";
			case tinyxml2::XML_ERROR_PARSING_TEXT:             return L"XML_ERROR_PARSING_TEXT";
			case tinyxml2::XML_ERROR_PARSING_CDATA:            return L"XML_ERROR_PARSING_CDATA";
			case tinyxml2::XML_ERROR_PARSING_COMMENT:          return L"XML_ERROR_PARSING_COMMENT";
			case tinyxml2::XML_ERROR_PARSING_DECLARATION:      return L"XML_ERROR_PARSING_DECLARATION";
			case tinyxml2::XML_ERROR_PARSING_UNKNOWN:          return L"XML_ERROR_PARSING_UNKNOWN";
			case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:           return L"XML_ERROR_EMPTY_DOCUMENT";
			case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:       return L"XML_ERROR_MISMATCHED_ELEMENT";
			case tinyxml2::XML_ERROR_PARSING:                  return L"XML_ERROR_PARSING";
			case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:           return L"XML_CAN_NOT_CONVERT_TEXT";
			case tinyxml2::XML_NO_TEXT_NODE:                   return L"XML_NO_TEXT_NODE";
			case tinyxml2::XML_ELEMENT_DEPTH_EXCEEDED:         return L"XML_ELEMENT_DEPTH_EXCEEDED";
			default:
			{
				AN_ERROR_LOG(L"존재하지 않는 열거형을 사용했습니다.");
				return L"XML_UNKNOWN";
			}
		}
	}

}
