#include<iostream>
#include<ctime>
#include<cmath>
#include<cstring>
using namespace std;
//��������飬ÿ��sort��ʵ�Σ������򲢲������������ֱ����
static int *kArr;
//��������Ĵ�С
static int kNumber;
//��Ϊ�жദ�������������β�̫���㣬��ͳһ�ѽ�������count��Ϊȫ�֣�ÿ��sort������
static int kCount = 0;

//ð������
void bubbleSort(int arr[]) {
	int temp, *test;
	int begin, end;

	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);
	begin = clock();

	for (int i = 0; i < kNumber - 1; i++) {
		for (int k = 0; k < kNumber - 1 - i; k++) {
			if (test[k] > test[k + 1]) {
				temp = test[k];
				test[k] = test[k + 1];
				test[k + 1] = temp;
				kCount++;
			}
		}
	}
	end = clock();
	delete[] test;
	cout << "ð����������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "ð�����򽻻�������      " << kCount << endl;
	kCount = 0;
}

//ѡ������
void selectionSort(int arr[]) {//wrong
	int temp, *test;
	int begin, end;

	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);

	begin = clock();

	for (int i = 0; i < kNumber - 1; i++) {
		for (int k = i + 1; k < kNumber; k++) {
			if (test[i] > test[k]) {
				temp = test[i];
				test[i] = test[k];
				test[k] = temp;
				kCount++;
			}
		}
	}
	

	end = clock();
	delete[] test;
	cout << "ѡ����������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "ѡ�����򽻻�������      " << kCount << endl;
	kCount = 0;
}

//ֱ�Ӳ�������
void insertionSort(int arr[]) {
	int temp, *test, j;
	int begin, end;

	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);

	begin = clock();

	for (int i = 1; i < kNumber; i++) {
		if (test[i] < test[i - 1]) {
			kCount++;
			temp = test[i];
			j = i - 1;
			do {
				test[j + 1] = test[j];
				j--;
			} while (j >= 0 && temp < test[j]);
			test[j + 1] = temp;
		}
	}

	end = clock();
	delete[] test;
	cout << "ֱ�Ӳ�����������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "ֱ�Ӳ������򽻻�������      " << kCount << endl;
	kCount = 0;
}

//ϣ������
void shellSort(int arr[]) {
	int temp, *test, j, gap;
	int begin, end;

	gap = kNumber + 1;
	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);
	begin = clock();
	do {
		gap = (gap / 3) + 1;
		for (int i = gap; i < kNumber; i++) {
			if (test[i] < test[i - gap]) {
				kCount++;
				temp = test[i];
				j = i - gap;
				do {
					test[j + gap] = test[j];
					j = j - gap;
				} while (j > 0 && temp < test[j]);
				test[j + gap] = temp;
			}
		}
	} while (gap > 1);
	end = clock();
	delete[] test;
	cout << "ϣ����������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "ϣ�����򽻻�������      " << kCount << endl;
	kCount = 0;
}
void quickSortHelp(int arr[], const int left, const int right) {
	if (left >= right)
		return;
	int first = left;
	int last = right;
	int key = arr[first];
	kCount++;
	while (first < last) {
		while (first < last && arr[last] >= key)
			--last;
		arr[first] = arr[last];
		kCount++;
		while (first < last && arr[first] <= key)
			++first;
		arr[last] = arr[first];
		kCount++;
	}
	arr[first] = key;
	quickSortHelp(arr, left, first - 1);
	quickSortHelp(arr, first + 1, right);
}
//��������
void quickSort(int arr[]) {
	int *test;
	int begin, end;
	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);
	begin = clock();
	quickSortHelp(test, 0, kNumber - 1);
	end = clock();
	delete[] test;
	cout << "������������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "�������򽻻�������      " << kCount << endl;
	kCount = 0;
}

void HeapAdjust(int arr[], int i, int nLength) {
	int child, temp;
	for (; 2 * i < nLength; i = child) {
		child = 2 * i + 1;
		if (child < nLength - 1 && arr[child + 1] > arr[child])
			++child;
		if (arr[i] < arr[child]) {
			kCount++;
			temp = arr[i];
			arr[i] = arr[child];
			arr[child] = temp;
		}
		else
			break;
	}
}
//������
void heapSort(int arr[]) {
	int temp, *test;
	int begin, end;
	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);
	begin = clock();
	for (int i = kNumber / 2 - 1; i >= 0; --i)
		HeapAdjust(test, i, kNumber);
	for (int i = kNumber - 1; i >= 0; i--) {
		kCount++;
		temp = test[i];
		test[i] = test[0];
		test[0] = temp;
		HeapAdjust(test, 0, i);
	}

	end = clock();
	delete[] test;
	cout << "����������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "�Ѷ����򽻻�������      " << kCount << endl;
	kCount = 0;
}


void mergeHelp2(int arr[], int temp[], int start, int mid, int end) {
	int i = start, j = mid + 1, k = start;
	while (i != mid + 1 && j != end + 1) {
		if (arr[i] > arr[j]) {
			temp[k++] = arr[i++];
			kCount++;
		}
		else {
			temp[k++] = arr[j++];
			kCount++;
		}
	}
	while (i != mid + 1)
		temp[k++] = arr[i++];
	while (j != end + 1)
		temp[k++] = arr[j++];
	for (i = start; i <= end; i++)
		arr[i] = temp[i];
}

void mergeHelp1(int arr[], int temp[], int start, int end) {
	int mid;
	if (start < end) {
		mid = (start + end) / 2;
		mergeHelp1(arr, temp, start, mid);
		mergeHelp1(arr, temp, mid + 1, end);
		mergeHelp2(arr, temp, start, mid, end);
	}
}
//�鲢����
void mergeSort(int arr[]) {

	int *test, *temparr;
	int begin, end;

	temparr = new int[kNumber];
	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);
	begin = clock();
	mergeHelp1(test, temparr, 0, kNumber - 1);
	end = clock();
	delete[] test;
	cout << "�鲢��������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "�鲢���򽻻�������      " << kCount << endl;
	kCount = 0;
}


int getPlaces(int num) {
	int count = 1;
	int temp = num / 10;
	while (temp != 0) {
		count++;
		temp /= 10;
	}
	return count;
}

int getMax(int arr[], int n) {
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

void radixHelp(int arr[], int n, int place) {
	int buckets[10][100] = { NULL };
	int temp = (int)pow(10, place - 1);
	for (int i = 0; i < n; i++) {
		int row = (arr[i] / temp) % 10;
		for (int j = 0; j < 100; j++) {
			if (buckets[row][j] == NULL) {
				kCount++;
				buckets[row][j] = arr[i];
				break;
			}
		}
	}
	int k = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (buckets[i][j] != NULL) {
				arr[k] = buckets[i][j];
				buckets[i][j] = NULL;
				k++;
			}
		}
	}
}
//��������
void radixSort(int arr[]) {
	int getPlaces(int num);
	int getMax(int arr[], int n);
	void radixHelp(int arr[], int n, int place);

	int *test, max, maxPlaces;
	int begin, end;
	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);
	max = getMax(test, kNumber);
	maxPlaces = getPlaces(max);
	begin = clock();
	for (int i = 1; i <= maxPlaces; i++)
		radixHelp(test, kNumber, i);

	end = clock();
	delete[] test;
	cout << "������������ʱ�䣺      " << end - begin << "ms" << endl;
	cout << "�������򽻻�������      " << kCount << endl;
	kCount = 0;
}



int main() {
	cout << "**                               �����㷨�Ƚ�                               **" << endl;
	cout << "==============================================================================" << endl;
	cout << "**                              1 --- ð������                              **" << endl;
	cout << "**                              2 --- ѡ������                              **" << endl;
	cout << "**                              3 --- ֱ�Ӳ�������                          **" << endl;
	cout << "**                              4 --- ϣ������                              **" << endl;
	cout << "**                              5 --- ��������                              **" << endl;
	cout << "**                              6 --- ������                                **" << endl;
	cout << "**                              7 --- �鲢����                              **" << endl;
	cout << "**                              8 --- ��������                              **" << endl;
	cout << "**                              9 --- �˳�����                              **" << endl;
	cout << "==============================================================================" << endl;

	int order;

	srand((int)time(NULL));

	cout << "������Ҫ������������ĸ�����";
	cin >> kNumber;
	kArr = new int[kNumber];
	for (int i = 0; i < kNumber; i++)
		kArr[i] = rand() % kNumber;

	cout << endl << "��ѡ�������㷨:        ";
	cin >> order;
	while (order != 9) {
		switch (order) {
		case 1:
			bubbleSort(kArr);
			break;
		case 2:
			selectionSort(kArr);
			break;
		case 3:
			insertionSort(kArr);
			break;
		case 4:
			shellSort(kArr);
			break;
		case 5:
			quickSort(kArr);
			break;
		case 6:
			heapSort(kArr);
			break;
		case 7:
			mergeSort(kArr);
			break;
		case 8:
			radixSort(kArr);
			break;
		default:
			cout << "��������!" << endl;
		}
		cout << endl << "��ѡ�������㷨:        ";
		cin >> order;
	}
	delete[] kArr;
	return 0;
}