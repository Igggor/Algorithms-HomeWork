#ifndef CONCRETE_SET_H
#define CONCRETE_SET_H

#include "Set.h"
#include "SetImplementation.h"
#include "ArraySet.h"
#include "BinaryTreeSet.h"
#include <algorithm>

template <typename Object>
class ConcreteSet : public Set<Object> {
private:
    SetImplementation<Object> *implementation;

    void switchImplementation() {
        if (implementation->shouldSwitchToBinaryTree() && dynamic_cast<ArraySetImpl<Object> *>(implementation)) {
            SetImplementation<Object> *newImplementation = new BinaryTreeSetImpl<Object>();

            const Object *elements = implementation->getElements();
            for (int idx = 0; idx < implementation->size(); idx++) {
                newImplementation->insert(elements[idx]);
            }

            delete implementation;
            implementation = newImplementation;
        }
        else if (implementation->shouldSwitchToArray() && dynamic_cast<BinaryTreeSetImpl<Object> *>(implementation)) {
            SetImplementation<Object> *newImplementation = new ArraySetImpl<Object>();

            const Object *elements = implementation->getElements();
            for (int idx = 0; idx < implementation->size(); idx++) {
                newImplementation->insert(elements[idx]);
            }

            delete implementation;
            implementation = newImplementation;
        }
    }

public:
    ConcreteSet() {
        implementation = new ArraySetImpl<Object>();
    }

    explicit ConcreteSet(SetImplementation<Object> *initialImpl) : implementation(initialImpl) { }

    ConcreteSet(const ConcreteSet &another) {
        implementation = another.implementation->clone();
    }

    ~ConcreteSet() {
        delete implementation;
    }

    void Add(const Object &value) override {
        implementation->insert(value);
        switchImplementation();
    }

    void Delete(const Object &value) override {
        implementation->remove(value);
        switchImplementation();
    }

    bool In(const Object &value) const override {
        return implementation->contains(value);
    }

    int GetSize() const override {
        return implementation->size();
    }

    Set<Object> *Unification(const Set<Object> &another) const override {
        const ConcreteSet<Object> *castedOther = dynamic_cast<const ConcreteSet<Object> *>(&another);
        if (!castedOther)
            return nullptr;

        SetImplementation<Object> *newImplementation = implementation->clone();

        const Object *theirElements = castedOther->implementation->getElements();
        for (int idx = 0; idx < castedOther->implementation->size(); idx++) {
            newImplementation->insert(theirElements[idx]);
        }

        ConcreteSet<Object> *result = new ConcreteSet<Object>(newImplementation);
        return result;
    }

    Set<Object> *Intersection(const Set<Object> &another) const override {
        const ConcreteSet<Object> *castedOther = dynamic_cast<const ConcreteSet<Object> *>(&another);
        if (!castedOther)
            return nullptr;

        SetImplementation<Object> *newImplementation = new ArraySetImpl<Object>();

        const Object *ourElements = implementation->getElements();
        for (int idx = 0; idx < implementation->size(); idx++) {
            if (castedOther->In(ourElements[idx])) {
                newImplementation->insert(ourElements[idx]);
            }
        }

        ConcreteSet<Object> *result = new ConcreteSet<Object>(newImplementation);
        return result;
    }
};

#endif