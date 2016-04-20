#ifndef __WRITE_RS__
#define __WRITE_RS__

bool write_rs(
		_In_ const std::vector<double>& periods, 
		_In_ const std::vector<double>& spec_acc, 
		_In_ const char* file_name);

#endif // __WRITE_RS__
