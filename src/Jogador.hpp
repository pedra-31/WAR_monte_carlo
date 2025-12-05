#ifndef JOGADOR_HPP
#define JOGADOR_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

class Territorio;

/**
 * @class Jogador
 * @brief Classe auxiliar, desenhada para representar um jogador de war  
 */
class Jogador {
    private:

        char _nome;
        std::vector<char> _cartas;
        std::vector<Territorio> _territorio;
        unsigned int _rodada_cartas

    public:
        /**
         * @brief Construtor de Jogador
         * @param nome nome do jogador
         */
        Jogador(char nome);

        //getters
        char get_nome();
        /**
         * @brief acha o territorio no vector de territorios e o retorna
         * @param id_territorio id do territorio 
         * @return retorna o objeto Territorio
         */
        Territorio get_territorio(uint16_t id_territorio);

        /**
         * @brief Checa se uma aresta possuim um territorio de id id_territorio
         * Joga exceção se já existe esse território em player 
         * @param territorio t para ser adicionado
         */
        void adicionar_territorio(Territorio t);

        /**
         * @brief Sorteia uma carta ao jogador e coloca no vector de cartas 
         */
        void adicionar_cartas();

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
         * @brief Destrutor de Jogador
         */
        ~Jogador();
};




#endif