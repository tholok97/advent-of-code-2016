#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>

int abs(int x) {
    if (x < 0)
        return -x;
    return x;
}

// parse input from file into vector of instructions 
std::vector<std::string> parse(std::string inputFile) {
    
    std::ifstream ifs(inputFile);
    std::vector<std::string> instructions;
    instructions.push_back("");

    char c;
    while (ifs >> c) {
        if (c != ',') {
            instructions.back().append(std::string(1, c));
        } else {
            instructions.push_back("");
        }
    }

    return instructions;
}

int part1(std::vector<std::string> instructions) {

    // N, E, S, W 
    std::array<int, 4> distances{0, 0, 0, 0};

    int facing = 0; // initially facing north

    for (std::string instruction : instructions) {

        char dir = instruction[0];

        if (dir == 'R') {
            // 90 degree turn right
            facing = (facing == 3) ? 0 : facing + 1;
        } else if (dir == 'L') {
            // 90 degree turn left
            facing = (facing == 0) ? 3 : facing - 1;
        } else {
            std::cout << "ERROR unknown direction " << dir << std::endl;
        }

        int dist = instruction[1] - '0';

        distances[facing] += dist;
    }

    std::cout << distances[0] << std::endl;
    std::cout << distances[1] << std::endl;
    std::cout << distances[2] << std::endl;
    std::cout << distances[3] << std::endl;

    return abs(distances[0] - distances[2]) + 
           abs(distances[1] - distances[3]);
}

int main() {


    // 332
    // 100
    auto instructions = parse("input/input_day1.cpp");

    std::cout << "Part 1: " << part1(instructions) << std::endl;


    return 0;
} 
