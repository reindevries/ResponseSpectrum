#ifndef __CALC_RS__
#define __CALC_RS__

bool calc_rs(
		_In_ const std::vector<double>& acc_data, 
		_In_ double timestep,
		_In_ const std::vector<double>& periods,
		_Out_ std::vector<double>& spec_acc,
		_In_ double damping_ratio = 0.05,
		_In_ double calculation_dt = 5e-4);

#endif // __CALC_RS__
