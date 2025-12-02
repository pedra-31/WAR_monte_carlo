#ifndef WAR_HPP
#define WAR_HPP

#include <vector>
#include <map>
#include <string>
#include <cstdint>

class Vertice;
class Edge;


/**
 * @class War
 * @brief Classe principal do jogo. Funciona como jogo e funciona para as trends do algoritmo de Monte Carlo
 */
class War {
    private:

        /**
         * @brief um mapa que contém os continentes e dentro de cada continente, seus id_territórios
         */
        std::map<std::string, std::vector<uint16_t>> continentes;

        /**
         * @brief vector que contém todos os vértices
         */
        std::vector<Vertice> vertices;

        /**
         * @brief vector que contém todas as arestas (grafo não orientado)
         */
        std::vector<Edge> arestas;

    public:
        /**
         * @brief Construtor de War
         */
        War(int players);










        /**
         * @brief Destrutor de War
         */
        ~War();
};




#endif