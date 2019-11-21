// 3_1. Дано число N < 10^6 и последовательность пар целых чисел из [-2^31..2^31] длиной N.
// Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
// Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
// Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
// При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное
// поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся
// два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
// Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
// Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.

#include <iostream>
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

    size_t get_height() {
        if (root == nullptr) {
            return 0;
        }

        std::queue<Node *> queue;
        queue.push(root);
        queue.push(nullptr);
        size_t height = 0;
        while (!queue.empty()) {
            Node *node = queue.front();
            queue.pop();

            if (node == nullptr) {
                if (!queue.empty()) {
                    queue.push(nullptr);
                }
                height++;
            } else {
                if (node->left != nullptr) {
                    queue.push(node->left);
                }
                if (node->right != nullptr) {
                    queue.push(node->right);
                }
            }
        }

        return height;
    }

private:
    Node *root;
    Comparator cmp = Comparator();
};

template<class T, class Comparator=std::less<T>>
class Treap {
    struct Node {
        Node(const T &value, int priority) : value(value), priotiry(priority), left(nullptr), right(nullptr) {}

        T value;
        int priotiry;
        Node *left;
        Node *right;
    };

public:
    Treap() : root(nullptr) {}

    ~Treap() {
        destroy_tree(root);
    }

    void add(const T &value, int priority) {
        if (root == nullptr) {
            root = new Node(value, priority);
            return;
        }

        if (root->priotiry < priority) {
            Node *tmp = root;
            root = new Node(value, priority);
            split(tmp, value, root->left, root->right);
            return;
        }

        Node *current_node = root;
        while (true) {
            if (cmp(current_node->value, value)) {
                if (current_node->right == nullptr) {
                    current_node->right = new Node(value, priority);
                    return;
                }

                if (current_node->right->priotiry < priority) {
                    Node *tmp = current_node->right;
                    current_node->right = new Node(value, priority);
                    split(tmp, value, current_node->right->left, current_node->right->right);
                    return;
                }

                current_node = current_node->right;
            } else {
                if (current_node->left == nullptr) {
                    current_node->left = new Node(value, priority);
                    return;
                }

                if (current_node->left->priotiry < priority) {
                    Node *tmp = current_node->left;
                    current_node->left = new Node(value, priority);
                    split(tmp, value, current_node->left->left, current_node->left->right);
                    return;
                }

                current_node = current_node->left;
            }
        }
    }

    size_t get_height() {
        return find_height(root);
    }

private:
    Node *root;
    Comparator cmp = Comparator();

    void destroy_tree(Node *node) {
        if (node) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

    void split(Node *current_node, const T &value, Node *&left, Node *&right) {
        if (current_node == nullptr) {
            left = nullptr;
            right = nullptr;
        } else if (cmp(current_node->value, value)) {
            split(current_node->right, value, current_node->right, right);
            left = current_node;
        } else {
            split(current_node->left, value, left, current_node->left);
            right = current_node;
        }
    }

    size_t find_height(Node *node) {
        if (node == nullptr) {
            return 0;
        }

        return 1 + std::max(find_height(node->left), find_height(node->right));
    }
};

int main() {
    BinaryTree<int> binary_tree;
    Treap<int> treap;

    int size = 0;
    std::cin >> size;

    int value = 0, priority = 0;
    for (int i = 0; i < size; i++) {
        std::cin >> value >> priority;
        binary_tree.add(value);
        treap.add(value, priority);
    }

    std::cout << binary_tree.get_height() - treap.get_height();

    return 0;
}
