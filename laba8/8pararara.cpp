#include <iostream>
#include <fstream>
#include <string>
#include <io.h>

class File;

class Shoes {
public:
	Shoes(std::string name, int articul, int quantuty, double price);
	Shoes() {};
	void PrintInfo() {
		std::cout << "Name: " << name << std::endl;
		std::cout << "Articul: " << articul << std::endl;
		std::cout << "Price: " << price << std::endl;
		std::cout << "Quantity: " << quantity << std::endl;
	}
	bool operator <(Shoes& other) {
		if (this->articul < other.articul) {
			return true;
		}
		else {
			return false;
		}
	}
		
	bool operator >(Shoes& other) {
		if (this->articul > other.articul) {
			return true;
		}
		else {
			return false;
		}
	}
		
	bool operator ==(Shoes& other) {
		if (this->articul == other.articul) {
			return true;
		}
		else {
			return false;
		}
	}
			
	bool operator !=(Shoes& other) {
		if (this->articul != other.articul) {
			return true;
		}
		else {
			return false;
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const Shoes& shoes);

private:
	int articul;
	std::string name;
	int quantity;
	double price;

	friend File;
};

class Exception
{
private:
	int error;

public:
	Exception()
	{
		error = 0;
	}
	Exception(int error)
	{
		this->error = error;
	}
	void what()
	{
		if (error == 0) {
			std::cout << "exception, blet!" << std::endl;
		}
		if (error == 1)
		{
			std::cout << "Cant insert Dublicate!" << std::endl;
		}
		if (error == 2)
		{
			std::cout << "No such value!" << std::endl;
		}
		if (error == 3)
		{
			std::cout << "pointer is empty" << std::endl;
		}
		if (error == 4)
		{
			std::cout << "Can't open such file" << std::endl;
		}
	}
};

template <class T>
class Iterator;
template <class T>
class BinaryTree;

template <class T>
class Node {
private:
	T data;
	Node* leftChild;
	Node* rightChild;
	Node* parent;

	friend Iterator<T>;
	friend BinaryTree<T>;
};

template <class T>
class Iterator {
public:
	Iterator() {
		nodePointer = nullptr;
	}
	Iterator(Node<T>* nodePointer) {
		this->nodePointer = nodePointer;
	}
	~Iterator() {
		nodePointer = nullptr;
	}
	bool operator== (Iterator other) {
		if (nodePointer == other.nodePointer) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!= (Iterator other) {
		return !operator==(other);
	}
	T GetValue() {
		if (nodePointer == nullptr) {
			throw 3;
		}
		return nodePointer->data;
	}
	void Next() {
		if (nodePointer->rightChild != nullptr) {
			nodePointer = nodePointer->rightChild;
			while (nodePointer->leftChild != nullptr) {
				nodePointer = nodePointer->leftChild;
			}
		}
		else {
			if (nodePointer->parent == nullptr) {
				return;
			}
			if (nodePointer->parent->leftChild && nodePointer->parent->leftChild == nodePointer) {
				nodePointer = nodePointer->parent;
				return;
			}
			if (nodePointer->parent->rightChild && nodePointer->parent->rightChild == nodePointer) {
				while (nodePointer->data > nodePointer->parent->data) {
					nodePointer = nodePointer->parent;
					if (nodePointer->parent == nullptr) {
						throw 3;
					}
				}
				nodePointer = nodePointer->parent;
				return;
			}
		}
	}

private:
	Node<T>* nodePointer;
};

template <class T>
class BinaryTree {
public:
	BinaryTree() {
		root = nullptr;
		size = 0;
	}

	Iterator<T> Begin() {
		Node<T>* temp = root;
		while (temp->leftChild) {
			temp = temp->leftChild;
		}
		return temp;
	}

	Iterator<T> End() {
		Node<T>* temp = root;
		while (temp->rightChild) {
			temp = temp->rightChild;
		}
		return temp;
	}

	Node<T>* GetNodeByValue(T value) {
		Node<T>* temp = root;
		while (temp) {
			if (value < temp->data) {
				temp = temp->leftChild;
				continue;
			}
			else if (value > temp->data) {
				temp = temp->rightChild;
				continue;
			}
			else {
				return temp;
			}
		}
		throw 2;
	}

	void InsertNode(T l_data) {
		Node<T>* temp = nullptr;
		if (!root) {
			root = GetFreeNode(l_data, nullptr);
			size++;
		}
		else {
			Node<T>* iterator = root;
			while (iterator) {
				if (l_data > iterator->data) {
					if (iterator->rightChild) {
						iterator = iterator->rightChild;
						continue;
					}
					else {
						iterator->rightChild = GetFreeNode(l_data, iterator);
						size++;
						return;
					}
				}
				else if (l_data < iterator->data) {
					if (iterator->leftChild) {
						iterator = iterator->leftChild;
						continue;
					}
					else {
						iterator->leftChild = GetFreeNode(l_data, iterator);
						size++;
						return;
					}
				}
				else {
					throw 1;
				}
			}
		}
	}

	void EraseNodeByValue(T l_value) {
		Node<T>* target = GetNodeByValue(l_value);
		RawEraseNode(target);
	}

private:
	Node<T>* root;
	int size;

	Node<T>* FindLocalMax(Node<T>* root) {
		while (root->rightChild) {
			root = root->rightChild;
		}
		return root;
	}

	void RawEraseNode(Node<T>* target) {
		if (target->leftChild && target->rightChild) {
			Node<T>* localMax = FindLocalMax(target->leftChild);
			target->data = localMax->data;
			RawEraseNode(localMax);
			return;
		}
		else if (target->leftChild) {
			if (target == target->parent->leftChild) {
				target->parent->leftChild = target->leftChild;
				target->leftChild->parent = target->parent;
			}
			else {
				target->parent->rightChild = target->leftChild;
				target->leftChild->parent = target->parent;
			}
		}
		else if (target->rightChild) {
			if (target == target->parent->rightChild) {
				target->parent->rightChild = target->rightChild;
				target->rightChild->parent = target->parent;
			}
			else {
				target->parent->leftChild = target->rightChild;
				target->rightChild->parent = target->parent;
			}
		}
		else {
			if (target == target->parent->leftChild) {
				target->parent->leftChild = nullptr;
			}
			else {
				target->parent->rightChild = nullptr;
			}
		}
		delete target;
		size--;
	}

	Node<T>* GetFreeNode(T l_data, Node<T>* parent) {
		Node<T>* temp = new Node<T>;
		temp->data = l_data;
		temp->leftChild = temp->rightChild = nullptr;
		temp->parent = parent;
		return temp;
	}
};

class File {
public:
	File(std::string filePath);
	void ReadTextFormat();
	void WriteTextFormat(const Shoes& shoes);
	void ReadBinFormat();
	void WriteBinFormat(const Shoes& shoes);
	void SortByPrice();
	void SortByArticul();
	void SortByQuantity();
	void SortByName();
	void InfoBeforePrice(double price);
	void DelByName(std::string name);
	void FindByName(std::string name);

private:
	std::string filePath;
	std::fstream ioFile;
	int CountElementOfBinFile();
	void GetElementOfBinFile(Shoes& shoes);
};

int main() {
	File file1("yeee.txt");
	File file2("yeee1.txt");
	File file3("yeee2.bin");
	
	BinaryTree<Shoes> tree;
	tree.InsertNode(Shoes("Nike", 123, 3, 350));
	tree.InsertNode(Shoes("Abibas", 126, 6, 250));
	tree.InsertNode(Shoes("Pyma", 124, 12, 300));
	tree.InsertNode(Shoes("Ribuk", 125, 4, 170));
	tree.InsertNode(Shoes("Converce", 122, 13, 90));

	Iterator<Shoes> it = tree.Begin();
	while (1) {
		if (it == tree.End()) {
			file1.WriteTextFormat(it.GetValue());
			break;
		}
		file1.WriteTextFormat(it.GetValue());
		it.Next();
	}

	it = tree.Begin();
	while (1) {
		if (it == tree.End()) {
			file2.WriteBinFormat(it.GetValue());
			break;
		}
		file2.WriteBinFormat(it.GetValue());
		it.Next();
	}

	it = tree.Begin();
	while (1) {
		if (it == tree.End()) {
			file3.WriteBinFormat(it.GetValue());
			break;
		}
		file3.WriteBinFormat(it.GetValue());
		it.Next();
	}

	
	std::cout << "Text File, Text format:\n" << "-------------------------\n";
	file1.ReadTextFormat();
	std::cout << "\nText File, bin format:\n" << "-------------------------\n";
	file2.ReadBinFormat();
	std::cout << "Bin File:\n" << "-------------------------\n";
	file3.ReadBinFormat();
	file3.SortByName();
	std::cout << "Sorted by name:\n" << "-------------------------\n";
	file3.ReadBinFormat();
	std::cout << "Find by name:\n" << "-------------------------\n";
	file3.FindByName("Nike");
}

/////////////////////

void File::InfoBeforePrice(double price) {
	SortByName();
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, std::ios::in | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Shoes temp;
	for (int i = 0; i < fileSize; i++) {
		GetElementOfBinFile(temp);
		if (temp.price < price) {
			std::cout << temp << std::endl;
		}
	}

	ioFile.close();
}

void File::SortByArticul() {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Shoes cur, next;
	int curPos, nextPos;
	for (int i = 0; i < fileSize; i++) {
		for (int j = 0; j < fileSize - 1; j++) {
			curPos = ioFile.tellg();
			GetElementOfBinFile(cur);
			nextPos = ioFile.tellg();
			GetElementOfBinFile(next);

			if (cur.articul > next.articul) {
				ioFile.seekp(curPos, std::ios::beg);

				ioFile.write((char*)&next.articul, sizeof(int));
				ioFile.write((char*)&next.quantity, sizeof(int));
				ioFile.write((char*)&next.price, sizeof(double));
				int len = next.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(next.name.data(), len);
				nextPos = ioFile.tellp();

				ioFile.write((char*)&cur.articul, sizeof(int));
				ioFile.write((char*)&cur.quantity, sizeof(int));
				ioFile.write((char*)&cur.price, sizeof(double));
				len = cur.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(cur.name.data(), len);
			}
			ioFile.seekg(nextPos, std::ios::beg);
		}
		ioFile.seekg(0, std::ios::beg);
	}
	ioFile.close();
}

void File::SortByQuantity() {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}
	Shoes cur, next;
	int curPos, nextPos;
	for (int i = 0; i < fileSize; i++) {
		for (int j = 0; j < fileSize - 1; j++) {
			curPos = ioFile.tellg();
			GetElementOfBinFile(cur);
			nextPos = ioFile.tellg();
			GetElementOfBinFile(next);


			if (cur.quantity > next.quantity) {
				ioFile.seekp(curPos, std::ios::beg);

				ioFile.write((char*)&next.articul, sizeof(int));
				ioFile.write((char*)&next.quantity, sizeof(int));
				ioFile.write((char*)&next.price, sizeof(double));
				int len = next.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(next.name.data(), len);
				nextPos = ioFile.tellp();

				ioFile.write((char*)&cur.articul, sizeof(int));
				ioFile.write((char*)&cur.quantity, sizeof(int));
				ioFile.write((char*)&cur.price, sizeof(double));
				len = cur.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(cur.name.data(), len);
			}
			ioFile.seekg(nextPos, std::ios::beg);
		}
		ioFile.seekg(0, std::ios::beg);
	}
	ioFile.close();
}

void File::SortByName() {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Shoes cur, next;
	int curPos, nextPos;
	for (int i = 0; i < fileSize; i++) {
		for (int j = 0; j < fileSize - 1; j++) {
			curPos = ioFile.tellg();
			GetElementOfBinFile(cur);
			nextPos = ioFile.tellg();
			GetElementOfBinFile(next);


			if (std::strcmp(next.name.c_str(), cur.name.c_str()) < 0) {
				ioFile.seekp(curPos, std::ios::beg);

				ioFile.write((char*)&next.articul, sizeof(int));
				ioFile.write((char*)&next.quantity, sizeof(int));
				ioFile.write((char*)&next.price, sizeof(double));
				int len = next.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(next.name.data(), len);
				nextPos = ioFile.tellp();

				ioFile.write((char*)&cur.articul, sizeof(int));
				ioFile.write((char*)&cur.quantity, sizeof(int));
				ioFile.write((char*)&cur.price, sizeof(double));
				len = cur.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(cur.name.data(), len);
			}
			ioFile.seekg(nextPos, std::ios::beg);
		}
		ioFile.seekg(0, std::ios::beg);
	}
	ioFile.close();
}

void File::SortByPrice() {
	int fileSize = CountElementOfBinFile();
	
	try {
		ioFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}
	Shoes cur, next;
	int curPos, nextPos;
	for (int i = 0; i < fileSize; i++) {
		for (int j = 0; j < fileSize - 1; j++) {
			curPos = ioFile.tellg();
			GetElementOfBinFile(cur);
			nextPos = ioFile.tellg();
			GetElementOfBinFile(next);
			
			if (cur.price > next.price) {
				ioFile.seekp(curPos, std::ios::beg);

				ioFile.write((char*)&next.articul, sizeof(int));
				ioFile.write((char*)&next.quantity, sizeof(int));
				ioFile.write((char*)&next.price, sizeof(double));
				int len = next.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(next.name.data(), len);
				nextPos = ioFile.tellp();

				ioFile.write((char*)&cur.articul, sizeof(int));
				ioFile.write((char*)&cur.quantity, sizeof(int));
				ioFile.write((char*)&cur.price, sizeof(double));
				len = cur.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(cur.name.data(), len);
			}
			ioFile.seekg(nextPos, std::ios::beg);
		}
		ioFile.seekg(0, std::ios::beg);
	}
	ioFile.close();
}

Shoes::Shoes(std::string name, int articul, int quantity, double price) {
	this->name = name;
	this->articul = articul;
	this->price = price;
	this->quantity = quantity;
}

std::ostream& operator<<(std::ostream& out, const Shoes& shoes) {
	out << "Name: " << shoes.name << std::endl;
	out << "Articul: " << shoes.articul << std::endl;
	out << "Price: " << shoes.price << std::endl;
	out << "Quantity: " << shoes.quantity << std::endl;
	return out;
}

//File///////////////////
File::File(std::string filePath) {
	this->filePath = filePath;
	ioFile.open(filePath, std::ios::out | std::ios::trunc);
	ioFile.close();
}

void File::ReadTextFormat() {

	try {
		ioFile.open(filePath, std::ios::in);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	std::string data;
	while (std::getline(ioFile, data)) {
		std::cout << data << std::endl;
	}
	ioFile.close();
}

void File::WriteTextFormat(const Shoes& shoes) {
	try {
		ioFile.open(filePath, std::ios::out | std::ios::app);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	ioFile << shoes;
	ioFile.close();
}

void File::FindByName(std::string name) {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, std::ios::in | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Shoes temp;
	for (int i = 0; i < fileSize; i++) {
		GetElementOfBinFile(temp);
		if (std::strcmp(temp.name.data(), name.data()) == 0) {
			std::cout << temp << std::endl;
			return;
		}
	}

	ioFile.close();
}

void File::DelByName(std::string name) {
	int fileSize = CountElementOfBinFile();
	
	try {
		ioFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Shoes cur, next;
	int curPos, nextPos;
	for (int i = 0; i < fileSize; i++) {
		curPos = ioFile.tellg();
		GetElementOfBinFile(cur);
		if (std::strcmp(cur.name.data(), name.data()) == 0) {
			ioFile.seekg(curPos, std::ios::beg);
			int size = 0;
			for (i; i < fileSize - 1; i++) {
				curPos = ioFile.tellg();
				GetElementOfBinFile(cur);
				nextPos = ioFile.tellg();
				GetElementOfBinFile(next);
				size = curPos - nextPos;

				ioFile.seekp(curPos, std::ios::beg);

				ioFile.write((char*)&next.articul, sizeof(int));
				ioFile.write((char*)&next.quantity, sizeof(int));
				ioFile.write((char*)&next.price, sizeof(double));
				int len = next.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(next.name.data(), len);
				nextPos = ioFile.tellp();

				ioFile.write((char*)&cur.articul, sizeof(int));
				ioFile.write((char*)&cur.quantity, sizeof(int));
				ioFile.write((char*)&cur.price, sizeof(double));
				len = cur.name.length();
				ioFile.write((char*)&len, sizeof(int));
				ioFile.write(cur.name.data(), len);

				ioFile.seekg(nextPos, std::ios::beg);
			}
			
			//chsize(_fileno(ioFile), size);
			ioFile.close();
			return;
		}
	}

	ioFile.close();
}

void File::ReadBinFormat() {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, std::ios::in | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Shoes temp;
	//for (int i = 0; i < fileSize; i++) {
	ioFile.seekg(0, std::ios::end);
	int size = ioFile.tellg();
	ioFile.seekg(0, std::ios::beg);
	while (ioFile.tellg() < size){
		GetElementOfBinFile(temp);
		std::cout << temp << std::endl;
	}

	ioFile.close();	
}

void File::WriteBinFormat(const Shoes& shoes) {
	try {
		ioFile.open(filePath, std::ios::out | std::ios::app | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}
	
	ioFile.write((char*)&shoes.articul, sizeof(int));
	ioFile.write((char*)&shoes.quantity, sizeof(int));
	ioFile.write((char*)&shoes.price, sizeof(double));
	int len = shoes.name.length();
	ioFile.write((char*)&len, sizeof(int));
	ioFile.write(shoes.name.data(), len);
	ioFile.close();
}

void File::GetElementOfBinFile(Shoes& temp) {
	int len;
	ioFile.read((char*)&temp.articul, sizeof(int));
	ioFile.read((char*)&temp.quantity, sizeof(int));
	ioFile.read((char*)&temp.price, sizeof(double));
	ioFile.read((char*)&len, sizeof(int));
	char* buf = new char[len + 1];
	ioFile.read(buf, len);
	buf[len] = 0;
	temp.name = buf;
	delete[] buf;
}

int File::CountElementOfBinFile() {
	int size = 0;

	try {
		ioFile.open(filePath, std::ios::in | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return 0;
	}
	ioFile.seekg(0, std::ios::end);
	int fileSize = ioFile.tellg();
	ioFile.seekg(0, std::ios::beg);

	while (ioFile.tellg() < fileSize) {
		Shoes temp;
		int len;
		ioFile.read((char*)&temp.articul, sizeof(int));
		ioFile.read((char*)&temp.quantity, sizeof(int));
		ioFile.read((char*)&temp.price, sizeof(double));
		ioFile.read((char*)&len, sizeof(int));
		char* buf = new char[len + 1];
		ioFile.read(buf, len);
		buf[len] = 0;
		temp.name = buf;
		delete[] buf;
		size++;
	}

	ioFile.close();
	return size;
}