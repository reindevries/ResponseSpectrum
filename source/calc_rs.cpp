#include "pch.hpp"
#include "calc_rs.hpp"
#include "interpolate.hpp"

bool calc_rs(
		_In_ const std::vector<double>& acc_data, 
		_In_ double timestep,
		_In_ const std::vector<double>& periods,
		_Out_ std::vector<double>& spec_acc,
		_In_ double damping_ratio,
		_In_ double calculation_dt)
{
	using namespace std;

	double pi = acos(-1.0);
	double xi = damping_ratio;

	spec_acc.resize(periods.size());

	int done = 0;

	//#pragma omp parallel for
	for (int i = 0; i < int(periods.size()); ++i)
	{
		double T = periods[i];
		double& Sa = spec_acc[i];

		if (abs(T) < 1e-10)  // zero period (PGA)
		{
			Sa = 0.0;
			for (auto&& a : acc_data)
				Sa = max(abs(a), Sa);
		}
		else
		{
			double dt = min(T / 10.0, calculation_dt);

			double omega_0 = 2.0 * pi / T;

			double d_nm1 = 0.0;
			double d_n = 0.0;
				
			double Sd = 0.0;

			for (double t_n = 0.0; t_n < acc_data.size() * timestep; t_n += dt)
			{
				Sd = max(abs(d_n), Sd);

				double a_g_n = interpolate(acc_data, timestep, t_n);
				ASSERT(a_g_n == a_g_n);
			
				double d_np1 = (-a_g_n + (2.0*d_n - d_nm1)/sq(dt) + 2.0*xi*omega_0*d_nm1/(2.0*dt) - 
						sq(omega_0)*d_n) / (1.0/sq(dt) + xi*omega_0/dt);
				ASSERT(d_np1 == d_np1);

				d_nm1 = d_n;
				d_n = d_np1;
			}

			Sa = sq(omega_0) * Sd;
			ASSERT(Sa == Sa);
		}

		//#pragma omp critical
		{
			++done;

			if (done == int(0.25 * periods.size()))
				cout << "25%" << endl;
			else if (done == int(0.5 * periods.size()))
				cout << "50%" << endl;
			else if (done == int(0.75 * periods.size()))
				cout << "75%" << endl;
		}
	}

	cout << "100%" << endl;

	return true;
}
