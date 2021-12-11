#include <iostream>
#include <fstream>
#include <string>
#include <list>


std::size_t power(unsigned int num, unsigned int pow) {
    if(pow == 0) {
        return 1;
    }
    else if(pow > 1) {
        return num * power(num, pow - 1);
    }
    else {
        return num;
    }
}

std::size_t bin_to_dec(std::string bin_num) {
    std::size_t ret = 0;
    
    std::string tmp;
    // reverse string so we can easily go from real begin to end
    for(int i = bin_num.length() - 1; i >= 0; --i) {
        tmp += bin_num[i];
    }
    bin_num = tmp;

    for(unsigned short i = 0; i < bin_num.size(); ++i) {
        ret += (bin_num[i] - '0') * power(2, i);
    }
    return ret;
}


int main() {
    std::fstream input("part2 - input.txt", std::ios::in);

    if(!input.good()) {
        std::cerr << "Error while parsing the input file...\n";
        return -1;
    }

    std::string oxygen_rate, co2_scrubber_rate;
    std::string line;

    std::list<std::string> input_data;

    while(std::getline(input, line)) {
        input_data.emplace_back(line);
    }

    
    std::list<std::string> oxygen_rating_options(input_data);
    std::list<std::string> co2_scrubber_rating_options(input_data);
    unsigned short position = 0;    // position in the binary string in every single line

    while(position < input_data.front().size() && oxygen_rating_options.size() > 1) {

        unsigned short zero_occourence = 0;
        for(std::string &option : oxygen_rating_options) {
            if(option[position] == '0') {
                ++zero_occourence;
            }
        }

        unsigned short ones_occourence = oxygen_rating_options.size() - zero_occourence;


        char most_common_value = zero_occourence > ones_occourence ? '0' : '1';     // if they are equal keep value 1
        // finding the oxygen_rating_value
        auto iterator = oxygen_rating_options.begin();
        while (iterator != oxygen_rating_options.end()) {
            if((*iterator)[position] != most_common_value) {
                decltype(iterator) tmp = iterator;
                ++tmp;
                oxygen_rating_options.erase(iterator);
                iterator = tmp;
            }
            else {
                ++iterator;
            }
        }
        ++position;
    }

    position = 0;

    while(position < input_data.front().size() && co2_scrubber_rating_options.size() > 1) {

        unsigned short zero_occourence = 0;
        for(std::string &option : co2_scrubber_rating_options) {
            if(option[position] == '0') {
                ++zero_occourence;
            }
        }

        unsigned short ones_occourence = co2_scrubber_rating_options.size() - zero_occourence;

        char least_common_value = zero_occourence <= ones_occourence ? '0' : '1';     // if they are equal keep value 0
        // finding co2_scrubber_rating
        auto iterator = co2_scrubber_rating_options.begin();
        while(iterator != co2_scrubber_rating_options.end()) {
            if((*iterator)[position] != least_common_value) {
                decltype(iterator) tmp = iterator;
                ++tmp;
                co2_scrubber_rating_options.erase(iterator);
                iterator = tmp;
            }
            else {
                ++iterator;
            }
        }

        ++position;
    }

    oxygen_rate = oxygen_rating_options.front();
    co2_scrubber_rate = co2_scrubber_rating_options.front();

    std::cout << "oxygen-Rate: " << oxygen_rate << " -> " << bin_to_dec(oxygen_rate) << '\n';
    std::cout << "CO2-scrubber-Rate: " << co2_scrubber_rate << " -> " << bin_to_dec(co2_scrubber_rate) << '\n';
    std::cout << "Life-Supporting-Rate: " << bin_to_dec(oxygen_rate) * bin_to_dec(co2_scrubber_rate) << '\n';


    return 0;
}