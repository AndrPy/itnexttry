#include<fstream>
#include<iostream>
#include<string>

int main()
{
	int line_length;

	int line_number;

	std::string line;

	std::fstream file("file.txt", std::ios::in);

	/*for (auto i = 0; i < 10; ++i)
	{
		for (auto j = 0; j < 5; ++j)
		{
			file << i;
		}

		file << '\n';

	}*/

	std::getline(file, line);

	line_length = line.length()+2;

	std::cin >> line_number;

	file.seekg(line_number*line_length);

	std::getline(file, line);

	std::cout << line;

	return 0;

}