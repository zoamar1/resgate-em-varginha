#pragma once
#include "Header.hpp"
#include "Gerenciador_Grafico.hpp"

namespace Gerenciadores 
{
    class Gerenciador_Eventos
    {
        private:
            static Gerenciador_Eventos* pEvento;
            Gerenciador_Grafico* pGG;
        public:
            Gerenciador_Eventos();
            ~Gerenciador_Eventos();
            static Gerenciador_Eventos* getGerenciador_Eventos();
            void setGerenciador_Grafico(Gerenciador_Grafico* pGG);
            void executar();
            void verificaTeclaPressionada(sf::Event &evento);
    };
};