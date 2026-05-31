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
        if (pe1 && pe2 && pe1->getpFig() && pe2->getpFig())
        {
            sf::Vector2f pos1 = pe1->getPosicao();
            float larg1 = static_cast<float>(pe1->getpFig()->getSize().x);
            float alt1 = static_cast<float>(pe1->getpFig()->getSize().y);

            sf::Vector2f pos2 = pe2->getPosicao();
            float larg2 = static_cast<float>(pe2->getpFig()->getSize().x);
            float alt2 = static_cast<float>(pe2->getpFig()->getSize().y);

            if (pos1.x < pos2.x + larg2 &&
                pos1.x + larg1 > pos2.x &&
                pos1.y < pos2.y + alt2 &&
                pos1.y + alt1 > pos2.y)
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
                if (pObstaculo && verificarColisao(pJog1, pObstaculo))
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
            std::vector<Entidades::Personagens::Inimigo *>::iterator it;

            for (auto it = LIs.begin(); it != LIs.end(); it++)
            {
                Entidades::Personagens::Inimigo *pInimigo = *it;

                if (pInimigo && verificarColisao(pJog1, pInimigo))
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
                if (pProjetil && pProjetil->getAtivo() && verificarColisao(pJog1, pProjetil))
                {
                    pJog1->recebeDano(pProjetil->getDano());
                }
            }
        }
    }

    void Gerenciador_Colisoes::colisaoJogadorChao(Entidades::Chao *pChao)
    {
        if (pChao)
        {
            if (verificarColisao(pJog1, pChao))
            {
                float pAlt = static_cast<float>(pJog1->getpFig()->getSize().y);
                sf::Vector2f posJog = pJog1->getPosicao();
                sf::Vector2f velJog = pJog1->getVelocidade();

                float chaoY = pChao->getPosicao().y;

                pJog1->setPosicao(sf::Vector2f(posJog.x, chaoY - pAlt));
                velJog.y = 0.0f;
                pJog1->setVelocidade(velJog);
                pJog1->setNoChao(true);
            } else
            {
                pJog1->setNoChao(false);
            }
        }
    }

    void Gerenciador_Colisoes::colisaoInimigoChao(Entidades::Chao *pChao)
    {
        if (pChao)
        {
            std::vector<Entidades::Personagens::Inimigo *>::iterator it;

            for (auto it = LIs.begin(); it != LIs.end(); it++)
            {
                Entidades::Personagens::Inimigo *pInimigo = *it;

                if (pInimigo)
                {
                    if (verificarColisao(pInimigo, pChao))
                    {
                        float pAlt = static_cast<float>(pInimigo->getpFig()->getSize().y);
                        sf::Vector2f posInimigo = pInimigo->getPosicao();
                        sf::Vector2f velInimigo = pInimigo->getVelocidade();

                        float chaoY = pChao->getPosicao().y;

                        pInimigo->setPosicao(sf::Vector2f(posInimigo.x, chaoY - pAlt));
                        velInimigo.y = 0.0f;
                        pInimigo->setVelocidade(velInimigo);
                    }
                }
            }
        }
    }

    Entidades::Personagens::Jogador *Gerenciador_Colisoes::getJogador1() const
    {
        return pJog1;
    }

    void Gerenciador_Colisoes::executar()
    {
        tratarColisoesJogsInimgs();
        tratarColisoesJogsObstacs();
        tratarColisoesJogsProjeteis();
    }

}