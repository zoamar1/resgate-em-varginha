#pragma once
#include "Header.hpp"

namespace Gerenciadores
{
    class Gerenciador_Grafico
    {
        private:
            static Gerenciador_Grafico* pGrafico;
            sf::RenderWindow window;
        private:
            Gerenciador_Grafico();
        public:
            static Gerenciador_Grafico* getGerenciador_Grafico();
            bool janelaAberta();
            sf::RenderWindow* getWindow();
            void fecharJanela();
    };
};