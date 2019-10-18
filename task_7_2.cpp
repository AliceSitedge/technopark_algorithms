// 7_2. LSD для long long.
// Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106. Отсортировать массив
// методом поразрядной сортировки LSD по байтам.

#include <iostream>
#include <cstring>

#define DIGITS_NUMBER 256
#define BYTES_NUMBER 8
#define BITS_IN_BYTE 8
#define LS_BYTE 255

void sort_digit(long long *arr, int n, int digit) {
    int *entries = new int[DIGITS_NUMBER]();

    for (int j = 0; j < n; j++) {
        long long digit_value = (arr[j] >> (BITS_IN_BYTE * digit)) & LS_BYTE;
        entries[digit_value]++;
    }

    for (int j = 1; j < DIGITS_NUMBER; j++) {
        entries[j] += entries[j - 1];
    }

    auto temp = new long long[n];
    for (int j = n - 1; j >= 0; j--) {
        long long digit_value = (arr[j] >> (BITS_IN_BYTE * digit)) & LS_BYTE;
        temp[--entries[digit_value]] = arr[j];
    }

    memcpy(arr, temp, n * sizeof(long long));
    delete[] entries;
    delete[] temp;
}

void lsd(long long *arr, int n) {
    for (int i = 0; i < BYTES_NUMBER; i++) {
        sort_digit(arr, n, i);
    }
}

int main() {
    int n = 0;
    std::cin >> n;

    auto arr = new long long[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    lsd(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }

    delete[] arr;
    return 0;
}
