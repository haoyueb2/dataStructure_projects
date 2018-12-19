#include <iostream>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
class MinHeap {
private:
	vector<int>  content;
	int size;
	int maxSize;
	//交换堆上的两个元素 
	void swap(int index1, int index2) {
		int temp = content[index1];
		content[index1] = content[index2];
		content[index2] = temp;
	}
	//返回一个节点的左右子节点中较小的元素的索引 
	int minIndex(int i) {
		int minIndex;
		//因为0没有存元素，所以当做特殊标识是可以的
		if (leftIndex(i) > size) {
			return 0;
		}
		else if (rightIndex(i) > size) {
			return leftIndex(i);
		}
		if (content[leftIndex(i)] < content[rightIndex(i)]) {
			minIndex = leftIndex(i);
		}
		else {
			minIndex = rightIndex(i);
		}
		return minIndex;
	}
public:
	MinHeap() : content(NULL), size(0),maxSize(0) {}
	MinHeap(int maxSize_) {
		//0的位置不放
		content .resize(maxSize_+1);
		size = 0;
		maxSize = maxSize_;
	}
	//返回一个节点左子女的索引
	int leftIndex(int i) {
		return 2 * i;
	}
	//返回一个节点右子女的索引
	int rightIndex(int i) {
		return 2 * i + 1;
	}
	//返回一个节点父节点索引
	int parent(int i) {
		return i / 2;
	}
	//将指定位置的元素向上调整到合适的位置
	void lift(int i) {
		while (i >= 1 && content[i] < content[parent(i)]) {
			swap(i, parent(i));
			i = parent(i);
		}
	}
	//插入一个元素
	void insert(int elem) {
		//0不放元素，导致size永远是有元素的，新元素在size+1
		content[size + 1] = elem;
		size++;
		lift(size);
	}
	//将某堆顶元素向下调整到合适的位置 
	void sink() {
		int i = 1;
		int smaller = minIndex(i);
		while (content[i] > content[smaller]) {
			swap(i, smaller);
			i = smaller;
			smaller = minIndex(i);
			if (smaller == 0) {
				break;
			}
		}
	}
	//删除并返回堆顶的最小元素
	int removeMin() {
		int res = content[1];
		content[1] = content[size];
		size--;
		sink();
		return res;
	}
	//返回堆的大小
	int getSize() {
		return size;
	}
};
int main() {
	//freopen("Text7.txt", "r", stdin);
	int N;
	cin >> N;
	MinHeap * priQueue;
	priQueue = new MinHeap(N);
	int woodLength;
	
	for(int i = 0; i <N; i++) {
		cin >> woodLength;
		priQueue->insert(woodLength);
	}
	int totalPrice = 0;
	while (priQueue->getSize() >= 2) {
		int wood1 = priQueue->removeMin();
		int wood2 = priQueue->removeMin();
		int sum = wood1 + wood2;
		totalPrice += sum;
		priQueue->insert(sum);
	}
	cout << "总价格为:" << endl;
	cout << totalPrice;
	delete priQueue;
	system("pause");
	return 0;
}
	