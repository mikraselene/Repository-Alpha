#include <iostream>
#include <vector>

enum {
  INSERTION,
  BUBBLE,
  SELECTION,
  SHELL,
  MERGE,
  QUICK,
  HEAP,
  INTRO,
};

template <class T>
class Sorting {
 public:
  Sorting(std::vector<T> arr, int code) {
    array = arr;
    len = arr.size();
    switch (code) {
      case INSERTION:
        InsertionSort();
        break;
      case BUBBLE:
        BubbleSort();
        break;
      case SELECTION:
        SelectionSort();
        break;
      case SHELL:
        ShellSort();
        break;
      case MERGE:
        MergeSort(0, len - 1);
        break;
      case QUICK:
        QuickSort(0, len - 1);
        break;
      case HEAP:
        HeapSort();
        break;
      case INTRO:
        IntroSort();
        break;
      default:
        break;
    }
    copy(array.begin(), array.end(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
  }

 private:
  void InsertionSort() {
    for (int i = 1; i != len; i++) {
      int j;
      int key = array[i];
      for (j = i - 1; j >= 0 && array[j] > key; j--) {
        array[j + 1] = array[j];
      }
      array[j + 1] = key;
    }
  }
  void BubbleSort() {
    for (int i = 0; i < len - 1; i++) {
      for (int j = 0; j < len - 1; j++) {
        if (array[j] > array[j + 1]) {
          std::swap(array[j], array[j + 1]);
        }
      }
    }
  }
  void SelectionSort() {
    for (int i = 0; i < len - 1; i++) {
      int min = i;
      for (int j = i + 1; j < len; j++) {
        if (array[j] < array[min]) {
          min = j;
        }
      }
      std::swap(array[i], array[min]);
    }
  }
  void ShellSort() {
    int h = 1;
    while (h < len / 3) {
      h = 3 * h + 1;
    }
    while (h >= 1) {
      for (int i = h; i < len; i++) {
        for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
          std::swap(array[j], array[j - h]);
        }
      }
      h = h / 3;
    }
  }
  void MergeSort(int lo, int hi) {
    if (lo < hi) {
      int mid = (lo + hi) / 2;
      MergeSort(lo, mid);
      MergeSort(mid + 1, hi);
      std::vector<int> left_subarray(array.begin() + lo,
                                     array.begin() + mid + 1);
      std::vector<int> right_subarray(array.begin() + mid + 1,
                                      array.begin() + hi + 1);
      int left = 0;
      int right = 0;
      left_subarray.insert(left_subarray.end(),
                           std::numeric_limits<int>::max());
      right_subarray.insert(right_subarray.end(),
                            std::numeric_limits<int>::max());
      for (int i = lo; i <= hi; i++) {
        if (left_subarray[left] < right_subarray[right]) {
          array[i] = left_subarray[left];
          left++;
        } else {
          array[i] = right_subarray[right];
          right++;
        }
      }
    }
  }
  void QuickSort(int lo, int hi) {
    if (lo < hi) {
      int i = lo - 1;
      for (int j = lo; j < hi; j++) {
        if (array[j] <= array[hi]) {
          i++;
          std::swap(array[i], array[j]);
        }
      }
      std::swap(array[i + 1], array[hi]);
      int p = i + 1;
      QuickSort(lo, p - 1);
      QuickSort(p + 1, hi);
    }
  }
  void HeapSort() {
    auto max_heapify = [=](int start, int end) {
      int parent = start;
      int child = parent * 2 + 1;
      while (child <= end) {
        if (child + 1 <= end && array[child] < array[child + 1]) {
          child++;
        }
        if (array[parent] > array[child]) {
          return;
        } else {
          std::swap(array[parent], array[child]);
          parent = child;
          child = parent * 2 + 1;
        }
      }
    };
    for (int i = len / 2 - 1; i >= 0; i--) {
      max_heapify(i, len - 1);
    }
    for (int i = len - 1; i > 0; i--) {
      std::swap(array[0], array[i]);
      max_heapify(0, i - 1);
    }
  }
  void IntroSort() { sort(array.begin(), array.end()); }

  std::vector<T> array;
  int len;
};

int main() {
  std::vector<int> d = {10, 2, 3,  44, 5, 3,   43, 1, 5,
                        7,  3, 34, 5,  3, 245, 64, 3, 4};
  for (int i = 0; i <= 7; i++) {
    Sorting<int>(d, i);
  }
}
