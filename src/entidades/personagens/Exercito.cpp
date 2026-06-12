#include "personagens/Exercito.hpp"
#include "personagens/Jogador.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp" // Adicionado o include do GG para garantir que compile
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

                for (size_t i = 0; i < listaJogadores.size(); ++i) // Mudado para size_t para evitar warnings de comparação signed/unsigned
                {
                    Jogador *outroJogador = listaJogadores[i];

                    if (outroJogador != nullptr && outroJogador != p) // Usando nullptr que é o padrão moderno do C++
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

        void Exercito::atirar(Entidades::Projetil *pProjetil)
        {
            // nao faz nada
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

        void Exercito::executar()
        {
            if (!explodindo)
            {
                mover();
            }
            else
            {
                // Controla o tempo de exibição do sprite da explosão (0.3 segundos)
                if (relogioExplosao.getElapsedTime().asSeconds() < 0.3f)
                {
                    Gerenciadores::Gerenciador_Grafico *pGrafico = Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico();

                    if (pGrafico)
                    {
                        // 1. Cria o sprite e puxa a textura correta do seu Gerenciador Gráfico
                        sf::Sprite spriteExplosao;
                        sf::Texture &texturaExplosao = pGrafico->getTextura(Gerenciadores::Explosao);
                        spriteExplosao.setTexture(texturaExplosao);

                        // 2. Centraliza a origem do sprite (para expandir a partir do meio exato do Exercito)
                        sf::Vector2u tamanhoTextura = texturaExplosao.getSize();
                        spriteExplosao.setOrigin((float)tamanhoTextura.x / 2.0f, (float)tamanhoTextura.y / 2.0f);
                        spriteExplosao.setPosition(getPosicao());

                        // 3. Calcula a escala para que o sprite ocupe o tamanho do diâmetro (raio * 2)
                        float diametroAlvo = (float)raio * 2.0f;
                        float escalaX = diametroAlvo / (float)tamanhoTextura.x;
                        float escalaY = diametroAlvo / (float)tamanhoTextura.y;
                        spriteExplosao.setScale(escalaX, escalaY);

                        // 4. O Gerenciador_Grafico só tem 'desenhaRect', 'desenhaTexto' e 'desenhaEnte'.
                        // Como um sprite não é um Ente puro e nem um Rect, você pode desenhar direto usando a window:
                        sf::RenderWindow *janela = pGrafico->getWindow();
                        if (janela)
                        {
                            janela->draw(spriteExplosao);
                        }
                    }
                }
                else
                {
                    explodindo = false;
                    // Se o inimigo deve sumir permanentemente após a explosão acabar,
                    // você pode setar uma flag de destruição aqui (ex: destruir = true;)
                }
            }
        }
    }
}