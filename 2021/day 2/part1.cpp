#include <iostream>
#include <fstream>
#include <string>

struct position {
    unsigned int horizontal = 0, vertical = 0;
};

int main() {
    std::string line;
    std::fstream input("part1 - input.txt", std::ios::in);

    position pos;

    while(std::getline(input, line)) {
        std::string command, parameter;

        // extract the values and store them in seperated variables
        unsigned short split_pos = line.find(' ');  // position to split between the command and the parameter(the number)
        command = line.substr(0, split_pos);
        parameter = line.substr(split_pos+1);   // to the end
        //std::cout << command << ':' << parameter << '\n';

        // convert the parameter into a int
        unsigned short parameter_int = 0;
        for(char digit : parameter) {
            parameter_int *= 10;
            parameter_int += digit - '0';
        }

        if(command == "forward") {
            pos.horizontal += parameter_int;
        }
        else if(command == "up") {
            pos.vertical -= parameter_int;
        }
        else if(command == "down") {
            pos.vertical += parameter_int;
        }
    }

    input.close();

    std::cout << "Position: \n\tVertical: " << pos.vertical << "\n\tHorizontal: " << pos.horizontal << "\n\n";
    std::cout << "Multiplication fof Horizontal and Vertical: " << pos.horizontal * pos.vertical << '\n';

    return 0;
}