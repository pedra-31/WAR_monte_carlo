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

    MonteCarloWar::~MonteCarloWar() = default;