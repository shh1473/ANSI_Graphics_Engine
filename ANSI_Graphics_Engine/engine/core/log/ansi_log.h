#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Log
	{
	public:
		explicit Log();
		~Log();

		bool Initialize();

		void WriteSpace(const std::wstring & string);
		void WriteLine(const std::wstring & string);
		void NextLine();

		void LineOpen();
		void LineClose();

	private:
		bool m_isGood;
		std::wstring m_fileName;
		std::wofstream m_file;

	};

}
