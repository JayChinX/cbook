
#include <algorithm>
#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ostream>

void printArrays(int array[], int size) {
    for (int i = 0; i < size; i++) { std::cout << array[i] << " "; }
    std::cout << std::endl;
}

void stlSort() {
    int array[] = {0, 2, 8, 7, 4, 1, 6, 3, 5, 9};
    int size = sizeof(array) / sizeof(array[0]);
    std::sort(array, array + size);
    printArrays(array, size);

    int array1[] = {0, 2, 8, 7, 4, 1, 6, 3, 5, 9};
    std::sort(array1, array1 + 10, std::less<int>());
    printArrays(array1, 10);

    std::sort(array1, array1 + 10, std::greater<int>());
    printArrays(array1, 10);

    std::array<int, 11> a = {0, 2, 8, 7, 4, 1, 6, 3, 5, 9, 10};
    std::sort(a.begin(), a.end());
    std::for_each(a.begin(), a.end(), [&](const int &index) {
        std::cout << index << " " << std::endl;
    });
}

void bubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            int tmp = 0;
            if (array[j] > array[j + 1]) {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
            printArrays(array, size);
        }
        // printArrays(array, size);
    }
}

int main(int argc, char **argv) {
    // stlSort();
    int array[] = {0, 2, 8, 7, 4, 1, 6, 3, 5, 9};
    bubbleSort(array, sizeof(array) / sizeof(array[0]));
    system("pause");
    return 0;
}
