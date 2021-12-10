#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::string line;
    unsigned int incerases = 0;

    unsigned short last_data_int = 0;
    while(std::getline(input, line)) {
        unsigned short data_int = 0;
        for(char digit : line) {
            data_int *= 10;
            data_int += digit - '0';
        }

        if(data_int > last_data_int) {
            ++incerases;
        }
        last_data_int = data_int;
    }

    input.close();

    incerases -= 1;     // first incerase we dont have a last_value
    std::cout << "Incerases: " << incerases << '\n';

    return 0;
}