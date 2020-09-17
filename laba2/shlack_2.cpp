#include <iostream>
using namespace std;

//Declaration
class Detail {
private:
	static size_t counter;
	size_t id;
	string name;
	float mass;
	void CheckValue();

public:
	Detail();
	Detail(string, float);
	~Detail();

	friend void Output(const Detail&);
	friend class Control;
};

class Control {
public:
	void setMass(Detail&, float);
};

void Output(const Detail&);
size_t Detail::counter = 1;

//MAIN
int main() {
	Control control;
	const size_t size = 3;

	Detail def;
	Detail display("Display", 1.5f);

	Output(def);
	Output(display);

	control.setMass(def, 1.f);
	control.setMass(display, 2.5f);

	Output(def);
	Output(display);

	Detail system_unit[size]{
		Detail("CPU", 0.7f),
		Detail("GPU", -2.3f),
		Detail("Memory", 1.4f)
	};

	for (size_t i = 0; i < size; i++) {
		Output(system_unit[i]);
	}

	control.setMass(system_unit[0], 0.5f);
	control.setMass(system_unit[1], 3.3f);
	control.setMass(system_unit[2], 2.2f);

	for (size_t i = 0; i < size; i++) {
		Output(system_unit[i]);
	}
	return 0;
}

//DESCRIPTION
void Detail::CheckValue() {
	if (mass < 0) {
		mass *= -1;
	}
}

Detail::Detail() {
	name = "default";
	mass = 0.f;
	id = counter++;
}

Detail::Detail(string name, float mass) {
	this->name = name;
	this->mass = mass;
	CheckValue();
	id = counter++;
}

Detail::~Detail() {

}

void Control::setMass(Detail& temp, float newMass) {
	temp.mass = newMass;
}

void Output(const Detail& temp) {
	cout << "Detail ID: " << temp.id << endl;
	cout << "Detail name: " << temp.name << endl;
	cout << "Detail mass: " << temp.mass << "kg" << endl;
	cout << "==============================" << endl << endl;
}


