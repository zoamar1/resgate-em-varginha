#include "entidades/obstaculos/Arbusto.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Arbusto::Arbusto(float posX, float posY, float tamanhoX, float tamanhoY) : Obstaculo(posX, posY, tamanhoX, tamanhoY), largura(tamanhoX)
        {
            if (pFig)
            {
                aplicarTextura(Gerenciadores::Arbusto);

                pFig->setSize(sf::Vector2f(tamanhoX, tamanhoY));
                pFig->setOrigin(0.0f, 0.0f);
                pFig->setPosition(getPosicao());
            }
        }

        Arbusto::~Arbusto()
        {
        }

        void Arbusto::salvar()
        {
            salvarDataBuffer();
            nlohmann::json j = nlohmann::json::parse(getBufferDados());
            j["tipo"] = "Arbusto";
            j["largura"] = largura;
            j["altura"] = pFig->getSize().y;
            escreverBuffer(j);
        }

        void Arbusto::obstaculizar(Entidades::Personagens::Jogador *p)
        {
            if (p)
            {
                sf::Vector2f pos = p->getPosicao();
                sf::Vector2f vel = p->getVelocidade();

                pos.x -= vel.x * 0.5f;
                p->setPosicao(pos);
            }
        }

        void Arbusto::executar()
        {
            aplicarGravidade();
            anularGravidade();
            atualizarPosicao();
        }
    }
}