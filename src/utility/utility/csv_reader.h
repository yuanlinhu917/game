

#ifndef _CSV_READER_H_
#define _CSV_READER_H_

#include <string>
#include <vector>
#include "csv_data.h"

class CsvReader
{
public:
	void read_file(const std::string& file_name);

	CsvData*	get_csv_data(int index);



private:
	std::vector<CsvData>	m_csv_data;
};

#endif