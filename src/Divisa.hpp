#ifndef DIVISA_HPP
#define DIVISA_HPP
#include <cstdint>
#include <iostream>

/**
 * @class Divisa
 * @brief Classe auxiliar, desenhada para representar as arestas entre 2 territorios de mapa 
 */
class Divisa {
    private:

    uint16_t _v1;
    uint16_t _v2;

    public:
        /**
         * @brief Construtor de Divisa
         * @param id_v1 id do vértice 1
         * @param id_v2 id do vértice 2
         */
        Divisa(uint16_t id_v1, uint16_t id_v2);

        //getters
        uint16_t get_v1() const;
        uint16_t get_v2() const;

        /**
         * @brief Checa se uma aresta possuim um territorio de id id_territorio 
         * @param id_territorio id do territorio para ser procurado
         * @return true se possui / falso se não possui
         */
        bool tem_territorio(uint16_t id_territorio) const;

        void info();

        /**
         * @brief Destrutor de Divisa
         */
        ~Divisa();
};




#endif