#include "ConcreteSet.h"
#include <iostream>
#include <string>

using namespace std;

template <typename T>
void ProcessIntegerSequence() {
    ConcreteSet<T> dataContainer;

    for (int idx = 1; idx <= 15; idx++) {
        dataContainer.Add(idx * 2);
    }

    cout << "Sequence loaded. Count: " << dataContainer.GetSize() << endl;

    for (int query = 2; query <= 20; query += 2) {
        cout << "Value " << query << " present: " << (dataContainer.In(query) ? "Yes" : "No") << endl;
    }

    dataContainer.Delete(10);
    dataContainer.Delete(20);
    cout << "After removals. Count: " << dataContainer.GetSize() << endl;
}

template <typename T>
void PerformExpansion() {
    cout << "\nExpanding set beyond array limit..." << endl;

    ConcreteSet<T> expanded;

    for (int idx = 0; idx < 150; idx++) {
        expanded.Add(idx);
    }

    cout << "Expanded set size: " << expanded.GetSize() << endl;

    int checkIdx = 125;
    cout << "Contains " << checkIdx << ": " << (expanded.In(checkIdx) ? "Yes" : "No") << endl;

    for (int idx = 100; idx < 120; idx++) {
        expanded.Delete(idx);
    }

    cout << "After bulk deletion. Size: " << expanded.GetSize() << endl;

    bool verified = true;
    for (int idx = 120; idx < 150; idx++) {
        if (!expanded.In(idx)) {
            verified = false;
            cout << "Missing: " << idx << endl;
        }
    }

    cout << "Remaining elements verified: " << (verified ? "Correct" : "Invalid") << endl;
}

void CombineSets() {
    std::cout << "\nCombining two sets..." << std::endl;

    ConcreteSet<int> firstCollection;
    ConcreteSet<int> secondCollection;

    for (int x = 0; x < 20; x += 2) {
        firstCollection.Add(x);
    }

    for (int x = 10; x < 30; x += 2) {
        secondCollection.Add(x);
    }

    cout << "First collection size: " << firstCollection.GetSize() << endl;
    cout << "Second collection size: " << secondCollection.GetSize() << endl;

    Set<int> *united = firstCollection.Unification(secondCollection);

    cout << "United size: " << united->GetSize() << " (should be 15)" << endl;

    bool allPresent = true;
    for (int x = 0; x < 30; x += 2) {
        if (!united->In(x)) {
            allPresent = false;
        }
    }

    cout << "All values present: " << (allPresent ? "Yes" : "No") << endl;

    delete united;
}

void IntersectSets() {
    cout << "\nFinding intersection..." << endl;

    ConcreteSet<int> groupA;
    ConcreteSet<int> groupB;

    for (int x = 0; x < 25; x++) {
        groupA.Add(x);
    }

    for (int x = 20; x < 40; x++) {
        groupB.Add(x);
    }

    cout << "Group A size: " << groupA.GetSize() << endl;
    cout << "Group B size: " << groupB.GetSize() << endl;

    Set<int> *shared = groupA.Intersection(groupB);

    cout << "Shared elements count: " << shared->GetSize() << " (should be 5)" << endl;

    bool correctShared = true;
    for (int x = 20; x < 25; x++) {
        if (!shared->In(x)) {
            correctShared = false;
        }
    }

    cout << "Correct intersection: " << (correctShared ? "Yes" : "No") << endl;

    delete shared;
}

void TestStringCollection() {
    cout << "\nProcessing string collection..." << endl;

    ConcreteSet<string> vocab;

    vocab.Add("alpha");
    vocab.Add("beta");
    vocab.Add("gamma");
    vocab.Add("delta");
    vocab.Add("alpha");

    cout << "Vocab size: " << vocab.GetSize() << " (should be 4)" << endl;

    cout << "Has 'beta': " << (vocab.In("beta") ? "Yes" : "No") << endl;
    cout << "Has 'theta': " << (vocab.In("theta") ? "Yes" : "No") << endl;

    vocab.Delete("beta");
    cout << "After removing 'beta'. Size: " << vocab.GetSize() << endl;
}

void CornerCases() {
    cout << "\nTesting corner cases..." << endl;

    ConcreteSet<int> emptyOne;
    cout << "Empty set size: " << emptyOne.GetSize() << endl;
    cout << "Empty contains value: " << emptyOne.In(0) << endl;

    emptyOne.Delete(99);
    cout << "After deleting from empty. Size: " << emptyOne.GetSize() << endl;

    ConcreteSet<int> filledSet;
    for (int idx = 1; idx <= 8; idx++) {
        filledSet.Add(idx);
    }

    Set<int> *unionWithEmpty = filledSet.Unification(emptyOne);
    Set<int> *intersectWithEmpty = filledSet.Intersection(emptyOne);

    cout << "Union with empty size: " << unionWithEmpty->GetSize() << endl;
    cout << "Intersection with empty size: " << intersectWithEmpty->GetSize() << endl;

    delete unionWithEmpty;
    delete intersectWithEmpty;

    ConcreteSet<int> original;
    for (int idx = 1; idx <= 12; idx++) {
        original.Add(idx);
    }

    ConcreteSet<int> duplicate(original);

    cout << "Original size: " << original.GetSize() << endl;
    cout << "Duplicate size: " << duplicate.GetSize() << endl;

    duplicate.Delete(6);

    cout << "Original has 6: " << original.In(6) << endl;
    cout << "Duplicate has 6: " << duplicate.In(6) << endl;
}

int main() {
    cout << "============================================" << endl;
    cout << "   SET IMPLEMENTATION TEST SUITE" << endl;
    cout << "============================================" << endl;

    ProcessIntegerSequence<int>();
    PerformExpansion<int>();
    CombineSets();
    IntersectSets();
    TestStringCollection();
    CornerCases();

    cout << "\n============================================" << endl;
    cout << "   TESTING COMPLETED" << endl;
    cout << "============================================" << endl;

    return 0;
}