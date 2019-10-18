// 5_4. На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка
// (Li и Ri). Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.

#include <iostream>
#include <cstring>

#define SEGMENT_BEGIN 1
#define SEGMENT_END -1

struct Point {
    explicit Point(int cd = 0, int sn = 0) : coord(cd), sign(sn) {}
    int coord;
    int sign;
};

namespace std {
    template<>
    struct less<Point> {
        bool operator()(Point &lhs, Point &rhs) {
            return lhs.coord < rhs.coord;
        }
    };
}

template<class T, class Comparator = std::less<T>>
void merge(T *first, int first_len, T *second, int second_len, T *dest, Comparator cmp = Comparator()) {
    int ptr1 = 0;
    int ptr2 = 0;
    int i = 0;

    while (ptr1 != first_len && ptr2 != second_len) {
        if (cmp(first[ptr1], second[ptr2])) {
            dest[i++] = first[ptr1++];
        } else {
            dest[i++] = second[ptr2++];
        }
    }

    if (ptr1 == first_len) {
        memcpy(dest + i, second + ptr2, (second_len - ptr2) * sizeof(T));
    } else {
        memcpy(dest + i, first + ptr1, (first_len - ptr1) * sizeof(T));
    }
}

template<class T, class Comparator = std::less<T>>
void merge_sort(T *arr, int n, Comparator cmp = Comparator()) {
    if (n == 1) {
        return;
    }

    int first_len = n / 2;
    int second_len = n - first_len;
    merge_sort(arr, first_len, cmp);
    merge_sort(arr + first_len, second_len, cmp);

    T *temp = new T[n];
    merge(arr, first_len, arr + first_len, second_len, temp, cmp);

    memcpy(arr, temp, n * sizeof(T));
    delete[] temp;
}

int main() {
    int n = 0;
    std::cin >> n;

    int points_num = n * 2;
    auto arr = new Point[points_num];
    
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i].coord;
        arr[i].sign = SEGMENT_BEGIN;
        std::cin >> arr[i + n].coord;
        arr[i + n].sign = SEGMENT_END;
    }

    merge_sort(arr, points_num);

    int sum = 0;
    int layer = 0;
    for (int i = 0; i < points_num; i++) {
        if (layer == 1) {
            sum += arr[i].coord - arr[i - 1].coord;
        }
        layer += arr[i].sign;
    }

    std::cout << sum;

    delete[] arr;
    return 0;
}
