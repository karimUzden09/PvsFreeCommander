// Copright(c) 2019-present, Karim Uzdenov & PVS Free comander & contributs
#pragma once
#include<boost/program_options.hpp>
#include<spdlog/spdlog.h>
#include<filesystem>
#include<string>
#include<vector>
#include<stdint.h>
#include <iomanip> 
#include<fstream>
#include"version.h"
using int32 = int32_t;
using string = std::string;
namespace po = boost::program_options;
namespace spd = spdlog;
namespace fs = std::filesystem;
constexpr size_t SUCES = 0;
constexpr size_t RUN_TIME_ERROR = 1;
class Eapp
{
public:
	explicit Eapp(int argv,char** argc);
	int32 exec();
	~Eapp();

private:
	const string PVS_comment_verefication_1{ "// This is a personal academic project. Dear PVS-Studio, please check it." };
	const string PVS_comment_verefication_2{ "// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com" };
	const string PVS_Full_coment{"// This is a personal academic project. Dear PVS-Studio, please check it.\n// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com\n"};
	po::options_description m_dec{ "Main functions" };
	po::variables_map m_vm;
	fs::path file_paths;
	fs::path catalog_path;
	std::vector<fs::path> files_and_folders;
	void finde_cpp(const fs::path& pat);
	void add_to_free_coment(const fs::path& path_to_cpp_file);
	template<class T>
	void file_push_front(const fs::path& path_to_cpp_file, T const& val);
	void delate_comment(const fs::path& path_to_cpp_file);
};

template<class T>
inline void Eapp::file_push_front(const fs::path& path_to_cpp_file, T const& val)
{
	std::fstream file(path_to_cpp_file);
	std::ostringstream sout;

	sout << val << file.rdbuf();
	file.seekg(0);
	file << sout.str();
	file.close();
}
