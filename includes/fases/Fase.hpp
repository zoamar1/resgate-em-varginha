#pragma once
#include "Header.hpp"
#include "entidades/Ente.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "listas/ListaEntidades.hpp"
#include "entidades/Chao.hpp"
#include "entidades/Projetil.hpp"

namespace Fases
{
    class Fase : public Ente
    {
    protected:
        Listas::ListaEntidades lista_ents;
        Gerenciadores::Gerenciador_Colisoes *GC;
        std::vector<sf::RectangleShape *> barra_de_vida;
        std::vector<sf::Vector2f> posicoesPlataformas;
        std::vector<sf::Vector2f> posicoesInimigosFaceis;
        std::vector<Entidades::Projetil *> ProjeteisPossiveis;
        std::vector<std::pair<Entidades::Projetil *, int>> projeteisPendentesDono;
        bool faseConcluida;

    public:
        Fase(Gerenciadores::Gerenciador_Colisoes *pGC);
        virtual ~Fase();
        virtual void executar();
        void incluirJogador(Entidades::Personagens::Jogador *pJogador, sf::Vector2f pos);
        void incluirProjetil(Entidades::Projetil *pProjetil);
        Entidades::Projetil *getProjetilDisponivel();

        bool getFaseConcluida() const;
        void setFaseConcluida(bool c);

        void desenharCena();
        std::vector<std::string> coletarDadosSalvamento();
        void carregarCenario(const std::vector<std::string> &dadosCenario);
        virtual void carregarInimigoEspecial(const std::string &dadoJson) = 0;
        void vincularDonosProjeteis(Entidades::Personagens::Jogador *pJog1, Entidades::Personagens::Jogador *pJog2);

    private:
        void dividirChao(sf::Vector2f pos, sf::Vector2f tam);
        void dividirPlataforma(sf::Vector2f pos, sf::Vector2f tam);

    protected:
        void criarChao();
        void criarInimFaceis();
        void criarPlataformas();
        void criarCenario();
        void criarPortal(float posX, float posY);
        void desenharBarraDeVida(Entidades::Personagens::Jogador *pJog, int indiceJogador);
        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;
        virtual void criarProjeteis() = 0;
        virtual void relacionarProjetilAlien(Entidades::Projetil *pProj, int idAlienSalvo);
    };
}