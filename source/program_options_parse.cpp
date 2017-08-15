#include "headers/program_options_parse.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

bool po_parse(const int argc, char* argv[], std::string& config_path)
{
	po::options_description general_options("General options");
	general_options.add_options()
		("help,h", "Show help")
		("config_path,c", po::value<std::string>(&config_path)->required(), "Enter path to the configuration file and the full file name");

	po::variables_map vm;

	try 
	{
		po::store(po::parse_command_line(argc, argv, general_options), vm);

		if(vm.count("help"))
		{
			std::cout << general_options << std::endl;
			std::cerr << "Entered the help option" << std::endl;
			return false;
		}

		po::notify(vm);
	}
	catch(boost::program_options::error ec)
	{
		std::cerr << "Can't parse command line: " << ec.what() << std::endl;
		return false;
	}
	catch(std::exception ex)
	{
		std::cerr << "Can't parse command line: " << ex.what() << std::endl;
		return false;
	}

	return true;
}
