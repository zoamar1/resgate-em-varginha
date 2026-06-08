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

    public:
        Fase(Gerenciadores::Gerenciador_Colisoes *pGC);
        virtual ~Fase();
        virtual void executar();
        void incluirJogador(Entidades::Personagens::Jogador *pJog1, sf::Vector2f pos);
        void incluirProjetil(Entidades::Projetil *pProjetil);

        Entidades::Projetil *getProjetilDisponivel();

    protected:
        void criarChao();
        void criarInimFaceis();
        void criarPlataformas();
        void criarCenario();
        void desenharBarraDeVida(Entidades::Personagens::Jogador *pJog);
        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;
        virtual void criarProjeteis() = 0;
    };

}