#include <iostream>
#include <map>
#include <string>
#pragma warning(disable:4996)
using namespace std;
template <class T>
class stack {
private:
	int size;
	T elements[50];
public:
	stack() : size(0) {};
	bool isFull() {
		return size == 50;
	}
	bool isEmpty() {
		return size == 0;
	}
	int Totalsize() {
		return size;
	}
	bool push(T elem) {
		if (isFull()) {
			return false;
		}
		elements[size] = elem;
		size++;
		return true;
	}
	T pop() {
		if (isEmpty()) {
			return NULL;
		}
		T elem = elements[size - 1];
		size--;
		return elem;
	}
	T peek() {
		if (isEmpty()) {
			return NULL;
		}
		return elements[size - 1];
	}
};
//设置输出函数和这个变量只是为了规范化输出使最后无空格
static bool isBegin = true;
template <class T>
void output(T elem) {
	if (isBegin) {
		cout << elem;
		isBegin = false;
	}
	else {
		cout << ' ' << elem;
	}
}

int main() {
	//freopen("Text4.txt", "r", stdin);
	map<string, int> opera_pri = { {"+",1},{"-",1},{"*",2},{"/",2},{"(",3},{")",3} };
	stack<string> opera_stack;
	string input[25];
	int total = 0;
	cout << "请输入，空格分割，请用半角符号，按ctrl+z停止输入:" << endl;
	while (cin >> input[total]) {
		total++;
	}
	cout << "结果为:" << endl;
	for (int i = 0; i < total; i++) {
		//首位是数字或者长度大于零的string判断为数字
		if (isdigit(input[i][0]) || input[i].size() > 1) {
			output(stod(input[i]));
		}
		else  if (opera_pri.count(input[i]) > 0) {
			if (input[i] == "(") {
				opera_stack.push(input[i]);
			}
			else if (input[i] == ")") {
				while (opera_stack.peek() != "(") {
					output(opera_stack.pop());
				}
				opera_stack.pop();
			}
			else if (!opera_stack.isEmpty()) {
				//左括号特殊处理是因为其优先级本来是高的，但不符合一般情况
				if (opera_stack.peek() == "(" || opera_pri[input[i]] > opera_pri[opera_stack.peek()]) {
					opera_stack.push(input[i]);
				}
				else {
					while (!opera_stack.isEmpty() && opera_stack.peek() != "(" &&(opera_pri[input[i]] <= opera_pri[opera_stack.peek()])) {
						output(opera_stack.pop());
					}
					opera_stack.push(input[i]);
				}
			} else if(opera_stack.isEmpty()){
				opera_stack.push(input[i]);
			}

		}
	}
	//输出还留在栈里的符号
	while (!opera_stack.isEmpty()) {
		output(opera_stack.pop());
	}

	return 0;
}


