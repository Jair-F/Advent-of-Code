#include <iostream>
#include <fstream>
#include <string>


int main() {
    std::fstream input;
    input.open("part2 - input.txt", std::fstream::in);

    unsigned int incerases = 0;     // number of measurement-incerases

    // 0 means not set
    int first_num = 0, second_num = 0, third_num = 0;
    int recent_measurement = 0, last_measurement = 0;

    std::string tmp;
    while(std::getline(input, tmp)) {
        for(char digit : tmp) {
            first_num *= 10;
            first_num += digit - '0';
        }
        if(first_num != 0 && second_num != 0 && third_num != 0) {    // if all three variables are set to a valid number
            recent_measurement = first_num + second_num + third_num;
            if(last_measurement != 0 && recent_measurement != 0) {
                if(recent_measurement > last_measurement) {
                    ++incerases;
                }
            }
        }


        // setting variables for the next loop
        third_num = second_num;
        second_num = first_num;
        first_num = 0;     // setting it to not set
        last_measurement = recent_measurement;
        recent_measurement = 0;
    }


    input.close();

    std::cout << "Incerases: " << incerases << '\n';

    return 0;
}