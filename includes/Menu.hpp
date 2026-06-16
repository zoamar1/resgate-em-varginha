#pragma once
#include "Header.hpp"
#include "Ente.hpp"
#include <vector>
#include <string>

class Jogo;

enum class TelaMenu
{
    PRINCIPAL,
    SELECAO_MODO,
    CONTINUAR_JOGO,
    SELECAO_FASE,
    RANKING,
    CADASTRO_NOME
};

class Menu : public Ente
{
private:
    Jogo *pJogo;
    TelaMenu telaAtual;
    int indice_cadastro;
    std::string buffer_nome;

    sf::Font fonte_padrao;
    sf::Text titulo;
    sf::Text opcao_1jog;
    sf::Text opcao_2jog;
    sf::Text opcao_ranking;
    sf::Text opcao_sair;
    sf::Text texto_prompt;
    sf::Text texto_input;

    std::vector<sf::Text> textos_ranking;

public:
    Menu();
    ~Menu();

    void formataTexto(sf::Text &texto, const std::string &frase, int tamanho, float posY, sf::Color cor = sf::Color::White);
    void iniciarCadastro(int indice);
    void processarEventoTexto(sf::Uint32 unicode);
    void apagarUltimoChar();
    void confirmarNome();
    const std::string &getNomeDigitado() const;
    void atualizaRanking();
    void setJogo(Jogo *pJ);

    void desenhaTextoPrincipal();
    void desenhaSelecaoModo();
    void desenhaContinuarJogo();
    void desenhaSelecaoFase();
    void desenhaRanking();
    void desenhaCadastro();
    void desenhaTexto();

    void executar();
    void setTela(TelaMenu t);
    TelaMenu getTela() const;
};