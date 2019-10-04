#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>


double my_Function(double x) {
    return -sqrt(x)*sin(x);
}

double multimodal_Function(double x) {
    return my_Function(x)*sin(5*x);
}

bool IsTransition(double delta, double temp_i) {
    std::mt19937 generator{ std::random_device{}() };
    std::uniform_real_distribution<> dis{0, 1};
    double value = dis(generator);
    double P = exp(-delta/temp_i);
    return value <= P;
}

void uni_ignition_simulation_method(double a, double b, double min, double max) {
    std::cout << "\t\t\tUnimodal Function:\n\n"
    << "N\t\t" << "Temperature\t\t\t\t" << "x\t\t\t\t" << "f(x)\n";
    double temp_i = max;

    std::mt19937 generator{ std::random_device{}() };
    std::uniform_real_distribution<> dis{a, b};
    double x1 = dis(generator);
    double x2, delta;
    size_t counter = 0;
    while(temp_i > min) {
        x2 = dis(generator);
        delta = my_Function(x2) - my_Function(x1);
        if(delta <= 0) {
            x1 = x2;
        }
        else if(delta > 0) {
            if(IsTransition(delta, temp_i)) {
                x1 = x2;
            }
        }
        counter++;
        std::cout << counter<< std::fixed << std::setprecision(7)  << "\t|\t" << temp_i << "  \t|\t" << x1 << "\t|\t" << my_Function(x1) << std::endl;
        temp_i *= 0.95;
    }
    std::cout << "X: " << x1 << "    Y: " << my_Function(x1) << std::endl;
}

void multi_ignition_simulation_method(double a, double b, double min, double max) {
    std::cout << "\t\t\tMultimodal Function:\n\n"
              << "N\t\t" << "Temperature\t\t\t\t" << "x\t\t\t\t" << "f(x)\n";
    double temp_i = max;

    std::mt19937 generator{ std::random_device{}() };
    std::uniform_real_distribution<> dis{a, b};
    double x1 = dis(generator);
    double x2, delta;
    size_t counter = 0;
    while(temp_i > min) {
        x2 = dis(generator);
        delta = multimodal_Function(x2) - multimodal_Function(x1);
        if(delta <= 0) {
            x1 = x2;
        }
        else if(delta > 0) {
            if(IsTransition(delta, temp_i)) {
                x1 = x2;
            }
        }
        counter++;
        std::cout << counter<< std::fixed << std::setprecision(7)  << "\t|\t" << temp_i << "  \t|\t" << x1 << "\t|\t" << multimodal_Function(x1) << std::endl;
        temp_i *= 0.95;
    }
    std::cout << "X: " << x1 << "    Y: " << multimodal_Function(x1) << std::endl;
}

int main() {
    double begin, end, max_temperature, min_temperature;
    std::string userChoice;
    std::cout << "Hello, user! This is test app =)\n";
    while(userChoice != "n") {
        std::cout << "\tEnter value \'a\'\n>> ";

        while(!(std::cin >> begin)) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Not a value, try again\n>> ";
        }
        std::cout << "Enter value \'b\'\n>> ";
        while(!(std::cin >> end)) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Not a value, try again\n>> ";
        }

        std::cout << "Enter value min temperature:\n>> ";
        while(!(std::cin >> min_temperature)) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Not a value, try again\n>> ";
        }

        std::cout << "Enter value max temperature:\n>> ";
        while(!(std::cin >> max_temperature)) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Not a value, try again\n>> ";
        }

        uni_ignition_simulation_method(begin, end, min_temperature, max_temperature);
        multi_ignition_simulation_method(begin, end, min_temperature, max_temperature);
        userChoice = "";
        while(userChoice != "n" && userChoice !="y") {
            std::cout << "\nWant again? (y/n): ";
            std::cin.clear();
            std::cin >> userChoice;
        }
    }
    return 0;
}