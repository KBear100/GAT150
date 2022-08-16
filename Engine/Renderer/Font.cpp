#include "Font.h"
#include "Core/Logger.h"
#include "Core/File.h"
#include <SDL_ttf.h>

namespace Bear
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont != NULL)
		{
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Create(std::string filename, ...)
	{
		if (!FileExists(filename))
		{
			LOG("Error could not create file $s", filename.c_str());
			return false;
		}

		return true;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	}
}