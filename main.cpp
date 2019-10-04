#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>

static std::mt19937 generator{ std::random_device{}() };

double my_Function(double x) {
    return -sqrt(x)*sin(x);
}

double multimodal_Function(double x) {
    return my_Function(x) * sin(5 * x);
}

bool IsTransition(double delta, double temp_i) {
    std::uniform_real_distribution<> dist{0, 1};
    double value = dist(generator);
    double P = exp(-delta/temp_i);
    return value <= P;
}

void uni_ignition_simulation_method(double begin, double end, double min_temp, double max_temp) {
    std::cout << "\t\t\tUnimodal Function:\n\n"
    << "N\t\t" << "Temperature\t\t\t\t" << "x\t\t\t\t" << "f(x)\n";
    double current_temperature = max_temp;

    std::uniform_real_distribution<> dis{begin, end};
    double first_x = dis(generator);
    double new_x, delta;
    size_t counter = 0;
    while(current_temperature > min_temp) {
        new_x = dis(generator);
        delta = my_Function(new_x) - my_Function(first_x);
        if(delta <= 0) {
            first_x = new_x;
        }
        else if(delta > 0) {
            if(IsTransition(delta, current_temperature)) {
                first_x = new_x;
            }
        }
        counter++;
        std::cout << counter<< std::fixed << std::setprecision(7)  << "\t|\t" << current_temperature
                  << "  \t|\t" << first_x
                  << "\t|\t" << my_Function(first_x) << std::endl;
        current_temperature *= 0.95;
    }
    std::cout << "X: " << first_x << "    Y: " << my_Function(first_x) << std::endl;
}

void multi_ignition_simulation_method(double begin, double end, double min_temp, double max_temp) {
    std::cout << "\t\t\tMultimodal Function:\n\n"
              << "N\t\t" << "Temperature\t\t\t\t" << "x\t\t\t\t" << "f(x)\n";
    double current_temperature = max_temp;
    std::uniform_real_distribution<> dis{begin, end};
    double first_x = dis(generator);
    double new_x, delta;
    size_t counter = 0;
    while(current_temperature > min_temp) {
        new_x = dis(generator);
        delta = multimodal_Function(new_x) - multimodal_Function(first_x);
        if(delta <= 0) {
            first_x = new_x;
        }
        else if(delta > 0) {
            if(IsTransition(delta, current_temperature)) {
                first_x = new_x;
            }
        }
        counter++;
        std::cout << counter<< std::fixed << std::setprecision(7)  << "\t|\t" << current_temperature
                  << "  \t|\t" << first_x
                  << "\t|\t" << multimodal_Function(first_x) << std::endl;
        current_temperature *= 0.95;
    }
    std::cout << "X: " << first_x << "    Y: " << multimodal_Function(first_x) << std::endl;
}

int main() {
    double begin, end, max_temperature, min_temperature;
    std::string userChoice;
    std::cout << "Hello, user! This is test app =)\n";
    while(userChoice != "n") {
        std::cout << "\tEnter value \'a\'\n>> ";
        std::cin >> begin;

        std::cout << "Enter value \'b\'\n>> ";
        std::cin >> end;

        std::cout << "Enter value min temperature:\n>> ";
        std::cin >> min_temperature;

        std::cout << "Enter value max temperature:\n>> ";
        std::cin >> max_temperature;

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