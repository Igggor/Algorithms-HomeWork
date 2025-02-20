#include <iostream>
#include <vector>


int searchInRotatedArray(const std::vector<int>& arr, const int x) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        const int mid = left + (right - left) / 2;
        if (arr[mid] == x)
            return mid;

        if (arr[left] <= arr[mid]) {
            if (arr[left] <= x && x < arr[mid])
                right = mid - 1;
            else
                left = mid + 1;

        } else {
            if (arr[mid] < x && x <= arr[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n, x;
    std::cin >> n;
    std::vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cin >> x;

    if (const int index = searchInRotatedArray(arr, x); index != -1)
        std::cout << "Элемент " << x << " находится на позиции " << index << '\n';
    else
        std::cout << "Элемент не был найден\n";

    return 0;
}
