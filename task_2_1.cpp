// 2_1. Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е. при добавлении очередного числа K в дерево с корнем root, если root->Key ≤ K, то узел K добавляется в
// правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
// Выведите элементы в порядке in-order (слева направо).

#include <iostream>
#include <stack>
#include <queue>

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

    ~BinaryTree() {
        std::queue<Node *> queue;

        if (root != nullptr) {
            queue.push(root);
        }

        while (!queue.empty()) {
            Node *node = queue.front();
            queue.pop();

            if (node->left != nullptr) {
                queue.push(node->left);
                node->left = nullptr;
            }
            if (node->right != nullptr) {
                queue.push(node->right);
                node->right = nullptr;
            }

            if (node->left == nullptr && node->right == nullptr) {
                delete node;
            } else {
                queue.push(node);
            }
        }
    }

    bool add(const T &value) {
        if (root == nullptr) {
            root = new Node(value);
            return true;
        }

        Node *current_node = root;
        while (true) {
            if (current_node->value == value) {
                return false;
            }

            if (cmp(current_node->value, value)) {
                if (current_node->right == nullptr) {
                    current_node->right = new Node(value);
                    return true;
                }
                current_node = current_node->right;
            } else {
                if (current_node->left == nullptr) {
                    current_node->left = new Node(value);
                    return true;
                }
                current_node = current_node->left;
            }
        }
    }

    void print() const {
        std::stack<Node *> stack;

        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        Node *current_node = root;
        while (true) {
            while (current_node != nullptr) {
                stack.push(current_node);
                current_node = current_node->left;
            }

            if (!stack.empty()) {
                current_node = stack.top();
                stack.pop();
                std::cout << current_node->value << " ";
                current_node = current_node->right;
            } else {
                break;
            }
        }

        std::cout << std::endl;
    }

private:
    Node *root;
    Comparator cmp = Comparator();
};

int main() {
    BinaryTree<int> tree;

    int size = 0;
    std::cin >> size;
    for (int i = 0; i < size; i++) {
        int elem = 0;
        std::cin >> elem;
        tree.add(elem);
    }

    tree.print();
    return 0;
}
