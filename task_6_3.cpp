// 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте
// методом прохода двумя итераторами от начала массива к концу.

#include <iostream>
#include <random>

template<class T, class Comparator = std::less<T>>
int partition(T *arr, int left, int right, Comparator cmp = Comparator()) {
    int pivot_pos = right == 0 ? 0 : rand() % (right - left + 1) + left;
    std::swap(arr[pivot_pos], arr[right]);

    int i = left;
    while (i != right && !cmp(arr[right], arr[i])) {
        i++;
    }
    if (i == right) {
        return right;
    }

    int j = i + 1;
    while (j != right) {
        if (!cmp(arr[right], arr[j])) {
            std::swap(arr[j], arr[i]);
            i++;
        }
        j++;
    }

    std::swap(arr[i], arr[right]);
    return i;
}

template<class T, class Comparator = std::less<T>>
int kth_statistic(T *arr, int left, int right, int k, Comparator cmp = Comparator()) {
    int pivot_pos = partition(arr, left, right, cmp);

    while (pivot_pos != k) {
        if (pivot_pos < k) {
            left = pivot_pos + 1;
        } else {
            right = pivot_pos - 1;
        }
        pivot_pos = partition(arr, left, right, cmp);
    }

    return arr[pivot_pos];
}

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    srand((unsigned int)time(nullptr));
    std::cout << kth_statistic(arr, 0, n - 1, k);

    return 0;
}
