#pragma once
#include "entidades/Entidade.hpp"
#include "Header.hpp"

namespace Entidades
{
    class Chao : public Entidade
    {
    private:
        float largura;

    public:
        Chao(sf::Vector2f pos = sf::Vector2f(0.0f, static_cast<float>(ALTURA - 90)), sf::Vector2f tam = sf::Vector2f(static_cast<float>(LARGURA), 30.0f));
        ~Chao();
        void executar();
        void salvar();

        float getLargura() const;
    };
}