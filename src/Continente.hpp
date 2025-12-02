#ifndef CONTINENTE_HPP
#define CONTINENTE_HPP
#include <cstdint>
#include <vector>
#include <algorithm>
#include <string>

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

        Continente(std::string nome, unsigned int pontos_conquista, std::vector<uint16_t> vertices);

        unsigned int get_pontos_conquista() const;
        const std::vector<uint16_t>& get_vertices() const;
        const std::string& get_nome() const;


        bool possui_territorios(const std::vector<uint16_t>& v) const;
        
};  




#endif