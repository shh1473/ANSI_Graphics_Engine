#pragma once

#include "tinyxml2/tinyxml2.h"
#include "common/ansi_common.h"

namespace AN
{
	class XML
	{
	protected:
		using ElementPair = std::pair<tinyxml2::XMLElement *, std::string>;
		
		explicit XML(const std::string & filePath);

		void Open();
		bool Load();
		bool Apply();
		void PushElement(ElementPair * elementPair);

	private:
		std::string	m_filePath;
		tinyxml2::XMLDocument m_document;
		tinyxml2::XMLElement * m_root;
		std::vector<ElementPair *> m_elements;

	};

}
