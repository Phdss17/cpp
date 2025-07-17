# Phdss
Projeto de implemetação de dicionarios usando as estrutura arvore avl e rubro-negra e as tebelas hash

Comando de compilação:
g++ -std=c++17 -Wall -Wextra -Wpedantic -o tst main.cpp -licuuc -licui18n

Comando de execução:
./tst (estrutura: dictionary_avl, dictionary_rb, dictionary_cht, dictionary_oah) (nome do arquivo que deseja que seja lido) (nome do arquivo de saida, opcional)

caso não coloque um nome para o arquivo de saida será retornado um arquivo no formato de estruturaUtilizada_arquivoLido

evite ler arquivos com _ no nome, o terminal não lida bem com esse tipo de entrada, não encontrei a razão
