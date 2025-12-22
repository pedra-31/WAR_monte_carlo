#include "MonteCarloWar.hpp"
#include "Jogador.hpp"
#include "Continente.hpp"   
#include "Divisa.hpp"   
#include "Territorio.hpp" 

    MonteCarloWar::MonteCarloWar(War& original)
        : _war(original){
        }

    War MonteCarloWar::encontrar_posicionamento(char player, unsigned int profundiadade, unsigned int tamanho_threads){
        
        if(tamanho_threads < 1 || profundiadade < 1){
            return War(0);
        }

        struct data_pos {
            War war;
            unsigned int pontos_vitoria;

            data_pos()
                : war(0), pontos_vitoria(0) {
            }
            data_pos(const War& war)
                : war(war), pontos_vitoria(1) {
            }
        };

        std::vector<data_pos> resultados(tamanho_threads);
        std::vector<std::thread> threads;

        for (unsigned int i = 0; i < tamanho_threads; i++) {
            threads.emplace_back([&, i, profundiadade, player]() {
                War war = _war; // cópia explícita aqui

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
                        war.simular_reposicionar(nome_j);
                    }
                }

                //faz o loop de simulações 
                for(unsigned int i = 0; i < profundiadade; i++){
                    for(auto& nome_j : war.get_ordem_jogadores()){
                        if(war.get_num_jogadores() == 1){
                            break;
                        } 
                        war.simular_posicionar_tropas(nome_j);
                        war.simular_multi_ataques(nome_j);
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

                // std::cout << data.pontos_vitoria << "\n";
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

        std::cout << "Pontos vitoria da thrend: " << maior_data.pontos_vitoria << "\n";
        maior_data.war.info_territorios();

        return maior_data.war;
    }

    void MonteCarloWar::encontrar_ataque(char player, unsigned int profundiadade, unsigned int tamanho_threads){
        
        if(tamanho_threads < 1 || profundiadade < 1){
            return;
        }

        struct data_pos {
            War war;
            unsigned int pontos_vitoria;
            Divisa divisa;

            data_pos()
                : war(0), pontos_vitoria(0), divisa(Divisa(0,0)){
            }
            data_pos(const War& war, Divisa divisa)
                : war(war), pontos_vitoria(1), divisa(divisa) {
            }
        };

        std::vector<data_pos> resultados(tamanho_threads);
        std::vector<std::thread> threads;

        for (unsigned int i = 0; i < tamanho_threads; i++) {
            threads.emplace_back([&, i, profundiadade, player]() {
                War war = _war; // cópia explícita aqui

                //Reseta o gerador de numeros aleatorios
                war.restart_gen();

                //Simula 1 ataque de forma aleatória e usa a função para retornar o ataque
                Divisa d = war.simular_atacar_divisa(player);

                //guarda o war em data
                data_pos data(war, d);

                //acaba a rodada desse player
                war.simular_multi_ataques(player);
                war.simular_reposicionar(player);

                //acaba as rodadas de outros players
                auto v = war.get_ordem_jogadores();
                for(auto& nome_j : v){
                    if(nome_j > player){
                        war.simular_posicionar_tropas(nome_j);
                        war.simular_multi_ataques(nome_j);
                        war.simular_reposicionar(nome_j);
                    }
                }

                //faz o loop de simulações 
                for(unsigned int i = 0; i < profundiadade; i++){
                    for(auto& nome_j : war.get_ordem_jogadores()){
                        if(war.get_num_jogadores() == 1){
                            break;
                        } 
                        war.simular_posicionar_tropas(nome_j);
                        war.simular_multi_ataques(nome_j);
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

                // std::cout << data.pontos_vitoria << "\n";
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
                maior_data.divisa = data.divisa;
                maior_data.war = data.war;
            }
        }

        std::cout << "Pontos vitoria da thrend: " << maior_data.pontos_vitoria << "\n";
        std::cout << "Divisa atacada: "; maior_data.divisa.info();
        maior_data.war.info_territorios();
    }

    War MonteCarloWar::encontrar_reposicionamento(char player, unsigned int profundiadade, unsigned int tamanho_threads){
        
        if(tamanho_threads < 1 || profundiadade < 1){
            return War(0);
        }

        struct data_pos {
            War war;
            unsigned int pontos_vitoria;

            data_pos()
                : war(0), pontos_vitoria(0) {
            }
            data_pos(const War& war)
                : war(war), pontos_vitoria(1) {
            }
        };

        std::vector<data_pos> resultados(tamanho_threads);
        std::vector<std::thread> threads;

        for (unsigned int i = 0; i < tamanho_threads; i++) {
            threads.emplace_back([&, i, profundiadade, player]() {
                War war = _war; // cópia explícita aqui

                //Reseta o gerador de numeros aleatorios
                war.restart_gen();

                //Simula as reposicições de forma aleatória
                war.simular_reposicionar(player);

                //guarda o war em data
                data_pos data(war);

                //acaba as rodadas de outros players
                auto v = war.get_ordem_jogadores();
                for(auto& nome_j : v){
                    if(nome_j > player){
                        war.simular_posicionar_tropas(nome_j);
                        war.simular_multi_ataques(nome_j);
                        war.simular_reposicionar(nome_j);
                    }
                }

                //faz o loop de simulações 
                for(unsigned int i = 0; i < profundiadade; i++){
                    for(auto& nome_j : war.get_ordem_jogadores()){
                        if(war.get_num_jogadores() == 1){
                            break;
                        } 
                        war.simular_posicionar_tropas(nome_j);
                        war.simular_multi_ataques(nome_j);
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

                // std::cout << data.pontos_vitoria << "\n";
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

        std::cout << "Pontos vitoria da thrend: " << maior_data.pontos_vitoria << "\n";
        maior_data.war.info_territorios();

        return maior_data.war;
    }

    War* MonteCarloWar::get_war(){
        return &_war;
    }

    MonteCarloWar::~MonteCarloWar() = default;