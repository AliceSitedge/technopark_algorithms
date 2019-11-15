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

class HashTable {
public:
    explicit HashTable(size_t size=DEFAULT_SIZE) : size(0), table(size, "NIL") {}
    ~HashTable() = default;

    bool has(const std::string &key) const {
        size_t hash = get_hash(key, 71, table.size());
        size_t odd_hash = get_odd_hash(key, 11, table.size());

        size_t current_pos = hash;
        for (int i = 1; table[current_pos] != "NIL" && table[current_pos] != key && i  != table.size(); i++) {
            current_pos = (hash + i * odd_hash) % table.size();
        }

        return !(table[current_pos] == "NIL" || table[current_pos] == "DEL");
    }

    bool add(const std::string &key) {
        if (size > table.size() * MAX_ALPHA) {
            grow();
        }

        size_t hash = get_hash(key, 71, table.size());
        size_t odd_hash = get_odd_hash(key, 11, table.size());

        int deleted_elem = -1;
        size_t current_pos = hash;
        for (int i = 1; table[current_pos] != "NIL" && table[current_pos] != key && i != table.size(); i++) {
            if (table[current_pos] == "DEL" && deleted_elem == -1) {
                deleted_elem = int(current_pos);
            }
            current_pos = (hash + i * odd_hash) % table.size();
        }

        if (table[current_pos] == key) {
            return false;
        }

        if (deleted_elem == -1) {
            table[current_pos] = key;
        } else {
            table[deleted_elem] = key;
        }
        size++;
        return true;
    }

    bool remove(const std::string &key) {
        size_t hash = get_hash(key, 71, table.size());
        size_t odd_hash = get_odd_hash(key, 11, table.size());

        size_t current_pos = hash;
        for (int i = 1; table[current_pos] != "NIL" && table[current_pos] != key && i != table.size(); i++) {
            current_pos = (hash + i * odd_hash) % table.size();
        }
        
        if (table[current_pos] == "NIL" || table[current_pos] == "DEL") {
            return false;
        }
        
        table[current_pos] = "DEL";
        size--;
        return true;        
    }
private:
    size_t size;
    std::vector<std::string> table;

    void grow() {
        std::vector<std::string> old_table = std::move(table);
        table = std::vector<std::string>(old_table.size() * 2, "NIL");
        size = 0;

        for (const auto &elem : old_table) {
            if (elem != "NIL" && elem != "DEL") {
                add(elem);
            }
        }
    }
};

int main() {
    HashTable hash_table;

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
