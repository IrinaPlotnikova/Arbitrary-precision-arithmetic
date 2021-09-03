#include "Hex.h"

// конструктор по умолчанию
// устанавливаем максимальное количество разрядов 
// заполняем массив символом '0'
Hex::Hex() {
	_numberOfDigits = 100;
	for (int i = 0; i < _numberOfDigits; i++) {
		_digits[i] = '0';
	}
}


// конструктор
// numberOfDigits - количество разрядов
// digits - cтрока, содержащая 16-ричное число
Hex::Hex(const int& numberOfDigits, const string& digits) {
	// при numberOfDigits > 100 отбрасываем разряды больше 100
	_numberOfDigits = min(100, numberOfDigits); 
	// k - количество разрядов, которое можно заполнить
	int k = min(_numberOfDigits, (int)digits.size());

	for (int i = 0; i < k; i++) {
		_digits[k - i - 1] = digits[i];
	}

	// если k < 100, то заполняем оставшиеся разряды символом '0'
	// это удобно для выполнения арифметических операций
	for (int i = k; i < 100; i++) { 
		_digits[i] = '0';
	}
}


// конструктор
// numberOfDigits - количество разрядов
// digits - вектор, содержащий 10-ричные числа в разрядах числа;
//          порядок разрядов: от младшего к старшему слева направо
Hex::Hex(const int& numberOfDigits, const int* digits) {
	_numberOfDigits = numberOfDigits;
	int i = 0;
	while (i < _numberOfDigits) {
		_digits[i] = toBase16(digits[i]);
		i++;
	}
	while (i < _numberOfDigits) {
		_digits[i] = '0';
		i++;
	}
}

// конструктор
// number - 10-ричное число, которое будет преобразовано к 16-ричному
// количество разрядов устанавливается максимальное (100)
Hex::Hex(int number) {
	_numberOfDigits = 100;
	int i = 0;
	while(number){
		_digits[i] = toBase16(number % 16);
		number /= 16;
		i++;
	}

	// заполняем свободные разряды символом '0'
	while (i < _numberOfDigits) {
		_digits[i] = '0';
		i++;
	}
}

// получение 16-ричной формы числа number
// 0 <= number < 16
unsigned char Hex::toBase16(const int& number) const {
	unsigned char base16[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
								 'A', 'B', 'C', 'D', 'E', 'F' };
	return base16[number];
}

// преобразование в строку
string Hex::ToString() const {
	int i = _numberOfDigits;
	string result;
	while (--i > 0 && _digits[i] == '0') {} // пропуск лидирующих нулей
	while (i >= 0) {
		result += _digits[i];
		i--;
	}
	return result;
}

// получение количества разрядов в числе
int Hex::GetNumberOfDigits() const {
	return _numberOfDigits;
}

// получение числа, стоящего в i-m разряде
// число пробразуется к 10-ричной системе счисления 
int Hex::GetDigit(int i) const {
	int result = _digits[i] - '0';
	if (result > 9)
		result -= 'A' - '9' - 1;
	return result;
}

/* сравнение двух чисел
   Возвращает: 
     1 при _hex > hex;
	 0 при _hex == hex;
	-1 при _hex < hex; */
int Hex::Compare(const Hex& hex) const {
	int i = max(_numberOfDigits, hex.GetNumberOfDigits());
	int result;

	// пропуск совпадающих чисел (начинаем со старшего разряда)
	i--;
	while (i && _digits[i] == hex.GetDigit(i)) { 
		i--;
	}

	if (_digits[i] > hex.GetDigit(i))
		result = 1;
	else if (_digits[i] == hex.GetDigit(i))
		result = 0;
	else
		result = -1;

	return result;
}

// считывание структуры (с консоли)
istream& operator>>(istream& cin, Hex& hex) {
	setlocale(LC_ALL, "Russian");
	int numberOfDigits;
	string digits;

	cout << "Введите количество разрядов: ";
	cin >> numberOfDigits;
	cout << "Введите шестнадцатеричное число: ";
	cin >> digits;
	hex = Hex(numberOfDigits, digits);
	return cin;
}

// вывод структуры 
ostream& operator<<(ostream& cout, const Hex& hex) {
	setlocale(LC_ALL, "Russian");
	int n = hex.GetNumberOfDigits();
	string s = hex.ToString();
	cout << "Количество разрядов: " << n << '\n';
	cout << "Шестнадцатеричное число: " << s << '\n';
	return cout;
}

// сложение чисел
Hex operator+(const Hex& lhs, const Hex& rhs) {
	int numberOfDigits = max(lhs.GetNumberOfDigits(), rhs.GetNumberOfDigits());	
	string result = "";
	int tmp[101];

	for (int i = 0; i < 100; i++)
		tmp[i] = 0;

	for (int i = 0; i < numberOfDigits; i++) {
		tmp[i] += lhs.GetDigit(i) + rhs.GetDigit(i); // складываем
		if (tmp[i] >= 16) { // если больше допустимого, перекидываем вперед
			tmp[i + 1]++;
			tmp[i] -= 16;
		}
	}

	return Hex(numberOfDigits, tmp);
}

// вычитание чисел
Hex operator-(const Hex& lhs, const Hex& rhs) {
	int numberOfDigits = max(lhs.GetNumberOfDigits(), rhs.GetNumberOfDigits());
	string result = "";
	int tmp[101];

	for (int i = 0; i < 100; i++)
		tmp[i] = 0;

	for (int i = 0; i < numberOfDigits; i++) {
		tmp[i] += lhs.GetDigit(i) - rhs.GetDigit(i); // вычитаем поразрядно
		if (tmp[i] < 0) { // если меньше необходимого - занимаем
			tmp[i + 1]--;
			tmp[i] += 16;
		}
	}

	return Hex(numberOfDigits, tmp);
}

// умножение чисел
Hex operator*(const Hex& lhs, const Hex& rhs) {
	int numberOfDigits = max(lhs.GetNumberOfDigits(), rhs.GetNumberOfDigits());
	string result = "";
	int carry = 0;
	int tmp[101];

	for (int i = 0; i < 100; i++)
		tmp[i] = 0;

	for (int i = 0; i < numberOfDigits; i++) {
		for (int j = 0, carry = 0; i + j < numberOfDigits; j++) {
			int x = tmp[i + j] + lhs.GetDigit(i) * rhs.GetDigit(j) + carry;
			tmp[i + j] = x % 16;
			carry = x / 16;
		}
	}

	return Hex(numberOfDigits, tmp);
}

bool operator<(const Hex& lhs, const Hex& rhs) {
	return lhs.Compare(rhs) == -1;
}

bool operator==(const Hex& lhs, const Hex& rhs) {
	return lhs.Compare(rhs) == 0;
}

bool operator>(const Hex& lhs, const Hex& rhs) {
	return lhs.Compare(rhs) == 1;
}

bool operator<=(const Hex& lhs, const Hex& rhs) {
	return lhs.Compare(rhs) <= 0;
}

bool operator>=(const Hex& lhs, const Hex& rhs) {
	return lhs.Compare(rhs) >= 0;
}

bool operator!=(const Hex& lhs, const Hex& rhs) {
	return lhs.Compare(rhs) != 0;
}