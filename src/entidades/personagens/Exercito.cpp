#include "personagens/Exercito.hpp"
#include "personagens/Jogador.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include <cmath>

namespace Entidades
{
    namespace Personagens
    {
        Exercito::Exercito(float posX, float posY, int n, int maldade, int r)
            : Inimigo(posX, posY, n, maldade),
              raio(r), explodindo(false)
        {
            setVel_Max(1.4f);
            setVelocidade(sf::Vector2f(1.4f, 0.0f));

            if (pFig)
            {
                pFig->setSize(sf::Vector2f(70.0f, 127.0f));
                pFig->setPosition(sf::Vector2f(posX, posY));
            }

            aplicarTextura(Gerenciadores::Exercito);
        }

        Exercito::~Exercito() {}

        void Exercito::danificar(Jogador *p)
        {
            if (explodindo)
            {
                return;
            }

            if (p)
            {
                p->recebeDano(nivel_maldade);
            }

            explodindo = true;
            relogioExplosao.restart();

            Gerenciadores::Gerenciador_Colisoes *pGC = Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes();
            sf::Vector2f posExercito = getPosicao();

            if (pGC)
            {
                const std::vector<Jogador *> &listaJogadores = pGC->getJogadores();

                for (int i = 0; i < listaJogadores.size(); ++i)
                {
                    Jogador *outroJogador = listaJogadores[i];

                    if (outroJogador != nullptr && outroJogador != p)
                    {
                        sf::Vector2f posJogador = outroJogador->getPosicao();

                        float dx = posExercito.x - posJogador.x;
                        float dy = posExercito.y - posJogador.y;
                        float distancia = std::sqrt((dx * dx) + (dy * dy));

                        if (distancia <= raio)
                        {
                            outroJogador->recebeDano(nivel_maldade);
                        }
                    }
                }
            }
        }

        void Exercito::mover()
        {
            aplicarGravidade();

            sf::Vector2f posicaoAtual = getPosicao();
            sf::Vector2f velAtual = getVelocidade();

            if (posicaoAtual.x > (posicaoInicial.x + 100) && velAtual.x > 0.0f)
            {
                setVelocidade(sf::Vector2f(-getVel_Max(), velAtual.y));
            }
            else if (posicaoAtual.x < (posicaoInicial.x - 100) && velAtual.x < 0.0f)
            {
                setVelocidade(sf::Vector2f(getVel_Max(), velAtual.y));
            }

            setPosicao(getPosicao() + getVelocidade());
        }

        void Exercito::salvar()
        {
        }

        bool Exercito::getExplodindo() const
        {
            return explodindo;
        }

        void Exercito::executar()
        {
            if (!explodindo)
            {
                mover();
            }
            else
            {
                if (relogioExplosao.getElapsedTime().asSeconds() >= 0.3f)
                {
                    explodindo = false;
                }
            }
        }

        void Exercito::desenharExplosao()
        {
            if (!explodindo)
            {
                return;
            }

            if (relogioExplosao.getElapsedTime().asSeconds() >= 0.3f)
            {
                return;
            }

            Gerenciadores::Gerenciador_Grafico *pGrafico = Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico();

            if (pGrafico && pFig)
            {
                sf::Sprite spriteExplosao;
                sf::Texture &texturaExplosao = pGrafico->getTextura(Gerenciadores::Explosao);
                spriteExplosao.setTexture(texturaExplosao);

                sf::Vector2u tamanhoTextura = texturaExplosao.getSize();
                spriteExplosao.setOrigin((float)tamanhoTextura.x / 2.0f, (float)tamanhoTextura.y / 2.0f);

                sf::Vector2f posFig = getPosicao();
                sf::Vector2f tamFig = pFig->getSize();
                sf::Vector2f centro = posFig + (tamFig / 2.0f);

                spriteExplosao.setPosition(centro);

                float fatorExplosao = 3.0f;
                float larguraAlvo = tamFig.x * fatorExplosao;
                float alturaAlvo = tamFig.y * fatorExplosao;

                float escalaX = larguraAlvo / (float)tamanhoTextura.x;
                float escalaY = alturaAlvo / (float)tamanhoTextura.y;

                spriteExplosao.setScale(escalaX, escalaY);

                sf::RenderWindow *janela = pGrafico->getWindow();
                if (janela)
                {
                    janela->draw(spriteExplosao);
                }
            }
        }
    }
}