#include "Evento.h"

// EVENTO

/*
 * CONSTRUCTORS
 */

Evento::Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco)
    : nome(nome){

    this->data = data;
    this->hora = hora;
    this->duracao = duracao;
    this->lotMax = lotMax;
    this->preco = preco;
    this->totalVendas = 0;
    this->bilhetesComprados = 0;
}

Evento::Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala, u_int bilhetesComprados)
        : nome(nome){

    this->data = data;
    this->hora = hora;
    this->duracao = duracao;
    this->lotMax = lotMax;
    this->preco = preco;
    this->sala = sala;
    this->totalVendas = 0;
    this->bilhetesComprados = bilhetesComprados;
}


/*
 * MEMBER FUNCTIONS
 */

string
Evento::getNome() const {
    return this->nome;
}

Date
Evento::getData() const {
    return this->data;
}

Time
Evento::getHora() const {
    return this->hora;
}

u_int
Evento::getDuracao() const {
    return this->duracao;
}

u_int
Evento::getLotMax() const {
    return this->lotMax;
}

float
Evento::getPreco() const {
    return this->preco;
}

u_int
Evento::getSala() const {
    return this->sala;
}

list<Utilizador>
Evento::getParticipantes() const {
    list<Utilizador> participantes = this->participantesNaoAderentes;

    for (auto aderente : this->participantesAderentes){
        Utilizador u = aderente;
        participantes.push_back(u);
    }

    return participantes;
}

u_int
Evento::getBilhetesComprados() const {
    return this->bilhetesComprados;
}

float
Evento::getTotalVendas() const {
    return this->totalVendas;
}

void
Evento::setSala(const u_int sala){
    this->sala = sala;
}

bool
Evento::isLotado() const {
    return (this->participantesAderentes.size() + this->participantesNaoAderentes.size()) == this->lotMax;
}

void
Evento::updateTotalVendas(float valor){
    this->totalVendas += valor;
}

void
Evento::updateBilhetesComprados() {
    this->bilhetesComprados++;
}

void
Evento::alocarParticipante(Aderente aderente){
    this->participantesAderentes.push_back(aderente);
}

void
Evento::alocarParticipante(Utilizador naoAderente){
    this->participantesNaoAderentes.push_back(naoAderente);
}

/*
 * OPERATOR OVERLOADS
 */

ostream&
operator <<(ostream& out, const Evento& evento){
    out << toUpper(evento.getNome())
        << "\nData: " << evento.getData()
        << "Inicio: " << evento.getHora()
        << "Duracao: " << evento.getDuracao()
        << "\nLotacao Maxima: " << evento.getLotMax()
        << "\nPreco: " << evento.getPreco()
        <<  endl << endl;

    return out;
}

bool
Evento::operator <(const Evento& evento) {
    return this->nome < evento.getNome();
}

void
Evento::operator=(const Evento& evento) {
    this->nome = evento.nome;
    this->data = evento.data;
    this->hora = evento.hora;
    this->duracao = evento.duracao;
    this->lotMax = evento.lotMax;
    this->preco = evento.preco;
    this->totalVendas = evento.getTotalVendas();
}

bool
Evento::operator==(const Evento& evento) {
    return this->nome == evento.getNome();
}


// ITEM HISTORICO EVENTOS

/*
 * CONSTRUCTORS
 */

ItemHistoricoEventos::ItemHistoricoEventos(Evento* itemEvento) {
    this->itemEvento = itemEvento;
}

ItemHistoricoEventos::ItemHistoricoEventos(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala, u_int bilhetesComprados) {
    this->itemEvento = new Evento(nome, data, hora, duracao, lotMax, preco, sala, bilhetesComprados);
}


/*
 * MEMBER FUNCTIONS
 */

string
ItemHistoricoEventos::getNome() const {
    return this->itemEvento->getNome();
}

Date
ItemHistoricoEventos::getData() const {
    return this->itemEvento->getData();
}

Time
ItemHistoricoEventos::getHora() const {
    return this->itemEvento->getHora();
}

u_int
ItemHistoricoEventos::getDuracao() const {
    return this->itemEvento->getDuracao();
}

u_int
ItemHistoricoEventos::getLotMax() const {
    return this->itemEvento->getLotMax();
}

float
ItemHistoricoEventos::getPreco() const {
    return this->itemEvento->getPreco();
}

u_int
ItemHistoricoEventos::getSala() const {
    return this->itemEvento->getSala();
}

list<Utilizador>
ItemHistoricoEventos::getParticipantes() const {
    return this->itemEvento->getParticipantes();
}

u_int
ItemHistoricoEventos::getBilhetesComprados() const {
    return this->itemEvento->getBilhetesComprados();
}

float
ItemHistoricoEventos::getTotalVendas() const {
    return this->itemEvento->getTotalVendas();
}


/*
 * OPERATOR OVERLOADS
 */

bool
ItemHistoricoEventos::operator <(const ItemHistoricoEventos& ihe) const {
    if (this->itemEvento->getBilhetesComprados() == ihe.itemEvento->getBilhetesComprados()) {
        return this->itemEvento->getSala() < ihe.itemEvento->getSala();
    } else {
        return this->itemEvento->getBilhetesComprados() < ihe.itemEvento->getBilhetesComprados();
    }
}

bool
ItemHistoricoEventos::operator ==(const ItemHistoricoEventos& ihe) const {
    return (this->itemEvento->getNome() == ihe.itemEvento->getNome() and this->itemEvento->getSala() == ihe.itemEvento->getSala());
}


// ITEM EVENTO

/*
 * CONSTRUCTORS
 */

ItemEvento::ItemEvento(Evento* evento) {
    this->evento = evento;
    this->satizfacao = 0.00;
}

ItemEvento::ItemEvento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala, u_int bilhetesComprados) {
    this->evento = new Evento(nome, data, hora, duracao, lotMax, preco, sala, bilhetesComprados);
    this->satizfacao = 0.00;
}


/*
 * MEMBER FUNCTIONS
 */

Evento*
ItemEvento::getEvento() const {
    return this->evento;
}

float
ItemEvento::getSatizfacao() const {
    return this->satizfacao;
}

vector<u_int>
ItemEvento::getTodosRatings() const {
    return this->todosRatings;
}

void
ItemEvento::setSatizfacao(const float satizfacao) {
    this->satizfacao = satizfacao;
}

void
ItemEvento::setTodosRatings(const vector<u_int> todosRatings) {
    this->todosRatings = todosRatings;
}

void
ItemEvento::adicionarRating(const u_int rating) {
    this->todosRatings.push_back(rating);
}

void
ItemEvento::updateSatizfacao(const float satizfacao) {
    this->adicionarRating(satizfacao);

    float res = 0;
    for (auto rating : this->todosRatings) {
        res += rating;
    }
    res /= this->todosRatings.size();
    this->setSatizfacao(res);
}


/*
 * OPERATOR OVERLOADS
 */

bool
ItemEvento::operator <(const ItemEvento& ie) const {
    return this->satizfacao < ie.getSatizfacao();
}


bool
ItemEvento::operator ==(const ItemEvento& ie) const {
    return (this->evento->getNome() == ie.evento->getNome() and this->evento->getSala() == ie.evento->getSala());
}

ostream&
operator <<(ostream& out, const ItemEvento& ie) {
    out << "Evento: " << ie.evento->getNome() << endl
        << "Satizfacao: " << ie.satizfacao
        <<  endl << endl;

    return out;
}


