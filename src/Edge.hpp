#ifndef EGDE_HPP
#define EGDE_HPP
#include <cstdint>


/**
 * @class Edge
 * @brief Classe auxiliar, desenhada para representar as arestas entre 2 vertices de mapa 
 */
class Edge {
    private:

    uint16_t _v1;
    uint16_t _v2;

    public:
        /**
         * @brief Construtor de Edge
         * @param id_v1 id do vértice 1
         * @param id_v2 id do vértice 2
         */
        Edge(uint16_t id_v1, uint16_t id_v2);

        uint16_t get_v1();
        uint16_t get_v2();

        bool has_vertice(uint16_t id);

        /**
         * @brief Destrutor de Edge
         */
        ~Edge();
};




#endif