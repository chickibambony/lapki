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

	Character() {
		hp = 100;
		name = "default";
	}

	void PrintInfoChar() {
		cout << "Name: " << name << endl;
		cout << "HP: " << hp << endl;
	}

	~Character() {

	}

protected:
	string name;
	int hp;
};

class Warrior : protected virtual Character
{
public:
	Warrior(string name, int hp, int armor, float damage) : Character(name, hp)
	{
		this->damage = damage;
		this->armor = armor;
	}

	void PrintInfoWarrior() {
		PrintInfoChar();
		cout << "Armor: " << armor << endl;
		cout << "Damage: " << damage << endl;
	}

	~Warrior() {

	}

protected:
	float damage;
	int armor;
};

class Knight : protected Warrior
{
public:
	Knight(string name, int hp, int armor, float damage, string skillName, float skillDamage) : Warrior(name, hp, armor, damage)
	{
		this->skillName = skillName;
		this->skillDamage = skillDamage;
	}

	void PrintInfoKnight() {
		PrintInfoWarrior();
		cout << "Skill name: " << skillName << endl;
		cout << "Skill damage: " << skillDamage << endl;
	}

	~Knight() {

	}

protected:
	string skillName;
	float skillDamage;
};

class Heeler : protected virtual Character
{
public:
	Heeler(string name, int hp, float heel, int potionCount) : Character(name, hp)
	{
		this->heel = heel;
		this->potionCount = potionCount;
	}

	void PrintInfoHeller() {
		PrintInfoChar();
		cout << "Heel: " << heel << endl;
		cout << "PotionCount: " << potionCount << endl;
	}

	~Heeler() {

	}

protected:
	float heel;
	int potionCount;
};

class Magician : protected Heeler
{
public:
	Magician(string name, int hp, float heel, int potionCount, string spellName, int spellDamage) : Heeler(name, hp, heel, potionCount)
	{
		this->spellName = spellName;
		this->spellDamage = spellDamage;
	}

	void PrintInfoMagician() {
		PrintInfoHeller();
		cout << "Spell name: " << potionCount << endl;
		cout << "Spell damage: " << potionCount << endl;
	}

	~Magician() {

	}

protected:
	string spellName;
	int spellDamage;
};

class Paladin : protected Magician, protected Knight
{
public:
	Paladin(string name, int hp, float heel, int potionCount, string spellName, int spellDamage, int armor, float damage, string skillName, float skillDamage, string XColor, int XCount)
		:Magician(name, hp, heel, potionCount, spellName, spellDamage), Knight(name, hp, armor, damage, skillName, skillDamage), Character(name, hp)
	{
		this->XColor = XColor;
		this->XCount = XCount;
	}

	void PrintInfoPaladin() {
		PrintInfoKnight();
		cout << "Heel: " << heel << endl;
		cout << "PotionCount: " << potionCount << endl;
		cout << "Spell name: " << potionCount << endl;
		cout << "Spell damage: " << potionCount << endl;
		cout << "XCount: " << XCount << endl;
		cout << "XColor: " << XColor << endl;
	}

	~Paladin() {

	}

private:
	string XColor;
	int XCount;
};

int GetValidInt(string);
float GetValidFloat(string);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string name, spellName, skillName, XColor;
	int hp, armor, XCount, potionCount;
	float damage, skillDamage, spellDamage, heel;

	//info input
	cout << "Name of Character: ";
	cin >> name;
	hp = GetValidInt("HP of Character");
	armor = GetValidInt("Armor of Character");
	damage = GetValidFloat("Damage of Character");
	heel = GetValidFloat("Heel of Character");
	potionCount = GetValidInt("Potion count");
	cout << "Name of spell: ";
	cin >> spellName;
	spellDamage = GetValidFloat("Damage of spell");
	cout << "Name of skill: ";
	cin >> skillName;
	skillDamage = GetValidFloat("Damage of skill");
	XCount = GetValidInt("Count of X");
	cout << "Color of X: ";
	cin >> XColor;

	system("cls");
	Paladin* test = new Paladin(name, hp, heel, potionCount, spellName, spellDamage, armor, damage, skillName, skillDamage, XColor, XCount);

	//info output
	cout << "Info about paladin" << endl;
	cout << "------------------" << endl;
	(*test).PrintInfoPaladin();
	delete test;
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