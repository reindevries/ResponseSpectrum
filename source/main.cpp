#include "pch.hpp"
#include "read_gm.hpp"
#include "read_periods.hpp"
#include "calc_rs.hpp"
#include "write_rs.hpp"

int main(int argc, char* argv[])
{
	using namespace std;

	//
	// If no additional arguments are provided print the help message
	//

	if (argc <= 1)
	{
		//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
		cout << "Obtain the response spectrum for a given accelerogram." << endl;
		cout << endl;
		cout << "ReponseSpectrum [-r response_spectrum] [-p periods] [-d damping_ratio]" << endl;
		cout << "                [-s timestep] [-n threads] ground_motion" << endl;
		cout << endl;
		cout << "  ground_motion      File name of the input accelerogram in CSV-format. If the" << endl;
		cout << "                     name contains spaces it should be put in quotes (\")." << endl;
		cout << endl;
		cout << "  response_spectrum  File name of the output response spectrum in CSV-format. If" << endl;
		cout << "                     the name contains spaces it should be put in quotes (\")." << endl;
		cout << "                     The default is the accelerogram file name appended with" << endl;
		cout << "                     \"_rs\" (excluding the extension)." << endl;
		cout << "  periods            File name of the periods to be used for the response" << endl;
		cout << "                     spectrum in CSV-format. If the name contains spaces it" << endl;
		cout << "                     should be put in quotes (\"). The default is a number of" << endl;
		cout << "                     approximately log-normally spaced periods as commonly used." << endl;
		//cout << "  type               Specifies the type of response spectrum, options are:" << endl;
		//cout << "                       Sa   spectral acceleration" << endl;
		//cout << "                       Sv   spectral velocity" << endl;
		//cout << "                       Sd   spectral displacement" << endl;
		//cout << "                       PSa  pseudo-spectral acceleration (default)" << endl;
		//cout << "                       PSv  pseudo-spectral velocity" << endl;
		cout << "  damping_ratio      The damping ratio to be used for the calculations, the" << endl;
		cout << "                     default is 0.05 (5%)." << endl;
		cout << "  timestep           The maximum timestep to be used for the calculations. Note" << endl;
		cout << "                     that the minimum is defined as dt = T / 10. The default" << endl;
		cout << "                     is set at 5e-4 s." << endl;
		cout << "  threads            Specified the number of concurrent threads that is used for" << endl;
		cout << "                     the calculation of the response spectrum. The default is" << endl;
		cout << "                     the maximum number available on the system." << endl;
		cout << endl;
		cout << "The unit of time is assumed to be in seconds (s) and the unit of acceleration" << endl;
		cout << "in metres per second squared (m/s^2). The output spectrum is the pseudo-" << endl;
		cout << "acceleration response spectrum." << endl;
		
		return -1;
	}

	//
	// Parse command line arguments
	//

	string gm_file_name;
	string rs_file_name;
	string periods_file_name;
	string type = "PSa";
	double damping_ratio = 0.05;
	double calc_timestep = 5e-4;
	int threads = omp_get_max_threads();

	for (int i = 1; i < argc; ++i)
	{
		string argument = argv[i];
		string prev_argument = argv[i-1];

		if (prev_argument.compare("-r") == 0)
			rs_file_name = argument;
		else if (prev_argument.compare("-p") == 0)
			periods_file_name = argument;
		else if (prev_argument.compare("-t") == 0)
			type = argument;
		else if (prev_argument.compare("-d") == 0)
			damping_ratio = stod(argument);
		else if (prev_argument.compare("-s") == 0)
			calc_timestep = stod(argument);
		else if (prev_argument.compare("-n") == 0)
			threads = stoi(argument);
		else if (argument.length() != 2 || argument.compare(0, 1, "-") != 0)
			gm_file_name = argument;
	}

	//
	// Generate name of response spectrum file if not provided
	//

	if (rs_file_name.empty())
	{
		size_t p = gm_file_name.find_last_of('.');

		if (p != string::npos)
		{
			size_t s = gm_file_name.find_last_of("/\\");

			if (s != string::npos && p < s)
				rs_file_name = gm_file_name + "_rs";
			else
				rs_file_name = gm_file_name.substr(0, p) + "_rs" + gm_file_name.substr(p);
		}
		else
			rs_file_name = gm_file_name + "_rs";
	}

	//
	// Set the number of concurrent threads
	//

	omp_set_num_threads(threads);

	//
	// Print the input parameters
	//

	cout << "Input parameters" << endl;
	cout << "----------------" << endl;
	cout << "gm_file_name = " << gm_file_name << endl;
	cout << "rs_file_name = " << rs_file_name << endl;
	cout << "periods_file_name = " << periods_file_name << endl;
	cout << "type = " << type << endl;
	cout << "damping_ratio = " << damping_ratio << endl;
	cout << "calc_timestep = " << calc_timestep << endl;
	cout << "threads = " << threads << endl;
	cout << endl;

	//
	// Read accelerogram
	//

	cout << "Reading ground motion" << endl;
	cout << "---------------------" << endl;
	
	cout << gm_file_name << endl;

	vector<double> acc_data;
	double timestep;
	if (!read_gm(gm_file_name.c_str(), acc_data, timestep) || acc_data.size() == 0)
	{
		cout << "Error reading file." << endl;
		return -3;
	}

	double PGA = 0.0;
	for (auto&& a : acc_data)
		PGA = max(abs(a), PGA);

	cout << "Read " << acc_data.size() << " points" << endl;
	cout << "Timestep is " << timestep << " s" << endl;
	cout << "Record duration is " << (acc_data.size() - 1) * timestep << " s" << endl;
	cout << "PGA is " << PGA << " m/s^2" << endl;
	cout << endl;
	
	//
	// Open periods file name if provided, otherwise initialise vector with default
	//

	cout << "Reading periods" << endl;
	cout << "---------------" << endl;

	vector<double> periods;

	if (periods_file_name.empty())
	{
		cout << "Period file not specified, using default." << endl;
		periods = {0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.075, 0.1, 0.11, 0.12, 0.13, 
				0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2, 0.22, 0.24, 0.26, 0.28, 
				0.3, 0.32, 0.34, 0.36, 0.38, 0.4, 0.42, 0.44, 0.46, 0.48, 0.5, 0.55, 
				0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.1, 1.2, 1.3, 1.4, 
				1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 
				3.8, 4.0};
	}
	else
	{
		if (!read_periods(periods_file_name.c_str(), periods) || periods.size() == 0)
		{
			cout << "Error reading file." << endl;
			return -4;
		}
	}

	cout << "Got " << periods.size() << " periods" << endl;
	cout << "First period is " << periods.front() << " s" << endl;
	cout << "Last period is " << periods.back() << " s" << endl;
	cout << endl;

	//
	// Calculate response spectrum
	//

	cout << "Response spectrum" << endl;
	cout << "-----------------" << endl;

	cout << "Calculating..." << endl;
	
	vector<double> spec_acc;
	if (!calc_rs(acc_data, timestep, periods, spec_acc, damping_ratio, calc_timestep))
	{
		cout << "Error while calculating." << endl;
		return -5;
	}

	cout << "Success." << endl;

	if (!write_rs(periods, spec_acc, rs_file_name.c_str()))
	{
		cout << "Error writing to file." << endl;
		return -6;
	}
	
	cout << "Written result to file." << endl;
	cout << endl;

	return 0;
}
