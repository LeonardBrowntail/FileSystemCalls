#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(void)
{
	//Opening file with fstream
	std::ifstream source;
	source.open("source.txt", std::ios::in);
	if (!source.is_open())
	{
		std::cout << "File cannot be opened, aborting...";
		std::exit(-1);
	}
	else
	{
		std::string header;
		std::string header2;
		std::vector<std::string> texts;
		std::string t;

		//Get title
		std::getline(source, header);

		//Get header
		std::getline(source, t, '\t');
		header2 += t + ',';
		std::getline(source, t, '\t');
		header2 += t + ',';
		std::getline(source, t, '\t');
		header2 += t + ',';
		std::getline(source, t, '\n');
		header2 += t;

		//Get data
		int num = 0;
		while (source)
		{
			num += 1;
			std::string str;
			std::getline(source, t, '\t');
			str += std::to_string(num) + ',';
			std::getline(source, t, '\t');
			str += t + ',';
			std::getline(source, t, '\t');
			str += t + ',';
			std::getline(source, t, '\n');
			str += t;
			texts.push_back(str);
		}
		//Closing the file as it is no longer needed
		source.close();

		//Overshoot handling
		texts.pop_back();
		num = texts.size();
		std::cout << num << "\n";

		//Write reverse
		int rnum = num * 2;
		while (num < rnum)
		{
			num++;
			std::string str;
			str = std::to_string(num) + ',' + texts[(rnum - num)].substr(texts[(rnum - num)].find(',') + 1);
			texts.push_back(str);
		}

		//Display
		std::cout << header << "\n\n" << header2 << "\n\n";
		for (auto i = texts.begin(); i != texts.end(); i++)
		{
			std::cout << *i << "\n\n";
		}

		//Write into .csv
		std::ofstream output;
		output.open("Data.csv", std::ios::out | std::ios::trunc);
		output << header << std::endl;
		output << header2 << std::endl;
		for (auto i = texts.begin(); i != texts.end(); i++)
		{
			output << *i << std::endl;
		}
		output.close();
	}
}