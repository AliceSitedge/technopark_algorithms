// 4_2. Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух
// чисел равно их сумме.
// Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от
// порядка вычислений.
// ((1+2)+3) -> 1+2 + 3+3 = 9
// ((1+3)+2) -> 1+3 + 4+2 = 10
// ((2+3)+1) -> 2+3 + 5+1 = 11
// Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы
// заданного набора чисел.

#include <iostream>
#include <cassert>
#include <functional>

template <class T, class Comparator = std::less<T>>
class Heap {
public:
    Heap() : buf(nullptr), buf_size(0), heap_size(0) {
        increase_heap();
    }
    Heap(const T *arr, size_t n) : buf(new T[n]), buf_size(n), heap_size(n) {
        for(size_t i = 0; i < n; i++) {
            buf[i] = arr[i];
        }
        build_heap();
    }
    ~Heap() {
        delete[] buf;
    }

    void insert(T value) {
        if (buf_size == heap_size) {
            increase_heap();
        }

        heap_size++;
        buf[heap_size - 1] = value;
        sift_up(heap_size - 1);
    }
    T extract_top() {
        assert(heap_size != 0);

        T value = buf[0];
        buf[0] = buf[--heap_size];
        if (heap_size != 0) {
            sift_down(0);
        }

        return value;
    }
    T peek_top() const {
        assert(heap_size != 0);
        return buf[0];
    }
    bool is_empty() const {
        return heap_size == 0;
    }

private:
    T *buf;
    size_t buf_size;
    size_t heap_size;
    Comparator cmp = Comparator();

    void increase_heap() {
        T *old_buf = buf;

        buf_size *= 2;
        buf = new T[buf_size];
        for (size_t i = 0; i < heap_size; i++) {
            buf[i] = old_buf[i];
        }

        delete[] old_buf;
    }
    void build_heap() {
        for (size_t i = heap_size / 2 - 1; i > 0; i--) {
            sift_down(i);
        }
        sift_down(0);
    }
    void sift_down(size_t i) {
        size_t left = i * 2 + 1;
        size_t right = i * 2 + 2;

        size_t i_top = i;

        if (left < heap_size && cmp(buf[left], buf[i])) {
            i_top = left;
        }
        if (right < heap_size && cmp(buf[right], buf[i_top])) {
            i_top = right;
        }

        if (i_top != i) {
            std::swap(buf[i_top], buf[i]);
            sift_down(i_top);
        }
    }
    void sift_up(size_t i) {
        if (i == 0) {
            return;
        }

        size_t parent = (i - 1) / 2;
        if (buf[i] < buf[parent]) {
            std::swap(buf[i], buf[parent]);
            sift_up(parent);
        }
    }
};

template <class T>
struct more {
    bool operator()(const T& l, const T& r) {
        return l > r;
    }
};

int main() {
    int n = 0;
    std::cin >> n;

    int *arr = new int[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    Heap<int> heap(arr, size_t(n));
    int elem1 = 0, elem2 = 0;
    int sum = 0;
    while (!heap.is_empty()) {
        elem1 = heap.extract_top();

        if (heap.is_empty()) {
            std::cout << sum;
        } else {
            elem2 = heap.extract_top();
            sum += elem1 + elem2;
            heap.insert(elem1 + elem2);
        }
    }

    delete[] arr;
    return 0;
}
