#include <iostream>
#include <fstream>
#include <string>

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
    std::fstream input("part1 - input.txt", std::ios::in);

    if(!input.good()) {
        std::cerr << "Error while parsing the input file...\n";
        return -1;
    }

    std::string gamma_rate_bin, epsilon_rate_bin;   // as binary
    std::size_t gamma_rate_int, epsilon_rate_int;   // convertet to an int
    unsigned short *occourence_ones, *occourence_zeros;
    std::string line;
    unsigned int num_of_lines = 0;

    std::getline(input, line);
    unsigned short chars_in_line = line.length();
    occourence_ones = new unsigned short[chars_in_line]; // get the length of one line
    occourence_zeros = new unsigned short[chars_in_line];

    for(unsigned short i = 0; i < chars_in_line; ++i) {
        occourence_ones[i] = 0;
    }

    input.seekg(std::fstream::beg);
    line.clear();

    while(std::getline(input, line)) {
        ++num_of_lines;
        for(unsigned short i = 0; i < line.size(); ++i) {
            if(line[i] == '1') {
                ++occourence_ones[i];
            }
        }
    }

    for(unsigned short i = 0; i < chars_in_line; ++i) {
        occourence_zeros[i] = num_of_lines - occourence_ones[i];
    }

    // calculating gamma_rate_bin - the most common bit
    for(unsigned short i = 0; i < chars_in_line; ++i) {
        gamma_rate_bin += occourence_ones[i] > occourence_zeros[i] ? '1' : '0';
    }
    // epsilon rate - the least common bit
    for(unsigned short i = 0; i < chars_in_line; ++i) {
        epsilon_rate_bin += occourence_ones[i] < occourence_zeros[i] ? '1' : '0';
    }

    delete [] occourence_ones;
    delete [] occourence_zeros;

    gamma_rate_int = bin_to_dec(gamma_rate_bin);
    epsilon_rate_int = bin_to_dec(epsilon_rate_bin);

    std::cout << "epsilon_rate: " << epsilon_rate_bin << ':' << epsilon_rate_int << "\tgamma_rate: " << gamma_rate_bin << ':' << gamma_rate_int << '\n';
    std::cout << "Power-Comsumption: " << epsilon_rate_int * gamma_rate_int << '\n';

    return 0;
}