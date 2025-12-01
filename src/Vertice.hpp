#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <string>
#include <iostream>

/**
 * @class Vertice
 * @brief Classe auxiliar, desenhada para representar os vértices do mapa 
 */
class Vertice {
    private:

        unsigned int _id_vertice;
        std::string _nome;
        char _player;
        unsigned int _num_tropas;

    public:

        /**
         * @brief Construtor de Vertice
         */
        Vertice(unsigned int id_vertice, std::string nome, char player, unsigned int tropas);


        //getters:
        unsigned int get_id();
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