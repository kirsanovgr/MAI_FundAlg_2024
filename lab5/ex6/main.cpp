#include "ex6.h"


int main(){
	const double a[] = {1, 2, 3, 4, 5, -17};
	Vector b(a, a + 6);
	Vector v = {1.0, 2.0, 3.0};
	v.insert(12, 4.0);
	std::cout << v;


	return 0;
}