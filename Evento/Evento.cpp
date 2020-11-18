#include "Evento.h"

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
}

Evento::Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala)
        : nome(nome){

    this->data = data;
    this->hora = hora;
    this->duracao = duracao;
    this->lotMax = lotMax;
    this->preco = preco;
    this->sala = sala;
    this->totalVendas = 0;
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
    return this->participantesAderentes.size() + this->participantesNaoAderentes.size();
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













