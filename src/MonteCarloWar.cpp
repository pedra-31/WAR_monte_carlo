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

    void MonteCarloWar::simular_rodada(){
        return;
    }

    void MonteCarloWar::posicionar_tropas(char player){
        uint16_t num_tropas = _war.get_jogador(player)->get_tropas();
        auto v_adj = _war.get_id_territorios_adjacentes_com_inimigos(player);

        
        std::uniform_int_distribution<size_t> dist(0, v_adj.size() - 1);

        for(uint16_t i = 0; i < num_tropas; i++){
            _war.get_jogador(player)->posicionar_tropa(v_adj[dist(_gen)], 1);
        }
    }

    MonteCarloWar::~MonteCarloWar() = default;