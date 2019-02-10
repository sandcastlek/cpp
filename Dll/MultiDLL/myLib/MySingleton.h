#pragma once
class MySingleton
{
public:
	static MySingleton& getInstance();
private:
	MySingleton();
	~MySingleton();
private:
	int iVal;
};

