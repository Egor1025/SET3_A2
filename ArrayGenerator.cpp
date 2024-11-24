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