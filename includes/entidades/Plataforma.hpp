#pragma once
#include "Header.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"

class Plataforma
{
private:
    sf::RectangleShape retangulo;

public:
    Plataforma(int posicaoX = 0, int posicaoY = 0, int largura = 0, int altura = 0);
    sf::FloatRect getLimites() const;
    void desenhar();
};