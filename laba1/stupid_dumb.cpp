#include <iostream>
#include <iomanip>
 
using namespace std;

void Union(const string, string&);

int main() {
	string first, second, union_str;
	cout << "first subset: ";
	cin >> first;
	cout << "second subset: ";
	cin >> second;

	Union(first, union_str);
	Union(second, union_str);

	cout << setfill('+') << setw(40) << right << union_str;

	return 0;
}

void Union(const string str, string& union_str) {
	int flag;
	for (int i = 0; i < str.size(); i++) {
		flag = 1;
		for (int j = 0; j < union_str.size(); j++) {
			if (union_str[j] == str[i]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			union_str.push_back(str[i]);
		}
	}
}
