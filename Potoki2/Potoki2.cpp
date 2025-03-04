// Potoki2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

void countSpaces(const std::string& filename, const std::string& outputFilename) {
    auto start = std::chrono::high_resolution_clock::now(); // Засекаем время начала

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    int spaceCount = 0;
    char ch;

    while (inFile.get(ch)) {
        if (ch == ' ') {
            spaceCount++;
        }
    }

    inFile.close();

    auto end = std::chrono::high_resolution_clock::now(); // Засекаем время окончания
    std::chrono::duration<double> elapsed = end - start; // Вычисляем время выполнения

    // Каждый поток пишет в свой файл
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        return;
    }

    outFile << "Поток " << std::this_thread::get_id()
        << ", пробелов = " << spaceCount
        << ", время выполнения = " << elapsed.count() << " секунд" << std::endl;

    outFile.close();
}

void countChars(const std::string& filename, const std::string& outputFilename) {
    auto start = std::chrono::high_resolution_clock::now(); // Засекаем время начала

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    int charCount = 0;
   
    char ch;

    while (inFile.get(ch)) {
        charCount++;
      
    }

    inFile.close();

    auto end = std::chrono::high_resolution_clock::now(); // Засекаем время окончания
    std::chrono::duration<double> elapsed = end - start; // Вычисляем время выполнения

    // Каждый поток пишет в свой файл
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        return;
    }

    outFile << "Поток " << std::this_thread::get_id() << ": символов = " << charCount
        << ", время выполнения = " << elapsed.count() << " секунд" << std::endl;

    outFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string inputFilename = "input.txt";

    std::thread thread1(countChars, inputFilename, "output1.txt");
    std::thread thread2(countSpaces, inputFilename, "output2.txt");

    // Ожидаем завершения всех потоков
    thread1.join();
    thread2.join();

    std::cout << "Успешно. Результаты записаны в файлы output1.txt, output2.txt" << std::endl;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
