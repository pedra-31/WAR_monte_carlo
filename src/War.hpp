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
class Jogador;


/**
 * @class War
 * @brief Classe principal do jogo. Funciona como jogo e funciona para as trends do algoritmo de Monte Carlo
 */
class War {
    private:
        
        /**
         * @brief quantidade de jogadores ativos
         */
        unsigned int _num_jogadores;

        /**
         * @brief um mapa que contém os continentes e dentro de cada continente, seus id_territórios
         */
        std::vector<Continente> _continentes;

        /**
         * @brief vector que contém todos os territorios (vértices)
         */
        std::vector<Jogador> _jogadores;

        /**
         * @brief vector que contém todas as divisas (arestas) (grafo não orientado)
         */
        std::vector<Divisa> _divisas;

    public:
        /**
         * @brief Construtor de War lê os continentes
         */
        War(int num_jogadores);

        //helpers de contrutor. Leêm informações do arquivo caminho
        void ler_territorios(const std::string& caminho);
        void ler_divisas(const std::string& caminho);
        void ler_continentes(const std::string& caminho);

        //getters
        Jogador get_jogador(char nome);
        const std::vector<uint16_t>& get_divisas() const;


        Territorio* get_territorio(const std::string& nome);


        std::vector<uint16_t> get_id_territorios_adjacentes(uint16_t id_territorio);

        /**
         * @brief Faz a troca de territórios (usado só para players reais), a quantidade de tropas cai para 1
         * @param nome_atacante nome do jogador defendendo o territorio
         * @param nome_atacante nome do jogador atacando o territorio
         * @param nome_territorio_defensor nome do território onde ocorreu a batalha
         * @param nome_territorio_atacante nome do território de onde o atacante iniciou a batalha
         */
        void recebe_territorio(char nome_atacante, const std::string& nome_territorio_atacado, const std::string& nome_territorio_atacante);

        /**
         * @brief info do jogo no cout, chama todos os infos de classes componentes
         */
        void info();
        /**
         * @brief info dos territórios no cout, chama somente o info de territorios
         */
        void info_territorios();



        ~War();   

};




#endif