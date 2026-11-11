#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 1. БЫСТРАЯ СОРТИРОВКА (QUICK SORT)

template <typename T>
void quickSort(vector<T>& arr, int low, int high) {
    if (low >= high) {
        return;
    }

    // Выбираем средний элемент в качестве опорного
    T pivot = arr[low + (high - low) / 2];

    int i = low;
    int j = high;

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (low < j) {
        quickSort(arr, low, j);
    }

    if (i < high) {
        quickSort(arr, i, high);
    }
}

// 2. СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT)

template <typename T>
void merge(vector<T>& arr, vector<T>& temp,
           int left, int mid, int right) {

    int i = left;
    int j = mid + 1;
    int k = left;

    // Сравниваем элементы двух частей
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    // Копируем оставшиеся элементы
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Возвращаем отсортированную часть в исходный массив
    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
}

template <typename T>
void mergeSort(vector<T>& arr, vector<T>& temp,
               int left, int right) {

    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

// 3. ПИРАМИДАЛЬНАЯ СОРТИРОВКА (HEAP SORT)

// Восстановление свойств max-heap
template <typename T>
void heapify(vector<T>& arr, int n, int i) {

    while (true) {
        int largest = i;

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest == i) {
            break;
        }

        swap(arr[i], arr[largest]);

        i = largest;
    }
}

template <typename T>
void heapSort(vector<T>& arr) {

    int n = arr.size();

    // Построение max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Последовательно переносим максимум в конец
    for (int i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

// 4. ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ

// Вывод массива
template <typename T>
void printArray(const vector<T>& arr) {

    for (const T& element : arr) {
        cout << element << " ";
    }

    cout << endl;
}

// Проверка правильности сортировки
template <typename T>
bool isSorted(const vector<T>& arr) {

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }

    return true;
}

// 5. ТЕСТИРОВАНИЕ ТРЁХ АЛГОРИТМОВ

template <typename T>
void testSorting(const vector<T>& original,
                 const string& typeName) {

    vector<T> quick = original;
    vector<T> merge = original;
    vector<T> heap = original;

    cout << "\n====================================\n";
    cout << "ТИП ДАННЫХ: " << typeName << endl;
    cout << "====================================\n";

    cout << "Исходный массив: ";
    printArray(original);

    // Быстрая сортировка
    if (!quick.empty()) {
        quickSort(quick, 0, static_cast<int>(quick.size()) - 1);
    }

    cout << "\n1. Быстрая сортировка: ";
    printArray(quick);

    cout << "Проверка: "
         << (isSorted(quick) ? "Успешно" : "Ошибка") << endl;

    // Сортировка слиянием
    if (!merge.empty()) {
        vector<T> temp(merge.size());

        mergeSort(merge, temp, 0,
                  static_cast<int>(merge.size()) - 1);
    }

    cout << "\n2. Сортировка слиянием: ";
    printArray(merge);

    cout << "Проверка: "
         << (isSorted(merge) ? "Успешно" : "Ошибка") << endl;

    // Пирамидальная сортировка
    heapSort(heap);

    cout << "\n3. Пирамидальная сортировка: ";
    printArray(heap);

    cout << "Проверка: "
         << (isSorted(heap) ? "Успешно" : "Ошибка") << endl;
}

// MAIN

int main() {

    setlocale(LC_ALL, "Russian");

    cout << "ЛАБОРАТОРНАЯ РАБОТА\n";
    cout << "Вариант 11\n";
    cout << "Тестирование трёх алгоритмов сортировки\n";

    // 1. Тестирование int
    vector<int> integers = {
        64, 34, 25, 12, 22, 11, 90, 5, 34
    };

    testSorting(integers, "int");

    // 2. Тестирование double
    vector<double> decimals = {
        64.5, 34.2, 25.8, 12.1, 22.7,
        11.3, 90.6, 5.4, 34.2
    };

    testSorting(decimals, "double");

    // 3. Тестирование string
    vector<string> words = {
        "banana", "apple", "orange",
        "grape", "cherry", "kiwi", "apple"
    };

    testSorting(words, "string");

    return 0;
}
