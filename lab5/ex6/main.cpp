#include "ex6.h"


#include <vector>
int main(){
	double b[] = {1, 2, 3};
	Vector a(b, b + 3);
	a.insert(8, 3);
	std::cout << a.back() << std::endl;
	std::cout << a;

	return 0;
}