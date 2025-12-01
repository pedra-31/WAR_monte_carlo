#ifndef WORLDMAP_HPP
#define WORLDMAP_HPP

#include <vector>
#include <map>
#include <string>
class Edge;

/**
 * @class World_map
 * @brief Classe que contém as informações do mapa
 */
class World_map {
    private:

        /**
         * @brief map que contém o par-ordenado d
         */
        std::vector<unsigned int> vertices;
        std::vector<Edge> arestas;

    public:
        /**
         * @brief Construtor de World_map. Começa um mapa do zero.
         */
        World_map(int players);










        /**
         * @brief Destrutor de World_map
         */
        ~World_map();
};




#endif