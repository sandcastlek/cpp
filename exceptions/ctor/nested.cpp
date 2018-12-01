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
			std::cout << "Outer Ctor" << std::endl;
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
	Outer obj_Outer;
	return 0;
}

