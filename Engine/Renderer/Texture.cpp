#include "Texture.h"
#include "Renderer\Renderer.h"
#include "Core\Logger.h"
#include <SDL.h>
#include <SDL_image.h>

namespace Bear
{
	Texture::~Texture()
	{
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}
	}

	bool Texture::Create(std::string name, ...)
	{
		va_list args;
		va_start(args, name);
		Renderer& renderer = va_arg(args, Renderer);
		va_end(args);

		return Create(renderer, name);
	}

	bool Texture::Create(Renderer& renderer, const std::string& filename)
	{
		// load surface
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (surface == nullptr)
		{
			LOG(SDL_GetError());
			return false;
		}

		//create texture
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (m_texture == nullptr)
		{
			LOG(SDL_GetError());
			SDL_FreeSurface(surface);

			return false;
		}

		SDL_FreeSurface(surface);

		return true;
	}

	bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
	{
		if (m_texture) SDL_DestroyTexture(m_texture);

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

		SDL_FreeSurface(surface);

		if (m_texture == nullptr)
		{
			LOG(SDL_GetError());
			return false;
		}

		return true;
	}

	Vector2 Texture::GetSize() const
	{
		SDL_Point point;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &(point).x, &(point).y);

		return Vector2(point.x, point.y);
	}
}
