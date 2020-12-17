#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <functional>
#include <set>

namespace cock {
	class Detail;

	class Algoritms {
	public:
		void Algoritm1();
		int Algoritm2(std::set<Detail>::iterator begin, std::set<Detail>::iterator end, std::function<bool(float)>);
		void Algoritm3(std::set<Detail>::iterator begin, std::set<Detail>::iterator end, std::set<Detail>& newSet, std::function<bool(float)>);
		void Print(std::set<Detail>::iterator begin, std::set<Detail>::iterator end);
	private:
		bool CheckBrackets(const std::string str);
	};
	
	class Detail {
	public:
		Detail(std::string name, int id, float mass) {
			this->name = name;
			this->id = id;
			this->mass = mass;
		}
		friend Algoritms;

		friend bool operator <(const cock::Detail& d1, const cock::Detail& d2) {
			return (d1.id < d2.id);
		}

		friend std::ostream& operator<< (std::ostream& out, const Detail& detail) {
			out << "Name: " << detail.name << std::endl;
			out << "ID: " << detail.id << std::endl;
			out << "Mass: " << detail.mass << std::endl;
			return out;
		}

	private:
		std::string name;
		int id;
		float mass;
	};

	class Exception{
	public:
		Exception() {
			this->errorIndex = 0;
		}
		Exception(int errorIndex){
			this->errorIndex = errorIndex;
		}
		void what(){
			if (errorIndex == 0){
				std::cout << "Input error! Enter int!" << std::endl;
			}
			else if (errorIndex == 1){
				std::cout << "Opening error!" << std::endl;
			}
			else if (errorIndex == 2){
				std::cout << "Stack is empty!" << std::endl;
			}
			else {
				std::cout << "EXCEPTION, BLAT" << std::endl;
			}
		}

	private:
		int errorIndex;
	};
}

bool massCheck(float mass) {
	return (mass < 15);
}

int main() {
	cock::Algoritms alg;
	std::set<cock::Detail> test;
	std::set<cock::Detail> newTest;

	test.insert(cock::Detail("chi", 13, 15.4));
	test.insert(cock::Detail("mi", 14, 12));
	test.insert(cock::Detail("ge", 15, 14));
	
	std::cout << "Algoritm 1\n" << "------------------------------------\n";
	alg.Algoritm1();
	std::cout << std::endl;

	std::cout << "Primary set\n" << "------------------------------------\n";
	alg.Print(test.begin(), test.end());


	std::cout << "Algoritm 2\n" << "------------------------------------\n";
	std::cout << "Quantity of valid values: "<< alg.Algoritm2(test.begin(), test.end(), massCheck) << std::endl;
	std::cout << std::endl;

	std::cout << "Algoritm 3\n" << "------------------------------------\n";
	alg.Algoritm3(test.begin(), test.end(), newTest, massCheck);
	alg.Print(newTest.begin(), newTest.end());
	
	return 0;
}

void cock::Algoritms::Print(std::set<Detail>::iterator begin, std::set<Detail>::iterator end) {
	auto it = begin;
	while (it != end) {
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl;
}

void cock::Algoritms::Algoritm3(std::set<Detail>::iterator begin, std::set<Detail>::iterator end, std::set<Detail>& newSet, std::function<bool(float)> func) {
	auto it = begin;
	while (it != end) {
		if (func(it->mass)) {
			newSet.insert(*it);
		}
		++it;
	}
}

int cock::Algoritms::Algoritm2(std::set<Detail>::iterator begin, std::set<Detail>::iterator end, std::function<bool(float)> func) {
	int counter = 0;
	auto it = begin;
	while (it != end) {
		if (func(it->mass)) {
			++counter;
		}
		++it;
	}

	return counter;
}

void cock::Algoritms::Algoritm1() {
	std::cout << "Checking the correct placement of brackets" << std::endl;
	std::fstream outFile;
	outFile.open("string.txt");

	try	{
		if (!outFile.is_open()){
			throw 1;
		}
		std::cout << "Data file is opened" << std::endl;
	}
	catch (int index){
		Exception ex(index);
		ex.what();
		return;
	}

	std::string buffer;
	std::list<std::string> strList;
	while (!outFile.eof()) {
		std::getline(outFile, buffer);
		if (CheckBrackets(buffer)) {
			strList.push_back(buffer + " : is right");
		}
		else {
			strList.push_back(buffer + " : is wrong");
		}
	}

	std::cout << "Algoritm is ended" << std::endl;
	outFile.close();
	std::cout << "Data file is closed" << std::endl;

	std::ofstream inFile("string2.txt");

	try {
		if (!inFile.is_open()) {
			throw 1;
		}
		std::cout << "Result file is opened" << std::endl << std::endl;
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	std::list<std::string>::const_iterator it = strList.begin();
	while (it != strList.end()) {
		inFile << *it << "\n";
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl << "Data was writen" << std::endl;
	inFile.close();
	std::cout << "Result file is closed" << std::endl;
}

bool cock::Algoritms::CheckBrackets(const std::string str) {
	int leftBracketCounter = 0, rightBracketCounter = 0;
	bool leftFirstFlag = false, rightLastFlag = false, firstFlag = true;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(') {
			leftBracketCounter++;
			if (firstFlag) {
				leftFirstFlag = true;
			}
			rightLastFlag = false;
			firstFlag = false;
		}if (str[i] == ')') {
			rightBracketCounter++;
			rightLastFlag = true;
			firstFlag = false;
		}
	}

	if ((leftBracketCounter == 0 && rightBracketCounter == 0) || (leftBracketCounter == rightBracketCounter && leftFirstFlag && rightLastFlag)) {
		return true;
	}
	else {
		return false;
	}
}