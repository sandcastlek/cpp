//#include <iostream>
class A
{
	public:
		virtual void funA() {}// std::cout << "A::funA" << std::endl; }
		int a;
		char a1[4];
};

class B
{
	public:
		virtual void funB() {} //std::cout << "B::funB" << std::endl; }
		virtual void funB2() {} //std::cout << "B::funB" << std::endl; }
		int b;
};

class C: public A, public B
{
	public:
		virtual void funC() {} //std::cout << "B::funB" << std::endl; }
		virtual void funC2() {} //std::cout << "B::funB" << std::endl; }
		int c;
};


int main(int argc, char* argv[])
{
	C c;
	c.funA();
	c.funB();
	c.funC();

	//std::cout << "sizeof(A) : " << sizeof(A) << std::endl;
	//std::cout << "sizeof(B) : " << sizeof(B) << std::endl;
	//std::cout << "sizeof(C) : " << sizeof(C) << std::endl;
}





