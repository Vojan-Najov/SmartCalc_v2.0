#include <iostream>
#include <cmath>

int foo() { return 1; }
int bar() { return 2; }


struct A {
	virtual ~A() {}
	virtual int foo() = 0;
};

struct B : A {
	int a_;
	B(int a) : a_(a) {}
	int foo() override { return a_; }
	~B() {}
};

int main() {
	A *ptr = new B{10};
	std::cout << ptr->foo() << std::endl;
	std::cout << static_cast<B*>(ptr)->a_ << std::endl;
	delete ptr;

	long double (*fptr)(long double) = &std::sinl;

	if (fptr == &std::sinl) {
			std::cout << "sin\n";
	} else if (fptr == &cosl) {
			std::cout << "cos\n";
	}

}
