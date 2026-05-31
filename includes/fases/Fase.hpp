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

    public:
        Fase(Gerenciadores::Gerenciador_Colisoes *pGC);
        virtual ~Fase();
        virtual void executar();
        void incluirJogador(Entidades::Personagens::Jogador *pJog1);

    protected:
        void criarChao();
        void criarInimFaceis();
        void criarPlataformas(const sf::Vector2f pos, const sf::Vector2f tam);
        void criarCenario();
        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;
    };

}