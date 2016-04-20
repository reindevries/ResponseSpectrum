#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include <omp.h>

#define ASSERT(x) assert(x)

template <typename T>
inline T sq(T x) {return x*x;}

/*
#define _WIN32_WINNT 0x0601	 // target Windows 7 and higher
#define WIN32_LEAN_AND_MEAN  // exclude rarely-used stuff from Windows headers
#define _USE_MATH_DEFINES
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS

#include <sdkddkver.h>
#include <windows.h>
#include <tchar.h>
#include "Base\debug.hpp"

#include <clocale>
#include <cmath>
#include <ctime>
#include <algorithm>

#include "Base\move.hpp"
#include "Base\Array.hpp"
#include "Base\String.hpp"

#include "Base\general.hpp"
#include "Base\convert.hpp"

using namespace Base;

template <typename T>
inline T sq(T x) {return x*x;}

template <typename T>
inline T ln(T x) {return log(x);}

template <typename T>
int sgn(T x) {return (T(0) < x) - (x < T(0));}

inline double round(double value)
	{return std::round(value);}

inline double round(double value, int digits)
{
	if (value == 0.0)  // otherwise it will return 'nan' due to the log10() of zero
		return 0.0;

	double factor = pow(10.0, digits - ceil(log10(fabs(value))));
	return round(value * factor) / factor;
}
*/