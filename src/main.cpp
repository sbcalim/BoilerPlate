//
// Created by regex on 02.09.2018.
//
#include "Logger/Logger.hpp"
#include <iostream>
#include <exception>

int main(int argc, char *argv[])
{
	try
	{
		Logger::initFromConfig("../../Logger/logconfig.ini");
	} catch (std::exception &e)
	{
		LOG_ERROR("Exception in main: " << e.what());
		return 1;
	}

	LOG_TRACE("Log trace test");
	LOG_DEBUG("Log debug test");
	LOG_INFO("Log info test");
	LOG_WARN("Log warn test");
	LOG_ERROR("Log error test");
	LOG_FATAL("Log fatal test");
}