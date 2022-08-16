#pragma once
#include <string>

namespace Bear
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;
	};
}