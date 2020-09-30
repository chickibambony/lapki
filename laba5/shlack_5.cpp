#include <iostream>
#include <windows.h>

using namespace std;

class Character 
{
public:
	Character(string name, int hp) {
		this->name = name;
		this->hp = hp;
	}

	virtual void PrintInfo() = 0;
	virtual int GetLevel() = 0;
	virtual ~Character() {}

protected:
	string name;
	int hp;
};

class Warrior : public Character
{
public:
	Warrior(string name, int hp, int armor, float damage) : Character(name, hp)
	{
		this->damage = damage;
		this->armor = armor;
	}

	void PrintInfo() override{		
		cout << "Name: " << name << endl;
		cout << "HP: " << hp << endl;
		cout << "Armor: " << armor << endl;
		cout << "Damage: " << damage << endl;
	}

	int GetLevel() override{
		return hp / 10 + damage / 10;
	}

	~Warrior() {}

protected:
	float damage;
	int armor;
};

class Knight : public Warrior
{
public:
	Knight(string name, int hp, int armor, float damage, string skillName, float skillDamage) : Warrior(name, hp, armor, damage)
	{
		this->skillName = skillName;
		this->skillDamage = skillDamage;
	}

	void PrintInfo() override {
		cout << "Name: " << name << endl;
		cout << "HP: " << hp << endl;
		cout << "Armor: " << armor << endl;
		cout << "Damage: " << damage << endl;
		cout << "Skill name: " << skillName << endl;
		cout << "Skill damage: " << skillDamage << endl;
	}

	int GetLevel() override {
		return hp / 10 + damage / 10 + skillDamage / 10;
	}

	~Knight() {}

protected:
	string skillName;
	float skillDamage;
};

class Heeler : public Character
{
public:
	Heeler(string name, int hp, float heel, int potionCount) : Character(name, hp)
	{
		this->heel = heel;
		this->potionCount = potionCount;
	}

	void PrintInfo() override {
		cout << "Name: " << name << endl;
		cout << "HP: " << hp << endl;
		cout << "Heel: " << heel << endl;
		cout << "PotionCount: " << potionCount << endl;
	}

	int GetLevel() override {
		return hp / 10 + heel / 10;
	}

	~Heeler() {}

protected:
	float heel;
	int potionCount;
};

int GetValidInt(string);
float GetValidFloat(string);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int count = 3;
	Character** chars = new Character*[count];
	chars[0] = new Heeler("Heeler", 100, 30, 5);
	chars[1] = new Warrior("Warrior", 130, 150, 35);
	chars[2] = new Knight("Knight", 150, 200, 50, "Uppercut", 75);

	for (int i = 0; i < count; i++) {
		cout << "Info about character" << endl;		
		chars[i]->PrintInfo();
		cout << "Lever of charcter: " << chars[i]->GetLevel() << endl ;
		cout << "_____________________" << endl << endl;
	}

	for (int i = 0; i < count; i++) {
		delete chars[i];
	}
	delete[] chars;

	/*Heeler *heeler = new Heeler("Heeler", 100, 30, 5);
	Warrior *warrior = new Warrior("Warrior", 130, 150, 35);
	Knight* knight = new Knight("Knight", 150, 200, 50, "Uppercut", 75);

	chars[0] = heeler;
	chars[1] = warrior;
	chars[2] = knight;*/

	return 0;
}

int GetValidInt(string title) {
	int temp;
	cout << title << ": ";

	while (true) {
		cin >> temp;
		if (cin.fail() || temp < 0) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << title << ": ";
		}
		else {
			cin.ignore(32767, '\n');
			return temp;
		}
	}
};

float GetValidFloat(string title) {
	float temp;
	cout << title << ": ";

	while (true) {
		cin >> temp;
		if (cin.fail() || temp < 0) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << title << ": ";
		}
		else {
			cin.ignore(32767, '\n');
			return temp;
		}
	}
};