#include "Jogador.hpp"
#include "Territorio.hpp"
#include "Divisa.hpp"

        
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
        const std::vector<std::string> Jogador::get_nome_territorios() const{
                std::vector<std::string> lista;
                for(auto& t : _territorios){
                        lista.push_back(t.get_nome());
                }
                return lista;
        }

        Territorio* Jogador::get_territorio(uint16_t id_territorio){
                for(auto& t : _territorios){
                        if(t.get_id() == id_territorio){
                                return &t;
                        }
                }
                throw std::runtime_error("Jogador::get_territorio(uint16_t id_territorio): Não foi encontrado esse território em jogador " + _nome);
        }

        Territorio* Jogador::get_territorio(const std::string& nome_territorio){
                for(auto& t : _territorios){
                        if(t.get_nome() == nome_territorio){
                                return &t;
                        }
                }
                throw std::runtime_error("Jogador::get_territorio(const std::string& nome_territorio): Não foi encontrado esse território em jogador " + _nome);
        }


        void Jogador::adicionar_territorio(Territorio territorio){
                for(auto& t : _territorios){
                        if(t.get_id() == territorio.get_id()){
                               throw std::runtime_error("Jogador::adicionar_territorio(Territorio territorio): Já existe esse território em jogador " + _nome);
                        }
                }
                _territorios.push_back(territorio);
        }

        Territorio Jogador::remover_territorio(uint16_t id_territorio) {
                for (auto it = _territorios.begin(); it != _territorios.end(); ++it) {
                        if (it->get_id() == id_territorio){
                                Territorio removido = *it;   // faz a cópia
                                _territorios.erase(it);      // remove do vetor
                                return removido;             // devolve a cópia
                        }
                }

                throw std::runtime_error("Jogador::remover_territorio(uint16_t id_territorio): Esse território não pertence ao jogador " + _nome);
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
        std::cout << "Jogador: " << _nome << "\nQuantidade de territorios: " << _territorios.size() << "\nTerritorios:\n";
        info_territorios();
    }

    void Jogador::info_territorios(){
        for(auto& t : _territorios){
           t.info();
        }
    }

        uint16_t Jogador::get_tropas(){
                return uint16_t(_territorios.size()/2) + trocar_cartas();
        }

        const std::vector<Territorio>& Jogador::get_territorios() const{
                return _territorios;
        }

        void Jogador::posicionar_tropa(uint16_t id_territorio, unsigned int quantidade){
                for(auto& t : _territorios){
                        if(t.get_id() == id_territorio){
                                t += quantidade;
                                return;
                        }
                }
                // throw std::runtime_error("Jogador::posicionar_tropa(uint16_t id_territorio, unsigned int quantidade) Território não encontrado");
        }


        void Jogador::posicionar_tropa(const std::string& nome_territorio, unsigned int quantidade){
                for(auto& t : _territorios){
                        if(t.get_nome() == nome_territorio){
                                t += quantidade;
                                return;
                        }
                }
                throw std::runtime_error("Jogador::posicionar_tropa(const std::string& nome_territorio, unsigned int quantidade) Território não encontrado");
        }

        void Jogador::reposicionar_tropa(const std::string& origem_territorio, const std::string& destino_territorio, unsigned int quantidade, const std::vector<Divisa>& divisas){
                Territorio* origem_t = nullptr;
                for(auto& t : _territorios){
                        if(t.get_nome() == origem_territorio){
                                origem_t = &t;
                                break;
                        }
                }
                if(origem_t == nullptr){
                        throw std::runtime_error("Jogador::reposicionar_tropa(const std::string& origem_territorio, ...): Jogador não possui territorio origem_territorio");
                }
                if(origem_t->get_num_tropas() - quantidade < 1){
                        throw std::runtime_error("Jogador::reposicionar_tropa(const std::string& origem_territorio, ...): Em origem_territorio, não há tropas suficientes para fazer o reposicionamento");              
                }

                Territorio* destino_t = nullptr;
                for(auto& t : _territorios){
                        if(t.get_nome() == destino_territorio){
                                destino_t = &t;
                                break;
                        }
                }
                if(destino_t == nullptr){
                        throw std::runtime_error("Jogador::reposicionar_tropa(..., const std::string& destino_territorio, ...): Jogador não possui territorio destino_territorio");
                }

                bool possui_adjacencia = false;

                for(auto& d : divisas){
                        if(d.tem_adjacencia(origem_t->get_id(), destino_t->get_id())){
                                possui_adjacencia = true;
                                break;
                        }
                }
                
                if(!possui_adjacencia){
                        throw std::runtime_error("Jogador::reposicionar_tropa(... divisas): Não há adjacencia");              
                }

                origem_t -= quantidade;
                destino_t += quantidade;

        }

        void Jogador::reposicionar_tropa(uint16_t id_origem_territorio, uint16_t id_destino_territorio, unsigned int quantidade, const std::vector<Divisa>& divisas){
                Territorio* origem_t = nullptr;
                for(auto& t : _territorios){
                        if(t.get_id() == id_origem_territorio){
                                origem_t = &t;
                                break;
                        }
                }
                if(origem_t == nullptr){
                        throw std::runtime_error("Jogador::reposicionar_tropa(const std::string& origem_territorio, ...): Jogador não possui territorio origem_territorio");
                }
                if(origem_t->get_num_tropas() - quantidade < 1){
                        throw std::runtime_error("Jogador::reposicionar_tropa(const std::string& origem_territorio, ...): Em origem_territorio, não há tropas suficientes para fazer o reposicionamento");              
                }

                Territorio* destino_t = nullptr;
                for(auto& t : _territorios){
                        if(t.get_id() == id_destino_territorio){
                                destino_t = &t;
                                break;
                        }
                }
                if(destino_t == nullptr){
                        throw std::runtime_error("Jogador::reposicionar_tropa(..., const std::string& destino_territorio, ...): Jogador não possui territorio destino_territorio");
                }

                bool possui_adjacencia = false;

                for(auto& d : divisas){
                        if(d.tem_adjacencia(origem_t->get_id(), destino_t->get_id())){
                                possui_adjacencia = true;
                                break;
                        }
                }
                
                if(!possui_adjacencia){
                        throw std::runtime_error("Jogador::reposicionar_tropa(... divisas): Não há adjacencia");              
                }

                origem_t -= quantidade;
                destino_t += quantidade;

        }

