#include "gerenciadores/Gerenciador_Colisoes.hpp"

namespace Gerenciadores
{
    Gerenciador_Colisoes *Gerenciador_Colisoes::pColisao = NULL;

    Gerenciador_Colisoes::Gerenciador_Colisoes()
    {
    }

    Gerenciador_Colisoes::~Gerenciador_Colisoes()
    {
    }

    Gerenciador_Colisoes *Gerenciador_Colisoes::getGerenciador_Colisoes()
    {
        if (!pColisao)
        {
            pColisao = new Gerenciador_Colisoes();
        }
        return pColisao;
    }

    void Gerenciador_Colisoes::setJogador1(Entidades::Personagens::Jogador *pJ)
    {
        pJog1 = pJ;
    }

    void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo *pi)
    {
    }

    void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo *po)
    {
        
    }

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