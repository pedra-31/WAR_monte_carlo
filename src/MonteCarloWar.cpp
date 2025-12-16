#include "MonteCarloWar.hpp"
#include "Jogador.hpp"
#include "Continente.hpp"   
#include "Divisa.hpp"   
#include "Territorio.hpp" 

    MonteCarloWar::MonteCarloWar(War& original)
        : _war(original), _gen(std::random_device{}()) {

        }

    War* MonteCarloWar::get_war(){
        return &_war;
    }

    void MonteCarloWar::posicionar_tropas(char player){
        uint16_t num_tropas = _war.get_jogador(player)->get_tropas();
        auto v_adj = _war.get_id_territorios_adjacentes_com_inimigos(player);

        
        std::uniform_int_distribution<size_t> dist(0, v_adj.size() - 1);

        for(uint16_t i = 0; i < num_tropas; i++){
            _war.get_jogador(player)->posicionar_tropa(v_adj[dist(_gen)], 1);
        }
    }

    void MonteCarloWar::atacar(char player){
        //acho divisas_interessantes
        auto divisas_interessantes = _war.get_divisas_intessantes(player); 

        //Sorteio uma divisa qualquer
        std::uniform_int_distribution<uint16_t> dist2(0, (uint16_t)divisas_interessantes.size() - 1);
        Divisa d_ataque = divisas_interessantes[dist2(_gen)];
        
        
        Territorio* t_ataque = _war.get_territorio(d_ataque.get_v1());
        Territorio* t_defesa = nullptr;
        
        //Se t_ataque é de player então v2 é o t_defesa
        if(t_ataque->get_player() == player){
            t_defesa = _war.get_territorio(d_ataque.get_v2());
        } else {
            //Se não, é só inverter, e v2 é o t_ataque
            t_defesa = t_ataque;
            t_ataque = _war.get_territorio(d_ataque.get_v2());
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
            _war.recebe_territorio(player, t_defesa->get_nome());

            //Comportamento estranho... esse t_defesa fica apontando para o lugar "errado"
            t_defesa = _war.get_territorio(id_defesa);
            t_ataque = _war.get_territorio(id_ataque);
            
            if(t_ataque->get_num_tropas() <= 3){
                *t_defesa += t_ataque->get_num_tropas()-2;
                *t_ataque -= t_ataque->get_num_tropas()-1;
            } else {
                *t_defesa += 2;
                *t_ataque -= 3;
            }
        }
    }

    void MonteCarloWar::reposicionar(char player){
        Jogador * j = _war.get_jogador(player);
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
            auto t_adjacentes = _war.get_id_territorios_adjacentes(t_id);
            std::uniform_int_distribution<uint16_t> dist4(0, (uint16_t)t_adjacentes.size() - 1);
            
            //escolhe um territorio adj para reposicionar
            Territorio* t_adj = _war.get_territorio(t_adjacentes[dist4(_gen)]);

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

    MonteCarloWar::~MonteCarloWar() = default;