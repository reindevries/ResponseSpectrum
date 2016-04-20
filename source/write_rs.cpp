#include "pch.hpp"
#include "write_rs.hpp"

bool write_rs(
		_In_ const std::vector<double>& periods, 
		_In_ const std::vector<double>& spec_acc, 
		_In_ const char* file_name)
{
	using namespace std;

	if (periods.size() != spec_acc.size())
		return false;

	ofstream file(file_name);

	if (!file.is_open())
		return false;

	file << "T [s],PSa [m/s^2]" << endl;
	for (size_t i = 0; i < periods.size(); ++i)
		file << periods[i] << "," << spec_acc[i] << endl;

	return true;
}
