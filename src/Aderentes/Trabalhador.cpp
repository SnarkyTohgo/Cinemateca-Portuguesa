#include "Trabalhador.h"

// TRABALHADOR

/*
 * CONSTRUCTORS
 */

Trabalhador::Trabalhador(string nome) {
    this->nome = nome;
    this->atual = true;

    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    Date dataContratacao(parts->tm_mday, parts->tm_mon + 1, 1900 + parts->tm_year);
    Date dataDespedimento(0, 0, 0);

    this->dataContratacao = dataContratacao;
    this->dataDespedimento = dataDespedimento;
}

Trabalhador::Trabalhador(string nome, string localizacao) {
    this->nome = nome;
    this->atual = true;
    this->localizacao = localizacao;

    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    Date dataContratacao(parts->tm_mday, parts->tm_mon + 1, 1900 + parts->tm_year);
    Date dataDespedimento(0, 0, 0);

    this->dataContratacao = dataContratacao;
    this->dataDespedimento = dataDespedimento;
}



Trabalhador::Trabalhador(string n, string l, Date dataCont, Date dataDesp, bool atual) {
    this->nome = n;
    this->localizacao = l;
    this->numContratacoes = 0;
    this->dataContratacao = dataCont;
    this->dataDespedimento = dataDesp;
    this->atual = atual;
}


/*
 * MEMBER FUNCTIONS
 */

string
Trabalhador::getNome() const {
    return this->nome;
}


string
Trabalhador::getLocalizacao() const {
    return this->localizacao;
}

bool
Trabalhador::getAtual() const {
    return this->atual;
}

void
Trabalhador::setAtual(const bool valor) {
    this->atual = valor;
}

Date
Trabalhador::getDataContatacao() const {
    return this->dataContratacao;
}

Date
Trabalhador::getDataDespedimento() const {
    return this->dataDespedimento;
}

void
Trabalhador::setDataDespedimento(Date dataDespedimento) {
    this->dataDespedimento = dataDespedimento;
}


// RegistoTrabalhador

/*
 * CONSTRUCTORS
 */
RegistoTrabalhador::RegistoTrabalhador(string trabalhador) {
    this->trabalhador = trabalhador;
    this->numContratacoes = 0;
    this->atual = true;

    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    Date dataContratacao(parts->tm_mday, parts->tm_mon + 1, 1900 + parts->tm_year);
    this->dataContratacao = dataContratacao;
}

RegistoTrabalhador::RegistoTrabalhador(string trabalhador, string localizacao) {
    this->trabalhador = trabalhador;
    this->localizacao = localizacao;
    this->numContratacoes = 0;
    this->atual = true;

    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    Date dataContratacao(parts->tm_mday, parts->tm_mon + 1, 1900 + parts->tm_year);
    this->dataContratacao = dataContratacao;
}

RegistoTrabalhador::RegistoTrabalhador(string t, string l, Date dataCont, Date dataDesp) {
    this->trabalhador = t;
    this->numContratacoes = 0;
    this->localizacao = l;
    this->dataContratacao = dataCont;
    this->dataDespedimento = dataDesp;
    this->atual = false;
}

RegistoTrabalhador::RegistoTrabalhador(string t, string l, Date dataCont, Date dataDesp, bool atual) {
    this->trabalhador = t;
    this->localizacao = l;
    this->numContratacoes = 0;
    this->dataContratacao = dataCont;
    this->dataDespedimento = dataDesp;
    this->atual = atual;
}


/*
 * MEMBER FUNCTIONS
 */

string
RegistoTrabalhador::getTrabalhador() const {
    return this->trabalhador;
}

string
RegistoTrabalhador::getLocalizacao() const {
    return this->localizacao;
}

u_int
RegistoTrabalhador::getNumContratacoes() const {
    return this->numContratacoes;
}

bool
RegistoTrabalhador::getAtual() const {
    return this->atual;
}

Date
RegistoTrabalhador::getDataContatacao() const {
    return this->dataContratacao;
}

Date
RegistoTrabalhador::getDataDespedimento() const {
    return this->dataDespedimento;
}

void
RegistoTrabalhador::setLocalizacao(const string localizacao) {
    this->localizacao = localizacao;
}

void
RegistoTrabalhador::setAtual(const bool valor) {
    this->atual = valor;
}


void
RegistoTrabalhador::setDataContratacao(Date dataContratacao) {
    this->dataContratacao = dataContratacao;
}

void
RegistoTrabalhador::setDataDespedimento(Date dataDespedimento) {
    this->dataDespedimento = dataDespedimento;
}

void
RegistoTrabalhador::incNumContratacoes() {
    this->numContratacoes++;
}

void
RegistoTrabalhador::assinarContrato() {
    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    Date dataContratacao(parts->tm_mday, parts->tm_mon + 1, 1900 + parts->tm_year);
    this->dataContratacao = dataContratacao;

    this->atual = true;

}

void
RegistoTrabalhador::resignarContrato() {
    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    Date dataDespedimento(parts->tm_mday, parts->tm_mon + 1, 1900 + parts->tm_year);
    this->dataDespedimento = dataDespedimento;

    this->atual = false;
}


/*
 * OPERATOR OVERLOADS
 */

void
RegistoTrabalhador::operator =(const RegistoTrabalhador& rt) {
    this->trabalhador = rt.trabalhador;
    this->atual = rt.atual;
    this->dataContratacao = rt.dataContratacao;
    this->dataDespedimento = rt.dataDespedimento;
}

ostream&
operator <<(ostream &out, RegistoTrabalhador &rt) {
    out << toUpper(rt.getTrabalhador())
        << "\nAtualmente contratado: " << rt.getAtual()
        << "\nData de contratacao: " << rt.getDataContatacao();

    if (!rt.getAtual()) {
        out << "Data de despedimento: " << rt.getDataDespedimento();
    }

    out << endl << endl;

    return out;
}