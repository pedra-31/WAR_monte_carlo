#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP
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

    public:

        /**
        * @brief Construtor de MonteCarloWar
        * @param war_original uma cópia que é entregue a classe, deve ser atualizada posteriormente depois que o lance for atualizada
        */
        MonteCarloWar(const War& war_original);

        /**
        * @brief simula uma rodada de todos jogadores de war
        */
        void simular_rodada();

        /**
        * @brief Escolhe aleatoriamente as posições para posicionar tropas 
        */
        void posicionar_tropas(char player);
};




#endif