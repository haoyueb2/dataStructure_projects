#include <iostream>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
class MinHeap {
private:
	vector<int>  content;
	int size;
	int maxSize;
	//�������ϵ�����Ԫ�� 
	void swap(int index1, int index2) {
		int temp = content[index1];
		content[index1] = content[index2];
		content[index2] = temp;
	}
	//����һ���ڵ�������ӽڵ��н�С��Ԫ�ص����� 
	int minIndex(int i) {
		int minIndex;
		//��Ϊ0û�д�Ԫ�أ����Ե��������ʶ�ǿ��Ե�
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
		//0��λ�ò���
		content .resize(maxSize_+1);
		size = 0;
		maxSize = maxSize_;
	}
	//����һ���ڵ�����Ů������
	int leftIndex(int i) {
		return 2 * i;
	}
	//����һ���ڵ�����Ů������
	int rightIndex(int i) {
		return 2 * i + 1;
	}
	//����һ���ڵ㸸�ڵ�����
	int parent(int i) {
		return i / 2;
	}
	//��ָ��λ�õ�Ԫ�����ϵ��������ʵ�λ��
	void lift(int i) {
		while (i >= 1 && content[i] < content[parent(i)]) {
			swap(i, parent(i));
			i = parent(i);
		}
	}
	//����һ��Ԫ��
	void insert(int elem) {
		//0����Ԫ�أ�����size��Զ����Ԫ�صģ���Ԫ����size+1
		content[size + 1] = elem;
		size++;
		lift(size);
	}
	//��ĳ�Ѷ�Ԫ�����µ��������ʵ�λ�� 
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
	//ɾ�������ضѶ�����СԪ��
	int removeMin() {
		int res = content[1];
		content[1] = content[size];
		size--;
		sink();
		return res;
	}
	//���ضѵĴ�С
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
	cout << "�ܼ۸�Ϊ:" << endl;
	cout << totalPrice;
	delete priQueue;
	system("pause");
	return 0;
}
	