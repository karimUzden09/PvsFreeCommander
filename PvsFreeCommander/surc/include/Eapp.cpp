// Copright(c) 2019-present, Karim Uzdenov & PVS Free comander & contributs
#include "Eapp.hpp"
#include<iostream>
#include <sstream> 
#include <numeric> 
#include <algorithm> 

Eapp::Eapp(int argc, char** argv)
{
	m_dec.add_options()
		("help,h", "produse help message")
		("curent_path,c", "shwos curent path")
		("finde_cpp,f",po::value<fs::path>(&file_paths)->composing(),"Finde cpp and c filse the specified path and add PVS Free coment")
		("recursive_finde,r",po::value<fs::path>(&catalog_path)->composing(),"Finde cpp an c filse in catalog and add PVS Free coment")
		("delate_coment,d", po::value<fs::path>(&catalog_path)->composing(),"Finde cpp an c filse in catalog and delate PVS Free coment")
		("about,a", "about programm and current version");
	po::store(po::parse_command_line(argc, argv, m_dec), m_vm);
	po::notify(m_vm);
}

int32 Eapp::exec()
{
	if (m_vm.count("help"))
	{
		std::cout << m_dec << std::endl;
		return 1;
	}
	else if (m_vm.count("curent_path"))
	{
		std::cout << fs::current_path() << std::endl;
		return 1;
	}

	else if(m_vm.count("finde_cpp"))
	{
		std::cout << file_paths << std::endl;
		finde_cpp(file_paths);
		return 1;
	}
	else if(m_vm.count("recursive_finde"))
	{
		files_and_folders = { fs::recursive_directory_iterator(catalog_path),
			fs::recursive_directory_iterator() };
		for (const auto& path : files_and_folders)
		{
			if (path.extension().string() == ".cpp")
			{
				std::cout << path.filename() << std::endl;
				add_to_free_coment(path);
			}
			if (path.extension().string() == ".c")
			{
				std::cout << path.filename() << std::endl;
				add_to_free_coment(path);
			}
		}
		spd::info("Done!");
		return 1;
	}
	else if(m_vm.count("delate_coment"))
	{
		files_and_folders = { fs::recursive_directory_iterator(catalog_path),
			fs::recursive_directory_iterator() };
		for (const auto& path : files_and_folders)
		{
			if (path.extension().string()==".cpp")
			{
				std::cout << path.filename() << std::endl;
				delate_comment(path);
			}
			else if (path.extension().string()==".c")
			{
				std::cout << path.filename() << std::endl;
				delate_comment(path);
			}
		}
		spd::info("Delited Donde!");
		return 1;
	}
	else if (m_vm.count("about"))
	{
		spd::info("Welcome to  PVS FREE ADDER ver: {}.{}.{} by Karim Uzdenov(c) 2019", PVS_FREE_COMANDE_VER_MAJOR,
			PVS_FREE_COMANDE_VER_MINOR, PVS_FREE_COMANDE_VER_PATCH);
		return 1;
	}
	else
	{
		spd::error("This is error comand Please, use --help or -h option for information");
		return 1;
	}
	return (SUCES);
}

Eapp::~Eapp()
{
}

void Eapp::finde_cpp(const fs::path& pat)
{
	
		if (fs::exists(pat))
		{
			for (const auto& entry : fs::directory_iterator(pat))
			{
				if (entry.path().extension().string() == ".cpp") {
					std::cout << entry.path().filename().string() << std::endl;
					add_to_free_coment(entry.path());
				}
				if (entry.path().extension().string() == ".c")
				{
					std::cout << entry.path().filename().string() << std::endl;
					add_to_free_coment(entry.path());
				}
				
			}

		}
		else
		{
			spd::error("File path is dose not exisst");
		}
	
}

void Eapp::add_to_free_coment(const fs::path& path_to_cpp_file)
{
	file_push_front(path_to_cpp_file, PVS_Full_coment);
}

void Eapp::delate_comment(const fs::path& path_to_cpp_file)
{
	std::ifstream sup(path_to_cpp_file);
	auto temp_file_name = path_to_cpp_file.string() + "temp";
	std::ofstream temp(temp_file_name);
	string line;
	size_t count = 0;
	while (std::getline(sup, line))
	{
		if (count == 0) {
			if (line != PVS_comment_verefication_1)
			{
				temp << line << std::endl;
			}
			count++;

		}
		else
		{
			if (line != PVS_comment_verefication_2)
			{
				temp << line << std::endl;
			}
		}
	}
	temp.close();
	sup.close();
	auto str = path_to_cpp_file.string();
	const char* p = str.c_str();
	std::remove(p);
	rename(temp_file_name.c_str(), p);
	
}
