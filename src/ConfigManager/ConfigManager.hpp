//
// Created by regex on 11.09.2018.
//

#ifndef BOILERPLATE_CONFIGMANAGER_HPP
#define BOILERPLATE_CONFIGMANAGER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <sstream>

class ConfigManager
{
private:

	// Singleton private functions

	/**
	 * Singleton object to be returned.
	 */
	static ConfigManager *configManager;

	/**
	 * Private constructor to prevent creating new instances.
	 */
	ConfigManager();

	// ConfigManager private functions.

	/**
	 * Converts string value to wanted type.
	 * @tparam T Type to be returned as.
	 * @param value String value to be returned as requested type.
	 * @return T equivalent (requested type) of given string
	 */
	template<typename T>
	T convertStringToType(const std::string &value) const;

	/**
	 * Converts any given value to string
	 * @tparam T Given value type
	 * @param value Given T type value
	 * @return String equivalent of given T type value.
	 */
	template<typename T>
	std::string convertToString(const T value) const;

	/**
	 * Opens and reads config file.
	 * @return true if able to read config file.
	 */
	bool read();

	/**
	 * Writes changes in _data to config file.
	 * @return true if writing is successful.s
	 */
	bool write() const;

	/**
	 * Helper function for write(). Creates a key-value pair from one line.
	 * @param line Given line to be converted to string:string key-value pair
	 * @return string:string key-value pair from given line
	 */
	std::pair<std::string, std::string> parseLine(const std::string &line) const;

	/**
	 * Whether the new value is set. Set true if set() function is used.
	 */
	bool _isChanged;

	/**
	 * Config file name. Declared when called loadFile().
	 */
	std::string _filename;

	/**
	 * Holds key-value pairs of config file.
	 */
	std::map<std::string, std::string> _data;

	/**
	 * Localization settings of the current computer.
	 */
	const std::locale _locale;


public:

	// Singleton public functions.

	/**
	 * Function to create ConfigManager object if does not exist.
	 * @return ConfigManager object.
	 */
	static ConfigManager *instance();

	/**
	 * Destructor.
	 */
	~ConfigManager();

	// ConfigManager public functions

	/**
	 * Getter function to find out whether the config file is changed.
	 * @return true if the config file has changed.
	 */
	bool isChanged() const;

	/**
	 * Loads file to memory.
	 * @param filename Full file path.
	 * @return true if file has read successfully.
	 */
	bool loadFile(const std::string &filename);

	/**
	 * Writes changes to loaded file.
	 * @return true if writing process was successful.
	 */
	bool writeFile();

	/**
	 * Gets a value from loaded file.
	 * @tparam T Variable type of value to be returned.
	 * @param key Value ID.
	 * @param value to be returned.
	 */
	template<typename T>
	void get(const std::string &key, const T &value) const;

	/**
	 * Gets a vector from loaded file.
	 * @tparam T Variable type of value to be returned.
	 * @param key Value ID.
	 * @param value to be returned.
	 */
	template<typename T>
	void get(const std::string &key, const std::vector<T> value) const;

	/**
	 * Declare a new value to a key if exist, creates otherwise.
	 * @tparam T Type of value to be declared.
	 * @param key Key to be set value of.
	 * @param value T type value to be set to given key.
	 */
	template<typename T>
	void set(const std::string &key, const T value);

	/**
	 * Declare a new vector to a key if exist, creates otherwise.
	 * @tparam T Type of vector value to be declared.
	 * @param key Key to be set value of.
	 * @param value Vector value to be set to given key.
	 */
	template<typename T>
	void set(const std::string &key, const std::vector<T> value);

	/**
	 * Prints out the _data vector with standart output. Used for testing purposes..
	 */
	void print() const;
};

#endif //BOILERPLATE_CONFIGMANAGER_HPP
