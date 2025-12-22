#include "War.hpp"
#include "Territorio.hpp"
#include "Jogador.hpp"
#include "Divisa.hpp"
#include "Continente.hpp"

        War::War(int num_jogadores) :
        _gen(std::random_device{}()){
            ler_territorios("../data/territorios.txt", num_jogadores);
            ler_divisas("../data/divisas.txt");
            ler_continentes("../data/continentes.txt");   
        }

        void War::ler_territorios(const std::string& caminho, unsigned int num_jogadores){
            std::ifstream arq(caminho); 
            if (!arq) {
                throw std::runtime_error("Arquivo nao pode ser aberto: " + caminho + "\n");
            }

            std::string nome;
            uint16_t id;
            char player;
            for(unsigned int i = 0; i < num_jogadores; i++){
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

        std::vector<char> War::get_ordem_jogadores() const{
            std::vector<char> lista;

            for(auto& j : _jogadores){
                lista.push_back(j.get_nome());
            }

            return lista;
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
            throw std::runtime_error("War::get_jogador(char jogador): Não existe jogador com esse nome: " + jogador);
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
                std::cout << id_territorio << std::endl;
                return lista;
            }
        }

        std::vector<uint16_t> War::get_id_territorios_adjacentes_com_inimigos(char jogador){
            std::vector<uint16_t> lista;

            Jogador* j = this->get_jogador(jogador);
            auto t_jogador = j->get_id_territorios();

            if(t_jogador.empty()){
                return lista;
            }

            for(auto& t : t_jogador){ //t representa um id_territorio em _territorios de player
                for(auto& t_adj : this->get_id_territorios_adjacentes(t)){ //t_adj é o id_territorio adjacente de um t
                    if(
                        !(std::find(t_jogador.begin(), t_jogador.end(), t_adj) != t_jogador.end()) && //Se t_adj não é de player e 
                        !(std::find(lista.begin(), lista.end(), t) != lista.end()) //já não foi colocado na lista
                    ){
                        lista.push_back(t);
                    }
                }
            }

            return lista;
        }

        std::vector<Divisa> War::get_divisas_intessantes(char jogador){
            //achando a lista de "territorios interessantes"

            Jogador* j = this->get_jogador(jogador);
            auto territorios_jogador = j->get_id_territorios();
            std::vector<Territorio*> territorios_interessantes;

            for(auto& id_t : territorios_jogador){
                if(j->get_territorio(id_t)->get_num_tropas() > 1){
                    territorios_interessantes.push_back(j->get_territorio(id_t));
                }
            }

            std::vector<Divisa> divisas_interessantes;
            for(auto& d : _divisas){
                for(auto& t : territorios_interessantes){
                    if(
                        !(std::find(divisas_interessantes.begin(), divisas_interessantes.end(), d) != divisas_interessantes.end()) &&
                        (d.get_v1() == t->get_id() || d.get_v2() == t->get_id()) && 
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
            return _jogadores.size();
        }

        void War::checa_jogadores() {
            for (auto it = _jogadores.begin(); it != _jogadores.end(); ) {
                if (it->get_id_territorios().empty()) {
                    it = _jogadores.erase(it); // erase devolve o próximo iterador
                } else {
                    ++it;
                }
            }
        }


        void War::recebe_territorio(Jogador* j_atacante, Territorio* t_defesa) {
            //Testa se j_atacante já possui t_defesa
            for (auto& t_id : j_atacante->get_id_territorios()){
                if(t_id == t_defesa->get_id()){
                    throw std::runtime_error(
                        std::string("War::recebe_territorio: Jogador atacante já possui o territorio ")
                        + std::to_string(t_id)
                    );
                }
            }

            // 1️⃣ Descobre o defensor ANTES de alterar qualquer coisa
            Jogador* j_defesa = this->get_jogador(t_defesa->get_player());

            if (!j_defesa) {
                throw std::runtime_error("War::recebe_territorio: Jogador defensor nao encontrado");
            }

            // 2️⃣ Remove o território do defensor
            Territorio t = j_defesa->remover_territorio(t_defesa->get_id());

            //Setta as tropas para 1
            t.set_tropas(1);

            // 3️⃣ Atualiza o dono do território
            t.set_player(j_atacante->get_nome());

            // 4️⃣ Adiciona ao atacante
            j_atacante->adicionar_territorio(t);
        }


        void War::info(){
            std::cout << "players restantes:" << _jogadores.size() << "\n\n";
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

    unsigned int War::calcular_pontos_vitoria(char nome){
        return this->get_jogador(nome)->get_nome_territorios().size() + this->get_jogador(nome)->num_get_tropas();
    }

    void War::simular_posicionar_tropas(char player){
        uint16_t num_tropas = this->get_jogador(player)->get_tropas();
        //somando quantidade de tropas providas pelos continentes
        for(auto& c : _continentes){
            //AHHHHHHHHHHHHHHHHHHH essa função deveria ser para jogador e não contrário, mas WHAREVER, vai ficar assim
            if(c.possui_continente(this->get_jogador(player))){
                num_tropas += c.get_pontos_conquista();
            }
        }
        
        auto v_adj = this->get_id_territorios_adjacentes_com_inimigos(player);

        if(v_adj.empty()){
            return;
        }
        
        std::uniform_int_distribution<size_t> dist(0, v_adj.size() - 1);

        for(uint16_t i = 0; i < num_tropas; i++){
            this->get_jogador(player)->posicionar_tropa(v_adj[dist(_gen)], 1);
        }
    }

    void War::simular_atacar(char player){
        //se só existe 1 player para a operação
        if(get_num_jogadores() == 1){
            return;
        }

        //acho divisas_interessantes
        auto divisas_interessantes = this->get_divisas_intessantes(player);
        
        if(divisas_interessantes.empty()){
            return;
        }

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

            //função emcapetada kkkkkkkkk
            Jogador* j_atacante = this->get_jogador(t_ataque->get_player());

            // 1️⃣ Descobre o defensor ANTES de alterar qualquer coisa
            Jogador* j_defesa = this->get_jogador(t_defesa->get_player());

            if (!j_defesa) {
                throw std::runtime_error("War::recebe_territorio: Jogador defensor nao encontrado");
            }

            // 2️⃣ Remove o território do defensor
            Territorio t = j_defesa->remover_territorio(t_defesa->get_id());

            //Setta as tropas para 1
            t.set_tropas(1);

            // 3️⃣ Atualiza o dono do território
            t.set_player(j_atacante->get_nome());

            // 4️⃣ Adiciona ao atacante
            j_atacante->adicionar_territorio(t);

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

    void War::simular_multi_ataques(char player){
        //gera uma quantidade aleatoria de ataques para fazer
        std::uniform_int_distribution<uint16_t> dist5(0, ((uint16_t)this->get_jogador(player)->num_get_tropas()/2) - 1);
        for(int i = 0; i < dist5(_gen); i++){
            if(this->get_num_jogadores() == 1){
                return;
            }
            this->checa_jogadores();
            if(this->get_num_jogadores() == 1){
                return;
            } 
            this->simular_atacar(player);
        }
    }

    void War::simular_reposicionar(char player){
        Jogador * j = this->get_jogador(player);
        auto territorios_jogador = j->get_id_territorios();

        if (territorios_jogador.empty()){
            return;
        }
        
        std::vector<Territorio*> territorios_interessantes;
        for(auto& id_t : territorios_jogador){
            if(j->get_territorio(id_t)->get_num_tropas() > 1){
                territorios_interessantes.push_back(j->get_territorio(id_t));
            }
        }
        
        if (territorios_interessantes.empty()){
            return;
        }

        std::uniform_int_distribution<uint16_t> dist3(0, territorios_interessantes.size() - 1);


        Territorio* t = territorios_interessantes[dist3(_gen)];
        uint16_t t_id = t->get_id();
        
        //escolhe um numero aleatorio de vezes para fazer reposicionamentos
        int max_movimentos = t->get_num_tropas() - 1;
        std::uniform_int_distribution<int> dist_mov(1, max_movimentos);
        int n = dist_mov(_gen);
        
        for(int i = 0; i < n && t->get_num_tropas() > 1; i++){
            auto t_adjacentes = this->get_id_territorios_adjacentes(t_id);
            if (t_adjacentes.empty()) break;

            std::uniform_int_distribution<uint16_t> dist4(0, t_adjacentes.size() - 1);
            Territorio* t_adj = this->get_territorio(t_adjacentes[dist4(_gen)]);

            if(t_adj->get_player() != player){
                continue; // melhor que break
            }

            *t_adj += 1;
            *t -= 1;
        }

    }


        War::~War() = default;  