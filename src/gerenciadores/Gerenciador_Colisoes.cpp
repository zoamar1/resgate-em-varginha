#include "gerenciadores/Gerenciador_Colisoes.hpp"

namespace Gerenciadores
{

    Gerenciador_Colisoes::Gerenciador_Colisoes()
    {
    }

    Gerenciador_Colisoes::~Gerenciador_Colisoes()
    {
    }

    void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo *pi)
    {
    }

    /* void Gerenciador_Colisoes::incluirObstaculo(Obstaculo *po)
    {
    } */

    void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil *pj)
    {
    }

    const bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade *pe1, Entidades::Entidade *pe2) const
    {
        return false;
    }

    void Gerenciador_Colisoes::tratarColisoesJogsObstacs()
    {
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
    {
    }

    void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
    {
    }

    void Gerenciador_Colisoes::executar()
    {
    }

}