#ifndef ARRAY_SET_IMPL_H
#define ARRAY_SET_IMPL_H

#include "SetImplementation.h"
#include <vector>
#include <algorithm>

template <typename Object>
class ArraySetImpl : public SetImplementation<Object> {
private:
    std::vector<Object> elements;
    static const int MAX_ARRAY_SIZE = 100;

public:
    ArraySetImpl() { }

    ArraySetImpl(const ArraySetImpl &another) : elements(another.elements) { }

    void insert(const Object &value) override {
        if (contains(value))
            return;
        elements.push_back(value);
    }

    void remove(const Object &value) override {
        auto it = std::find(elements.begin(), elements.end(), value);
        if (it != elements.end()) {
            elements.erase(it);
        }
    }

    bool contains(const Object &value) const override {
        return std::find(elements.begin(), elements.end(), value) != elements.end();
    }

    int size() const override {
        return elements.size();
    }

    bool isEmpty() const override {
        return elements.empty();
    }

    void clear() override {
        elements.clear();
    }

    SetImplementation<Object> *clone() const override {
        return new ArraySetImpl<Object>(*this);
    }

    const Object *getElements() const override {
        return elements.data();
    }

    bool shouldSwitchToBinaryTree() const override {
        return size() > MAX_ARRAY_SIZE;
    }

    bool shouldSwitchToArray() const override {
        return false;
    }
};

#endif