#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

struct Board {
    std::vector<std::vector<unsigned short>> numbers;
    std::vector<std::vector<bool>> marked_nums;
};

/*
    checks if all numbers in a row or a column are marked as used
*/
bool check_board(const Board& b) {
    // rows
    for(const auto& row : b.marked_nums) {
        bool all_nums_used = true;  // condition variable if all nums are used in this row
        for(const auto &i : row) {
            if(!i) {
                all_nums_used = false;
                break;
            }
        }
        if(all_nums_used) {
            return true;
        }
    }

    // columns
    for(unsigned short column = 0; column < b.marked_nums[0].size(); ++column) {
        bool all_nums_used = true;  // condition variable if all nums are used in this row
        for(unsigned short row = 0; row < b.marked_nums.size(); ++row) {
            if(! b.marked_nums[row][column]) {
                all_nums_used = false;
                break;
            }
        }
        if(all_nums_used) {
            return true;
        }
    }
    return false;
}


int main() {
    std::fstream input;
    std::vector<Board> boards;  // list of all boards and their "marked" numbers
    Board* winner_board = nullptr;
    unsigned int winner_board_score = 0;

    input.open("part1 - input.txt", std::fstream::in);
    if(! input.good()) {
        std::cerr << "Error while opening the input-file\n";
        return -1;
    }

    char tmp;

    std::string r_nums;     // the random_nums as string
    std::getline(input, r_nums);

    std::vector<unsigned short> random_nums;
    unsigned int tmp_num = 0;
    for(char c : r_nums) {
        if(c != ',') {
            tmp_num *= 10;
            tmp_num += c - '0';
        }
        else {
            random_nums.push_back(tmp_num);
            tmp_num = 0;
        }
    }
    random_nums.push_back(tmp_num);


    tmp_num = 0;


    Board board;
    char last_read = '-';   // give it just a random value
    while(input.read(&tmp, 1)) {
        if( (tmp == ' ' && last_read != ' ' && last_read != '\n') || (tmp == '\n' && last_read >= '0' && last_read <= '9') ) {
            // add num to last line
            board.numbers[board.numbers.size() - 1].push_back(tmp_num);
            tmp_num = 0;
        }
        else if(tmp >= '0' && tmp <= '9') {
            // convert num
            tmp_num *= 10;
            tmp_num += tmp - '0';
        }
        else if(tmp == '\n' && last_read == '\n') {
            // create new board
            board.numbers.pop_back();   // added one line to much
            boards.push_back(board);
            board = Board();
            board.numbers.push_back(std::vector<unsigned short>());
            //break;
        }

        if(tmp == '\n' && last_read != '\n') {
            // add new line
            board.numbers.push_back(std::vector<unsigned short>());
        }
        last_read = tmp;
    }
    board.numbers.pop_back();   // remove last line like in create new board
    boards.push_back(board);    // add last board to boards

    input.close();

    // setup for every number a indicator if the number is marked and mark it at not used(false)
    for(Board &b : boards) {
        for(std::vector<unsigned short> &row : b.numbers) {
            b.marked_nums.push_back(std::vector<bool>(row.size(), false));
        }
    }


    // calling numbers
    unsigned short last_called_number = 0;
    for(unsigned short r_num : random_nums) {
        if(winner_board != nullptr) {   // we found the winnerboard - exit
            break;
        }
        last_called_number = r_num;
        // go over the boards and check if they are "finished"
        // otherwise set the current number as marked
        for(unsigned short board_num = 0; board_num < boards.size(); ++board_num) {

            for(unsigned short x = 0; x < boards[board_num].numbers.size(); ++x) {
                for(unsigned short y = 0; y < boards[board_num].numbers[x].size(); ++y) {
                    if(boards[board_num].numbers[x][y] == r_num) {
                        boards[board_num].marked_nums[x][y] = true;
                    }
                }
            }

            if(check_board(boards[board_num])) {
                // the actual board is the winner-Board
                winner_board = & boards[board_num];
                break;
            }
        }
    }

    // --------> calculating the score of the winner-board
    unsigned short sum_unmarked_nums = 0;
    for(unsigned short row = 0; row < winner_board->marked_nums.size(); ++row) {
        for(unsigned short column = 0; column < winner_board->marked_nums[row].size(); ++ column) {
            if(winner_board->marked_nums[row][column] == false) {
                sum_unmarked_nums += winner_board->numbers[row][column];
            }
        }
    }
    winner_board_score = sum_unmarked_nums * last_called_number;
    std::cout << "Winner-Board-Score: " << winner_board_score << '\n';

    return 0;
}