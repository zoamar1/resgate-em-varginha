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

    void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo *pI)
    {
        if (pI)
        {
            LIs.push_back(pI);
        }
    }

    void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo *pO)
    {
        if (pO)
        {
            LOs.push_back(pO);
        }
    }

    void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil *pP)
    {
        if (pP)
        {
            LPs.insert(pP);
        }
    }

    // falta verificar
    const bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade *pe1, Entidades::Entidade *pe2) const
    {
        if (pe1 && pe2)
        {
            if (pe1->getX() == pe2->getX())
            {
                return true;
            }
            if (pe1->getY() == pe2->getY())
            {
                return true;
            }
        }
        return false;
    }

    void Gerenciador_Colisoes::tratarColisoesJogsObstacs()
    {
        if (pJog1)
        {
            std::list<Entidades::Obstaculos::Obstaculo *>::iterator it;

            for (it = LOs.begin(); it != LOs.end(); it++)
            {
                Entidades::Obstaculos::Obstaculo *pObstaculo = *it;
                if (verificarColisao(pJog1, pObstaculo))
                {
                    pObstaculo->obstaculizar(pJog1);
                    // falta corrigir posicao
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
    {
        if (pJog1)
        {
            std::vector<Entidades::Personagens::Personagem *>::iterator it;

            for (it = LOs.begin(); it != LOs.end(); it++)
            {
                Entidades::Personagens::Inimigo *pInimigo = *it;
                if (verificarColisao(pJog1, pInimigo))
                {
                    pInimigo->danificar(pJog1); // verificar se faz sentido
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
    {
    }

    void Gerenciador_Colisoes::executar()
    {
        tratarColisoesJogsInimgs();
        tratarColisoesJogsObstacs();
        tratarColisoesJogsProjeteis();
    }

}