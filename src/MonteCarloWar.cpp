#include "MonteCarloWar.hpp"
#include "Jogador.hpp"
#include "Continente.hpp"   
#include "Divisa.hpp"   
#include "Territorio.hpp" 

#define Profundiadade 100
#define Tamanho_threads 1

    MonteCarloWar::MonteCarloWar(War& original)
        : _war(original){
        }

    void MonteCarloWar::encontrar_posicionamento(char player){
        
        struct data_pos {
            War war;
            int pontos_vitoria;

            data_pos()
                : war(0), pontos_vitoria(0) {
            }
            data_pos(const War& war)
                : war(war), pontos_vitoria(0) {
            }
        };

        std::vector<data_pos> resultados(Tamanho_threads);
        std::vector<std::thread> threads;

        for (int i = 0; i < Tamanho_threads; i++) {
            threads.emplace_back([i, player, war = _war, &resultados]() mutable{

                //Reseta o gerador de numeros aleatorios
                war.restart_gen();

                //Simula as posicições de forma aleatória
                war.simular_posicionar_tropas(player);

                //guarda o war em data
                data_pos data(war);

                //acaba a rodada desse player
                war.simular_multi_ataques(player);
                war.simular_reposicionar(player);

                //acaba as rodadas de outros players
                auto v = war.get_ordem_jogadores();
                for(auto& nome_j : v){
                    if(nome_j > player){
                        war.simular_posicionar_tropas(nome_j);
                        war.simular_multi_ataques(nome_j);
                        war.checa_jogadores();
                        war.simular_reposicionar(nome_j);
                    }
                }

                //faz o loop de simulações 
                for(int i = 0; i < Profundiadade; i++){
                    for(auto& nome_j : war.get_ordem_jogadores()){
                        war.simular_posicionar_tropas(nome_j);
                        try{
                            war.simular_multi_ataques(nome_j);
                        } catch(std::runtime_error& e){
                            std::cout << e.what() << std::endl;
                        }
                        war.checa_jogadores();
                        war.simular_reposicionar(nome_j);
                    }
                    //se ainda existe o jogador player então soma pontos_vitoria
                    for(auto& j : war.get_ordem_jogadores()){
                        if(j == player){
                            data.pontos_vitoria += war.calcular_pontos_vitoria(player);
                            break;
                        }
                    }
                }
                war.info_territorios();
                resultados[i] = data;
            });
        }

        for (auto& t : threads) {
            t.join();
        }

        data_pos maior_data;

        for(auto& data : resultados){
            if(data.pontos_vitoria > maior_data.pontos_vitoria){
                maior_data.pontos_vitoria = data.pontos_vitoria;
                maior_data.war = data.war;
            }
        }
        
        maior_data.war.info_territorios();
    }

    War* MonteCarloWar::get_war(){
        return &_war;
    }

    MonteCarloWar::~MonteCarloWar() = default;