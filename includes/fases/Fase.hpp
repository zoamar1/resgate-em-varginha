#pragma once
#include "Header.hpp"
#include "entidades/Ente.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "listas/ListaEntidades.hpp"
#include "entidades/Chao.hpp"

namespace Fases
{

    class Fase : public Ente
    {

    protected:
        Listas::ListaEntidades lista_ents;
        Gerenciadores::Gerenciador_Colisoes *GC;
        Entidades::Chao *pChao;
        std::vector<Entidades::Chao *> vChaos;
        std::vector<sf::RectangleShape*> barra_de_vida;
    public:
        Fase(Gerenciadores::Gerenciador_Colisoes *pGC);
        virtual ~Fase();
        virtual void executar();
        void incluirJogador(Entidades::Personagens::Jogador *pJog1, sf::Vector2f pos);
        void incluirProjetil(Entidades::Projetil *pProjetil);

    protected:
        void criarChao();
        void criarInimFaceis(sf::Vector2f pos);
        void criarPlataformas(const sf::Vector2f pos, const sf::Vector2f tam);
        void criarCenario();
        void desenharBarraDeVida(int vida_atual);
        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;
    };

}