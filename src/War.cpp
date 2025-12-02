#include "War.hpp"
#include "Territorio.hpp"
#include "Divisa.hpp"
#include "Continente.hpp"

        War::War(int players) :
        _players(players){
            ler_territorios("../data/territorios.txt");
            ler_divisas("../data/divisas.txt");
            ler_continentes("../data/continentes.txt");   
        }


        void War::ler_territorios(const std::string& caminho){
            std::ifstream arq(caminho);
            std::vector<Territorio> territorios;

            std::string nome;
            uint16_t id;
            char player;

            while (arq >> nome >> id >> player) {
                territorios.push_back(Territorio(id, nome, player, 1));
            }

            territorios = _territorios;
        }

        void War::ler_divisas(const std::string& caminho){
            std::ifstream arq(caminho);
            std::vector<Divisa> divisas;

            std::string nome;
            uint16_t id_1;
            uint16_t id_2;

            while (arq >> id_1 >> id_2) {
                divisas.push_back(Divisa(id_1, id_2));
            }

            _divisas = divisas;
        }

        void War::ler_continentes(const std::string& caminho){
            std::ifstream arq(caminho);
            std::vector<Continente> continentes;

            unsigned int valor;
            std::string nome;
            int tamanho;

            while (arq >> nome >> valor >> tamanho){
                std::vector<uint16_t> ids;
                for(int i = 0; i < tamanho; i++){
                    arq >> ids[i];
                }
                continentes.push_back(Continente(nome, valor, ids));
            }

            _continentes = continentes;
        }








        /**
         * @brief Destrutor de War
         */
        War::~War(){

        }