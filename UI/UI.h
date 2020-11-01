#ifndef SRC_UI_H
#define SRC_UI_H

#include "../Utils/utils.h"
#include "../Utils/defs.h"

#include "../Aderentes/Aderente.h"
#include "../Cinemateca/Cinemateca.h"
#include "../Evento/Evento.h"
#include "../Sala/Sala.h"


using namespace std;

typedef void (*menuFunctionPtr)();

/*
 * Criação de menus
 */

static void close();
static void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr>> menuItems);
static u_int getUnsignedIntInputInclusive(u_int lowerBound, u_int higherBound, string errorMsg);

/*
 * Menus
 */

void menuMain();
void menuAderentes();
void menuEventos();
void menuKiosk();
void menuOrdenarAderentes();
void menuOrdenarEventos();

/*
 * Views
 */

void viewRegistarAderente();
void viewListarAderentes();
void viewMostrarEvento(Evento evento);
void viewAdicionarEvento();
void viewListarEventos();
void viewComprarBilhetes();
void viewBilhetesComprados();
void viewValorDeVendas();
void viewTotalBilhetesComprados();
void viewTotalVendas();

/*
 * Funções
 */

void funcOrdenarAderentesNome();
void funcOrdenarAderentesDataNasc();
void funcOrdenarAderentesAnoAdesao();
void funcOrdenarEventosNome();
void funcOrdenarEventosData();
void funcOrdenarEventosPreco();


#endif //SRC_UI_H
