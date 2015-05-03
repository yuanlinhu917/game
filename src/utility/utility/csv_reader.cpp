#include "csv_reader.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sstream>

using std::string;

void CsvReader::read_file(const std::string& file_name)
{
	std::ifstream inFile(file_name.c_str());
	if (!inFile)
	{
		return ;
	}
	string strLine;

	//Person per;
	//vector<Person> personVec;
	//vector<Person>::iterator iter;
	//char tmp;

	while (!inFile.eof())
	{
		getline(inFile, strLine);
		std::stringstream stream(strLine);
		//stream >> per.id;
		//stream >> tmp;
		//stream >> per.name;
		//stream >> tmp; //这样不行
		//stream >> per.age;
		//personVec.push_back(per);
	}
}

CsvData* CsvReader::get_csv_data(int index)
{
	return NULL;
}