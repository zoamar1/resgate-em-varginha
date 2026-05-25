#pragma once
#include "Header.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "entidades/Entidade.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        class Plataforma : public Entidade
        {

        public:
            Plataforma(int posicaoX = 0, int posicaoY = 0, int largura = 0, int altura = 0);
            sf::FloatRect getLimites() const;
            void desenhar();
            void executar() override;
            void salvar() override;

        };
    }
}