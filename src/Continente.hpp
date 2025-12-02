#ifndef CONTINENTE_HPP
#define CONTINENTE_HPP
#include <cstdint>
#include <vector>
#include <algorithm>

/**
 * @class Continente
 * @brief Classe auxiliar, desenhada para representar os continentes do mapa
 */
class Continente {
    private:
        /**
         * @brief valor de quanto vale o continente
         */
        unsigned int _pontos_conquista;
        /**
         * @brief lista de vertices que o continente possui
         */
        std::vector<uint16_t> _vertices;

    public:

        Continente(unsigned int pontos_conquista, std::vector<uint16_t> vertices);

        unsigned int get_pontos_conquista() const;
        const std::vector<uint16_t>& get_vertices() const;


        bool possui_territorios(const std::vector<uint16_t>& v) const;
        
};  




#endif