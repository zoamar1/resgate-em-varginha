#include "entidades/Chao.hpp"

namespace Entidades
{
    Chao::Chao() : Entidade(LARGURA/2,ALTURA-10,LARGURA,20)
    {
        pFig->setFillColor(sf::Color::White);
    }
    
    Chao::~Chao()
    {
    }

    void Chao::executar()
    {
        desenhar();
    }
    void Chao::salvar()
    {

    }
}