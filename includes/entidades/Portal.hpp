#pragma once
#include "Header.hpp"
#include "Entidade.hpp"
#include "Jogador.hpp"

namespace Entidades
{
    class Portal : public Entidade
    {
        private:
            sf::Color cor;
        public:
            Portal(float posX = 0, float posY = 0, sf::Color cor = sf::Color::Red);
            ~Portal();
            void executar();
            void salvar();
            void teleportar(Entidades::Personagens::Jogador* pJog);
    };
}