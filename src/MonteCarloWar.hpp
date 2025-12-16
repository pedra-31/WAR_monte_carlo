#ifndef MONTECARLOWAR_HPP
#define MONTECARLOWAR_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <random>
#include "War.hpp"

class Territorio;
class Divisa;


/**
 * @class MonteCarloWar
 * @brief Classe descobrir os melhores lançes um certo ponto do jogo
 */
class MonteCarloWar{
    private:
        /**
        * @brief Partida de War no momento do jogo
        */
        War _war;

        /**
         * @brief gerador de números aleatórios
         */
        std::mt19937 _gen;

    public:

        /**
        * @brief Construtor de MonteCarloWar
        * @param war_original uma cópia que é entregue a classe, deve ser atualizada posteriormente depois que o lance for atualizada
        */
        MonteCarloWar(War& original);

        War* get_war();

        /**
        * @brief Escolhe aleatoriamente as posições para posicionar tropas 
        */
        void posicionar_tropas(char player);

        /**
        * @brief Escolhe um ataque 
        */
        void atacar(char player);

        /**
        * @brief Faz reposicionamentos
        */
        void reposicionar(char player);

        ~MonteCarloWar();
};




#endif