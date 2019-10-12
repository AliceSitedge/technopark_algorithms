// 1_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале
// вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке
// обхода по часовой стрелке.
// n < 1000, координаты < 10000.
// Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей
// трапеций под каждой стороной многоугольника.

#include <iostream>

struct Point {
    Point(): x(0), y(0) {}
    int x;
    int y;
};

float get_area(const Point *arr, int n) {
    float area = 0.0;

    if (n < 3) {
        return 0.0;
    }

    // вычисление ориентированных площадей трапеций
    for (size_t i = 1; i < n; i++) {
        area += float((arr[i].x - arr[i-1].x) * (arr[i].y + arr[i-1].y)) / 2;
    }
    area += float((arr[0].x - arr[n - 1].x) * (arr[0].y + arr[n - 1].y)) / 2;

    if (area < 0) {
        area = -area;
    }

    return area;
}

int main() {
    int n = 0;
    std::cin >> n;

    auto arr = new Point[n];

    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i].x >> arr[i].y;
    }

    std::cout << get_area(arr, n);

    delete[] arr;

    return 0;
}