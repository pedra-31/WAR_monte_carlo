#include "War.hpp"
#include "Territorio.hpp"
#include "Divisa.hpp"

        War::War(int players) :
        _players(players){
            
        }


        void War::ler_territorios(const std::string& caminho){
            std::ifstream arq(caminho);
            std::vector<Territorio> territorios;

            std::string nome;
            uint16_t id;
            char player;

            while (arq >> nome >> id >> player) {
                Territorio t(id, nome, player, 1); 
                territorios.push_back(t);
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
                Divisa a(id_1, id_2); 
                divisas.push_back(a);
            }

            _divisas = divisas;
        }

        void War::ler_continentes(const std::string& caminho){
            std::ifstream arq(caminho);
            std::map<std::string, std::vector<uint16_t>> continentes;

            std::string nome;
            std::vector<uint16_t>

            while (arq >> id_1 >> id_2) {
                continentes.push_back(a);
            }

            _divisas = divisas;
        }








        /**
         * @brief Destrutor de War
         */
        War::~War(){

        }