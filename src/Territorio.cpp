#include "Territorio.hpp"



        Territorio::Territorio(uint16_t id_Territorio, std::string nome, char player, unsigned int num_tropas) 
            : _id_Territorio(id_Territorio),
            _nome(nome),
            _player(player),
            _num_tropas(num_tropas){
        }

        uint16_t Territorio::get_id() const{
            return _id_Territorio;
        }
        std::string Territorio::get_nome() const{
            return _nome;
        }
        char Territorio::get_player() const{
            return _player;
        }
        unsigned int Territorio::get_num_tropas() const{
            return _num_tropas;
        }

        void Territorio::set_player(char novo_player){
            _player = novo_player;
        }
        void Territorio::set_tropas(unsigned int numero){
            if(numero < 1){
                throw std::runtime_error("Territorio::set_tropas(uint16_t numero): numero (parametro) deve ser MAIOR que 1");
            }
            _num_tropas = numero;
        }
        
        void Territorio::info() const{
            std::cout << "Id: " << _id_Territorio << " "
                << "Nome: " << _nome << " "
                << "Player: " << _player << " "
                << "Num. tropas: " << _num_tropas << std::endl;

        }

        Territorio& Territorio::operator+=(unsigned int x) {
            _num_tropas += x;
            return *this;
        }

        Territorio& Territorio::operator-=(unsigned int x) {
            _num_tropas -= x;
            return *this;
        }
