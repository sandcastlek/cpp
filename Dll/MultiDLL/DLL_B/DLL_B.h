#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef DLL_EXPORTS
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT __declspec(dllimport)
#endif

	DLL_EXPORT void*  getFromB();


#ifdef __cplusplus
}
#endif