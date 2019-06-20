#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>
#define SHIFT_CONSTANT 16
using namespace std;
template <class Container>
void split1(const std::string &str, Container &cont) {
  std::istringstream iss(str);
  std::copy(std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(), std::back_inserter(cont));
}

template <class Container>
void split3(const std::string &str, Container &cont, char delim = ' ') {
  std::size_t current, previous = 0;
  current = str.find(delim);
  while (current != std::string::npos) {
    cont.push_back(str.substr(previous, current - previous));
    previous = current + 1;
    current = str.find(delim, previous);
  }
  cont.push_back(str.substr(previous, current - previous));
}
map<string, int> instructions = {{"ADD", 0b000}, {"SUB", 0b001}, {"DIV", 0b010},
                                 {"MUL", 0b011}, {"MC", 0b100},  {"MR", 0b110},
                                 {"MW", 0b111},  {"HLT", 0b101}};

map<string, int> registers = {
    {"A", 0b00}, {"B", 0b01}, {"ACC", 0b10}, {"ZERO", 0b11}};

vector<unsigned long> compiledInstructions;
int main(int argc, char const *argv[]) {
  string file = argv[1], outputFile = "mem.txt";

  if (argc > 2) {
    if (argv[2] != "-o") {
      cerr << ("Argumento invalido! Terminando programa... \n");
      return 1;
    }
    outputFile = argv[3];
  }
  fstream fileStream(file);
  string currInstruction;
  int i = 0;
  bool canDo = true;
  string line;
  unsigned long fullInstruction = 0;
  while (getline(fileStream, line)) {
    stringstream stream(line);
    string opCode;
    stream >> opCode;
    fullInstruction = 0;
    try {
      fullInstruction += instructions.at(opCode) << 29;
    } catch (const std::exception &e) {
      cerr << "Instrução invalida '" << opCode << "' - linha " << i << endl
           << line << endl
           << endl;
      canDo = false;
      continue;
    }
    if (opCode == "HLT") {
      compiledInstructions.push_back(fullInstruction);
      break;
    }
    string rest;
    getline(stream, rest);
    vector<string> params;
    split3(rest, params, ',');
    for (auto &param : params) {
      string::iterator end_pos = std::remove(param.begin(), param.end(), ' ');
      param.erase(end_pos, param.end());
    }
    if (params.size() != 3) {
      cerr << "Numero de parametros invalido - " << params.size() << " - linha "
           << i << endl
           << line << endl
           << endl;
      canDo = false;
      continue;
    }
    if (opCode == "MR") {
      try {
        fullInstruction += registers.at(params[1]) << 25;
      } catch (const std::exception &e) {
        cerr << "Registrador invalido: '" << params[1] << "' - linha " << i
             << endl
             << line << endl
             << endl;
        canDo = false;
        continue;
      }
    } else {
      try {
        fullInstruction += registers.at(params[0]) << 27;
      } catch (const std::exception &e) {
        cerr << "Registrador invalido: '" << params[0] << "' - linha " << i
             << endl
             << line << endl
             << endl;
        canDo = false;
        continue;
      }
    }
    int imediato;
    try {
      imediato = stoi(params[2]);
    } catch (const std::exception &e) {
      cerr << "Imediato invalido: '" << params[2] << "' - linha " << i << endl
           << line << endl
           << endl;
      canDo = false;
      continue;
    }
    if (abs(imediato) >= (1 << 24)) {
      cerr << "Imediato grande demais! - linha " << i << endl
           << line << endl
           << endl;
      canDo = false;
      continue;
    }
    fullInstruction += imediato;
    compiledInstructions.push_back(fullInstruction);
  }
  FILE *outputStream = fopen(outputFile.c_str(), "w");
  if (canDo) {
    for (auto instruction : compiledInstructions)
      fprintf(outputStream, "%08lX\n", instruction);
  }
}
