#include "Jogador.hpp"
#include "Territorio.hpp"

        
        Jogador::Jogador(char nome) : 
                _nome(nome),
                _rodada_cartas(0), 
                _gen(std::random_device{}()){

        }

        char Jogador::get_nome() const{
                return _nome;
        }

        const std::vector<uint16_t> Jogador::get_id_territorios() const{
                std::vector<uint16_t> lista;
                for(auto& t : _territorios){
                        lista.push_back(t.get_id());
                }
                return lista;
        }

        const Territorio Jogador::get_territorio(uint16_t id_territorio) const{
                for(auto& t : _territorios){
                        if(t.get_id() == id_territorio){
                                return t;
                        }
                }
                throw std::runtime_error("Jogador::get_territorio(uint16_t id_territorio): Não foi encontrado esse território em jogador " + _nome);
        }


        void Jogador::adicionar_territorio(Territorio territorio){
                for(auto& t : _territorios){
                        if(t.get_id() == territorio.get_id()){
                               throw std::runtime_error("Jogador::adicionar_territorio(Territorio territorio): Já existe esse território em jogador " + _nome);
                        }
                }
                _territorios.push_back(territorio);
        }


        void Jogador::sorteia_carta(){
                std::uniform_int_distribution<int> dist(97, 99);
                _cartas.push_back(dist(_gen));
        }

 
        unsigned int Jogador::trocar_cartas(){
                int count_a = 0;
                int count_b = 0;
                int count_c = 0;
                //conta as cartas de cada tipo
                for(int i : _cartas){
                        if(i == 'a'){
                                count_a++;
                        } else if(i == 'b'){
                                count_b++;
                        } else if(i == 'c'){
                                count_c++;
                        } else{
                                throw std::runtime_error("Jogador::trocar_cartas(): erro estranho...");
                        }
                }
                bool retorna = false;
                //se tem 3 cartas de 1 tipo qualquer:
                if(count_a >= 3){
                        count_a -= 3;
                        retorna = true;
                }
                if(count_b >= 3){
                        count_b -= 3;
                        retorna = true;
                }
                if(count_c >= 3){
                        count_c -= 3;
                        retorna = true;
                }

                //se tem 1 cartas de 3 tipo:
                if(count_a >= 1 && count_b >= 1 && count_c >= 1){
                        count_a--; count_b--; count_c--;
                        retorna = true;
                }

                //valores de retorno
                if(retorna){
                        switch (_rodada_cartas){
                                case 0: return 4;
                                case 1: return 6;
                                case 2: return 8;
                                case 3: return 10;
                                case 4: return 12;
                                default: return (_rodada_cartas-2)*5;
                        }
                }

                return 0;
        }

        
    void Jogador::info(){
        std::cout << "Jogador: " << _nome << "\nQuantidade de territorios: " << _territorios.size() << "\n\n";
        info_territorios();
    }

    void Jogador::info_territorios(){
        for(auto& t : _territorios){
           t.info();
        }
    }

