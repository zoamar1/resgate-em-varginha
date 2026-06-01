#include "personagens/Jogador.hpp"
#include "entidades/Projetil.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Jogador::Jogador(float posX, float posY, int n, int p) : Personagem(posX, posY, 40.0f, 40.0f, n),
                                                                 pontos(p),
                                                                 direcao(1)
        {
            setVel_Max(4);
            aplicarTextura(Gerenciadores::Jogador);
        }

        Jogador::~Jogador()
        {
        }

        void Jogador::executar()
        {
            aplicarGravidade();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                pular();
            }

            mover();
        }

        void Jogador::salvar()
        {
        }

        void Jogador::mover()
        {
            sf::Vector2f deslocamento = getVelocidade();

            if (deslocamento.x != 0.0f || deslocamento.y != 0.0f)
            {
                setPosicao(getPosicao() + deslocamento);
            }
        }

        Entidades::Projetil* Jogador::atirar()
        {
            Entidades::Projetil *novoProjetil = new Entidades::Projetil(getX(), getY(), false, 5);
            return novoProjetil;
        }

        void Jogador::setDirecao(int num)
        {
            if (num < 0)
                direcao = -1;
            else
                direcao = 1;
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
            if (pI)
            {
                sf::Vector2f posJogador = this->getPosicao();
                sf::Vector2f posInimigo = pI->getPosicao();
                float largJogador = static_cast<float>(this->getpFig()->getSize().x);
                float largInimigo = static_cast<float>(pI->getpFig()->getSize().x);

                float direcaoX;

                if (posJogador.x > posInimigo.x)
                {
                    direcaoX = 1.0f;
                    this->setPosicao(sf::Vector2f(posInimigo.x + largInimigo, posJogador.y));
                }
                else
                {
                    direcaoX = -1.0f;
                    this->setPosicao(sf::Vector2f(posInimigo.x - largJogador, posJogador.y));
                }

                this->setVelocidade(sf::Vector2f(direcaoX * 4.0f, this->getVelocidade().y));
            }
        }

    }
}