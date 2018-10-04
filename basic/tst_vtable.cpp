#include <iostream>
class A
{
	public:
		virtual void funA() {}// std::cout << "A::funA" << std::endl; }
		int a;
};

class B : public A
{
	public:
		virtual void funB() {}// std::cout << "B::funB" << std::endl; }
		int b;
};

int main(int argc, char* argv[])
{
	B b;
	b.funA();
	b.funB();
	std::cout << "sizeof(A) : " << sizeof(A) << std::endl;
	std::cout << "sizeof(B) : " << sizeof(B) << std::endl;
}





