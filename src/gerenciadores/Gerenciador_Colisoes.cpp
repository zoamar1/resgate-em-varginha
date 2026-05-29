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

    bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade *pe1, Entidades::Entidade *pe2) const
    {
        if (pe1 && pe2)
        {
            float x1 = pe1->getX();
            float y1 = pe1->getY();
            float larg1 = static_cast<float>(pe1->getpFig()->getSize().x);
            float alt1 = static_cast<float>(pe1->getpFig()->getSize().y);

            float x2 = pe2->getX();
            float y2 = pe2->getY();
            float larg2 = static_cast<float>(pe2->getpFig()->getSize().x);
            float alt2 = static_cast<float>(pe2->getpFig()->getSize().y);

            if (x1 < x2 + larg2 &&
                x1 + larg1 > x2 &&
                y1 < y2 + alt2 &&
                y1 + alt1 > y2)
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

            for (auto it = LOs.begin(); it != LOs.end(); it++)
            {
                Entidades::Obstaculos::Obstaculo *pObstaculo = *it;
                if (verificarColisao(pJog1, pObstaculo))
                {
                    pObstaculo->obstaculizar(pJog1);
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
    {
        if (pJog1)
        {
            std::vector<Entidades::Personagens::Personagem *>::iterator it;

            for (auto it = LIs.begin(); it != LIs.end(); it++)
            {
                Entidades::Personagens::Inimigo *pInimigo = dynamic_cast<Entidades::Personagens::Inimigo *>(*it);

                if (verificarColisao(pJog1, pInimigo) && pInimigo)
                {
                    pInimigo->danificar(pJog1);
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
    {
        if (pJog1)
        {
            std::set<Entidades::Projetil *>::iterator it;

            for (auto it = LPs.begin(); it != LPs.end(); it++)
            {
                Entidades::Projetil *pProjetil = *it;
                if (verificarColisao(pJog1, pProjetil) && pProjetil->getAtivo())
                {
                    pJog1->recebeDano(pProjetil->getDano());
                }
            }
        }
    }

    void Gerenciador_Colisoes::executar()
    {
        tratarColisoesJogsInimgs();
        tratarColisoesJogsObstacs();
        tratarColisoesJogsProjeteis();
    }

}