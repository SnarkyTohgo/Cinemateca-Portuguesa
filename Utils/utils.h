#ifndef CINEMATECAPORTUGUESA_UTILS_H
#define CINEMATECAPORTUGUESA_UTILS_H

/** @defgroup Utils
 * Funções de utilidade geral
 *
 * @{
 */

#include "defs.h"


/*
 * Extern Globals
 */

extern ifstream salasDB;
extern ifstream eventosDB;
extern ifstream aderentesDB;
extern ifstream naoAderentesDB;

extern vector<string> salasData;
extern vector<string> eventosData;
extern vector<string> aderentesData;
extern vector<string> naoAderentesData;


/**
 * @defgroup I/O
 * Funções de input/output de dados
 *
 * @{
 */

/**
 * @brief Imprime uma linha de tamanho especificado com um caracter especificado
 * @param size Tamanho da linha
 * @param ch Caracter
 */
void line(int size, char ch = '-');

/**
 * @brief Imprime uma uma mensagem de erro para o descritor STDERR
 * @param message Mensagem a iprimir
 */
void cinERR(const string &message);


/**
 * @brief Tenta aceder a uma opção válida do tipo inteiro do descritor STDIN para utilizar dentro de um switch-case
 * @param dest Espaço em memória onde a opção é armazenada
 * @param message Mensagem que aparece no ecrã
 * @param cond Função de condição
 */
void getOption(int &dest, const string &message = "Option: ", function<bool(int)> cond = [](int a) { return true; });


/**
 * @brief Tenta aceder a uma lista de opções válidas do tipo inteiro do descritor STDIN para utilizar dentro de um switch-case
 * @param dest Array dinâmico para onde são guardadas as opções
 * @param message Mensagem que aparece no ecrã
 * @param cond Função de condição
 */
void getOptionList(vector<int> &dest, const string &message = "Option (* to end): ", function<bool(int)> cond = [](int a) { return true; });

void getDouble(double &dest, const string &message = "Enter double: ");

void enterWait(const string &message = "ENTER to go back");

/** @} */ // end of I/O

/**
 * @defgroup CALC
 * Funções de cálculo
 *
 * @{
 */

/**
 * @brief Calcula um valor pseudo-aleatório dentro de um intervalo numérico
 * @param lower chão do intervalo numérico
 * @param upper teto do intervalo numérico
 * @return valor aleatório
 */
int rng(int lower, int upper);

/** @} */ // end of Calc

/**
 * @defgroup TEXT
 * Funções de manipulação de strings
 *
 * @{
 */

/**
 * @brief Transforma uma string em uppercase
 * @param s String a transformar
 */
string toUpper(string s);

/**
 * @brief Poda uma string à esquerda
 * @param s String a transformar
 */
void lTrim(string &s);

/**
 * @brief Poda uma string à direita
 * @param s String a transformar
 */
void rTrim(string &s);

/**
 * @brief Poda uma string de ambos os lados
 * @param s String a transformar
 */
void trim(string &s);

// Split
template<typename t>
void split(const string& s, char delim, t result);

/**
 * @brief Corta uma string por um delimitador e transforma-a num array
 * @param s String a transformar
 * @param delim Delimitador
 * @return Array composto pelas partes da string
 */
vector<string> split(const string &s, char delim);

/** @} */ // end of TEXT

/**
 * @defgroup FILES
 * Funções de manipulação de ficheiros
 *
 * @{
 */

/**
 * @brief Verifica se um ficheiro está vazio
 * @param file Ficheiro a verificar
 * @return true se está vazio, false caso contrário
 */
bool fileIsEmpty(ifstream& file);

/**
 * @brief Cria um novo ficheiro
 * @param filename String contendo o nome do ficheiro
 */
void makeFile(string filename);

/**
 * @brief Abre um ficheiro em modo de leitura
 * @param filename String contendo o nome do ficheiro
 * @return ficheiro aberto em modo de leitura
 */
ifstream readFile(string filename);

/**
 * @brief Escreve para um ficheiro
 * @param data Endereço de memória da informação a escrever para o ficheiro
 * @param filename Nome do ficheiro para onde escrever
 */
void writeToFile(vector<string> &data, string filename);
void writeToFile(string &data, string filename);

/**
 * @brief Escreve para um ficheiro
 * @param data Informação a escrever para o ficheiro
 * @param filename Nome do ficheiro para onde escrever
 */
void writeData(string data, string filename);

/**
 * @brief Faz parsing da informação de um ficheiro
 * @param file Endereço de memória do ficheiro contendo a informação
 * @return Array dinâmico contendo a informação do ficheiro
 */
vector<string> parseFile(ifstream &file);

/**
 * @brief Apaga a informação de um ficheiro
 * @param filename Nome do ficheiro
 */
void deleteFileData(string filename);

/** @} */ // end of FILES

/** @} */ // end of Utils

#endif //CINEMATECAPORTUGUESA_UTILS_H
