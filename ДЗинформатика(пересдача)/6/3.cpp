#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>

void print_last_write_time (std::filesystem::file_time_type const& ftime)
{
	std::time_t cftime = std::chrono::system_clock::to_time_t(std::chrono::utc_clock::to_sys(std::chrono::file_clock::to_utc(ftime)));

	std::cout << std::asctime(std::localtime(&cftime));
};

void view_directory(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		std::cout << std::setw(40)<< std::left << "Filename:" << std::setw(20) << "Extension:"<<std::setw(23)<< "Last write time:" << std::endl;

		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();

			auto type = entry.path().extension().string();

			auto ftime = std::filesystem::last_write_time(entry.path());

			std::cout << std::setw(40) << file_name << std::setw(20) << type;;

			print_last_write_time(ftime);

		}
	}
}

int main(int argc, char** argv)
{
	system("chcp 1251");

	std::string str_path;

	std::cin >> str_path;

	const std::filesystem::path path(str_path);

	view_directory(path);

	return 0;
}