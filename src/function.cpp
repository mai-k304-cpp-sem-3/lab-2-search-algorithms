#include "function.h"
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>


using namespace std;
const int INPUT_VALUES = 7;
const int INPUT_INT_VALUES = 5;

// Реализация функций

// Функции генерации последовательностей
void* allRandom( // Функция формирующая случайную последовательность
    int* arr, // Массив
    int& size, // Количество элементов
    int& interval, // Интервал
    int& minLimitation, // Ограничение на минимальное число
    int& maxLimitation // Ограничение на максимальное число
) {
    for (int i = 0; i < size; i++) {
        arr[i] = minLimitation + rand() % (maxLimitation - minLimitation);
    }
    return 0;
}

void* allRandom( // Функция формирующая случайную последовательность
    float* arr, // Массив
    int& size, // Количество элементов
    int& interval, // Интервал
    float& minLimitation, // Ограничение на минимальное число
    float& maxLimitation // Ограничение на максимальное число
) {
    for (int i = 0; i < size; i++) {
        arr[i] = minLimitation + rand() % int(maxLimitation - minLimitation);
    }
    return 0;
}

void* upRegularize( // Функция формирующая упорядоченную последовательность по возрастанию
    int* arr, // Массив
    int& size, // Количество элементов
    int& interval, // Интервал
    int& minLimitation, // Ограничение на минимальное число
    int& maxLimitation // Ограничение на максимальное число
) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * (maxLimitation - minLimitation) / (size - 1) + minLimitation;
    }
    return 0;
}

void* upRegularize( // Функция формирующая упорядоченную последовательность по возрастанию
    float* arr, // Массив
    int& size, // Количество элементов
    int& interval, // Интервал
    float& minLimitation, // Ограничение на минимальное число
    float& maxLimitation // Ограничение на максимальное число
) {
    for (int i = 0; i < size; i++) {
        arr[i] = (i * (maxLimitation - minLimitation) / (size - 1) + minLimitation);
    }
    return 0;
}

// Функции сортировки последовательностей

// Алгоритм Better Linear Search
int betterLinearSearch(int* arr, int& size, int& key, int& count) {
    for (int i = 0; i < size; i++) { // Цикл по всем элементам массива
        count++;
        if (arr[i] == key) { // Проверка элемента на ключ-число
            return i; // Возвращения номера нужного элемента
        }
    }
    return -1; // Возвращение -1 при отсудствии нужного элемента
}

int betterLinearSearch(float* arr, int& size, int& key, int& count) {
    for (int i = 0; i < size; i++) { // Цикл по всем элементам массива
        count++;
        if (arr[i] == key) { // Проверка элемента на ключ-число
            return i; // Возвращения номера нужного элемента
        }
    }
    return -1; // Возвращение -1 при отсудствии нужного элемента
}

// Алгоритм Sentinel Linear Search
int sentinelLinearSearch(int* arr, int& size, int& key, int& count) {
    int last = arr[size - 1];
    arr[size - 1] = key;
    int i = 0;
    while (arr[i] != key) {
        count++;
        i++;
    }
    arr[size - 1] = last;
    if ((i < size - 1) || (key == arr[size - 1])) {
        return i;
    }
    return -1;
}

int sentinelLinearSearch(float* arr, int& size, int& key, int& count) {
    float last = arr[size - 1];
    arr[size - 1] = key;
    int i = 0;
    while (arr[i] != key) {
        count++;
        i++;
    }
    arr[size - 1] = last;
    if ((i < size - 1) || (key == arr[size - 1])) {
        return i;
    }
    return -1;
}

// Алгоритм бинарного поиска
int binarySearch(int* arr, int& size, int& key, int& count) {
    int low = 0;
    int high = size;
    int mid;
    while (low <= high) {

        mid = int((low + high) / 2);
        if (key < arr[mid]) {
            high = mid - 1;
        }
        else if (key > arr[mid]) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}

int binarySearch(float* arr, int& size, int& key, int& count) {
    int low = 0;
    int high = size;
    int mid;
    while (low <= high) {

        mid = int((low + high) / 2);
        if (key < arr[mid]) {
            high = mid - 1;
        }
        else if (key > arr[mid]) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}