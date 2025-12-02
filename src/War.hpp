#ifndef WAR_HPP
#define WAR_HPP

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <fstream>

class Territorio;
class Divisa;
class Continente;


/**
 * @class War
 * @brief Classe principal do jogo. Funciona como jogo e funciona para as trends do algoritmo de Monte Carlo
 */
class War {
    private:
        
        /**
         * @brief quantidade de jogadores jogando o jogo
         */
        unsigned int _players;

        /**
         * @brief um mapa que contém os continentes e dentro de cada continente, seus id_territórios
         */
        std::map<Continente> _continentes;

        /**
         * @brief vector que contém todos os territorios (vértices)
         */
        std::vector<Territorio> _territorios;

        /**
         * @brief vector que contém todas as divisas (arestas) (grafo não orientado)
         */
        std::vector<Divisa> _divisas;

    public:
        /**
         * @brief Construtor de War lê os continentes
         */
        War(int players);

        //helpers de contrutor. Leêm do arquivo caminho
        void ler_territorios(const std::string& caminho);
        void ler_divisas(const std::string& caminho);
        void ler_continentes(const std::string& caminho);









        /**
         * @brief Destrutor de War
         */
        ~War();
};




#endif