#include <ctime>
#include <iostream>



int main() {
	int a = 0, b = 0, c = 0, d = 0;

	clock_t start = clock();

	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 10000; j++) {
			a++;
			b++;
		}
	}

	clock_t part1 = clock();
	double time1 = (part1 - start) / (double)CLOCKS_PER_SEC;
	std::cout << " part 1: " << time1 <<'\n';

	for (int k = 0; k < 10000; k++) {
		for (int m = 0; m < 10000; m++) {
			c++;
		}
	} 

	for (int k = 0; k < 10000; k++) {
		for (int m = 0; m < 10000; m++) {
			d++;
		}
	}

	clock_t part2 = clock();
	double time2 = (part2 - part1) / (double)CLOCKS_PER_SEC;
	std::cout << " part 2: " << time2 <<'\n';


	system("pause");

	return 0;
}