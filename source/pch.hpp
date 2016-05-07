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

#define _In_
#define _Out_
