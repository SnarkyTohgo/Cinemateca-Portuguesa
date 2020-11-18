#include "Cinemateca.h"

// Globlas
ifstream salasDB;
ifstream eventosDB;
ifstream aderentesDB;
ifstream naoAderentesDB;

vector<string> salasData;
vector<string> eventosData;
vector<string> aderentesData;
vector<string> naoAderentesData;

/*
 * CONSTRUCTORS
 */

auto now = Clock::now();
std::time_t now_c = Clock::to_time_t(now);
struct tm *parts = std::localtime(&now_c);

u_int Cinemateca::anoAtual = 1900 + parts->tm_year;

Cinemateca::Cinemateca(string localizacao, string morada)
    : localizacao(localizacao), morada(morada){

    this->parseEventos();
    this->parseSalas();
    this->parseAderentes();
    this->parseNaoAderentes();

    this->bilhetesComprados = 0;
    this->totalVendas = 0;

    for (auto evento : this->eventos)
        this->alocarSala(&evento);
}


/*
 * MEMBER FUNCTIONS
 */

// GETTERS
u_int
Cinemateca::getAnoAtual() const {
    return this->anoAtual;
}


string
Cinemateca::getLocalizacao() const {
    return this->localizacao;
}

string
Cinemateca::getMorada() const {
    return this->morada;
}

list<Aderente>
Cinemateca::getAderentes() const {
    return this->aderentes;
}

list<Utilizador>
Cinemateca::getNaoAderentes() const {
    return this->naoAderentes;
}

list<Sala>
Cinemateca::getSalas() const {
    return this->salas;
}

Evento
Cinemateca::getEvento(int pos) const {

    int idx = 0;
    for (auto evento : this->eventos){
        if (idx == pos) return evento;
        idx++;
    }

    return Evento();
}

u_int
Cinemateca::getBilhetesComprados() const {
    return this->bilhetesComprados;
}

double
Cinemateca::getTotalVendas() const {
    return this->totalVendas;
}

// SETTERS

void
Cinemateca::setSalas(list<Sala> salas){
    this->salas = salas;
}

void
Cinemateca::setEventos(list<Evento> eventos){
    this->eventos = eventos;
}

void
Cinemateca::setAderentes(list<Aderente> aderentes){
    this->aderentes = aderentes;
}

void
Cinemateca::setNaoAderentes(list<Utilizador> naoAderentes){
    this->naoAderentes = naoAderentes;
}

// OTHER

void
Cinemateca::registarAderente(string nome, u_int nif, Date dataNasc, u_int anoAtual) {
    Aderente novoAderente(nome, nif, dataNasc, anoAtual);

    this->aderentes.push_back(novoAderente);
    this->updateAderentes(novoAderente);

    cout << "\n>>>Novo aderente dos Amigos da Cinematega registado com successo!<<<\n"
         << novoAderente;
}

void
Cinemateca::registarUtilizadorNaoAderente(u_int nif) {
    Utilizador novoUtilizador(nif);

    for (auto utilizador : this->naoAderentes){
        if (nif == utilizador.getNif())
            return;
    }

    this->naoAderentes.push_back(novoUtilizador);
    this->updateNaoAderentes(novoUtilizador);

    cout << "\n>>>Novo utilizador registado com successo!<<<\n"
         << novoUtilizador;
}

void
Cinemateca::adicionarEvento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco){

    Evento novoEvento(nome, data, hora, duracao, lotMax, preco);
    this->eventos.push_back(novoEvento);

    Evento* eventoPtr = &novoEvento;
    this->alocarSala(eventoPtr);

    // Write to file
    this->updateEventos(novoEvento);

    cout << "\n>>>Novo evento adicionado com sucesso!<<<\n"
         << novoEvento;
}

void
Cinemateca::alocarSala(Evento* evento){

    this->ordenarSalasCapacidade();

    for (auto sala : this->salas){

        if (sala.getCapacidade() >= evento->getLotMax()){
            bool salaDisponivel = sala.checkDisponibilidade(*evento);

            if (salaDisponivel){
                evento->setSala((u_int) stoi(sala.getNome()));
                break;
            }
        }
    }
}

int
Cinemateca::comprarBilhete(Aderente aderente, list<Evento>::iterator evento){

    if (evento->isLotado()){
        cout << "Evento " << toUpper(evento->getNome()) << " já se encontra lotado\n";

        return EXIT_FAILURE;
    }

    float valorComDesconto = evento->getPreco() - (evento->getPreco() * (this->anoAtual - aderente.getAnoAdesao()) * 0.01);

    evento->alocarParticipante(aderente);
    evento->updateTotalVendas(valorComDesconto);

    this->updateBilhetesComprados();
    this->updateTotalVendas(valorComDesconto);

    cout << "\nBilhete comprado com sucesso!\n"
         << "\nEvento: " << toUpper(evento->getNome())
         << "\nTitular: " << aderente.getNome()
         << "\nNIF: " << aderente.getNif()
         << "\nPvP: " << valorComDesconto
         << endl;

    return EXIT_SUCCESS;
}

int
Cinemateca::comprarBilhete(Utilizador utilizador, list<Evento>::iterator evento){

    if (evento->isLotado()){
        cout << "Evento " << toUpper(evento->getNome()) << " já se encontra lotado\n";

        return EXIT_FAILURE;
    }

    evento->alocarParticipante(utilizador);
    evento->updateTotalVendas(evento->getPreco());

    this->updateBilhetesComprados();
    this->updateTotalVendas(evento->getPreco());

    cout << "\nBilhete comprado com sucesso!\n"
         << "\nEvento: " << toUpper(evento->getNome())
         << "\nNIF: " << utilizador.getNif()
         << "\nPvP: " << evento->getPreco()
         << endl;

    return EXIT_SUCCESS;
}

// PARSING

void
Cinemateca::parseSalas(){
    salasDB = readFile("../salas.dat");
    salasData = parseFile(salasDB);

    list<Sala> parsedSalas;

    for (auto tuple : salasData){
        vector<string> data = split(tuple, ';');

        string nome = data[0];
        u_int capacidade = (u_int) stoi(data[1]);

        Sala novaSala(nome, capacidade);

        for (auto tuple : eventosData){
            vector<string> data = split(tuple, ';');

            if (stoi(data[6]) == stoi(nome)){
                string nome = data[0];
                u_int duracao = (u_int) stoi(data[3]);
                u_int lotMax = (u_int) stoi(data[4]);
                // float preco = stof(data[5]);
                float preco = 12.99;

                // parse date
                vector<string> dataEventoStr = split(data[1], '/');

                u_int d = (u_int) stoi(dataEventoStr[0]);
                u_int m = (u_int) stoi(dataEventoStr[1]);
                u_int a = (u_int) stoi(dataEventoStr[2]);

                Date dataEvento(d, m, a);

                // parse time
                vector<string> horaStr = split(data[2], ':');

                u_int h = (u_int) stoi(horaStr[0]);
                u_int min = (u_int) stoi(horaStr[1]);
                u_int s = (u_int) stoi(horaStr[2]);

                Time hora(h, min, s);

                Evento novoEvento(nome, dataEvento, hora, duracao, lotMax, preco);
                novaSala.adicionarEvento(novoEvento);
            }
        }

        parsedSalas.push_back(novaSala);
    }

    this->setSalas(parsedSalas);
}

void
Cinemateca::parseEventos(){
    eventosDB = readFile("../eventos.dat");
    eventosData = parseFile(eventosDB);

    list<Evento> parsedEventos;

    for (auto tuple : eventosData){
        vector<string> data = split(tuple, ';');

        string nome = data[0];
        u_int duracao = (u_int) stoi(data[3]);
        u_int lotMax = (u_int) stoi(data[4]);
        u_int sala = (u_int) stoi(data[6]);
        // float preco = stof(data[5]);
        float preco = 12.99;

        // parse date
        vector<string> dataEventoStr = split(data[1], '/');

        u_int dia = (u_int) stoi(dataEventoStr[0]);
        u_int mes = (u_int) stoi(dataEventoStr[1]);
        u_int ano = (u_int) stoi(dataEventoStr[2]);

        Date dataEvento(dia, mes, ano);

        // parse time
        vector<string> horaStr = split(data[2], ':');

        u_int h = (u_int) stoi(horaStr[0]);
        u_int m = (u_int) stoi(horaStr[1]);
        u_int s = (u_int) stoi(horaStr[2]);

        Time hora(h, m, s);

        Evento novoEvento(nome, dataEvento, hora, duracao, lotMax, preco, sala);
        parsedEventos.push_back(novoEvento);
    }

    this->setEventos(parsedEventos);
}

void
Cinemateca::parseAderentes(){
    aderentesDB = readFile("../aderentes.dat");
    aderentesData = parseFile(aderentesDB);

    list<Aderente> parsedAderentes;

    for (auto tuple : aderentesData){
        vector<string> data = split(tuple, ';');

        string nome = data[0];
        u_int nif = (u_int) stoi(data[1]);
        u_int anoAdesao = (u_int) stoi(data[3]);

        // parse date
        vector<string> dataNascStr = split(data[2], '/');

        u_int d = (u_int) stoi(dataNascStr[0]);
        u_int m = (u_int) stoi(dataNascStr[1]);
        u_int a = (u_int) stoi(dataNascStr[2]);

        Date dataNasc(d, m, a);

        Aderente novoAderente(nome, nif, dataNasc, anoAdesao);
        parsedAderentes.push_back(novoAderente);
    }

    this->setAderentes(parsedAderentes);
}

void
Cinemateca::parseNaoAderentes(){
    naoAderentesDB = readFile("../nao_aderentes.dat");
    naoAderentesData = parseFile(naoAderentesDB);

    list<Utilizador> parsedNaoAderentes;

    for (auto tuple : naoAderentesData){
        vector<string> data = split(tuple, ';');

        u_int nif = (u_int) stoi(data[0]);

        Utilizador novoUtilizador(nif);
        parsedNaoAderentes.push_back(novoUtilizador);
    }

    this->setNaoAderentes(parsedNaoAderentes);
}

// UPDATE

void
Cinemateca::updateAderentes(Aderente aderente) const {
    string data = "";

    data += aderente.getNome() + "; " + to_string(aderente.getNif()) + "; "
         + to_string(aderente.getDataNasc().getD()) + "/" + to_string(aderente.getDataNasc().getM()) + "/" + to_string(aderente.getDataNasc().getA()) + "; "
         + to_string(aderente.getAnoAdesao());

    writeData(data, "../aderentes.dat");
}

void
Cinemateca::updateNaoAderentes(Utilizador naoAderente) const {
    string data = "";

    data += to_string(naoAderente.getNif());

    writeData(data, "../nao_aderentes.dat");
}

void
Cinemateca::updateEventos(Evento evento) const {
    string data = "";

    data += evento.getNome() + "; "
         + to_string(evento.getData().getD()) + "/" + to_string(evento.getData().getM()) + "/" + to_string(evento.getData().getA()) + "; "
         + to_string(evento.getHora().getH()) + ":" + to_string(evento.getHora().getM()) + ":" + to_string(evento.getHora().getS()) + "; "
         + to_string(evento.getDuracao()) + "; " + to_string(evento.getLotMax()) + "; " + to_string(evento.getPreco()) + "; " + to_string(evento.getSala());


    writeData(data, "../eventos.dat");
}

void
Cinemateca::updateBilhetesComprados(){
    this->bilhetesComprados++;
}

void
Cinemateca::updateTotalVendas(const float valor){
    this->totalVendas += (double) valor;
}

// ORDENAR SALAS

void
Cinemateca::ordenarSalasNome(){
    this->salas.sort();
}

void
Cinemateca::ordenarSalasCapacidade(){
    this->salas.sort([](const Sala& s1, const Sala& s2){
        return s1.getCapacidade() < s2.getCapacidade();
    });
}

// ORDENAR EVENTOS

void
Cinemateca::ordenarEventosNome(){
    this->eventos.sort();
}

void
Cinemateca::ordenarEventosData(){
    this->eventos.sort([](const Evento& e1, const Evento& e2){
        return e1.getData() < e2.getData();
    });
}

void
Cinemateca::ordenarEventosPreco(){
    this->eventos.sort([](const Evento& e1, const Evento& e2){
        return e1.getPreco() < e2.getPreco() ;
    });
}

void
Cinemateca::ordenarEventosLotMax(){
    this->eventos.sort([](const Evento& e1, const Evento& e2){
        return e1.getLotMax() < e2.getLotMax() ;
    });
}

// ORDENAR ADERENTES

void
Cinemateca::ordenarAderentesNome(){
    this->aderentes.sort();
}

void
Cinemateca::ordenarAderentesDataNasc(){
    this->aderentes.sort([](const Aderente& a1, const Aderente& a2){
        return a1.getDataNasc() < a2.getDataNasc() ;
    });
}

void
Cinemateca::ordenarAderentesAnoAdesao(){
    this->aderentes.sort([](const Aderente& a1, const Aderente& a2){
        return a1.getAnoAdesao() < a2.getAnoAdesao() ;
    });
}






