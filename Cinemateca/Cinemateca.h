#ifndef SRC_CINEMATECA_H
#define SRC_CINEMATECA_H

#include "../Utils/utils.h"

#include "../Aderentes/Aderente.h"
#include "../Evento/Evento.h"
#include "../Sala/Sala.h"

class Cinemateca {
private:
    static u_int anoAtual;

    const string localizacao;
    const string morada;

    list<Aderente> aderentes;
    list<Sala> salas;
    list<Evento> eventos;

    u_int bilhetesComprados;
    double totalVendas;

public:
    Cinemateca(){};
    Cinemateca(string localizacao, string morada);

    u_int getAnoAtual() const;
    string getLocalizacao() const;
    string getMorada() const;
    list<Aderente> getAderentes() const;
    list<Sala> getSalas() const;
    list<Evento> getEventos() const;
    Evento getEvento(int pos) const;
    u_int getBilhetesComprados() const;
    double getTotalVendas() const;

    void setSalas(list<Sala> salas);
    void setEventos(list<Evento> eventos);
    void setAderentes(list<Aderente> aderentes);

    void registarAderente(string nome, u_int nif, Date dataNasc, u_int anoAtual);
    void adicionarEvento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco);
    void adicionarSala(string nome, u_int capacidade);

    void alocarSala(Evento* evento);
    int comprarBilhete(Aderente aderente, Evento* evento);

    void parseSalas();
    void parseEventos();
    void parseAderentes();

    void updateAderentes(Aderente aderente) const;
    void updateEventos(Evento evento) const;
    void updateBilhetesComprados();
    void updateTotalVendas(const float valor);

    void ordenarSalasNome();
    void ordenarSalasCapacidade();

    void ordenarEventosNome();
    void ordenarEventosData();
    void ordenarEventosPreco();
    void ordenarEventosLotMax();

    void ordenarAderentesNome();
    void ordenarAderentesDataNasc();
    void ordenarAderentesAnoAdesao();
};


#endif //SRC_CINEMATECA_H
