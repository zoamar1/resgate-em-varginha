#include "personagens/Inimigo.hpp"

namespace Entidades
{
    namespace Personagens
    {

        Inimigo::Inimigo(float posX, float posY, int n, int maldade)
            : Personagem(posX, posY, 70.0f, 127.0f, n),
              nivel_maldade(maldade),
              posicaoInicial(posX, posY)

        {
        }

        Inimigo::~Inimigo() {}

        void Inimigo::salvarDataBuffer()
        {
            Personagem::salvarDataBuffer();
            nlohmann::json j = nlohmann::json::parse(getBufferDados());
            j["nivel_maldade"] = nivel_maldade;
            j["posicaoInicialX"] = posicaoInicial.x;
            j["posicaoInicialY"] = posicaoInicial.y;
            escreverBuffer(j);
        }

        void Inimigo::setPosicaoInicial(const sf::Vector2f &pos)
        {
            posicaoInicial = pos;
        }

        sf::Vector2f Inimigo::getPosicaoInicial() const
        {
            return posicaoInicial;
        }
    }
}