//
// Created by regex on 11.09.2018.
//

#include <string>
#include <locale>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "ConfigManager.hpp"
#include "../Logger/Logger.hpp"

ConfigManager *ConfigManager::configManager = NULL;

ConfigManager::ConfigManager() : _isChanged(false)
{

}

ConfigManager::~ConfigManager()
{
	writeFile();
	configManager = NULL;
}

ConfigManager *ConfigManager::instance()
{
	if (configManager == NULL)
	{
		configManager = new ConfigManager();
	}
	return configManager;
}

bool ConfigManager::loadFile(const std::string &filename)
{
	_data.clear();
	_filename = filename;
	return read();
}

bool ConfigManager::writeFile()
{
	if (_isChanged)
	{
		_isChanged = false;
		return write();
	}
	return true;
}


bool ConfigManager::read()
{
	std::ifstream in(_filename);

	if (!in.is_open())
	{
		LOG_FATAL("Could not read config file: " << _filename);
		return false;
	}

	std::string line;
	while (std::getline(in, line))
	{
		std::pair<std::string, std::string> keyValuePair = parseLine(line);

		if (!keyValuePair.first.empty())
		{
			_data[keyValuePair.first] = keyValuePair.second;
		}
	}

	in.close();
	_isChanged = false;
	return true;
}

bool ConfigManager::write() const
{
	std::vector<std::pair<std::string, std::string>> fileData;

	std::ifstream in(_filename);

	if (in.is_open())
	{
		std::string line;
		while (std::getline(in, line))
		{
			std::pair<std::string, std::string> keyValuePair = parseLine(line);

			if (!keyValuePair.first.empty())
			{
				auto it = _data.find(keyValuePair.first);
				if (it != _data.end())
				{
					keyValuePair.second = it->second;
				}
			}
			else
			{
				keyValuePair.first = line;
			}
			fileData.push_back(keyValuePair);
		}
	}
	else
	{
		for (auto it = _data.begin(); it != _data.end(); ++it)
		{
			fileData.push_back(std::make_pair(it->first, it->second));
		}
	}

	in.close();

	std::ofstream out(_filename);
	if (!out.is_open())
	{
		LOG_ERROR("Could not open config file [" << _filename << "] for writing!");
		return false;
	}
	for (auto it = fileData.begin(); it != fileData.end(); ++it)
	{
		out << it->first;

		if (!it->second.empty())
		{
			out << " = " << it->second;
		}

		out << std::endl;
	}
	out.close();
	return true;
}

std::pair<std::string, std::string> ConfigManager::parseLine(const std::string &line) const
{
	if(line.size() > 0 && line[0] != '#')
	{
		size_t index = 0;

		while(std::isspace(line[index], _locale))
			index++;

		const size_t beginKeyString = index;
		while(!std::isspace(line[index], _locale) && line[index] != '=')
			index++;

		const std::string key = line.substr(beginKeyString, index - beginKeyString);

		while(std::isspace(line[index], _locale) || line[index] == '=')
			index++;

		const std::string value = line.substr(index, line.size() - index);

		return std::make_pair(key, value);
	}

	return std::make_pair(std::string(), std::string());
}

bool ConfigManager::isChanged() const
{
	return _isChanged;
}

void ConfigManager::print() const
{
	std::cout << "Data size: " << _data.size() << std::endl;
	std::cout << std::endl;

	for(auto &i : _data)
	{
		std::cout << i.first << " : " << i.second << std::endl;
	}
}

template<typename T>
inline std::string ConfigManager::convertToString(const T value) const
{
	LOG_ERROR("Unsupported type supplied.");
	throw "Unsupported type supplied.";
}

template<>
inline std::string ConfigManager::convertToString<std::string>(std::string value) const
{
	return value;
}

template<>
inline std::string ConfigManager::convertToString<const char *>(const char *value) const
{
	return std::string(value);
}

template<>
inline std::string ConfigManager::convertToString<bool>(bool value) const
{
	return value ? "TRUE" : "FALSE";
}

template<>
inline std::string ConfigManager::convertToString<char>(char value) const
{
	std::string str;
	str = value;
	return str;
}

template<>
inline std::string ConfigManager::convertToString<int>(int value) const
{
	std::stringstream strstream;
	strstream << value;
	return strstream.str();
}

template<>
inline std::string ConfigManager::convertToString<unsigned int>(unsigned int value) const
{
	std::stringstream strstream;
	strstream << value;
	return strstream.str();
}

template<>
inline std::string ConfigManager::convertToString<short>(short value) const
{
	std::stringstream strstream;
	strstream << value;
	return strstream.str();
}

template<>
inline std::string ConfigManager::convertToString<long>(long value) const
{
	std::stringstream strstream;
	strstream << value;
	return strstream.str();
}

template<>
inline std::string ConfigManager::convertToString<unsigned long>(unsigned long value) const
{
	std::stringstream strstream;
	strstream << value;
	return strstream.str();
}

template<>
inline std::string ConfigManager::convertToString<float>(float value) const
{
	std::stringstream strstream;
	strstream << value;
	return strstream.str();
}

template<>
inline std::string ConfigManager::convertToString<double>(double value) const
{
	std::stringstream strstream;
	strstream << value;
	return strstream.str();
}

template<typename T>
inline T ConfigManager::convertStringToType(const std::string &value) const
{
	LOG_ERROR("Unconvertable type supplied.");
	throw "Unconvertable type supplied.";
}

template<>
inline bool ConfigManager::convertStringToType<bool>(const std::string &value) const
{
	if (value == "TRUE")
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<>
inline int ConfigManager::convertStringToType<int>(const std::string &value) const
{
	int retval;
	std::stringstream strStream(value);
	strStream >> retval;

	return retval;
}

template<>
inline unsigned int ConfigManager::convertStringToType<unsigned int>(const std::string &value) const
{
	unsigned int retval;
	std::stringstream strStream(value);
	strStream >> retval;

	return retval;
}

template<>
inline double ConfigManager::convertStringToType<double>(const std::string &value) const
{
	double retval;
	std::stringstream strStream(value);
	strStream >> retval;

	return retval;
}

template<>
inline float ConfigManager::convertStringToType<float>(const std::string &value) const
{
	float retval;
	std::stringstream strStream(value);
	strStream >> retval;

	return retval;
}

template<>
inline short ConfigManager::convertStringToType<short>(const std::string &value) const
{
	short retval;
	std::stringstream strStream(value);
	strStream >> retval;

	return retval;
}

template<>
inline long ConfigManager::convertStringToType<long>(const std::string &value) const
{
	long retval;
	std::stringstream strStream(value);
	strStream >> retval;

	return retval;
}

template<>
inline unsigned long ConfigManager::convertStringToType<unsigned long>(const std::string &value) const
{
	unsigned long retval;
	std::stringstream strStream(value);
	strStream >> retval;

	return retval;
}

template<>
inline char ConfigManager::convertStringToType<char>(const std::string &value) const
{
	return value[0];
}

template<>
inline std::string ConfigManager::convertStringToType<std::string>(const std::string &value) const
{
	return value;
}

template<typename T>
inline void ConfigManager::get(const std::string &key, const T &value) const
{
	auto iterator = _data.find(key);

	if (iterator != _data.end())
	{
		value = convertStringToType<T>(iterator->second);
	}
}

template<typename T>
inline void ConfigManager::get(const std::string &key, const std::vector<T> value) const
{
	auto iterator = _data.find(key);

	if (iterator != _data.end())
	{
		std::string output;
		std::istringstream parser(iterator->second);

		value.clear();

		while (std::getline(parser, output, ','))
		{
			value.push_back(convertStringToType<T>(output));
		}
	}
}

template<typename T>
inline void ConfigManager::set(const std::string &key, const T value)
{
	_data[key] = convertToString<T>(value);
	_isChanged = true;
}

template<typename T>
inline void ConfigManager::set(const std::string &key, const std::vector<T> value)
{
	std::string valueAsString;

	for (size_t i = 0; i < value.size() - 1; ++i)
	{
		valueAsString += convertToString<T>(value.at(i)) + ",";
	}

	valueAsString += convertToString<T>(value.back());

	_data[key] = valueAsString;
	_isChanged = true;
}

