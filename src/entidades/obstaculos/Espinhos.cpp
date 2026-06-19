#include "entidades/obstaculos/Espinhos.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Espinhos::Espinhos(float posX, float posY, float tamanhoX, float tamanhoY, short int dano) : Obstaculo(posX, posY, tamanhoX, tamanhoY), danosidade(dano)
        {
            if (pFig)
            {
                aplicarTextura(Gerenciadores::Espinhos);

                pFig->setSize(sf::Vector2f(tamanhoX, tamanhoY));
                pFig->setOrigin(0.0f, 0.0f);
                pFig->setPosition(getPosicao());
            }
        }

        Espinhos::~Espinhos()
        {
        }

        void Espinhos::salvar()
        {
            salvarDataBuffer();
            nlohmann::json j = nlohmann::json::parse(bufferDados);
            j["tipo"] = "Espinhos";
            j["danosidade"] = danosidade;
            bufferDados = j.dump();
        }

        void Espinhos::obstaculizar(Entidades::Personagens::Jogador *p)
        {
            if (p)
            {
                p->recebeDano(danosidade);
            }
        }

        void Espinhos::executar()
        {
            aplicarGravidade();
            anularGravidade();
            atualizarPosicao();
        }
    }
}