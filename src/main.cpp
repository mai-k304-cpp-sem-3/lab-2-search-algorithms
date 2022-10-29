#include <iomanip>
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include "function.h"

using namespace std;

const int FUNCTION_GENERATION_COUNT = 2; // Количество функций генерации последовательностей
const int FUNCTION_SEARCH_COUNT = 3; // Количество функций поиска
const char OUT_PATH[] = "output//"; // Папка в которую выводим результаты


const char FILE_NAME_IN[] = "Input.txt"; // Имя файла входных данных

// Основная программа
int main() {
    // Системные команды
    setlocale(LC_ALL, "ru"); // Подключение русской локализации
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Массив указателей на функции генерации целых чисел
    void* (*menuFunctionGenerationInt[FUNCTION_GENERATION_COUNT])
        (int* arr, int& size, int& interval, int& minLimitation, int& maxLimitation) =
    { &allRandom, &upRegularize };

    // Массив указателей на функции генерации дробных чисел
    void* (*menuFunctionGenerationFloat[FUNCTION_GENERATION_COUNT])
        (float* arr, int& size, int& interval, float& minLimitation, float& maxLimitation) =
    { &allRandom, &upRegularize };

    // Массив указателей на функции поиска целых чисел
    int (*menuFunctionSearchInt[FUNCTION_SEARCH_COUNT])
        (int* arr, int& size, int& key, int& count)
    {
        &betterLinearSearch, & sentinelLinearSearch, & binarySearch
    };

    // Массив указателей на функции поиска дробных чисел
    int (*menuFunctionSearchFloat[FUNCTION_SEARCH_COUNT])
        (float* arr, int& size, int& key, int& count)
    {
        &betterLinearSearch, & sentinelLinearSearch, & binarySearch
    };

    // Переменные
    int size = 0; // Количество элементов
    int key; // Искомое значение
    int interval; // Интервал
    int minLimitationInt; // Ограничение на минимальное значение для целых чисел
    int maxLimitationInt; // Ограничение на максимальное значение для целых чисел
    float minLimitationFloat; // Ограничение на минимальное значение для дробных чисел
    float maxLimitationFloat; // Ограничение на максимальное значение для дробных чисел

    int count[FUNCTION_SEARCH_COUNT];

    const char* FUNCTION_NAME[] = {
    { "betterLinearSearch" },
    { "sentinelLinearSearch" },
    { "binarySearch" }
    };

    for (int i = 0; i < FUNCTION_SEARCH_COUNT; i++) {
        count[i] = 0;
    }
    // Ввод значений переменных с файла

    ifstream fin(FILE_NAME_IN); // Открытие файла входных данных

    /***************************************
    *       ВВОД ДАННЫХ ИЗ ФАЙЛА           *
    ***************************************/

    if (fin.is_open()) { // Проверка открытия файла
        fin >> key;
        cout << "key = " << key << endl;
        fin >> size;
        cout << "size = " << size << endl;
        fin >> interval;
        cout << "interval = " << interval << endl;
        fin >> minLimitationInt;
        cout << "minLimitationInt = " << minLimitationInt << endl;
        fin >> maxLimitationInt;
        cout << "maxLimitationInt = " << maxLimitationInt << endl;
        fin >> minLimitationFloat;
        cout << "minLimitationFloat = " << minLimitationFloat << endl;
        fin >> maxLimitationFloat;
        cout << "maxLimitationFloat = " << maxLimitationFloat << endl;
    }
    else {
        cout << "Error: File not found" << endl; // Сообщение об ошибки
        exit(0);
    }
    fin.close(); // Закрытие файла


    // Объявление массивов
    int* arrInt = new int[size]; // Создание массива целых чисел
    float* arrFloat = new float[size]; // Создание массива дробных чисел

    // Генерация рандомной последовательности целых чисел
    menuFunctionGenerationInt[0](arrInt, size, interval, minLimitationInt, maxLimitationInt);
    // Генерация рандомной последовательности дробных чисел
    menuFunctionGenerationFloat[0](arrFloat, size, interval, minLimitationFloat, maxLimitationFloat);

    int temp; // Искомый номер элемента
    float ftemp;
    cout << "\nРезультаты работы функций:\n\n";
    ofstream ofs(OUT_PATH + string("time.txt"));

    for (int i = 0; i < FUNCTION_SEARCH_COUNT; i++) {

        auto beginInt = chrono::steady_clock::now();	// Запуск отсчёта
        temp = menuFunctionSearchInt[i](arrInt, size, key, count[i]);
        auto endInt = std::chrono::steady_clock::now();	// получаем время по окончанию 
        auto timeOfWorkInt = std::chrono::duration_cast<std::chrono::microseconds>(endInt - beginInt);


        ofs << FUNCTION_NAME[i] << ": " << timeOfWorkInt.count() << endl;
        cout << FUNCTION_NAME[i] << "Int:" << timeOfWorkInt.count() << endl;
        if (i < 2) {
            ofs << "Counts = " << count[i] << endl << endl;
            cout << "Counts = " << count[i] << endl << endl;
        }

        if (temp == -1) {
            cout << "Ключ не найден.\n\n";
        }
        else {
            cout << "Ключ найден в элементе номер " << temp << endl << endl;
        }


        auto beginFloat = chrono::steady_clock::now();	// Запуск отсчёта
        ftemp = menuFunctionSearchFloat[i](arrFloat, size, key, count[i]);
        auto endFloat = std::chrono::steady_clock::now();	// получаем время по окончанию 
        auto timeOfWorkFloat = std::chrono::duration_cast<std::chrono::microseconds>(endFloat - beginFloat);

        ofs << FUNCTION_NAME[i] << ": " << timeOfWorkFloat.count() << endl;
        cout << FUNCTION_NAME[i] << "Float:" << timeOfWorkFloat.count() << endl;
        if (i < 2) {
            ofs << "Counts = " << count[i] << endl << endl;
            cout << "Counts = " << count[i] << endl << endl;
        }
        if (ftemp == -1) {
            cout << "Ключ не найден.\n\n";
        }
        else {
            cout << "Ключ найден в элементе номер " << ftemp << endl << endl;
        }
    }
}