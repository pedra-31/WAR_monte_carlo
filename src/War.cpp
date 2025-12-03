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
            if (!arq) {
                throw std::runtime_error("Arquivo nao pode ser aberto: " + caminho + "\n");
                return;
            }

            std::string nome;
            uint16_t id;
            char player;

            while (arq >> nome >> id >> player) {
                _territorios.emplace_back(id, nome, player, 1);
            }
        }


        void War::ler_divisas(const std::string& caminho){
            std::ifstream arq(caminho);
            if (!arq) {
                throw std::runtime_error("Arquivo nao pode ser aberto: " + caminho + "\n");
            }
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
            if (!arq) {
                std::cerr << "Arquivo nao pode ser aberto: " << caminho << "\n";
                return;
            }

            std::vector<Continente> continentes;
            std::string nome;
            unsigned int valor;
            int tamanho;

            while (arq >> nome >> valor >> tamanho){
                if (tamanho < 0) {
                    std::cerr << "Tamanho negativo em continente " << nome << '\n';
                    continue;
                }
                std::vector<uint16_t> ids;
                for(int i = 0; i < tamanho; ++i){
                    uint16_t id;
                    if (!(arq >> id)) {
                        std::cerr << "Erro de leitura de id para continente " << nome << '\n';
                        break;
                    }
                    ids.push_back(id);
                }
                continentes.emplace_back(nome, valor, ids);
            }

            _continentes = std::move(continentes);
        }



        void War::info(){
            std::cout << "players restantes:" << _players << "\n\n"
            << "Info territorios:" << "\n";
            for(auto& t : _territorios){
                t.info();
            }
            std::cout << "\n\nInfo divisas:" << "\n";
            for(auto& d : _divisas){
                d.info();
            }
            std::cout << "\n\nInfo continentes:" << "\n";
            for(auto& c : _continentes){
                c.info();
            }
        }


        War::~War(){

        }