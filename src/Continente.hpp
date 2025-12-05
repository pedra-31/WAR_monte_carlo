#ifndef CONTINENTE_HPP
#define CONTINENTE_HPP
#include <cstdint>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

class Jogador;

/**
 * @class Continente
 * @brief Classe auxiliar, desenhada para representar os continentes do mapa
 */
class Continente {
    private:
        /**
         * @brief nome do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do do continente
         */
        std::string _nome;
        /**
         * @brief valor de quanto vale o continente
         */
        unsigned int _pontos_conquista;
        /**
         * @brief lista de vertices que o continente possui
         */
        std::vector<uint16_t> _vertices;

    public:

        /**
         * @brief Construtor
         */
        Continente(std::string nome, unsigned int pontos_conquista, std::vector<uint16_t> vertices);

        //getters
        unsigned int get_pontos_conquista() const;
        const std::vector<uint16_t>& get_vertices() const;
        const std::string& get_nome() const;

        /**
         * @brief função que checa se um jogador possuí todos os territórios de um continente
         * @return True se possui, False se não possui
         */
        bool possui_continente(Jogador j) const;

        /**
         * @brief Imprime as informações da classe no cout
         */
        void info();
};  




#endif