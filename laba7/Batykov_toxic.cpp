#include <iostream>

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
			if (temp->data > value) {
				temp = root->leftChild;
				continue;
			}
			else if (temp->data < value) {
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

int main() {
	BinaryTree<int> tree;
	tree.InsertNode(15);
	tree.InsertNode(16);
	tree.InsertNode(17);
	tree.InsertNode(2);
	tree.InsertNode(8);
	tree.InsertNode(1);

	Iterator<int> it = tree.Begin();
	while (1) {
		if (it == tree.End()) {
			std::cout << it.GetValue() << "; ";
			break;
		}
		std::cout << it.GetValue() << "; ";
		try {
			it.Next();
		}
		catch (int exIndex) {
			Exception ex(exIndex);
			ex.what();
		}
	}
	
	
	
	

	
	return 0;
}