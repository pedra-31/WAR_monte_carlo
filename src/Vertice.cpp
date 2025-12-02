#include "Vertice.hpp"



        Vertice::Vertice(uint16_t id_vertice, std::string nome, char player, unsigned int num_tropas) 
            : _id_vertice(id_vertice),
            _nome(nome),
            _player(player),
            _num_tropas(num_tropas){
        }

        uint16_t Vertice::get_id(){
            return _id_vertice;
        }
        std::string Vertice::get_nome(){
            return _nome;
        }
        char Vertice::get_player(){
            return _player;
        }
        unsigned int Vertice::get_num_tropas(){
            return _num_tropas;
        }

        void Vertice::set_player(char novo_player){
            _player = novo_player;
        }
        void Vertice::set_tropas(unsigned int numero){
            if(numero < 1){
                throw std::runtime_error("Vertice error: Em set_tropas(unsigned int numero), numero (parametro) deve ser MAIOR que 1");
            }
            _num_tropas = numero;
        }
        
        void Vertice::info(){
            std::cout << "Id: " << _id_vertice << " "
                << "Nome: " << _nome << std::endl
                << "Player: " << _player << " "
                << "Quantidade de tropas: " << _num_tropas << std::endl;

        }

        Vertice& Vertice::operator+=(unsigned int x) {
            _num_tropas += x;
            return *this;
        }

        Vertice& Vertice::operator-=(unsigned int x) {
            if (_num_tropas - x < 1){
                throw std::runtime_error("Vertice error: Em operator-=(unsigned int x), ao final da operação DEVE conter pelo menor 1 tropa posicionada em cada vértice");
            }
            
            _num_tropas -= x;
            return *this;
        }

        Vertice::~Vertice(){

        }
