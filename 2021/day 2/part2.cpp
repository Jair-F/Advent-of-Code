#include <iostream>
#include <fstream>
#include <string>

struct position {
    unsigned int horizontal = 0;
    unsigned int vertical = 0;      // depth
};

struct trackers {
    position pos;
    unsigned short aim = 0;
};

int main() {
    std::string line;
    std::fstream input("part2 - input.txt", std::ios::in);

    if(!input.good()) {
        std::cerr << "Error while reding the input file!!\n";
        return -1;
    }

    trackers trcks;     // the values we have to keep tracking bundeld togehter

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
            trcks.pos.horizontal += parameter_int;
            trcks.pos.vertical = trcks.pos.vertical + trcks.aim * parameter_int;
        }
        else if(command == "up") {
            trcks.aim -= parameter_int;
        }
        else if(command == "down") {
            trcks.aim += parameter_int;
        }
    }

    input.close();

    std::cout << "Position: \n\tVertical: " << trcks.pos.vertical << "\n\tHorizontal: " << trcks.pos.horizontal << "\n\n";
    std::cout << "Multiplication fof Horizontal and Vertical: " << trcks.pos.horizontal * trcks.pos.vertical << '\n';

    return 0;
}