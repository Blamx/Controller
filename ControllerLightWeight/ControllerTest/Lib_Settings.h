#pragma once

#define Controller_EXPORTS

#ifdef Controller_EXPORTS
#define LIB_API __declspec(dllexport)
#elif Controller_EXPORTS
#define LIB_API __declspec(dllimport)
#else
#define LIB_API
#endif
