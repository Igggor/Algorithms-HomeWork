#include <iostream>
#include <algorithm>
#include <stdexcept>

// Я решил сделать через АВЛ дерево. На красно-черное меня сегодня не хватит :)
class OrderStatisticTree {
private:
    struct Node {
        int value;
        int height;
        int size; // тут я веду учет количества узлов в поддереве
        Node* left;
        Node* right;

        Node(int val) : value(val), height(1), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Обновление высоты и размера узла
    void update(Node* node) {
        if (!node) return;
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
    }

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    int getSize(Node* node) const {
        return node ? node->size : 0;
    }

    // Баланс-фактор
    int balanceFactor(Node* node) const {
        return getHeight(node->left) - getHeight(node->right);
    }

    // Повороты
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        update(y);
        update(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        update(x);
        update(y);

        return y;
    }

    // Вставка
    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        else
            return node;

        update(node);

        // Балансировка
        int balance = balanceFactor(node);

        // Left Left
        if (balance > 1 && value < node->left->value)
            return rotateRight(node);

        // Right Right
        if (balance < -1 && value > node->right->value)
            return rotateLeft(node);

        // Left Right
        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left
        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Поиск k-ой порядковой статистики
    Node* findKth(Node* node, int k) const {
        if (!node) return nullptr;

        int leftSize = getSize(node->left);

        if (k == leftSize + 1) return node;
        else if (k <= leftSize) return findKth(node->left, k);
        return findKth(node->right, k - leftSize - 1);
    }

    // Рекурсивное удаление дерева, сделал как в Декартовом, которое отправлял ранее
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    OrderStatisticTree() : root(nullptr) {}
    ~OrderStatisticTree() { clear(root); }

    void insert(int value) {
        root = insert(root, value);
    }

    // Поиск k-ой порядковой статистики 
    int findKthElement(int k) const {
        if (k <= 0 || k > getSize(root)) {
            throw std::out_of_range("Invalid k value");
        }

        Node* node = findKth(root, k);
        return node->value;
    }

    int size() const {
        return getSize(root);
    }
};

int main() {
    OrderStatisticTree tree;
    int values[] = {20, 10, 30, 5, 15, 25, 35};
    
    for (int val : values)
        tree.insert(val);

    for (int k = 1; k <= tree.size(); ++k)
        std::cout << k << "-th element: " << tree.findKthElement(k) << std::endl;
    return 0;
}