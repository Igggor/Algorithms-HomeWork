#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>

template <typename T>
class Treap {
private:
    struct Node {
        T value;
        int priority;
        int count;
        int size;
        Node* left;
        Node* right;

        explicit Node(const T& val)
            : value(val), priority(rand()), count(1), size(1),
              left(nullptr), right(nullptr) {}
    };

    Node* root;

    static void updateSize(Node* node) {
        // Тут я обновляю размеры поддерева
        if (node) {
            node->size = node->count;
            if (node->left) node->size += node->left->size;
            if (node->right) node->size += node->right->size;
        }
    }

    std::pair<Node*, Node*> split(Node* node, const T& key) {
        // Разделение дерева по ключу
        if (!node) return {nullptr, nullptr};

        if (node->value < key) {
            auto [left, right] = split(node->right, key);
            node->right = left;
            updateSize(node);
            return {node, right};
        }
        auto [left, right] = split(node->left, key);
        node->left = right;
        updateSize(node);
        return {left, node};
    }

    Node* merge(Node* left, Node* right) {
        // Функция слияния двух деревьев
        if (!left) return right;
        if (!right) return left;

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            updateSize(left);
            return left;
        }
        right->left = merge(left, right->left);
        updateSize(right);
        return right;
    }

    void clear(Node* node) {
        // Удаление дерева. Рекурсивное, чтобы очистить все
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    Treap() : root(nullptr) {
        std::srand(std::time(nullptr));
    }

    ~Treap() {
        // Деструктор для очистки дерева.
        // Вызываю рекурсивную функцию очистки дерева, начиная с корня.
        clear(root);
    }

    void insert(const T& value) {
        // Добавление элемента
        auto [left, right] = split(root, value);

        if (auto [left2, right2] = split(right, value + 1); left2) {
            // Узел с таким значением уже существует
            ++left2->count;
            updateSize(left2);
            root = merge(left, merge(left2, right2));
        } else {
            // Создаем новый узел
            Node* newNode = new Node(value);
            root = merge(left, merge(newNode, right2));
        }
    }

    bool erase(const T& value) {
        // Удаление элемента
        auto [left, right] = split(root, value);
        auto [left2, right2] = split(right, value + 1);

        if (left2) {
            if (left2->count > 1) {
                --left2->count;
                updateSize(left2);
                root = merge(left, merge(left2, right2));
            } else {
                delete left2;
                root = merge(left, right2);
            }
            return true;
        }
        root = merge(left, right2);
        return false;
    }

    int size() const {
        // Количество элементов в дереве
        return root ? root->size : 0;
    }

    int count(const T& value) const {
        // Количество определенных значений в дереве
        Node* current = root;
        while (current) {
            if (value < current->value) current = current->left;
            else if (value > current->value) current = current->right;
            else return current->count;
        }
        return 0;
    }
};
