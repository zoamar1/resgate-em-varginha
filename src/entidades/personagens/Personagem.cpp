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

        int Personagem::get_vida_atual() const{
            return vida_atual;
        }

        void Personagem::set_vida_atual(int vida)
        {
            if (vida_atual + vida <= num_vidas) vida_atual += vida;
            else vida_atual = num_vidas;
        }

        int Personagem::get_num_vidas() const
        {
            return num_vidas;
        }

        void Personagem::operator++()
        {
            if (vida_atual < num_vidas) vida_atual++;
        }
    }
}
