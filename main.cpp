#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class ArrayGenerator {
 public:
  ArrayGenerator(int maxSize, int rangeMin, int rangeMax)
      : maxSize(maxSize), rangeMin(rangeMin), rangeMax(rangeMax) {
    generateRandomArray();
    generateReverseSortedArray();
    generateAlmostSortedArray();
  }

  std::vector<int> getRandomArray(int size) {
    return {randomArray.begin(), randomArray.begin() + size};
  }

  std::vector<int> getReverseSortedArray(int size) {
    return {reverseSortedArray.begin(), reverseSortedArray.begin() + size};
  }

  std::vector<int> getAlmostSortedArray(int size) {
    return {almostSortedArray.begin(), almostSortedArray.begin() + size};
  }

 private:
  int maxSize;
  int rangeMin;
  int rangeMax;
  std::vector<int> randomArray;
  std::vector<int> reverseSortedArray;
  std::vector<int> almostSortedArray;

  void generateRandomArray() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(rangeMin, rangeMax);
    for (int i = 0; i < maxSize; ++i)
      randomArray.push_back(dis(gen));
  }

  void generateReverseSortedArray() {
    reverseSortedArray = randomArray;
    std::sort(reverseSortedArray.rbegin(), reverseSortedArray.rend());
  }

  void generateAlmostSortedArray() {
    almostSortedArray = randomArray;
    std::sort(almostSortedArray.begin(), almostSortedArray.end());
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < maxSize / 10; ++i) {
      int idx1 = gen() % maxSize;
      int idx2 = gen() % maxSize;
      std::swap(almostSortedArray[idx1], almostSortedArray[idx2]);
    }
  }
};


void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
  for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }

  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
}


void mergeSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void insertionSort(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

void hybridSort(std::vector<int>& arr, int left, int right, int threshold) {
  if (right - left < threshold) {
    insertionSort(arr, left, right);
    return;
  }

  int mid = left + (right - left) / 2;
  hybridSort(arr, left, mid, threshold);
  hybridSort(arr, mid + 1, right, threshold);
  merge(arr, left, mid, right);
}


class SortTester {
 public:
  void testSort(const std::vector<int>& arr, int threshold) {
    std::vector<int> testArray = arr;
    auto start = std::chrono::high_resolution_clock::now();
    if (threshold == -1)
      mergeSort(testArray, 0, testArray.size() - 1);
    else
      hybridSort(testArray, 0, testArray.size() - 1, threshold);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long usec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << usec;
  }
};


int main() {
  ArrayGenerator generator(10000, 0, 6000);
  SortTester tester;

  std::cout << "Size,Microseconds,,\n";
  for (int size = 500; size <= 10000; size += 100) {
    std::cout << size << ',';

//    tester.testSort(generator.getRandomArray(size), -1);
    tester.testSort(generator.getRandomArray(size), 15);
    std::cout << ',';

//    tester.testSort(generator.getReverseSortedArray(size), -1);
    tester.testSort(generator.getReverseSortedArray(size), 15);
    std::cout << ',';

//    tester.testSort(generator.getAlmostSortedArray(size), -1);
    tester.testSort(generator.getAlmostSortedArray(size), 15);
    std::cout << '\n';
  }
  return 0;
}