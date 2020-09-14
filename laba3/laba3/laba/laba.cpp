#include <iostream>

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
		delete[] arr;
	}

	void SetValue(size_t index, int value) {
		arr[index] = value;
	}

	int GetValue(size_t index) {
		return arr[index];
	}

	//overload
	friend ostream& operator<< (ostream&, const Array&);

	Array operator+ (const Array& other) {
		Array out;
		out.size = this->size < other.size ? this->size : other.size;
		out.arr = new int[out.size];

		for (size_t i = 0; i < out.size; i++) {
			out.arr[i] = this->arr[i] + other.arr[i];
		}

		return out;
	}

	bool operator< (const Array& other) {
		if (this->size != other.size || this->size == 0) {
			return false;
		}
		for (size_t i = 0; i < this->size; i++) {
			if (this->arr[i] >= other.arr[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator> (const Array& other) {
		if (this->size != other.size || this->size == 0) {
			return false;
		}
		for (size_t i = 0; i < this->size; i++) {
			if (this->arr[i] <= other.arr[i]) {
				return false;
			}
		}
		return true;
	}

	void ShellSort() {
		for (size_t step = this->size / 2; step > 0; step /= 2) {
			for (size_t i = step; i < size; i++) {
				for (size_t j = i; j >= step; j -= step) {
					if (arr[j] < arr[j - step]) {
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
		for (size_t i = 0; i < size; i++) {
			cout << i << ": ";
			cin >> arr[i];
		}
	}
};

int main() {

	return 0;
}

ostream& operator<< (ostream& out, const Array& array) {
	for (size_t i = 0; i < array.size; i++) {
		out << array.arr[i] << "; ";
	}
	return out;
}