# Compilador para arquitetura `CALC1`

Compilador de código para a arquitetura `CALC1`, feito em `c++`.

## Instalação

Caso queira utilizar o compilador em qualquer pasta, pelo terminal, mova o arquivo executável para o destino final que você quiser e adicione o caminho desse destino à sua variável `PATH` no seu computador. A instalação em geral colocar o arquivo binário na pasta `bin`, dentro da pasta principal do arquivo.

### Linux

Vá para a pasta do compilador no terminal e digite `make install`.

### Windows

Vá para a pasta do compilador no terminal e digite `g++ src/*.cpp -o bin/calc1c.exe`.

#### Compilação em geral

Para compilar um arquivo, apenas escreva `calc1c nomeDoArquivo.cac`. A opção `-o` muda o nome do arquivo de saída, porém é desnecessário, a saída default é mem.txt.

## Linguagem

`ADD` - adicionar  
`SUB` - subtrair  
`MUL` - multiplicar  
`DIV` - dividir  
`MR` - memory read  
`MC` - memory clear  
`MW` - memory write  
`HLT` - halt / parar programa
