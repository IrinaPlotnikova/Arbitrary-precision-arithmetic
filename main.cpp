#include "Hex.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Перемножение чисел 1, 2, 3, ..., 20\n\n";
	
	Hex c(1);
	int dec = 1;
	for (int i = 1; i < 21; i++) {
		Hex d(i);
		c = c * d;
		dec = dec * i;
		cout << "i = " << i << '\n' << c << '\n';
	}


	
	return 0;
}
