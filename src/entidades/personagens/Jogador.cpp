#include "personagens/Jogador.hpp"
#include "entidades/Projetil.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Jogador::Jogador(int n, int p, float tInvencivel, bool inv)
            : Personagem(0, 0, 40.0f, 40.0f, n),
              pontos(p),
              direcao(1),
              tempoInvencivel(tInvencivel),
              invencivel(inv)
        {
            cooldownTiros = 0.5f;
            setVel_Max(4);
            aplicarTextura(Gerenciadores::Jogador);
        }

        Jogador::~Jogador()
        {
        }

        void Jogador::executar()
        {
            mover();
            atualizarInvencibilidade();
        }

        void Jogador::salvar()
        {
        }

        void Jogador::mover()
        {
            aplicarGravidade();

            sf::Vector2f deslocamento = getVelocidade();

            if (deslocamento.x != 0.0f || deslocamento.y != 0.0f)
            {
                setPosicao(getPosicao() + deslocamento);
            }
        }

        void Jogador::atirar(Entidades::Projetil *pProjetil)
        {
            if (!pProjetil || relogioTiro.getElapsedTime().asSeconds() < cooldownTiros)
                return;

            sf::Vector2f tamJog = getpFig()->getSize();
            float offsetX = (direcao > 0) ? tamJog.x + 5.0f : -(tamJog.x + 5.0f);

            sf::Vector2f pos = getPosicao();
            pProjetil->setPosicao(sf::Vector2f(pos.x + offsetX, pos.y + (tamJog.y / 2.0f) - 10.0f));

            pProjetil->setVelocidade(sf::Vector2f(30.0f * static_cast<float>(direcao), 0.0f));
            pProjetil->setDeJogador(true);
            pProjetil->setAtivo(true);

            Gerenciadores::Gerenciador_Colisoes *pGC = Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes();
            if (pGC)
            {
                pGC->incluirProjetil(pProjetil);                
                pGC->registrarProjetilJogador(pProjetil, this); 
            }

            relogioTiro.restart();
        }

        void Jogador::setDirecao(int num)
        {

            if (num > 0)
                direcao = 1;
            else if (num < 0)
                direcao = -1;
        }

        int Jogador::getDirecao() const
        {
            return direcao;
        }

        void Jogador::pular()
        {
            if (getNoChao())
            {
                setVelocidade(sf::Vector2f(getVelocidade().x, -18.0f));
                setNoChao(false);
            }
        }

        void Jogador::colidir(Entidades::Personagens::Inimigo *pI)
        {
            if (pI && !invencivel)
            {
                sf::Vector2f posJogador = this->getPosicao();
                sf::Vector2f posInimigo = pI->getPosicao();
                float largJogador = static_cast<float>(this->getpFig()->getSize().x);
                float largInimigo = static_cast<float>(pI->getpFig()->getSize().x);
                float direcaoX;

                if (posJogador.x > posInimigo.x)
                {
                    direcaoX = 1.0f;
                    this->setPosicao(sf::Vector2f(posInimigo.x + largInimigo + 18.0f, posJogador.y));
                }
                else
                {
                    direcaoX = -1.0f;
                    this->setPosicao(sf::Vector2f(posInimigo.x - largJogador - 18.0f, posJogador.y));
                }

                this->setVelocidade(sf::Vector2f(direcaoX * 6.0f, -5.0f));

                invencivel = true;
                clockInvencivel.restart();
            }
        }

        void Jogador::atualizarInvencibilidade()
        {
            if (invencivel && clockInvencivel.getElapsedTime().asSeconds() >= tempoInvencivel)
            {
                invencivel = false;
            }
        }

        bool Jogador::getInvencivel() const
        {
            return invencivel;
        }

    }
}