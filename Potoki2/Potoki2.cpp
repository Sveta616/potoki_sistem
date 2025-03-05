#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>


HANDLE hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
DWORD WINAPI countChars(LPVOID lpParam) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string* filenames = static_cast<std::string*>(lpParam);
    std::string fileinput = filenames[0];
    std::string output = filenames[1];

    std::ifstream inFile(fileinput);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия входного файла!" << std::endl;
        return 1;
    }

    int charCount = 0; 
    char ch;

    while (inFile.get(ch)) {
        charCount++; 
    }

    inFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> fin = end - start;

   
    WaitForSingleObject(hSemaphore, INFINITE);

    std::ofstream outFile(output, std::ios::app); 
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        ReleaseSemaphore(hSemaphore, 1, NULL); 
        return 1;
    }

   
    outFile << "Поток " << GetCurrentThreadId() << ": символов = " << charCount
        << ", время выполнения = " << fin.count() << " секунд" << std::endl;

   
    std::cout << "Поток " << GetCurrentThreadId() << ": символов = " << charCount
        << ", время выполнения = " << fin.count() << " секунд" << std::endl;

    outFile.close();

    
    ReleaseSemaphore(hSemaphore, 1, NULL);

    return 0;
}


DWORD WINAPI countSpaces(LPVOID lpParam) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string* filenames = static_cast<std::string*>(lpParam);
    std::string fileinput = filenames[0];
    std::string output = filenames[1];

    std::ifstream inFile(fileinput);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия входного файла!" << std::endl;
        return 1;
    }

    int spaceCount = 0; 
    char ch;

    while (inFile.get(ch)) {
        if (ch == ' ') {
            spaceCount++; 
        }
    }

    inFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> fin = end - start;

   
    WaitForSingleObject(hSemaphore, INFINITE);

    std::ofstream outFile(output, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        ReleaseSemaphore(hSemaphore, 1, NULL); 
        return 1;
    }

   
    outFile << "Поток " << GetCurrentThreadId() << ": пробелов = " << spaceCount
        << ", время выполнения = " << fin.count() << " секунд" << std::endl;

    std::cout << "Поток " << GetCurrentThreadId() << ": пробелов = " << spaceCount
        << ", время выполнения = " << fin.count() << " секунд" << std::endl;

    outFile.close();

    
    ReleaseSemaphore(hSemaphore, 1, NULL);

    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::string inputname = "input.txt";
    std::string outputname = "output.txt"; 

  
    std::string filenames[] = { inputname, outputname };

 
    HANDLE hThread1 = CreateThread(NULL, 0, countChars, &filenames, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, countSpaces, &filenames, 0, NULL);

    if (hThread1 == NULL || hThread2 == NULL) {
        std::cerr << "Ошибка создания потока!" << std::endl;
        CloseHandle(hSemaphore); 
        return 1;
    }

   
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

   
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hSemaphore);

    std::cout << "Успешно. Результаты записаны в файл output.txt" << std::endl;

    return 0;
}