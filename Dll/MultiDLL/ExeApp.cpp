#include <DLL_A.h>
#include <DLL_B.h>
#include <iostream>
#include <windows.h>

typedef void*(*MY_FUN)(void);

void for_B()
{

	std::cout << "Going for B" << std::endl;

	HMODULE dllModule = LoadLibrary("DLL_B.dll");
	MY_FUN fn_B = (MY_FUN)GetProcAddress(dllModule, "getFromB");

	//void* from_B = getFromB();
	void* from_B = fn_B();

	std::cout << "From B : " << from_B << std::endl;


}


int main(int argc, char* argv[])
{
	void* from_A = getFromA();
	std::cout << "From A : " << from_A << std::endl;

	for_B();

	return 0;
}