// 2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента
// массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]:
// A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
// Требования:  Время работы поиска k для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого
// B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k, а потом уже в нем делать
// бинарный поиск.

#include <iostream>

// поиск диапазона
int find_range(const int *arr, int n, int elem, int &first, int &last) {
    first = 0, last = 1;
    while (first < n) {
        if (last > n) {
            last = n;
        }

        if (arr[last - 1] >= elem) {
            break;
        }

        first = last;
        last *= 2;
    }

    if (first >= n) {
        return -1;
    }

    return 0;
}

// поиск элемента, равного или большего elem
int find_index(const int *arr, int elem, int &first, int &last) {
    while (first < last) {
        int mid = (first + last) / 2;
        if (arr[mid] < elem) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }

    return first;
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;

    int *arr_a = new int[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr_a[i];
    }

    int elem = 0;
    for (size_t i = 0; i < m; i++) {
        std::cin >> elem;
        int first = 0, last = 0;
        if (find_range(arr_a, n, elem, first, last) == -1) {
            std::cout << n << ' ';
        } else {
            std::cout << find_index(arr_a, elem, first, last) << ' ';
        }
    }

    delete[] arr_a;
    return 0;
}
