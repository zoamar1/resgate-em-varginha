#pragma once
#include "Header.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "fases/FasePrimeira.hpp"
#include "fases/FaseSegunda.hpp"
#include "Menu.hpp"
#include "Armazenamento/Ranking.hpp"
#include "Armazenamento/Salvamento.hpp"

class Jogo
{
public:
    enum Estados
    {
        MENU,
        SUB_SELECAO_MODO,
        SUB_CONTINUAR_JOGO,
        SUB_SELECAO_FASE,
        CADASTRO_J1,
        CADASTRO_J1_2P,
        CADASTRO_J2,
        RANKING_TELA,
        FASE1,
        FASE2,
        PAUSADO
    };

private:
    Gerenciadores::Gerenciador_Grafico *pGG;
    Gerenciadores::Gerenciador_Eventos *pGE;
    Gerenciadores::Gerenciador_Colisoes *pGC;

    Estados estado;
    Estados faseAoPausar;
    Menu *pMenu;
    bool modo2Jogadores;

    Entidades::Personagens::Jogador *pJog1;
    Entidades::Personagens::Jogador *pJog2;

    Fases::FasePrimeira *pFase1;
    Fases::FaseSegunda *pFase2;

    sf::Font fontePlacar;
    bool fontePlacarCarregada;

public:
    Jogo();
    ~Jogo();

    void iniciarFase1(const std::vector<std::string> &dadosCenario = std::vector<std::string>());
    void iniciarFase2(const std::vector<std::string> &dadosCenario = std::vector<std::string>());
    void executar();
    void salvarRanking();
    void desenharPlacar();

    void salvarProgresso();
    void carregarSalvamento(const std::string &chave);
    void desenharMenuPausa();

    Estados getEstado();
    void setEstado(Estados valor);
    bool getModo2Jogadores() const;
    Ente *getCenarioAtual();

    bool temJogadoresCriados() const;
    std::string getNomeJogador1() const;
    std::string getNomeJogador2() const;
    Entidades::Personagens::Jogador *getJogador2() const;

    Menu* getMenu() const;
    void setModo2Jogadores(bool modo);
    void limparJogadores();
    void configurarJogador1(const std::string& nome);
    void configurarJogador2(const std::string& nome);
    void deletarFases();
    void pausarJogo();
    void despausarJogo();
};