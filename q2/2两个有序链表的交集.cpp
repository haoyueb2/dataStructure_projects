#include <iostream>
#pragma warning(disable:4996)
using namespace std;
class LinkNode {
public:
	int data;
	LinkNode * link;
	LinkNode() :link(NULL) {}
	LinkNode(int data_) : data(data_), link(NULL) {}
};
class List {
private:
	LinkNode * sentinal;
	
		
public:
	List() {
		sentinal = new LinkNode();
	}
	~List() {
		LinkNode * p = sentinal;
		while (p->link != NULL) {
			LinkNode * tmp = p;
			p = p->link;
			delete p;
		}

	}
	void build() {
		LinkNode * p = sentinal;
		int data;
		cin >> data;
		while(data != -1) {
			p->link = new LinkNode(data);
			p = p->link;
			cin >> data;
		}
	}
	friend void output(List * l) {
		LinkNode * p = l->sentinal;
		if (p->link == NULL) {
			cout << "NULL" << endl;
			return;
		}
		p = p->link;
		while (p != NULL) {
			cout << p->data << ' ';
			p = p->link;
		}
		cout << endl;
	}

	friend List * intersection(List * a, List * b) {
		List * c = new List();
		LinkNode * pc = c->sentinal;
		LinkNode * pa = a->sentinal->link;
		LinkNode * pb = b->sentinal->link;
		while (pa != NULL && pb != NULL) {
			if (pa->data == pb->data) {
				pc->link = new LinkNode(pa->data);
				pc = pc->link;
				pa = pa->link;
				pb = pb->link;
			}
			else if (pa->data > pb->data) {
				pb = pb->link;
			}
			else {
				pa = pa->link;
			}
		}
		return c;
	}
};
int main() {
	//freopen("Text2.txt", "r", stdin);
	List * s1 = new List();
	List * s2 = new List();
	s1->build();
	s2->build();
	cout << "½á¹ûÎª:" << endl;
	output(intersection(s1, s2));
	system("pause");
	return 0;
}
	

