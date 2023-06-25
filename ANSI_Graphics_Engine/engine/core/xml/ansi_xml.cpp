#include "ansi_xml.h"

#include "core/ansi_core.h"
#include "core/log/ansi_log.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	XML::XML(const std::string & filePath) :
		m_filePath(filePath),
		m_document(),
		m_root(nullptr),
		m_elements()
	{

	}

	void XML::Open()
	{
		m_root = m_document.NewElement("ansi_graphics_engine_config");
		m_document.LinkEndChild(m_root);
	}

	bool XML::Load()
	{
		tinyxml2::XMLError error{ m_document.LoadFile(m_filePath.c_str()) };
		AN_CHECK_LOG_M(error == tinyxml2::XML_SUCCESS, L"[XML Error]: " + Converter::TinyXMLErrorToString(error));

		m_root = m_document.FirstChildElement();
		for (auto iter : m_elements)
		{
			iter->first = m_root->FirstChildElement(iter->second.c_str());
		}
		return true;
	}

	bool XML::Apply()
	{
		tinyxml2::XMLError error{ m_document.SaveFile(m_filePath.c_str()) };
		AN_CHECK_LOG_M(error == tinyxml2::XML_SUCCESS, L"[XML Error]: " + Converter::TinyXMLErrorToString(error));

		return true;
	}

	void XML::PushElement(ElementPair * elementPair)
	{
		elementPair->first = m_document.NewElement(elementPair->second.c_str());

		m_root->LinkEndChild(elementPair->first);

		m_elements.push_back(elementPair);
	}

}
