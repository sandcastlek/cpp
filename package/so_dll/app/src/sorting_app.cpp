//#include <sort.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	string strNumbers;
	do {
		cout << "Enter Number to be Sorted" << std::endl;
		std::getline( std::cin, strNumbers);
		stringstream ss;
		std::vector<int> vtr;
		ss << strNumbers;
		string tmp;
		while(!ss.eof())
		{
			int iNum;
			ss >> iNum;
			if(!ss.fail()) 
			{
				vtr.push_back(iNum);
			} else {
				ss >> tmp;
			}
		}
		cout << "Vector count : " << vtr.size()  << std::endl;
	} while( 1 < strNumbers.length() );

	return 0;
}

