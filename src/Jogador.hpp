#ifndef JOGADOR_HPP
#define JOGADOR_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <random>

class Territorio;

/**
 * @class Jogador
 * @brief Classe auxiliar, desenhada para representar um jogador de war  
 */
class Jogador {
    private:
        /**
         * @brief Nome do jogador
         */
        char _nome;
        /**
         * @brief Vetor das cartas que jogador possuí
         */
        std::vector<char> _cartas;
        /**
         * @brief Vetor de territórios que jogador possuí
         */
        std::vector<Territorio> _territorios;
        /**
         * @brief contador das rodadas que jogador já trocou de cartas
         */
        unsigned int _rodada_cartas;

        /**
         * @brief gerador de números aleatórios
         */
        std::mt19937 _gen;

    public:
        /**
         * @brief Construtor de Jogador
         * @param nome nome do jogador
         */
        Jogador(char nome);

        //getters
        char get_nome() const;
        
        /**
         * @brief devolva a lista de id_territorios que o jogador possui
         * @return retorna um vector com os ids
         */
        const std::vector<uint16_t> get_id_territorios() const;

        /**
         * @brief acha o territorio no vector de territorios e o retorna para somente consulta 
         * @param id_territorio id do territorio 
         * @return retorna o objeto Territorio
         */
        const Territorio get_territorio(uint16_t id_territorio) const;

        /**
         * @brief Checa se uma aresta possuim um territorio de id id_territorio
         * Joga exceção se já existe esse território em player 
         * @param territorio (objeto) para ser adicionado
         */
        void adicionar_territorio(Territorio territorio);

        /**
         * @brief Sorteia uma carta ao jogador e coloca no vector de cartas 
         */
        void sorteia_carta();

        /**
         * @brief Se for possível trocar cartas: devolve o numero de tropas + aumenta o contador _rodada_cartas
         * Se não for possível retorna 0
         */
        unsigned int trocar_cartas();

        /**
         * @brief info de jogador e chama o info de territórios que possui
         */
        void info();

        
        /**
         * @brief info de territórios que jogador possui
         */
        void info_territorios();
};




#endif