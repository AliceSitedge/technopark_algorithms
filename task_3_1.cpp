// 3_1. Реализовать очередь с динамическим зацикленным буфером.
// Требования: Очередь должна быть реализована в виде класса.

#include <iostream>

class Queue {
public:
    Queue() : buf(nullptr), size(0), head(nullptr), tail(nullptr) {
        increase_buf();
    }
    ~Queue() {
        delete[] buf;
    }
    void enqueue(int value) {
        if (is_empty()) {
            head = tail = buf;
            *head = value;
            return;
        }

        if (++tail == buf + size) {
            tail = buf;
        }

        // если буфер заполнен
        if (tail == head) {
            increase_buf();
        }

        *tail = value;
    }
    int dequeue() {
        if (is_empty()) {
            return -1;
        }

        int value = *head;

        if (head == tail) {
            head = tail = nullptr;
            return value;
        }

        if (++head == buf + size) {
            head = buf;
        }

        return value;
    }
    bool is_empty() const {
        return head == nullptr && tail == nullptr;
    }
private:
    int *buf;
    size_t size;
    int *head, *tail;
    void increase_buf() {
        if (size == 0) {
            // начальный размер
            size = 2;
            buf = new int[size];
        } else {
            int *old_buf = buf;
            size_t old_size = size;
            size *= 2;
            buf = new int[size];

            size_t i = 0;
            while(i == 0 || head != tail) {
                buf[i] = *head;
                if (++head == old_buf + old_size) {
                    head = old_buf;
                }
                i++;
            }

            head = buf;
            tail = head + i;

            delete[] old_buf;
        }
    }
};

int main() {
    Queue queue;

    int n = 0;
    std::cin >> n;

    int op = 0, val = 0;
    for (size_t i = 0; i < n; i++) {
        std::cin >> op >> val;

        switch(op) {
            case 2: {
                int value = queue.dequeue();
                if (value != val) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            }
            case 3: {
                queue.enqueue(val);
                break;
            }
            default:
                break;
        }
    }

    std::cout << "YES";
    return 0;
}
