#ifndef JOGADOR_HPP
#define JOGADOR_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <random>

class Territorio;
class Divisa;

/**
 * @class Jogador
 * @brief Classe auxiliar, desenhada para representar um jogador de war  
 */
class Jogador {
    private:
        /**
         * @brief Nome do jogador
         */
        char _nome;
        /**
         * @brief Vetor das cartas que jogador possuí
         */
        std::vector<char> _cartas;
        /**
         * @brief Vetor de territórios que jogador possuí
         */
        std::vector<Territorio> _territorios;
        /**
         * @brief contador das rodadas que jogador já trocou de cartas
         */
        unsigned int _rodada_cartas;

        /**
         * @brief gerador de números aleatórios
         */
        std::mt19937 _gen;

    public:
        /**
         * @brief Construtor de Jogador
         * @param nome nome do jogador
         */
        Jogador(char nome);

        //getters
        char get_nome() const;
        
        /**
         * @brief devolva a lista de id_territorios que o jogador possui
         * @return retorna um vector com os ids
         */
        const std::vector<uint16_t> get_id_territorios() const;

        /**
         * @brief devolva a lista de nomes territorios que o jogador possui
         * @return retorna um vector com os nomes
         */
        const std::vector<std::string> get_nome_territorios() const;

        /**
         * @brief acha o territorio no vector de territorios e o retorna para somente consulta 
         * @param id_territorio id do territorio 
         * @return retorna um ponteiro para Territorio
         */
        Territorio* get_territorio(uint16_t id_territorio);

        /**
         * @brief acha o territorio no vector de territorios e o retorna
         * @param nome_territorio nome do territorio para ser encontrado
         * @return retorna um ponteiro para Territorio
         */
        Territorio* get_territorio(const std::string& nome_territorio);

        /**
         * @brief Checa se uma aresta possuim um territorio de id id_territorio
         * Joga exceção se já existe esse território em player 
         * @param territorio (objeto) para ser adicionado
         */
        void adicionar_territorio(Territorio territorio);

        /**
         * @brief Retira territorio da lista de territórios de player
         * Joga exceção se não existe
         * @return territorio (objeto) 
         */
        Territorio remover_territorio(uint16_t id_territorio);

        /**
         * @brief Sorteia uma carta ao jogador e coloca no vector de cartas 
         */
        void sorteia_carta();

        /**
         * @brief Se for possível trocar cartas: devolve o numero de tropas + aumenta o contador _rodada_cartas
         * Se não for possível retorna 0
         */
        unsigned int trocar_cartas();

        /**
         * @brief info de jogador e chama o info de territórios que possui
         */
        void info();
        
        /**
         * @brief info de territórios que jogador possui
         */
        void info_territorios();
        
        /**
         * @brief acha a quantidade de tropas que um jogador tem na rodada / troca as cartes de um certo jogador
         * @return quantidade de tropas
         */
        uint16_t get_tropas();

        /**
         * @brief posiciona tropas do jogador no território 
         * @param id_territorio id do território para posicionar tropas
         * @param quantidade quantidade de tropas para ser posicionada
         */
        void posicionar_tropa(uint16_t id_territorio, unsigned int quantidade);
        
        /**
         * @brief posiciona tropas do jogador no território 
         * @param nome_territorio nome do território para posicionar tropas
         * @param quantidade quantidade de tropas para ser posicionada
         */
        void posicionar_tropa(const std::string& nome_territorio, unsigned int quantidade);

        /**
         * @brief Ao final de uma rodada de um jogador faz o reposicionamento de tropas 
         * @param origem_territorio nome do território de origem 
         * @param destino_territorio nome do território de destino das tropas 
         * @param quantidade quantidade de tropas para ser reposicionada
         * @param divisas lista das divisas existentes em War
         */
        void reposicionar_tropa(const std::string& origem_territorio, const std::string& destino_territorio, unsigned int quantidade, const std::vector<Divisa>& divisas);
        /**
         * @brief Ao final de uma rodada de um jogador faz o reposicionamento de tropas 
         * @param id_origem_territorio id do território de origem 
         * @param id_destino_territorio id do território de destino das tropas 
         * @param quantidade quantidade de tropas para ser posicionada
         * @param divisas lista das divisas existentes em War
         */
        void reposicionar_tropa(uint16_t id_origem_territorio, uint16_t id_destino_territorio, unsigned int quantidade, const std::vector<Divisa>& divisas);
};




#endif