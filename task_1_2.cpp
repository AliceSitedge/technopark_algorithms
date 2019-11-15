#include <utility>

#include <utility>

// 1_2. Реализуйте структуру данных типа "множество строк" на основе динамической хеш-таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
// когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
// принадлежности данной строки множеству.
// Для разрешения коллизий используйте двойное хеширование.

#include <iostream>
#include <vector>

#define DEFAULT_SIZE 8
#define MAX_ALPHA 0.75

size_t get_hash(const std::string &str, size_t constant, size_t size) {
    size_t hash = 0;
    for (auto ch : str) {
        hash = (hash * constant + ch) % size;
    }

    return hash;
}

size_t get_odd_hash(const std::string &str, size_t constant, size_t size) {
    size_t hash = get_hash(str, constant, size);
    if (hash % 2 == 0) {
        hash++;
    }

    return hash;
}

template<class T>
struct HashElement {
    explicit HashElement(T key, bool deleted=false) : key(std::move(key)), deleted(deleted) {}
    T key;
    bool deleted;
};

template<class T>
class HashTable {
public:
    explicit HashTable(size_t size=DEFAULT_SIZE) : size(0), table(size, nullptr) {}
    ~HashTable() {
        for (auto elem : table) {
            delete elem;
        }
    }

    bool has(const T &key) const {
        size_t hash = get_hash(key, 71, table.size());
        size_t odd_hash = get_odd_hash(key, 11, table.size());

        HashElement<T> *elem = table[hash];
        size_t current_pos = hash;
        for (int i = 1; elem != nullptr && elem->key != key; i++) {
            hash = (hash + i * odd_hash) % table.size();
            elem = table[hash];
        }

        return !(elem == nullptr || elem->deleted);
    }

    bool add(const T &key) {
        if (size > table.size() * MAX_ALPHA) {
            grow();
        }

        size_t hash = get_hash(key, 71, table.size());
        size_t odd_hash = get_odd_hash(key, 11, table.size());

        HashElement<T> *elem = table[hash];
        HashElement<T> *deleted_elem = nullptr;
        size_t current_pos = hash;
        for (int i = 1; elem != nullptr && elem->key != key; i++) {
            if (elem->deleted && deleted_elem == nullptr) {
                deleted_elem = elem;
            }

            hash = (hash + i * odd_hash) % table.size();
            elem = table[hash];
        }

        if (elem == nullptr) {
            table[hash] = new HashElement<T>(key);
            size++;
            return true;
        }

        if (elem->key == key && !elem->deleted) {
            return false;
        }

        if (deleted_elem == nullptr) {
            elem->deleted = false;
        } else {
            deleted_elem->key = key;
            deleted_elem->deleted = false;
        }
        size++;
        return true;
    }

    bool remove(const T &key) {
        size_t hash = get_hash(key, 71, table.size());
        size_t odd_hash = get_odd_hash(key, 11, table.size());

        HashElement<T> *elem = table[hash];
        size_t current_pos = hash;
        for (int i = 1; elem != nullptr && elem->key != key; i++) {
            hash = (hash + i * odd_hash) % table.size();
            elem = table[hash];
        }
        
        if (elem == nullptr || elem->deleted) {
            return false;
        }
        
        elem->deleted = true;
        size--;
        return true;        
    }
private:
    size_t size;
    std::vector<HashElement<T>*> table;

    void grow() {
        std::vector<HashElement<T>*> old_table = std::move(table);
        table = std::vector<HashElement<T>*>(old_table.size() * 2, nullptr);
        size = 0;

        for (auto elem : old_table) {
            if (elem != nullptr && !elem->deleted) {
                add(elem->key);
                delete elem;
            }
        }
    }
};

int main() {
    HashTable<std::string> hash_table;

    char op;
    std::string key;

    while (std::cin >> op >> key) {
        switch (op) {
            case '?': {
                std::cout << (hash_table.has(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '+': {
                std::cout << (hash_table.add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-': {
                std::cout << (hash_table.remove(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            default:
                break;
        }
    }

    return 0;
}
