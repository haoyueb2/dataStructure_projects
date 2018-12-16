#include<iostream>
#include<ctime>
#include<cmath>
#include<cstring>
using namespace std;
//输入的数组，每回sort的实参，但排序并不会在这个数组直接排
static int *kArr;
//排序数组的大小
static int kNumber;
//因为有多处辅助函数，传参不太方便，就统一把交换次数count设为全局，每回sort完置零
static int kCount = 0;

//冒泡排序
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
	cout << "冒泡排序所用时间：      " << end - begin << "ms" << endl;
	cout << "冒泡排序交换次数：      " << kCount << endl;
	kCount = 0;
}

//选择排序
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
	cout << "选择排序所用时间：      " << end - begin << "ms" << endl;
	cout << "选择排序交换次数：      " << kCount << endl;
	kCount = 0;
}

//直接插入排序
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
	cout << "直接插入排序所用时间：      " << end - begin << "ms" << endl;
	cout << "直接插入排序交换次数：      " << kCount << endl;
	kCount = 0;
}

//希尔排序
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
	cout << "希尔排序所用时间：      " << end - begin << "ms" << endl;
	cout << "希尔排序交换次数：      " << kCount << endl;
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
//快速排序
void quickSort(int arr[]) {
	int *test;
	int begin, end;
	test = new int[kNumber];
	memcpy(test, arr, sizeof(int) * kNumber);
	begin = clock();
	quickSortHelp(test, 0, kNumber - 1);
	end = clock();
	delete[] test;
	cout << "快速排序所用时间：      " << end - begin << "ms" << endl;
	cout << "快速排序交换次数：      " << kCount << endl;
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
//堆排序
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
	cout << "堆排序所用时间：      " << end - begin << "ms" << endl;
	cout << "堆尔排序交换次数：      " << kCount << endl;
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
//归并排序
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
	cout << "归并排序所用时间：      " << end - begin << "ms" << endl;
	cout << "归并排序交换次数：      " << kCount << endl;
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
//基数排序
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
	cout << "基数排序所用时间：      " << end - begin << "ms" << endl;
	cout << "基数排序交换次数：      " << kCount << endl;
	kCount = 0;
}



int main() {
	cout << "**                               排序算法比较                               **" << endl;
	cout << "==============================================================================" << endl;
	cout << "**                              1 --- 冒泡排序                              **" << endl;
	cout << "**                              2 --- 选择排序                              **" << endl;
	cout << "**                              3 --- 直接插入排序                          **" << endl;
	cout << "**                              4 --- 希尔排序                              **" << endl;
	cout << "**                              5 --- 快速排序                              **" << endl;
	cout << "**                              6 --- 堆排序                                **" << endl;
	cout << "**                              7 --- 归并排序                              **" << endl;
	cout << "**                              8 --- 基数排序                              **" << endl;
	cout << "**                              9 --- 退出程序                              **" << endl;
	cout << "==============================================================================" << endl;

	int order;

	srand((int)time(NULL));

	cout << "请输入要产生的随机数的个数：";
	cin >> kNumber;
	kArr = new int[kNumber];
	for (int i = 0; i < kNumber; i++)
		kArr[i] = rand() % kNumber;

	cout << endl << "请选择排序算法:        ";
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
			cout << "输入有误!" << endl;
		}
		cout << endl << "请选择排序算法:        ";
		cin >> order;
	}
	delete[] kArr;
	return 0;
}