#include <iostream>
#include "math.h"
#include <fstream>
#include <string>

int main()
{
    double x, y;
    //a - початок проміжку, b - кінець проміжку, h - крок функції
    double a, b, h;

    //задання параметрів для точок графіку
    a = -10.0;
    b = 10.0;
    h = 0.1;
    x = a;

    std::ofstream file;
    file.open("Output.txt");
    if (!file.is_open()) {
        std::cout << " Файл не може бути відкрито!\n";
    }
    else {
        while (x <= b) {
            //задання функції y
            y = x * x;
            file << x << std::endl;
            file << y << std::endl;
            x = round((x + h) * 100) / 100;
        }
    }

    file.close();

    //вивід даних, записаних у файл
    std::string s;

    std::ifstream fin;
    fin.open("Output.txt");
    while (!fin.eof()) {
        getline(fin, s);
        x = atof(s.c_str());
        getline(fin, s);
        y = atof(s.c_str());
        std::cout << "x = " << x << " y = " << y << std::endl;
    }

    fin.close();

    return 0;
}