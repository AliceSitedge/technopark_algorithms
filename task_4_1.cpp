// 4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая,
// то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
// Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в
// конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты
// в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для
// каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
// Требования: скорость выполнения команды - O(log n). Решение должно поддерживать передачу функции сравнения снаружи.

#include <iostream>

template<class T, class Comparator=std::less<T>>
class AvlTree {
    struct Node {
        explicit Node(const T &value) : value(value), left(nullptr), right(nullptr), height(1), count(1) {}

        T value;
        Node *left;
        Node *right;
        unsigned char height;
        unsigned int count;
    };

public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() {
        destroy_tree(root);
    }

    void add(const T &value) {
        root = add_internal(root, value);
    }

    void remove_pos(unsigned int pos) {
        root = remove_internal(root, pos);
    }

    unsigned int get_position(const T &value) {
        Node *current_node = root;

        unsigned int pos = 0;
        while (current_node) {
            if (current_node->value == value) {
                return pos + get_count(current_node->left);
            }
            if (cmp(current_node->value, value)) {
                pos += get_count(current_node->left) + 1;
                current_node = current_node->right;
            } else {
                current_node = current_node->left;
            }
        }

        return 0;
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

    Node *add_internal(Node *node, const T &value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (cmp(node->value, value)) {
            node->right = add_internal(node->right, value);
        } else {
            node->left = add_internal(node->left, value);
        }

        return do_balance(node);
    }

    Node *do_balance(Node *node) {
        fix_height(node);
        fix_count(node);

        switch (get_balance(node)) {
            case 2: {
                if (get_balance(node->right) < 0) {
                    node->right = rotate_right(node->right);
                }
                return rotate_left(node);
            }
            case -2: {
                if (get_balance(node->left) > 0) {
                    node->left = rotate_left(node->left);
                }
                return rotate_right(node);
            }
            default:
                return node;
        }
    }

    void fix_height(Node *node) {
        node->height = std::max(get_height(node->left), get_height(node->right)) + (unsigned char) 1;
    }

    unsigned char get_height(Node *node) {
        return node ? node->height : (unsigned char) 0;
    }

    void fix_count(Node *node) {
        node->count = get_count(node->left) + get_count(node->right) + 1;
    }

    unsigned int get_count(Node *node) {
        return node ? node->count : 0;
    }

    int get_balance(Node *node) {
        return get_height(node->right) - get_height(node->left);
    }

    Node *rotate_left(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        fix_height(node);
        fix_height(tmp);
        fix_count(node);
        fix_count(tmp);

        return tmp;
    }

    Node *rotate_right(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        fix_height(node);
        fix_height(tmp);
        fix_count(node);
        fix_count(tmp);

        return tmp;
    }

    Node *remove_internal(Node *node, unsigned int pos) {
        if (node == nullptr) {
            return nullptr;
        }

        unsigned int current_pos = get_count(node->left);
        if (current_pos < pos) {
            node->right = remove_internal(node->right, pos - current_pos - 1);
        } else if (current_pos > pos) {
            node->left = remove_internal(node->left, pos);
        } else {
            Node *left = node->left;
            Node *right = node->right;
            delete node;

            if (left == nullptr && right == nullptr) {
                return nullptr;
            }

            if (get_height(left) > get_height(right)) {
                Node *min = find_right(left);
                min->left = remove_right(left);
                min->right = right;

                return do_balance(min);
            } else {
                Node *min = find_left(right);
                min->right = remove_left(right);
                min->left = left;

                return do_balance(min);
            }
        }

        return do_balance(node);
    }

    Node *find_left(Node *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node *find_right(Node *node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    Node *remove_left(Node *node) {
        if (!node->left)
            return node->right;
        node->left = remove_left(node->left);
        return do_balance(node);
    }

    Node *remove_right(Node *node) {
        if (!node->right)
            return node->left;
        node->right = remove_right(node->right);
        return do_balance(node);
    }
};

int main() {
    AvlTree<int, std::greater<>> avl_tree;

    int n = 0;
    std::cin >> n;

    unsigned int op = 0, value = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> op >> value;
        switch (op) {
            case 1: {
                avl_tree.add(value);
                std::cout << avl_tree.get_position(value) << std::endl;
                break;
            }
            case 2: {
                avl_tree.remove_pos(value);
                break;
            }
            default:
                break;
        }
    }

    return 0;
}
