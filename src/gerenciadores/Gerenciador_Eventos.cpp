#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "Jogo.hpp"

namespace Gerenciadores
{
    Gerenciador_Eventos *Gerenciador_Eventos::pEvento(NULL);

    Gerenciador_Eventos::Gerenciador_Eventos(Jogo *pJ)
        : pGG(NULL), pJogo(pJ), pJog1(NULL), pJog2(NULL) {}

    Gerenciador_Eventos::~Gerenciador_Eventos()
    {
        pGG = NULL;
        pJogo = NULL;
    }

    Gerenciador_Eventos *Gerenciador_Eventos::getGerenciador_Eventos(Jogo *pJ)
    {
        if (!pEvento)
            pEvento = new Gerenciador_Eventos(pJ);
        return pEvento;
    }

    void Gerenciador_Eventos::setGerenciador_Grafico(Gerenciador_Grafico *pGG)
    {
        this->pGG = pGG;
    }

    void Gerenciador_Eventos::setJogador1(Entidades::Personagens::Jogador *pJogador1)
    {
        pJog1 = pJogador1;
    }

    void Gerenciador_Eventos::setJogador2(Entidades::Personagens::Jogador *pJogador2)
    {
        pJog2 = pJogador2;
    }

    void Gerenciador_Eventos::executar()
    {
        if (!pGG || !pJogo)
            return;

        if (pJog1)
            controlaMovimentoJogador1();

        if (pJog2)
            controlaMovimentoJogador2();
    }

    void Gerenciador_Eventos::verificaTeclaPressionada(sf::Event &evento)
    {
        if (!pJogo || !pGG)
            return;

        Jogo::Estados estado = pJogo->getEstado();

        if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
        {
            if (estado == Jogo::RANKING_TELA || estado == Jogo::SUB_SELECAO_MODO || estado == Jogo::SUB_CONTINUAR_JOGO)
            {
                pJogo->setEstado(Jogo::MENU);
                pJogo->getMenu()->setTela(TelaMenu::PRINCIPAL);
                return;
            }
            else if (estado == Jogo::SUB_SELECAO_FASE)
            {
                pJogo->setEstado(Jogo::MENU);
                pJogo->getMenu()->setTela(TelaMenu::PRINCIPAL);
                return;
            }
            else if (estado == Jogo::CADASTRO_J1 || estado == Jogo::CADASTRO_J1_2P)
            {
                pJogo->setEstado(Jogo::SUB_SELECAO_MODO);
                pJogo->getMenu()->setTela(TelaMenu::SELECAO_MODO);
                return;
            }
            else if (estado == Jogo::CADASTRO_J2)
            {
                pJogo->setEstado(Jogo::CADASTRO_J1_2P);
                pJogo->getMenu()->iniciarCadastro(1);
                return;
            }
            else if (estado == Jogo::FASE1 || estado == Jogo::FASE2)
            {
                pJogo->pausarJogo();
                return;
            }
            else if (estado == Jogo::PAUSADO)
            {
                pJogo->despausarJogo();
                return;
            }

            pGG->fecharJanela();
            return;
        }

        if (estado == Jogo::CADASTRO_J1 || estado == Jogo::CADASTRO_J1_2P || estado == Jogo::CADASTRO_J2)
        {
            if (evento.type == sf::Event::TextEntered)
            {
                sf::Uint32 c = evento.text.unicode;
                if (c == 8)
                    pJogo->getMenu()->apagarUltimoChar();
                else if (c != 13)
                    pJogo->getMenu()->processarEventoTexto(c);
            }

            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Return)
            {
                pJogo->getMenu()->confirmarNome();
                std::string nome = pJogo->getMenu()->getNomeDigitado();

                if (estado == Jogo::CADASTRO_J1)
                {
                    pJogo->setModo2Jogadores(false);
                    pJogo->configurarJogador1(nome);
                    pJogo->setEstado(Jogo::SUB_SELECAO_FASE);
                    pJogo->getMenu()->setTela(TelaMenu::SELECAO_FASE);
                }
                else if (estado == Jogo::CADASTRO_J1_2P)
                {
                    pJogo->setModo2Jogadores(true);
                    pJogo->configurarJogador1(nome);
                    pJogo->getMenu()->iniciarCadastro(2);
                    pJogo->setEstado(Jogo::CADASTRO_J2);
                }
                else if (estado == Jogo::CADASTRO_J2)
                {
                    pJogo->configurarJogador2(nome);
                    pJogo->setEstado(Jogo::SUB_SELECAO_FASE);
                    pJogo->getMenu()->setTela(TelaMenu::SELECAO_FASE);
                }
                return;
            }
        }

        if (evento.type == sf::Event::KeyPressed)
        {
            if (estado == Jogo::MENU)
            {
                if (evento.key.code == sf::Keyboard::Num1)
                {
                    pJogo->setEstado(Jogo::SUB_CONTINUAR_JOGO);
                    pJogo->getMenu()->setTela(TelaMenu::CONTINUAR_JOGO);
                }
                else if (evento.key.code == sf::Keyboard::Num2)
                {
                    pJogo->setEstado(Jogo::SUB_SELECAO_MODO);
                    pJogo->getMenu()->setTela(TelaMenu::SELECAO_MODO);
                }
                else if (evento.key.code == sf::Keyboard::Num3)
                {
                    pJogo->setEstado(Jogo::RANKING_TELA);
                    pJogo->getMenu()->setTela(TelaMenu::RANKING);
                }
            }
            else if (estado == Jogo::SUB_SELECAO_MODO)
            {
                if (evento.key.code == sf::Keyboard::Num1)
                {
                    pJogo->setModo2Jogadores(false);
                    pJogo->limparJogadores();
                    pJogo->getMenu()->iniciarCadastro(1);
                    pJogo->setEstado(Jogo::CADASTRO_J1);
                }
                else if (evento.key.code == sf::Keyboard::Num2)
                {
                    pJogo->setModo2Jogadores(true);
                    pJogo->getMenu()->iniciarCadastro(1);
                    pJogo->setEstado(Jogo::CADASTRO_J1_2P);
                }
            }
            else if (estado == Jogo::SUB_SELECAO_FASE)
            {
                if (evento.key.code == sf::Keyboard::Num1 || evento.key.code == sf::Keyboard::Numpad1)
                {
                    pJogo->setEstado(Jogo::FASE1);
                    pJogo->iniciarFase1();
                }
                else if (evento.key.code == sf::Keyboard::Num2 || evento.key.code == sf::Keyboard::Numpad2)
                {
                    pJogo->setEstado(Jogo::FASE2);
                    pJogo->iniciarFase2();
                }
            }
            else if (estado == Jogo::SUB_CONTINUAR_JOGO)
            {
                int idx = -1;
                if (evento.key.code == sf::Keyboard::Num1 || evento.key.code == sf::Keyboard::Numpad1) idx = 0;
                else if (evento.key.code == sf::Keyboard::Num2 || evento.key.code == sf::Keyboard::Numpad2) idx = 1;
                else if (evento.key.code == sf::Keyboard::Num3 || evento.key.code == sf::Keyboard::Numpad3) idx = 2;
                else if (evento.key.code == sf::Keyboard::Num4 || evento.key.code == sf::Keyboard::Numpad4) idx = 3;
                else if (evento.key.code == sf::Keyboard::Num5 || evento.key.code == sf::Keyboard::Numpad5) idx = 4;
                else if (evento.key.code == sf::Keyboard::Num6 || evento.key.code == sf::Keyboard::Numpad6) idx = 5;
                else if (evento.key.code == sf::Keyboard::Num7 || evento.key.code == sf::Keyboard::Numpad7) idx = 6;
                else if (evento.key.code == sf::Keyboard::Num8 || evento.key.code == sf::Keyboard::Numpad8) idx = 7;
                else if (evento.key.code == sf::Keyboard::Num9 || evento.key.code == sf::Keyboard::Numpad9) idx = 8;
                
                if (idx >= 0)
                {
                    const std::vector<std::string>& chaves = pJogo->getMenu()->getChavesSalvamento();
                    if (idx < (int)chaves.size())
                    {
                        pJogo->carregarSalvamento(chaves[idx]);
                    }
                }
            }
            else if (estado == Jogo::PAUSADO)
            {
                if (evento.key.code == sf::Keyboard::Num1)
                {
                    pJogo->despausarJogo();
                }
                else if (evento.key.code == sf::Keyboard::Num2)
                {
                    pJogo->salvarProgresso();
                    pJogo->deletarFases();
                    pJogo->setEstado(Jogo::MENU);
                    pJogo->getMenu()->setTela(TelaMenu::PRINCIPAL);
                }
            }
            else if (estado == Jogo::FASE1 || estado == Jogo::FASE2)
            {
                if (evento.key.code == sf::Keyboard::G && pJog1)
                {
                    Fases::Fase *pFase = static_cast<Fases::Fase *>(pJogo->getCenarioAtual());
                    if (pFase)
                    {
                        Entidades::Projetil *pProjetil = pFase->getProjetilDisponivel();
                        if (pProjetil)
                        {
                            pJog1->atirar(pProjetil);
                            Gerenciador_Colisoes::getGerenciador_Colisoes()->registrarProjetilJogador(pProjetil, pJog1);
                        }
                    }
                }
                else if (evento.key.code == sf::Keyboard::P && pJog2)
                {
                    Fases::Fase *pFase = static_cast<Fases::Fase *>(pJogo->getCenarioAtual());
                    if (pFase)
                    {
                        Entidades::Projetil *pProjetil = pFase->getProjetilDisponivel();
                        if (pProjetil)
                        {
                            pJog2->atirar(pProjetil);
                            Gerenciador_Colisoes::getGerenciador_Colisoes()->registrarProjetilJogador(pProjetil, pJog2);
                        }
                    }
                }
            }
        }
    }

    void Gerenciador_Eventos::controlaMovimentoJogador1()
    {
        if (!pJog1)
            return;

        bool esquerda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool direita = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        if (pJog1->getConfuso())
        {
            bool temp = esquerda;
            esquerda = direita;
            direita = temp;
        }

        int x = (direita ? 1 : 0) + (esquerda ? -1 : 0);
        if (x != 0)
            pJog1->setDirecao(x);

        float velMax = pJog1->getVel_Max();
        float velY = pJog1->getVelocidade().y;
        pJog1->setVelocidade(sf::Vector2f(x * velMax, velY));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            pJog1->pular();
    }

    void Gerenciador_Eventos::controlaMovimentoJogador2()
    {
        if (!pJog2)
            return;

        bool esquerda = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool direita = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        if (pJog2->getConfuso())
        {
            bool temp = esquerda;
            esquerda = direita;
            direita = temp;
        }

        int x = (direita ? 1 : 0) + (esquerda ? -1 : 0);
        if (x != 0)
            pJog2->setDirecao(x);

        float velMax = pJog2->getVel_Max();
        float velY = pJog2->getVelocidade().y;
        pJog2->setVelocidade(sf::Vector2f(x * velMax, velY));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pJog2->pular();
    }
}