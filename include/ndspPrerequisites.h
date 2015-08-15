#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>
#include <list>
#include <vector>
#include <string>
#include <exception>
#include <intrin.h>

#define NDSP_AVX_ALIGN __declspec(align(32))