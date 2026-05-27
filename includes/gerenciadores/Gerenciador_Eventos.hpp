#pragma once
#include "Header.hpp"
#include "Gerenciador_Grafico.hpp"
#include "entidades/personagens/Jogador.hpp"

class Jogo;

namespace Gerenciadores 
{
    class Gerenciador_Eventos
    {
        private:
            static Gerenciador_Eventos* pEvento;
            Gerenciador_Grafico* pGG;
            Jogo* pJogo;
            Entidades::Personagens::Jogador* pJog1;
            Gerenciador_Eventos(Jogo* pJ);
        public:
            ~Gerenciador_Eventos();
            static Gerenciador_Eventos* getGerenciador_Eventos(Jogo* pJ);
            void setGerenciador_Grafico(Gerenciador_Grafico* pGG);
            void setJogador1(Entidades::Personagens::Jogador* pJogador1);
            void executar();
            void verificaTeclaPressionada(sf::Event &evento);
    };
};