#include <iostream>
#pragma warning(disable:4996)
using namespace std;

class myqueue {
private:
	int size;
	int elements[10];
	int front;
	int tail;
public:
	myqueue() : size(0), front(0), tail(0) {};
	bool isEmpty() {
		return size == 0;
	}
	bool isFull() {
		return size == 10;
	}
	bool push(int ele) {
		if (isFull()) {
			return false;
		}
		elements[tail] = ele;
		size++;
		tail = (tail + 1) % 10;
		return true;
	}
	int pop() {
		if (isEmpty()) {
			return NULL;
		}
		size--;
		int res = elements[front];
		front = (front + 1) % 10;
		return res;
	}
		
};

int main() {
	//freopen("Text5.txt", "r", stdin);
	int total;
	cin >> total;
	myqueue queueA, queueB;
	for (int i = 0; i < total; i++) {
		int id;
		cin >> id;
		if (id % 2 == 1) {
			queueA.push(id);
		}
		else {
			queueB.push(id);
		}
	}
	int time = 1;
	int isBegin = 1;
	cout << "½á¹ûÎª:" << endl;
	while (!queueA.isEmpty() || !queueB.isEmpty()) {
		
		if (!queueA.isEmpty()) {
			if (!isBegin) cout << ' ';
			cout << queueA.pop();
			isBegin = 0;
		}
		if (time % 2 == 0) {	
			if (!queueB.isEmpty()) {
				if (!isBegin) cout << ' ';
				cout << queueB.pop();
				isBegin = 0;
			}
		}
		time++;
	}
	system("pause");
	return 0;
}
