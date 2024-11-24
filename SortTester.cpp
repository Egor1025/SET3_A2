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