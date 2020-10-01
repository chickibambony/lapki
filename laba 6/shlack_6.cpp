#include <iostream>
#include <windows.h>
using namespace std;

template <typename T>
T getMaxElement(T*, int size = 0);
char getMaxElement(char*, int size = 0);

template <typename T>
void GetValidValue(T& , string title = "Value");

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size;
	int* intArr;
	double* doubleArr;
	char* charArr, buffer[64];

	GetValidValue(size, "Enter the size of INT array");	
	intArr = new int[size];
	for (int i = 0; i < size; i++) {
		_itoa_s(i + 1, buffer, 10);
		GetValidValue(intArr[i], buffer);
	}
	cout << "Max elem: " << getMaxElement(intArr, size) << endl;
	cout << "-------------------" << endl << endl;

	GetValidValue(size, "Enter the size of DOUBLE array");
	doubleArr = new double[size];
	for (int i = 0; i < size; i++) {
		_itoa_s(i + 1, buffer, 10);
		GetValidValue(doubleArr[i], buffer);
	}
	cout << "Max elem: " << getMaxElement(doubleArr, size) << endl;
	cout << "-------------------" << endl << endl;
	
	GetValidValue(size, "Enter the size of CHAR array");
	charArr = new char[size];
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ": ";
		cin >> charArr[i];
	}
	cout << "Max elem: " << getMaxElement(charArr, size) << endl;
	cout << "-------------------" << endl << endl;
	
	return 0; 
}

template <typename T>
T getMaxElement(T* arr, int size) {
	if (size == 0) {
		throw -1;
	}
	else {
		T max = arr[0];
		for (int i = 1; i < size; i++) {
			if (arr[i] > max) {
				max = arr[i];
			}
		}
		return max;	
	}
}

char getMaxElement(char* arr, int size) {
	if (size == 0) {
		throw - 1;
	}
	else {
		char max = arr[0];
		for (int i = 1; i < size; i++) {
			if (arr[i] > max) {
				max = arr[i];
			}
		}
		return max;	
	}
}

template <typename T>
void GetValidValue(T& value, string title) {
	T temp;
	cout << title << ": ";

	while (true) {
		cin >> temp;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << title << ": ";
		}
		else {
			cin.ignore(32767, '\n');
			value = temp;
			return;
		}
	}
};