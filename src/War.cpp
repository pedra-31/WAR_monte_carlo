#include "War.hpp"
#include "Territorio.hpp"
#include "Jogador.hpp"
#include "Divisa.hpp"
#include "Continente.hpp"

        War::War(int num_jogadores) :
        _num_jogadores(num_jogadores){
            ler_territorios("../data/territorios.txt");
            ler_divisas("../data/divisas.txt");
            ler_continentes("../data/continentes.txt");   
        }


        void War::ler_territorios(const std::string& caminho){
            std::ifstream arq(caminho); 
            if (!arq) {
                throw std::runtime_error("Arquivo nao pode ser aberto: " + caminho + "\n");
            }

            std::string nome;
            uint16_t id;
            char player;
            for(unsigned int i = 0; i < _num_jogadores; i++){
                _jogadores.emplace_back(i+97);
            }

            while (arq >> nome >> id >> player) {
                for(auto& j : _jogadores){
                    if(j.get_nome() == player){
                        j.adicionar_territorio(Territorio(id, nome, player, 1));
                        break;
                    }
                }
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
                throw std::runtime_error("Arquivo nao pode ser aberto: " + caminho + "\n");
            }

            std::vector<Continente> continentes;
            std::string nome;
            unsigned int valor;
            int tamanho;

            while (arq >> nome >> valor >> tamanho){
                if (tamanho < 0) {
                    throw std::runtime_error("Tamanho negativo em continente " + nome);
                }
                std::vector<uint16_t> ids;
                for(int i = 0; i < tamanho; ++i){

                    
                    uint16_t id;
                    if (!(arq >> id)) {
                        throw std::runtime_error("Erro de leitura de id para continente " + nome);
                    }
                    ids.push_back(id);
                }
                continentes.emplace_back(nome, valor, ids);
            }

            _continentes = std::move(continentes);
        }

        Territorio* War::get_territorio(const std::string& nome){
            for(auto& j : _jogadores){
                return j.get_territorio(nome);
            }
        }

        void War::recebe_territorio(char nome_atacante, const std::string& nome_territorio_defensor, const std::string& nome_territorio_atacante){
            Jogador* j_defensor = nullptr;
            Jogador* j_atacante = nullptr;

            for(auto& j : _jogadores){
                if(j.get_nome() == nome_atacante){
                    j_atacante = &j;
                }
            }
            if(j_atacante == nullptr){
                throw std::runtime_error("void War::recebe_territorio(char nome_atacante, ...): Não existe jogador com nome_atacante: " + nome_atacante);
            }

            for (auto& j : _jogadores){
                for(auto& t : j.get_nome_territorios()){
                    if(t == nome_territorio_defensor){
                        j_defensor = &j;
                        if(j.get_nome() == j_atacante->get_nome()){
                            throw std::runtime_error("void War::recebe_territorio(): nome_defensor == nome_atacante");
                        }
                        //para não ficar fazendo umas 30 funções auxiliares eu fiz essa maravilha de código, entenda se quiser...
                        Territorio territorio = j.remover_territorio(j_defensor->get_territorio(nome_territorio_defensor)->get_id());
                        //seta as tropas para 1
                        territorio.set_tropas(1);
                        //adiciona o territorio em j_atacante
                        j_atacante->adicionar_territorio(territorio);
                        return; 
                    }
                }
            }

            if(j_defensor == nullptr){
                throw std::runtime_error("void War::recebe_territorio(...): Não existe território com o nome: " + nome_territorio_defensor);
            }

            
        }



        void War::info(){
            std::cout << "players restantes:" << _num_jogadores << "\n\n";
            std::cout << "Info jogadores:" << "\n";
            for(auto& j : _jogadores){
                j.info();
                std::cout << "\n\n";
            }
            std::cout << "\n\nInfo divisas:" << "\n";
            for(auto& d
                 : _divisas){
                d.info();
            }
            std::cout << "\n\nInfo continentes:" << "\n";
            for(auto& c : _continentes){
                c.info();
            }
        }

        void War::info_territorios(){
            std::cout << "Info territorios:" << "\n";
            for(auto& j : _jogadores){
                j.info_territorios();
            }
        }


        War::~War() = default;  