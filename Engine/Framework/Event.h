#pragma once
#include <string>
#include <variant>
#include <functional>

namespace Bear
{
	class GameObject;

	class Event
	{
	public:
		using funcionPtr = std::function<void(const Event&)>;

	public:
		std::string name;
		GameObject* receiver = nullptr;
		std::variant<int, bool, float, std::string> data;
	};

	class INotify
	{
	public:
		virtual void OnNotify(const Event& event) = 0;
	};
}