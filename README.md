# Compilador para arquitetura `CALC1`

Compilador de código para a arquitetura `CALC1`, feito em `c++`.

## Instalação

Caso queira utilizar o compilador em qualquer pasta, pelo terminal, mova o arquivo executável para o destino final que você quiser e adicione o caminho desse destino à sua variável `PATH` no seu computador.

A instalação em geral colocar o arquivo binário na pasta `bin`, dentro da pasta principal do arquivo.

### Linux

Vá para a pasta do compilador no terminal e digite `make install`.

### Windows

Vá para a pasta do compilador no terminal e digite `g++ src/*.cpp -o bin/calc1c.exe -Iinclude`.

## Compilação

Para compilar um arquivo, apenas escreva `calc1c nomeDoArquivo.cac`. A opção `-o` muda o nome do arquivo de saída, porém é desnecessário, a saída default é `mem.txt`.

Caso você não adicione o compilador ao `PATH`, basta abrir o diretório do arquivo gerado pela instalação, normalmente o `/bin`, e digitar

`calc1c caminhoDoArquivo/nomeDoArquivo.cac`.

## Linguagem

`ADD` - adicionar  
`SUB` - subtrair  
`MUL` - multiplicar  
`DIV` - dividir  
`MR` - memory read  
`MC` - memory clear  
`MW` - memory write  
`HLT` - halt / parar programa

Todos os comandos exigem três argumentos posicionais, separados por `,`, exceto o comando `HLT`, no qual o compilador ignora tudo que está escrito depois dele.

O primeiro argumento é o registrador que guarda os dados que serão usados no comando. No caso do comando `MR`, esse primeiro argumento é ignorado pelo compilador, então você pode deixar o espaço vazio ou escrever qualquer coisa.

O segundo argumento é apenas útil para o comando `MR`, e ele representa o registrador que guardará os dados lidos na posição de memória especificada.

### Os registradores

Para os comandos que exigem registradores (todos menos o `HLT`), os registradores aceitos pelo compilador são o `A`,
o `B`, o `ACC` e o `ZERO`. O `A` e o `B` são registradores intermediários de leitura de memória. O registrador `ACC` é o acumulador da calculadora.

Para o comando `MR`, o registrador `ZERO` é substítuido por `ACC` no código de máquina final.

### Terceiro argumento

O terceiro argumento é um imediato, que no caso das instruções `MR`, `MC` e `MW` indica a posição de memória que será afetada, e no caso das outras é um imediato que faz o papel de um número qualquer na operação.
