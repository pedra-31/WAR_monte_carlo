#include "Jogador.hpp"
#include "Territorio.hpp"

        Jogador::Jogador(char nome) : _nome(nome){

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
                               throw std::runtime_error("Jogador::adicionar_territorio(Territorio territorio): Não foi encontrado esse território em jogador " + _nome);
                        }
                }
        }


        void Jogador::adicionar_cartas(){

        }

 
        unsigned int Jogador::trocar_cartas(){

        }


        void Jogador::info(){
                
        }
