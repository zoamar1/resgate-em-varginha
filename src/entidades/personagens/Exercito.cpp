#include "personagens/Exercito.hpp"
#include "personagens/Jogador.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"

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
                p->recebeDano(nivel_maldade*20);
            }

            explodindo = true;
            relogioExplosao.restart();

            Gerenciadores::Gerenciador_Colisoes *pGC = Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes();
            sf::Vector2f posExercito = getPosicao();

            if (pGC)
            {
                const std::vector<Jogador *> &listaJogadores = pGC->getJogadores();

                for (int i = 0; i < (int)listaJogadores.size(); ++i)
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

            float raioPercepcao = 300.0f;

            Gerenciadores::Gerenciador_Colisoes *pGC = Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes();
            Jogador *jogadorAlvo = NULL;

            if (pGC)
            {
                const std::vector<Jogador *> &jogadores = pGC->getJogadores();
                float menorDistancia = -1.0f;

                for (int i = 0; i < (int)jogadores.size(); i++)
                {
                    Jogador *pJog = jogadores[i];
                    if (!pJog)
                        continue;

                    float dx = pJog->getPosicao().x - posicaoAtual.x;
                    float dy = pJog->getPosicao().y - posicaoAtual.y;
                    float distancia = std::sqrt(dx * dx + dy * dy);

                    if (distancia <= raioPercepcao && (menorDistancia < 0.0f || distancia < menorDistancia))
                    {
                        menorDistancia = distancia;
                        jogadorAlvo = pJog;
                    }
                }
            }

            if (jogadorAlvo)
            {
                float dx = jogadorAlvo->getPosicao().x - posicaoAtual.x;
                float direcaoX = (dx > 0.0f) ? 1.0f : -1.0f;

                if ((direcaoX > 0.0f) != (pSprite->getScale().x > 0.0f))
                    pSprite->setScale(-pSprite->getScale().x, pSprite->getScale().y);

                setVelocidade(sf::Vector2f(direcaoX * getVel_Max(), velAtual.y));
            }
            else
            {
                if (posicaoAtual.x > (posicaoInicial.x + 100) && velAtual.x > 0.0f)
                {
                    setVelocidade(sf::Vector2f(-getVel_Max(), velAtual.y));
                    pSprite->setScale(-pSprite->getScale().x, pSprite->getScale().y);
                }
                else if (posicaoAtual.x < (posicaoInicial.x - 100) && velAtual.x < 0.0f)
                {
                    setVelocidade(sf::Vector2f(getVel_Max(), velAtual.y));
                    pSprite->setScale(-pSprite->getScale().x, pSprite->getScale().y);
                }
            }

            setPosicao(getPosicao() + getVelocidade());
        }

        void Exercito::salvar()
        {
            salvarDataBuffer();
            nlohmann::json j = nlohmann::json::parse(getBufferDados());
            j["tipo"] = "Exercito";
            j["raio"] = raio;
            escreverBuffer(j);
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
                    set_vida_atual(0);
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