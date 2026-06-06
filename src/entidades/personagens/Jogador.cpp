#include "personagens/Jogador.hpp"
#include "entidades/Projetil.hpp"

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
            if (!pProjetil)
                return;

            sf::Vector2f tamJog = getpFig()->getSize();

            float offsetX = (direcao > 0) ? tamJog.x + 5.0f : -(40.0f + 5.0f);

            float posXProjetil = getX() + offsetX;
            float posYProjetil = getY() + (tamJog.y / 2.0f) - 10.0f;

            pProjetil->setPosicao(sf::Vector2f(posXProjetil, posYProjetil));

            float velX = 30.0f * static_cast<float>(direcao);
            pProjetil->setVelocidade(sf::Vector2f(velX, -6.7f));

            pProjetil->setDono(this);
            pProjetil->setAtivo(true);
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
                setVelY(-18.0f);
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