#include "calc1c.hpp"
using namespace std;

template <class Container>
/**
 * @brief  Função para se dividir uma string em divisores definidos
 * @note  Pega de um site
 * @param  &str: String a ser dividida
 * @param  &cont: Container que carregará as strings oriundas da divisão
 * @param  delim: Delimitador que define onde será dividida a string
 */
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

vector<unsigned long> compiledInstructions;
int main(int argc, char const *argv[]) {
  string file = argv[1], outputFile = "mem.txt";
  int i = 0;
  bool canDo = true;
  string currInstruction;
  unsigned long fullInstruction = 0;
  string line;

  if (argc > 2) {
    if ((string)argv[2] != (string) "-o") {
      cerr << ("Argumento invalido! Terminando programa... \n");
      return 1;
    }
    outputFile = argv[3];
  }
  fstream fileStream(file);

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
    i++;
  }
  while (i++ < 1024) {
    compiledInstructions.push_back(0);
  }

  FILE *outputStream = fopen(outputFile.c_str(), "w");
  if (canDo) {
    for (auto instruction : compiledInstructions)
      fprintf(outputStream, "%08lX\n", instruction);
  }
}
