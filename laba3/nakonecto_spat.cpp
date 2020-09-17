#include <iostream>
#include <conio.h>

using namespace std;

class Array {
private:
	int* arr;
	size_t size;

public:
	Array() {
		arr = nullptr;
		size = 0;
	}
	
	Array(size_t size) {
		this->size = size;
		arr = new int[size];
		Initial();
	}

	Array(const Array& other) {
		this->size = other.size;
		this->arr = new int[this->size];
		for (size_t i = 0; i < this->size; i++) {
			this->arr[i] = other.arr[i];
		}
	}

	~Array() {
		delete[] this->arr;
	}

	void SetValue(size_t index, int value) {
		if (index >= size || index < 0) {
			throw 0;
		}
		else {
			arr[index] = value;		
		}
	}

	int GetValue(size_t index) {
		if (index >= size || index < 0) {
			throw 0;
		}
		else {
			return arr[index];	
		}
	}

	//overload
	friend ostream& operator<< (ostream&, const Array&);

	Array operator+ (const Array& other) {
		Array out;
		if (this->size < other.size) {
			out.size = this->size;
		}
		else {
			out.size = other.size;
		}
		out.arr = new int[out.size];
		
		for (size_t i = 0; i < out.size; i++) {
			out.arr[i] = this->arr[i] + other.arr[i];
		}

		return out;
	}
	
	Array& operator= (const Array& other) {
		if (this->arr != nullptr) {
			delete[] arr;
		}
		this->size = other.size;
		this->arr = new int[this->size];
		for (size_t i = 0; i < this->size; i++) {
			this->arr[i] = other.arr[i];
		}
		return *this;
	}

	bool operator< (const Array& other) {
		if (this->size < other.size) {
			return true;
		}
		else {
			return false;
		}		
	}
	
	bool operator> (const Array& other) {
		if (this->size < other.size) {
			return false;
		}
		else {
			return true;
		}
	}

	void ShellSort() {
		for (size_t step = this->size / 2; step > 0; step /= 2) {
			for (size_t i = step; i < size; i++) {
				for (size_t j = i; j >= step; j -= step) {
					if (arr[j] > arr[j - step]) {
						int temp = arr[j];
						arr[j] = arr[j - step];
						arr[j - step] = temp;
					}
				}
			}
		}
	}

private:
	void Initial() {
		cout << "Enter the array values: " << endl;
		for (size_t i = 0; i < size; i++) {
			cout << i + 1 << ": ";
			while (!(cin >> arr[i]) || cin.get() != '\n') {
				cin.clear();
				cin.ignore();
				cin.sync();
				cout << i + 1 << ": ";
			}
		}
		cout << endl;
	}
};

void PrintMenu(size_t, const Array*);

int main() {		
	/*Array arr1(2), arr2(3), arr3(arr1), sum;
	sum = arr1 + arr2;
	cout << arr1 << endl;
	cout << arr2 << endl;
	cout << arr3 << endl;
	cout << sum << endl;
	cout << (arr1 < arr2) << endl;
	cout << (arr2 > arr3) << endl;
	*/
	
	size_t numOfArrays = 3, index, num, elem, value;
	
	Array* test = new Array[numOfArrays]{
		Array(4),
		Array(3),
		Array(5),
	};	
	system("cls");

	while (1) {		
		PrintMenu(numOfArrays, test);		
		while (!(cin >> index) || index < 0 || index > 3) {
			cin.clear();
			cin.ignore();
			cout << ">>> ";
		}
		cout << endl;

		switch(index) {
		case 1:
			cout << "Choose the number of Array: ";
			while (!(cin >> num) || num < 1 || num > numOfArrays) {
				cin.clear();
				cin.ignore();
				cout << "Choose the number of Array: ";
			}

			cout << "Choose element of array: ";
			while (!(cin >> elem)) {
				cin.clear();
				cin.ignore();
				cout << "Choose element of array: ";
			}
			try {
				cout << test[num - 1].GetValue(elem - 1) << endl;			
			}
			catch(const int &ex){
				cout << "Wrong index, out of memory" << endl;
				system("pause");
			}
			system("pause");
			system("cls");
			break;

		case 2:
			cout << "Choose the number of Array: ";
			while (!(cin >> num) || num < 1 || num > numOfArrays) {
				cin.clear();
				cin.ignore();
				cout << "Choose the number of Array: ";
			}

			cout << "Choose element of array: ";
			while (!(cin >> elem)) {
				cin.clear();
				cin.ignore();
				cout << "Choose element of array: ";				
			}

			cout << "Enter new value of element: ";
			while (!(cin >> value)) {
				cin.clear();
				cin.ignore();
				cout << "Enter new value of element: ";			
			}			

			try {
				test[num - 1].SetValue(elem - 1, value);	
			}
			catch (const int &ex) {
				cout << "Wrong index, out of memory" << endl;
				system("pause");
			}

			system("cls");
			break;

		case 3:
			cout << "Choose the number of Array: ";
			while (!(cin >> num) || num < 1 || num > numOfArrays) {
				cin.clear();
				cin.ignore();
				cout << "Choose the number of Array: ";
			}

			test[num - 1].ShellSort();
			system("cls");
			break;

		case 0:
			delete[] test;
			exit(0);
			break;
		}
	}
	return 0;
}

void PrintMenu(size_t size, const Array* list) {
	if (size == 0) {
		cout << "No Arrays was added..." << endl;
	}
	else {
		cout << "Available Arrays" << endl;
		for (size_t i = 0; i < size; i++) {
			cout << "#" << i + 1 << ": " << list[i] << endl;
		}
	}
	cout << endl;

	cout  << "What do you want to do?" << endl;
	cout << "1. Get element" << endl;
	cout << "2. Set Element" << endl;
	cout << "3. Shell sort" << endl;
	cout << "0. Exit" << endl;
	cout << ">>> ";
}

ostream& operator<< (ostream& out, const Array& array) {
	for (size_t i = 0; i < array.size; i++) {
		out << array.arr[i] << "; ";
	}
	return out;
}