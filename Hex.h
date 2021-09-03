#pragma once
#include <iostream>
#include <string>
using namespace std;


class Hex {
private:
	int _numberOfDigits;
	unsigned char _digits[100];
	unsigned char toBase16(const int& number) const; // number >= 0 && number < 16
public:
	Hex(const int& numberOfDigits, const string& digits);
	Hex(const int& numberOfDigits, const int* digits);
	Hex(int number);
	Hex();
	string ToString() const;
	int GetNumberOfDigits() const;
	int GetDigit(int pIndex) const;
	
	int Compare(const Hex& hex) const;
};

istream& operator>>(istream& cin, Hex& hex);
ostream& operator<<(ostream& cout, const Hex& hex);

Hex operator+(const Hex& lhs, const Hex& rhs);
Hex operator-(const Hex& lhs, const Hex& rhs);
Hex operator*(const Hex& lhs, const Hex& rhs);

bool operator<(const Hex& lhs, const Hex& rhs);
bool operator>(const Hex& lhs, const Hex& rhs);
bool operator<=(const Hex& lhs, const Hex& rhs);
bool operator>=(const Hex& lhs, const Hex& rhs);
bool operator==(const Hex& lhs, const Hex& rhs);
bool operator!=(const Hex& lhs, const Hex& rhs);