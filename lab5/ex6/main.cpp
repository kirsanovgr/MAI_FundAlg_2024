#include "ex6.h"


#include <vector>

int main(){
	std::vector<double> a = {1, 2, 3, 4, 5, -17};
	Vector b(a.begin(), a.end());
	Vector v = {1.0, 2.0, 3.0};
	v.insert(12, 4.0);
	std::cout << v;



	return 0;
}