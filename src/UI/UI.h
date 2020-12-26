#ifndef SRC_UI_H
#define SRC_UI_H

/** @defgroup UI - Interface de Utilizador
 * Funções para a interface de utilizador
 *
 * @{
 */

#include "../Utils/utils.h"
#include "../Utils/defs.h"

#include "../Aderentes/Aderente.h"
#include "../Cinemateca/Cinemateca.h"
#include "../Evento/Evento.h"
#include "../Sala/Sala.h"


using namespace std;

typedef void (*menuFunctionPtr)();

/**
 * @defgroup Criação de menus
 * Funções para a criação dinâmica de menus para a interface gráfica
 *
 * @{
 */

/**
 * @brief Função que encerra o menu corrente
 */
static void close();

/**
 * @brief Função que gera dinamicamente um menu
 * @param menuTitle Título do menu
 * @param menuItems Array de pares nome da opção - função da opção
 */
static void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr>> menuItems);

/**
 * @brief Função que interpreta o input do utilizador
 * @param lowerBound Mínimo permitido
 * @param higherBound Máximo permitido
 * @param errorMsg Mensagem em caso de erro
 */
static u_int getUnsignedIntInputInclusive(u_int lowerBound, u_int higherBound, string errorMsg);

/** @} */ // end of Criação de menus

/**
 * @defgroup Menus
 * Funções para a geração de menus (interface interativa com o utilizador)
 *
 * @{
 */

/**
 * @brief Função que gera o menu principal
 */
void menuMain();

/**
 * @brief Função que gera o menu Aderentes
 */
void menuAderentes();

/**
 * @brief Função que gera o menu Eventos
 */
void menuEventos();

/**
 * @brief Função que gera o menu Kiosk
 */
void menuKiosk();

/**
 * @brief Função que gera o menu Recursos Humanos
 */
void menuRecursosHumanos();

/**
 * @brief Função que gera o menu de ordenação de Aderentes
 */
void menuOrdenarAderentes();

/**
 * @brief Função que gera o menu de ordenação de Eventos
 */
void menuOrdenarEventos();

/** @} */ // end of Menus

/**
 * @defgroup Vistas
 * Funções para a geração de Vistas (informação que aparece no ecrân
 *
 * @{
 */

/**
 * @brief Função que gera o ecrã de registo de um novo aderente
 */
void viewRegistarAderente();

/**
 * @brief Função que gera o ecrã para apagar o registo de um aderente
 */
void viewApagarAderente();

/**
 * @brief Função que gera o ecrã de listagem de todos os aderente
 */
void viewListarAderentes();

/**
 * @brief Função que gera o ecrã de listagem de um evento
 */
void viewMostrarEvento(Evento evento);

/**
 * @brief Função que gera o ecrã de registo de um novo evento
 */
void viewAdicionarEvento();

/**
 * @brief Função que gera o ecrã para apagar um evento
 */
void viewApagarEvento();

/**
 * @brief Função que gera o ecrã de listagem de todos os eventos
 */
void viewListarEventos();

/**
 * @brief Função que gera o ecrã de compra de bilhetes
 */
void viewComprarBilhetes();

/**
 * @brief Função que gera o ecrã de listagem do total de bilhetes comprados
 */
void viewBilhetesComprados();

/**
 * @brief Função que gera o ecrã de listagem do total das vendas
 */
void viewValorDeVendas();

/**
 * @brief Função que gera o ecrã de listagem de um trabalhador
 */
void viewMostrarTrabalhador(RegistoTrabalhador registo);

/**
 * @brief Função que gera o ecrã de pesquisa de trabalhadores por nome
 */
void viewPesquisarTrabalhador();     // TODO

/**
 * @brief Função que gera o ecrã de contratação de um trabalhador
 */
void viewContratarTrabalhador();    // TODO

/**
 * @brief Função que gera o ecrã de listagem dos trabalhadores atuais
 */
void viewListarTrabalhadores();

/**
 * @brief Função que gera o ecrã de listagem de todos os trabalhadores
 */
void viewListarExTrabalhadores();

/** @} */ // end of Vistas

/**
 * @defgroup Funções
 * Funções gerais para o funcionamento do programa
 *
 * @{
 */

/**
 * @brief Função que ordena a lista de aderentes da cinemateca por nome
 */
void funcOrdenarAderentesNome();

/**
 * @brief Função que ordena a lista de aderentes da cinemateca por data de nascimento
 */
void funcOrdenarAderentesDataNasc();

/**
 * @brief Função que ordena a lista de aderentes da cinemateca por ano de adesao
 */
void funcOrdenarAderentesAnoAdesao();

/**
 * @brief Função que ordena a lista de eventos da cinemateca por nome
 */
void funcOrdenarEventosNome();

/**
 * @brief Função que ordena a lista de eventos da cinemateca por data
 */
void funcOrdenarEventosData();

/**
 * @brief Função que ordena a lista de eventos da cinemateca por preço
 */
void funcOrdenarEventosPreco();

/** @} */ // end of Funções

/** @} */ // end of UI
#endif //SRC_UI_H
