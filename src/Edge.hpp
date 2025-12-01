#ifndef EGDE_HPP
#define EGDE_HPP


/**
 * @class Edge
 * @brief Classe auxiliar, desenhada para representar as arestas entre 2 vertices de mapa 
 */
class Edge {
    private:

    unsigned int _v1;
    unsigned int _v2;

    public:
        /**
         * @brief Construtor de Edge
         * @param id_v1 id do vértice 1
         * @param id_v2 id do vértice 2
         */
        Edge(unsigned int id_v1, unsigned int id_v2);







        /**
         * @brief Destrutor de Edge
         */
        ~Edge();
};




#endif