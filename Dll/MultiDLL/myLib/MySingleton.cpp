#include "MySingleton.h"

MySingleton & MySingleton::getInstance()
{
	static MySingleton s_obj;
	return s_obj;
}

MySingleton::MySingleton() : iVal(0)
{
}


MySingleton::~MySingleton()
{
}
