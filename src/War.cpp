#include "War.hpp"
#include "Territorio.hpp"
#include "Jogador.hpp"
#include "Divisa.hpp"
#include "Continente.hpp"

        War::War(int num_jogadores) :
        _gen(std::random_device{}()),
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

        Territorio* War::get_territorio(uint16_t id_territorio){
            for(auto& j : _jogadores){
                try{
                    return j.get_territorio(id_territorio);
                } catch(const std::runtime_error& e){

                } catch(...){
                    std::cout << "Erro inesperado em War::get_territorio(uint16_t id_territorio)\n";
                }
            }
            return nullptr;
        }

        Territorio* War::get_territorio(const std::string& nome){
            for(auto& j : _jogadores){
                try{
                    return j.get_territorio(nome);
                } catch(const std::runtime_error& e){

                }  catch(...){
                    std::cout << "Erro inesperado em War::get_territorio(const std::string& nome)\n";
                }
            }
            return nullptr;
        }

        Jogador* War::get_jogador(char jogador){
            for(auto& j : _jogadores){
                if(j.get_nome() == jogador){
                    return &j;
                }
            }
            throw std::runtime_error("War::get_jogador(char jogador): Não existe jogador com esse nome");
        }

        std::vector<uint16_t> War::get_id_territorios_adjacentes(uint16_t id_territorio){
            std::vector<uint16_t> lista;

            for(auto& d : _divisas){
                if(d.tem_territorio(id_territorio)){
                    if(d.get_v1() == id_territorio){
                        lista.push_back(d.get_v2());
                    } else {
                        lista.push_back(d.get_v1());
                    }
                }
            }

            if(!lista.empty()){
                return lista;
            } else {
                throw std::runtime_error("War::get_id_territorios_adjacentes(uint16_t id_territorio): id_territorio nao e um territorio valido");
            }
        }

        std::vector<uint16_t> War::get_id_territorios_adjacentes_com_inimigos(char jogador){
            std::vector<uint16_t> lista;

            Jogador* j = this->get_jogador(jogador);
            auto t_jogador = j->get_id_territorios();

            for(auto& t : j->get_id_territorios()){ //t representa um id_territorio em _territorios de player
                for(auto& t_adj : this->get_id_territorios_adjacentes(t)){ //t_adj é o id_territorio adjacente de um t
                    if(
                        !(std::find(t_jogador.begin(), t_jogador.end(), t_adj) != t_jogador.end()) && //Se t_adj não é de player e 
                        !(std::find(lista.begin(), lista.end(), t) != lista.end()) //já não foi colocado na lista
                    ){
                        lista.push_back(t);
                    }
                }
            }
            if(!lista.empty()){
                return lista;
            } else {
                throw std::runtime_error("War::get_id_territorios_adjacentes_com_inimigos(char jogador): Algum erro estranho");
            }
        }

        std::vector<Divisa> War::get_divisas_intessantes(char jogador){
            //achando a lista de "territorios interessantes"

            Jogador* j = this->get_jogador(jogador);
            auto territorios_jogador = j->get_territorios();
            std::vector<Territorio> territorios_interessantes;
            for(auto& t : territorios_jogador){
                if(t.get_num_tropas() > 1){
                    territorios_interessantes.push_back(t);
                }
            }

            std::vector<Divisa> divisas_interessantes;
            for(auto& d : _divisas){
                for(auto& t : territorios_interessantes){
                    if(
                        !(std::find(divisas_interessantes.begin(), divisas_interessantes.end(), d) != divisas_interessantes.end()) &&
                        (d.get_v1() == t.get_id() || d.get_v2() == t.get_id()) && 
                        ((this->get_territorio(d.get_v1())->get_player() == jogador && this->get_territorio(d.get_v2())->get_player() != jogador) || 
                        (this->get_territorio(d.get_v1())->get_player() != jogador && this->get_territorio(d.get_v2())->get_player() == jogador))
                    ){
                        divisas_interessantes.push_back(d);
                    }
                }
            }

            return divisas_interessantes;
        }   

        unsigned int War::get_num_jogadores(){
            return _num_jogadores;
        }



        void War::recebe_territorio(char nome_atacante, const std::string& nome_territorio_defensor){
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
                        territorio.set_player(j_atacante->get_nome());
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

        void War::restart_gen(){
            std::random_device rd;
            _gen.seed(rd());
        }

        void War::restart_gen(uint32_t seed){
            _gen.seed(seed);
        }

    void War::simular_posicionar_tropas(char player){
        uint16_t num_tropas = this->get_jogador(player)->get_tropas();
        auto v_adj = this->get_id_territorios_adjacentes_com_inimigos(player);

        
        std::uniform_int_distribution<size_t> dist(0, v_adj.size() - 1);

        for(uint16_t i = 0; i < num_tropas; i++){
            this->get_jogador(player)->posicionar_tropa(v_adj[dist(_gen)], 1);
        }
    }

    void War::simular_atacar(char player){
        //acho divisas_interessantes
        auto divisas_interessantes = this->get_divisas_intessantes(player); 

        //Sorteio uma divisa qualquer
        std::uniform_int_distribution<uint16_t> dist2(0, (uint16_t)divisas_interessantes.size() - 1);
        Divisa d_ataque = divisas_interessantes[dist2(_gen)];
        
        
        Territorio* t_ataque = this->get_territorio(d_ataque.get_v1());
        Territorio* t_defesa = nullptr;
        
        //Se t_ataque é de player então v2 é o t_defesa
        if(t_ataque->get_player() == player){
            t_defesa = this->get_territorio(d_ataque.get_v2());
        } else {
            //Se não, é só inverter, e v2 é o t_ataque
            t_defesa = t_ataque;
            t_ataque = this->get_territorio(d_ataque.get_v2());
        }

        //Se existe desvantagem forte recua o ataque
        if(t_ataque->get_num_tropas() + 3 < t_defesa->get_num_tropas()){
            return;
        }
        
        std::uniform_real_distribution<double> uniform{0.0, 1.0};
        double x = uniform(_gen);

        uint16_t A; uint16_t D;

        if(t_ataque->get_num_tropas() <= 3){
            A = t_ataque->get_num_tropas() - 1;
        } else {
            A = 3;
        }

        if(t_defesa->get_num_tropas() <= 3){
            D = t_defesa->get_num_tropas();
        } else {
            D = 3;
        }

        // Fanfic: A3 vs D3
        if (A == 3 && D == 3) {
            if (x < 0.3497){ //resultado = ResultadoRodada::A_perde_3;
                *t_ataque -= 3;

            } else if (x < 0.3497 + 0.2953){ //resultado = ResultadoRodada::A_perde_2_D_perde_1;
                *t_ataque -= 2;  *t_defesa -= 1; 

            } else if (x < 0.3497 + 0.2953 + 0.2248){ //resultado = ResultadoRodada::A_perde_1_D_perde_2;
                *t_ataque -= 1;  *t_defesa -= 2; 

            } else { //resultado = ResultadoRodada::D_perde_3;
                *t_defesa -= 3; 
            } 
        }

        // A2 vs D3
        else if (A == 2 && D == 3) {
            if (x < 0.4483) {                 // A perde 2
                *t_ataque -= 2;

            } else if (x < 0.4483 + 0.3241) { // A perde 1 / D perde 1
                *t_ataque -= 1;
                *t_defesa -= 1;

            } else {                          // D perde 2
                *t_defesa -= 2;
            }
        }

        // A1 vs D3
        else if (A == 1 && D == 3) {
            if (x < 0.8264) { // atacante perde 1
                *t_ataque -= 1;
            } else {          // defensor perde 1
                *t_defesa -= 1;
            }
        }

        // Restante dos casos (War clássico)
        // A3 vs D2
        else if (A == 3 && D == 2) {
            if (x < 0.2929) {//resultado = ResultadoRodada::A_perde_2;
                *t_ataque -= 2;
            
            } else if (x < 0.2929 + 0.3358) {//resultado = ResultadoRodada::A_perde_1_D_perde_1;
                *t_ataque -= 1; *t_defesa -= 1;
            
            } else {//resultado = ResultadoRodada::D_perde_2;
                *t_defesa -= 2;
            
            }
        }

        // A2 vs D2
        else if (A == 2 && D == 2) {
            if (x < 0.2276) { //resultado = ResultadoRodada::A_perde_2;
                *t_ataque -= 2;

            } else if (x < 0.2276 + 0.3240) { //resultado = ResultadoRodada::A_perde_1_D_perde_1;
                *t_ataque -= 1; *t_defesa -= 1;

            } else { //resultado = ResultadoRodada::D_perde_2;
                *t_defesa -= 2;
            
            }
        }

        // A3/A2 vs D1
        else if ((A == 3 || A == 2) && D == 1) {
            if (x < 0.3403) {  // atacante perde 1
                *t_ataque -= 1;

            } else {           // defensor perde 1
                *t_defesa -= 1;

            }
        }

        // A1 vs D1
        else  if (A == 1 && D == 1) {
            if (x < 0.4167) {//resultado = ResultadoRodada::A_perde_1;
                *t_ataque -= 1;

            } else { //resultado = ResultadoRodada::D_perde_1
                *t_defesa -= 1;
            }
        }

        if(t_defesa->get_num_tropas() == 0){
            uint16_t id_defesa = t_defesa->get_id();
            uint16_t id_ataque = t_ataque->get_id();

            //Função emcapetada consertar depois
            this->recebe_territorio(player, t_defesa->get_nome());

            //Comportamento estranho... esse t_defesa fica apontando para o lugar "errado"
            t_defesa = this->get_territorio(id_defesa);
            t_ataque = this->get_territorio(id_ataque);
            
            if(t_ataque->get_num_tropas() <= 3){
                *t_defesa += t_ataque->get_num_tropas()-2;
                *t_ataque -= t_ataque->get_num_tropas()-1;
            } else {
                *t_defesa += 2;
                *t_ataque -= 3;
            }
        }
    }

    void War::simular_reposicionar(char player){
        Jogador * j = this->get_jogador(player);
        auto territorios_jogador = j->get_territorios();

        std::vector<Territorio*> territorios_interessantes;
        for(auto& t : territorios_jogador){
            if(t.get_num_tropas() > 1){
                territorios_interessantes.push_back(&t);
            }
        }

        std::uniform_int_distribution<uint16_t> dist3(0, territorios_interessantes.size() - 1);


        Territorio* t = territorios_interessantes[dist3(_gen)];
        uint16_t t_id = t->get_id();
        
        //escolhe um numero aleatorio de vezes para fazer reposicionamentos
        int n = dist3(_gen);
        for(int i = 0; i < n; i++){
            auto t_adjacentes = this->get_id_territorios_adjacentes(t_id);
            std::uniform_int_distribution<uint16_t> dist4(0, (uint16_t)t_adjacentes.size() - 1);
            
            //escolhe um territorio adj para reposicionar
            Territorio* t_adj = this->get_territorio(t_adjacentes[dist4(_gen)]);

            //Se não for de player, que pena
            if(t_adj->get_player() != player){
                break;
            }

            *t_adj += 1;
            *t -= 1;

            std::cout << "---------------------------------\n";
            t->info(); t_adj->info();
            std::cout << "---------------------------------\n";
        }
    }

        War::~War() = default;  