#ifndef __READ_GM__
#define __READ_GM__

bool read_gm(
		_In_ const char* file_name, 
		_Out_ std::vector<double>& acc_data, 
		_Out_ double& timestep);

#endif // __READ_GM__
