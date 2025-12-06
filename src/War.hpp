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
        const Jogador get_jogador(char nome) const;
        //Etapa 1 ------ Posicionar
        /**
         * @brief acha a quantidade de tropas que um jogador tem na rodada / troca as cartes de um certo jogador
         * @param nome nome do jogador
         * @return quantidade de tropas
         */
        unsigned int get_tropas(char nome);

        /**
         * @brief posiciona tropas do jogador no território 
         * @param nome nome do jogador fazendo a ação
         * @param id_territorio id do território para posicionar tropas
         * @param quantidade quantidade de tropas para ser posicionada
         */
        void posicionar_tropa(char nome, uint16_t id_territorio, unsigned int quantidade);

        /**
         * @brief posiciona tropas do jogador no território 
         * @param nome nome do jogador fazendo a ação
         * @param nome_territorio nome do território para posicionar tropas
         * @param quantidade quantidade de tropas para ser posicionada
         */
        void posicionar_tropa(char nome, const std::string& nome_territorio, unsigned int quantidade);

        //Etapa 1 ------ Atacar

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