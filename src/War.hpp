#ifndef WAR_HPP
#define WAR_HPP

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <fstream>
#include <algorithm>
#include <random>

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
         * @brief gerador de números aleatórios
         */
        std::mt19937 _gen;    

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
        void ler_territorios(const std::string& caminho, unsigned int num_jogadores);
        void ler_divisas(const std::string& caminho);
        void ler_continentes(const std::string& caminho);

        //getters
        Jogador* get_jogador(char nome);
        unsigned int get_num_jogadores();
        std::vector<char> get_ordem_jogadores() const;
        const std::vector<uint16_t>& get_divisas() const;


        Territorio* get_territorio(const std::string& nome);
        Territorio* get_territorio(uint16_t id_territorio);


        /**
         * @brief Encontra todos os ids territórios adjacentes ao território parametro
         * @param id_territorio id do territorio para buscar territorios adjacentes
         * @return Retorna a lista de ids
         */
        std::vector<uint16_t> get_id_territorios_adjacentes(uint16_t id_territorio);

        /**
         * @brief Retorna a lista de id territórios que fazem fronteira com territórios inimigos;
         * @param jogador nome do jogador para a ação
         * @return Retorna a lista de ids
         */
        std::vector<uint16_t> get_id_territorios_adjacentes_com_inimigos(char jogador);

        /**
         * @brief Retorna a lista de Divisas que podem ser interessantes para um ataque
         * @param jogador nome do jogador para encontrar essas divisas
         * @return Retorna a lista de divisas
         */
        std::vector<Divisa> get_divisas_intessantes(char jogador);

        /**
         * @brief Faz a troca de territórios (usado só para players reais), a quantidade de tropas cai para 1
         * @param nome_atacante nome do jogador atacando o territorio
         * @param nome_territorio_atacado nome do território onde ocorreu a batalha
         */
        void recebe_territorio(char nome_atacante, const std::string& nome_territorio_atacado);

        /**
         * @brief info do jogo no cout, chama todos os infos de classes componentes
         */
        void info();
        /**
         * @brief info dos territórios no cout, chama somente o info de territorios
         */
        void info_territorios();

        /**
        * @brief Reseta o gerador de numeros aleatorios
        * @param seed seed para colocar como geradora de numeros aleatorios
        */
        void restart_gen(uint32_t seed);

        /**
        * @brief Reseta o gerador de numeros aleatorios
        */

        void restart_gen();

        /**
        * @brief calcula a quantidade de pontos vitoria
        */
        unsigned int calcular_pontos_vitoria(char nome);
        
        /**
        * @brief Escolhe aleatoriamente as posições para posicionar tropas 
        */
        void simular_posicionar_tropas(char player);

        /**
        * @brief Escolhe um ataque 
        */
        void simular_atacar(char player);

        /**
        * @brief Escolhe um ataque 
        */
        void simular_multi_ataques(char player);

        /**
        * @brief Faz reposicionamentos
        */
        void simular_reposicionar(char player);

        void checa_jogadores();

        ~War();   

};




#endif