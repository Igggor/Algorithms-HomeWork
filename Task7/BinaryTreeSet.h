#ifndef BINARY_TREE_SET_IMPL_H
#define BINARY_TREE_SET_IMPL_H

#include "SetImplementation.h"

template <typename Object>
class BinaryTreeSetImpl : public SetImplementation<Object> {
private:
    struct Node {
        Object val;
        Node *lft;
        Node *rgt;

        Node(const Object &value) : val(value), lft(nullptr), rgt(nullptr) { }
    };

    Node *tree;
    int sz;
    static const int MIN_TREE_SIZE = 50;

    Node *insertRec(Node *nd, const Object &value) {
        if (nd == nullptr) {
            sz++;
            return new Node(value);
        }

        if (value < nd->val)
            nd->lft = insertRec(nd->lft, value);
        else if (value > nd->val)
            nd->rgt = insertRec(nd->rgt, value);

        return nd;
    }

    Node *findMin(Node *nd) const {
        while (nd && nd->lft)
            nd = nd->lft;
        return nd;
    }

    Node *removeRec(Node *nd, const Object &value) {
        if (nd == nullptr)
            return nullptr;

        if (value < nd->val)
            nd->lft = removeRec(nd->lft, value);
        else if (value > nd->val)
            nd->rgt = removeRec(nd->rgt, value);
        else {
            if (nd->lft == nullptr && nd->rgt == nullptr) {
                delete nd;
                sz--;
                return nullptr;
            }
            else if (nd->lft == nullptr) {
                Node *tmp = nd->rgt;
                delete nd;
                sz--;
                return tmp;
            }
            else if (nd->rgt == nullptr) {
                Node *tmp = nd->lft;
                delete nd;
                sz--;
                return tmp;
            }
            else {
                Node *minNd = findMin(nd->rgt);
                nd->val = minNd->val;
                nd->rgt = removeRec(nd->rgt, minNd->val);
            }
        }
        return nd;
    }

    bool containsRec(Node *nd, const Object &value) const {
        if (nd == nullptr)
            return false;

        if (value < nd->val)
            return containsRec(nd->lft, value);

        if (value > nd->val)
            return containsRec(nd->rgt, value);
        return true;
    }

    void clearRec(Node *nd) {
        if (nd == nullptr)
            return;
        clearRec(nd->lft);
        clearRec(nd->rgt);
        delete nd;
    }

    Node *cloneRec(Node *nd) const {
        if (nd == nullptr)
            return nullptr;
        Node *newNd = new Node(nd->val);
        newNd->lft = cloneRec(nd->lft);
        newNd->rgt = cloneRec(nd->rgt);
        return newNd;
    }

    void collectElementsRec(Node *nd, Object *arr, int &idx) const {
        if (nd == nullptr)
            return;
        collectElementsRec(nd->lft, arr, idx);
        arr[idx++] = nd->val;
        collectElementsRec(nd->rgt, arr, idx);
    }

public:
    BinaryTreeSetImpl() : tree(nullptr), sz(0) { }

    BinaryTreeSetImpl(const BinaryTreeSetImpl &another) : sz(another.sz) {
        tree = cloneRec(another.tree);
    }

    ~BinaryTreeSetImpl() {
        clearRec(tree);
    }

    void insert(const Object &value) override {
        if (contains(value))
            return;
        tree = insertRec(tree, value);
    }

    void remove(const Object &value) override {
        tree = removeRec(tree, value);
    }

    bool contains(const Object &value) const override {
        return containsRec(tree, value);
    }

    int size() const override {
        return sz;
    }

    bool isEmpty() const override {
        return sz == 0;
    }

    void clear() override {
        clearRec(tree);
        tree = nullptr;
        sz = 0;
    }

    SetImplementation<Object> *clone() const override {
        return new BinaryTreeSetImpl<Object>(*this);
    }

    const Object *getElements() const override {
        Object *arr = new Object[sz];
        int idx = 0;
        collectElementsRec(tree, arr, idx);
        return arr;
    }

    bool shouldSwitchToBinaryTree() const override {
        return false;
    }

    bool shouldSwitchToArray() const override {
        return sz < MIN_TREE_SIZE;
    }
};

#endif
