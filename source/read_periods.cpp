#include "pch.hpp"
#include "read_periods.hpp"

bool read_periods(
		_In_ const char* file_name, 
		_Out_ std::vector<double>& periods)
{
	using namespace std;

	periods.resize(0);

	ifstream file(file_name);
	
	if (!file.is_open())
		return false;

	string line;

	for (int i = 0; getline(file, line); ++i)
	{
		stringstream ss_val(line);
		double val;
		ss_val >> val;

		if (ss_val.fail())
		{
			if (i == 0)
				continue;
			else
				return false;
		}

		periods.push_back(val);
	}

	return true;
}
