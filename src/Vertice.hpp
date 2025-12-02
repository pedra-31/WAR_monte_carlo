#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <string>
#include <iostream>
#include <cstdint>

/**
 * @class Vertice
 * @brief Classe auxiliar, desenhada para representar os vértices do mapa 
 */
class Vertice {
    private:

        uint16_t _id_vertice;
        std::string _nome;
        char _player;
        unsigned int _num_tropas;

    public:

        /**
         * @brief Construtor de Vertice
         */
        Vertice(uint16_t id_vertice, std::string nome, char player, unsigned int tropas);


        //getters:
        uint16_t get_id();
        std::string get_nome();
        char get_player();
        unsigned int get_num_tropas();

        //setters
        void set_player(char novo_player);
        void set_tropas(unsigned int numero);

        /**
         * @brief Mostra no cout a situação do vértice
         */
        void info();

        /**
         * @brief += Sobrecarregado. Soma ao num de tropas que está posicionada no vértice
         */
        Vertice& operator+=(unsigned int x);

        /**
         * @brief -= Sobrecarregado. Subtrai ao num de tropas que está posicionada no vértice
         * Joga uma exceção
         */
        Vertice& operator-=(unsigned int x);

        /**
         * @brief Destrutor de Vertice
         */
        ~Vertice();
};




#endif