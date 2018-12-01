#include <iostream>

class Embedded
{
	public:
		Embedded(){
			std::cout << "Embedded Ctor" << std::endl;
		}
		~Embedded(){
			std::cout << "Embedded Dtor" << std::endl;
		}
};

class Aggregation
{
	public:
		Aggregation(){
			std::cout << "Aggregation Ctor" << std::endl;
		}
		~Aggregation(){
			std::cout << "Aggregation Dtor " << std::endl;
		}
};

class Outer
{
	public:
		Outer(){
			m_pAggre = new Aggregation;
			std::cout << "Outer Ctor Now throwing" << std::endl;
			throw 1;
		}
		~Outer(){
			std::cout << "Outer Dtor" << std::endl;
		}
	private:
		Aggregation* m_pAggre;
		Embedded     m_ebd;
};

int main(int argc, char* argv[])
{
	try{
		Outer obj_Outer;
	}
	catch(...)
	{
		std::cout << "catched" << std::endl;
	}
	return 0;
}

