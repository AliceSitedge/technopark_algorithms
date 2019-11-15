// 2_1. Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е. при добавлении очередного числа K в дерево с корнем root, если root->Key ≤ K, то узел K добавляется в
// правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
// Выведите элементы в порядке in-order (слева направо).

#include <iostream>
#include <stack>

template<class T, class Comparator=std::less<T>>
class BinaryTree {
    struct Node {
        explicit Node(const T &value) : value(value), left(nullptr), right(nullptr) {}
        T value;
        Node *left;
        Node *right;
    };
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {}

    bool add(const T &value) {
        Node *current_node = root;

        while (true) {
            if (current_node == nullptr) {
                current_node = new Node(value);
                return true;
            }

            if (current_node->value == value) {
                return false;
            }

            if (cmp(current_node->value, value)) {
                current_node = current_node->right;
            } else {
                current_node = current_node->left;
            }
        }
    }
    void print() const {
        std::stack<Node> stack;

        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        Node *current_node = root;
        while (current_node != nullptr) {
            while (current_node->left != nullptr) {
                stack.top(current_node->left);
                current_node = current_node->left;
            }

            if (!stack.empty()) {
                current_node = stack.pop();
                std::cout << current_node->value << " ";
                current_node = current_node->right;
            }
        }

        std::cout << std::endl;
    }
private:
    Node *root;
    Comparator cmp = Comparator();
};
