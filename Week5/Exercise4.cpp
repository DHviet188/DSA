#include<bits/stdc++.h>
using namespace std;

typedef struct Node* node;

class Student {
	private:
	string Class;
    string name;

	public:
	Student() {
		Class = "NA";
		name = "NA";
	}

	void setName(string _name) {
		this->name = _name;
	}

	string getName() {
		return this->name;
	}
	
    void setClass(string _class) {
		this->Class = _class;
	}

	string getClass() {
		return this->Class;
	}
};

class Node {
	int data;
	Node* next;
};

map<int, Student> mp;

void Insert(int ID, string Name, string Class) {
	Student x;
	x.setName(Name);
	x.setClass(Class);
	mp[ID] = x;
}

void INFO(int ID) {
	for(auto tmp : mp) {
		if(tmp.first == ID) {
			cout << tmp.first << " " << tmp.second.getName() << " " << tmp.second.getClass() << endl;
			return;
		}
	}
	cout <<" NA" << ",NA" << endl;
}
void DELETE(int tmp) {
	mp.erase(tmp);
}
int main()
{  
	
	
	Insert(1, "Tuan", "K61KS");
	Insert(2, "Vuong Thi Hai Yen", "k55");
	INFO(3);
	INFO(2);
	DELETE(2);
	INFO(2);
	



	return 0;
}

