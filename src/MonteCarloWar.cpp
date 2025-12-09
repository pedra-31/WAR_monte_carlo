#include "MonteCarloWar.hpp"
#include "Jogador.hpp"

    MonteCarloWar::MonteCarloWar(const War& war_original)
        : _war(war_original) {}

    void MonteCarloWar::simular_rodada(){
        return;
    }

    void MonteCarloWar::posicionar_tropas(char player){
        uint16_t num_tropas = _war.get_jogador(player).get_tropas();
    }
