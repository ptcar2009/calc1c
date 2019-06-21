#ifndef CALC1C_HPP
#define CALC1C_HPP
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <vector>


unordered_map<string, int> instructions = {
    {"ADD", 0b000}, {"SUB", 0b001}, {"DIV", 0b010}, {"MUL", 0b011},
    {"MC", 0b100},  {"MR", 0b110},  {"MW", 0b111},  {"HLT", 0b101}};

unordered_map<string, int> registers = {
    {"A", 0b00}, {"B", 0b01}, {"ACC", 0b10}, {"ZERO", 0b11}};

#endif // !CALC1C_HPP