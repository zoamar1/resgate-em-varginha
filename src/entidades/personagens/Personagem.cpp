#include "personagens/Personagem.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Personagem::Personagem(float posX, float posY, float tamanhoX, float tamanhoY, int n) : Entidade(sf::Vector2f(posX, posY), sf::Vector2f(tamanhoX, tamanhoY)),
                                                                                                num_vidas(n), vida_atual(n)
        {
        }

        Personagem::~Personagem()
        {
        }

        void Personagem::recebeDano(int dano)
        {
            vida_atual -= dano;
        }

        int Personagem::get_vida_atual() const
        {
            return vida_atual;
        }

        void Personagem::set_vida_atual(int vida)
        {
            int max_vidas = get_num_vidas();
            if (vida < 0)
            {
                vida_atual = 0;
            }
            else if (vida > max_vidas)
            {
                vida_atual = max_vidas;
            }
            else
            {
                vida_atual = vida;
            }
        }

        int Personagem::get_num_vidas() const
        {
            return num_vidas;
        }

        void Personagem::operator++()
        {
            if (vida_atual < get_num_vidas())
                vida_atual++;
        }

        void Personagem::salvarDataBuffer()
        {
            Entidade::salvarDataBuffer();
            nlohmann::json j = nlohmann::json::parse(getBufferDados());
            j["vida_atual"] = vida_atual;
            j["num_vidas"] = num_vidas;
            escreverBuffer(j);
        }
    }
}