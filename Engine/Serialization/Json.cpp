#include "Json.h"
#include "rapidjson/istreamwrapper.h"
#include "Core/Logger.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Math/Rect.h"
#include <fstream>

namespace Bear::json
{
	bool Load(const std::string& filename, rapidjson::Document& document)
	{
		std::ifstream stream(filename);
		if (!stream.is_open())
		{
			LOG("Error opening file %s", filename.c_str());
			return false;
		}

		rapidjson::IStreamWrapper istream(stream);
		document.ParseStream(istream);
		if (document.IsObject() == false)
		{
			LOG("json file cannot be read %s", filename.c_str());
			return false;
		}
		
		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, int& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsInt())
		{
			LOG("Error reading json data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetInt();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, float& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsNumber())
		{
			LOG("Error reading json data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetFloat();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsBool())
		{
			LOG("Error reading json data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetBool();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsString())
		{
			LOG("Error reading json data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetString();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
		{
			LOG("Error Reading json data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				LOG("Error reading json data (not a float) %s", name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			LOG("Error Reading json data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsInt())
			{
				LOG("Error reading json data (not a float) %s", name.c_str());
				return false;
			}
			data[i] = array[i].GetInt();
		}
		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, Rect& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			LOG("Error Reading json data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		data.x = array[0].GetInt();
		data.y = array[1].GetInt();
		data.w = array[2].GetInt();
		data.h = array[3].GetInt();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsArray())
		{
			LOG("Error Reading json data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsString())
			{
				LOG("Error reading json data (not a string) %s", name.c_str());
				return false;
			}
			data.push_back(array[i].GetString());
		}
		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
	{
		if (!value.HasMember(name.c_str())) return false;

		if (!value[name.c_str()].IsArray())
		{
			LOG("Error Reading json data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsInt())
			{
				LOG("Error reading json data (not an int) %s", name.c_str());
				return false;
			}
			data.push_back(array[i].GetInt());
		}
	}
}