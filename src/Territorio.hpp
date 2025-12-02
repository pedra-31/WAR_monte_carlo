#ifndef TERRITORIO_HPP
#define TERRITORIO_HPP

#include <string>
#include <iostream>
#include <cstdint>

/**
 * @class Territorio
 * @brief Classe auxiliar, desenhada para representar os vértices do mapa 
 */
class Territorio {
    private:

        uint16_t _id_Territorio;
        std::string _nome;
        char _player;
        unsigned int _num_tropas;

    public:

        /**
         * @brief Construtor de Territorio
         */
        Territorio(uint16_t id_Territorio, std::string nome, char player, unsigned int tropas);


        //getters:
        uint16_t get_id() const;
        std::string get_nome() const;
        char get_player() const;
        unsigned int get_num_tropas() const;

        //setters
        void set_player(char novo_player);
        void set_tropas(unsigned int numero);

        /**
         * @brief Mostra no cout a situação do vértice
         */
        void info() const;

        /**
         * @brief += Sobrecarregado. Soma ao num de tropas que está posicionada no vértice
         */
        Territorio& operator+=(unsigned int x);

        /**
         * @brief -= Sobrecarregado. Subtrai ao num de tropas que está posicionada no vértice
         * Joga uma exceção
         */
        Territorio& operator-=(unsigned int x);

        /**
         * @brief Destrutor de Territorio
         */
        ~Territorio();
};




#endif