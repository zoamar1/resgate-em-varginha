#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "entidades/Portal.hpp"

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

    void Gerenciador_Colisoes::incluirJogador(Entidades::Personagens::Jogador *pJ)
    {
        if (pJ)
        {
            LJs.push_back(pJ);
        }
    }

    void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo *pI)
    {
        if (pI)
        {
            LIs.push_back(pI);
        }
    }

    void Gerenciador_Colisoes::removerInimigo(Entidades::Personagens::Inimigo *pI)
    {
        if (!pI)
            return;
        for (int i = 0; i < (int)LIs.size(); i++)
        {
            if (LIs[i] == pI)
            {
                LIs.erase(LIs.begin() + i);
                return;
            }
        }
    }

    void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo *pO)
    {
        if (pO)
        {
            LOs.push_back(pO);
        }
    }

    void Gerenciador_Colisoes::incluirChao(Entidades::Chao *pC)
    {
        if (pC)
        {
            LCs.push_back(pC);
        }
    }

    void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil *pP)
    {
        if (pP)
        {
            LPs.insert(pP);
        }
    }

    void Gerenciador_Colisoes::incluirPortal(Entidades::Portal *pPortal)
    {
        if (pPortal)
        {
            LPo.push_back(pPortal);
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
        for (size_t i = 0; i < LJs.size(); i++)
        {
            Entidades::Personagens::Jogador *pJog = LJs[i];
            if (pJog)
            {
                for (std::list<Entidades::Obstaculos::Obstaculo *>::iterator it = LOs.begin(); it != LOs.end(); ++it)
                {
                    Entidades::Obstaculos::Obstaculo *pObstaculo = *it;
                    if (pObstaculo && verificarColisao(pJog, pObstaculo))
                    {
                        pObstaculo->obstaculizar(pJog);
                    }
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs()
    {
        for (size_t i = 0; i < LJs.size(); i++)
        {
            Entidades::Personagens::Jogador *pJog = LJs[i];
            if (pJog)
            {
                for (size_t j = 0; j < LIs.size(); j++)
                {
                    Entidades::Personagens::Inimigo *pInimigo = LIs[j];
                    if (pInimigo && verificarColisao(pJog, pInimigo))
                    {
                        if (!pJog->getInvencivel())
                        {
                            pInimigo->danificar(pJog);
                            pJog->colidir(pInimigo);
                        }
                    }
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesInimProjeteis()
    {
        for (std::set<Entidades::Projetil *>::iterator itProj = LPs.begin(); itProj != LPs.end(); ++itProj)
        {
            Entidades::Projetil *pProjetil = *itProj;
            if (pProjetil && pProjetil->getAtivo())
            {
                if (pProjetil->getDeJogador())
                {
                    for (size_t i = 0; i < LIs.size(); i++)
                    {
                        Entidades::Personagens::Inimigo *pInimigo = LIs[i];
                        if (pInimigo && verificarColisao(pInimigo, pProjetil))
                        {
                            pInimigo->recebeDano(pProjetil->getDano());

                            pProjetil->setAtivo(false);
                            pProjetil->setPosicao(sf::Vector2f(-500.0f, -500.0f));
                            pProjetil->setVelocidade(sf::Vector2f(0.0f, 0.0f));
                            break;
                        }
                    }
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
    {
        for (size_t i = 0; i < LJs.size(); i++)
        {
            Entidades::Personagens::Jogador *pJog = LJs[i];
            if (pJog)
            {
                for (std::set<Entidades::Projetil *>::iterator itProj = LPs.begin(); itProj != LPs.end(); ++itProj)
                {
                    Entidades::Projetil *pProjetil = *itProj;
                    if (pProjetil && pProjetil->getAtivo() && !pProjetil->getDeJogador() && verificarColisao(pJog, pProjetil))
                    {
                        pJog->recebeDano(pProjetil->getDano());
                    }
                }
            }
        }
    }

    void Gerenciador_Colisoes::colisaoJogadorChao(Entidades::Chao *pChao)
    {
        if (!pChao)
            return;

        for (size_t i = 0; i < LJs.size(); i++)
        {
            Entidades::Personagens::Jogador *pJog = LJs[i];
            if (pJog && verificarColisao(pJog, pChao))
            {
                sf::Vector2f posJog = pJog->getPosicao();
                sf::Vector2f velJog = pJog->getVelocidade();
                float pAlt = static_cast<float>(pJog->getpFig()->getSize().y);

                sf::Vector2f posChao = pChao->getPosicao();
                float chaoAlt = static_cast<float>(pChao->getpFig()->getSize().y);

                float centroJogY = posJog.y + (pAlt / 2.0f);
                float centroChaoY = posChao.y + (chaoAlt / 2.0f);

                if (centroJogY < centroChaoY)
                {
                    pJog->setPosicao(sf::Vector2f(posJog.x, posChao.y - pAlt));
                    velJog.y = 0.0f;
                    pJog->setNoChao(true);
                }
                else
                {
                    pJog->setPosicao(sf::Vector2f(posJog.x, posChao.y + chaoAlt));
                    velJog.y = 0.1f;
                }

                pJog->setVelocidade(velJog);
            }
        }
    }

    void Gerenciador_Colisoes::colisaoInimigoChao(Entidades::Chao *pChao)
    {
        if (!pChao)
            return;

        for (size_t i = 0; i < LIs.size(); i++)
        {
            Entidades::Personagens::Inimigo *pInimigo = LIs[i];
            if (pInimigo && verificarColisao(pInimigo, pChao))
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

    const std::vector<Entidades::Personagens::Jogador *> &Gerenciador_Colisoes::getJogadores() const
    {
        return LJs;
    }

    const std::vector<Entidades::Personagens::Inimigo *> &Gerenciador_Colisoes::getInimigos() const
    {
        return LIs;
    }

    void Gerenciador_Colisoes::executar()
    {
        tratarColisoesJogsInimgs();
        tratarColisoesJogsObstacs();
        tratarColisoesJogsProjeteis();
        tratarColisoesInimProjeteis();
        tratarColisoesJogsPortal();

        if (!LCs.empty())
        {
            for (size_t i = 0; i < LCs.size(); i++)
            {
                Entidades::Chao *pChao = LCs[i];
                if (pChao)
                {
                    colisaoJogadorChao(pChao);
                    colisaoInimigoChao(pChao);
                }
            }
        }
    }

    void Gerenciador_Colisoes::limparTudo()
    {
        LIs.clear();
        LOs.clear();
        LPs.clear();
        LCs.clear();
        LPo.clear();
    }

    void Gerenciador_Colisoes::tratarColisoesJogsPortal()
    {
        for (int i = 0; i < (int)LJs.size(); i++)
        {
            Entidades::Personagens::Jogador *pJog = LJs[i];
            if (pJog)
            {
                for (int j = 0; j < (int)LPo.size(); j++)
                {
                    Entidades::Portal *pPortal = LPo[j];
                    if (pPortal && verificarColisao(pJog, pPortal))
                    {
                        pPortal->teleportar(pJog);
                    }
                }
            }
        }
    }
}