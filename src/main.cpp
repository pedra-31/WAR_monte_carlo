#include <iostream>
#include <sstream>
#include <string>

#include "MonteCarloWar.hpp"
#include "Jogador.hpp"
#include "War.hpp"
#include "Continente.hpp"   
#include "Divisa.hpp"   
#include "Territorio.hpp" 


int main() {

    War main_war(2);

    std::string linha;
    std::string comando;
        
    while (std::getline(std::cin, linha)) {
        std::istringstream iss(linha);
        if (!(iss >> comando)) {
            continue;
        }


        if(comando == "ajuda" || comando == "help"){
            std::cout << "\najuda/help - Mostra todos os comandos disponiveis\n\n" 
                << "clear/cls/limpar - Limpa a tela do console\n\n"
                << "info - Mostra informacoes do jogo\n\n"
                << "info_territorios - Mostra informacoes dos territorios\n\n"
                << "territorio [territorio] - Mostra informacao sobre um territorio especifico\n\n" 
                << "set_tropas [territorio] [tropas] - \nMuda a quantidade de tropas em um certo territorio de nome [territorio] para [tropas]\n\n"
                << "adicionar_tropas [territorio] [tropas] - \nAdiciona tropas em um certo territorio de nome [territorio] com [tropas] como quantidade de tropas\n\n"
                << "trocar_territorio [player] [territorio] - \nEntrega um territorio de nome [territorio] para o player de nome [player]\n\n"
                << "remove_cartas [player] [cartas] - \nRetira a quantidade [cartas] de cartas para o player de nome [player]\n\n"
                << "encontrar_pos [player] - \nEncontra o melhor posicionamento para a jogada atual de [player]\n\n"
                << "encontrar_ataque [player] - \nEncontra o melhor ataque para a jogada atual de [player]\n\n"
                << "encontrar_repos [player] - \nEncontra o melhor reposicionamento para a jogada atual de [player]\n\n";

        } else if(comando == "clear" || comando == "cls" || comando == "limpar"){
            for(int i = 0; i < 50; i++){
                std::cout << "\n";
            }

        } else if(comando == "info"){
            main_war.info();
            
        } else if(comando == "info_territorios" || comando == "info_territórios"){
            main_war.info_territorios();

        } else if(comando == "territorio"){
            std::string nome_territorio; iss >> nome_territorio;
            try{
                main_war.get_territorio(nome_territorio)->info();
            } catch (std::runtime_error& e){
                std::cout << "Territorio nao encontrado\n";
            }

        } else if(comando == "adicionar_tropas"){
            std::string nome_territorio; unsigned int quant_tropas;
            iss >> nome_territorio; iss >> quant_tropas;
            try{
                (*main_war.get_territorio(nome_territorio)) += quant_tropas;
                std::cout << "Tropas adicionadas\n";
            } catch(std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
            }

        } else if(comando == "set_tropas"){
            std::string nome_territorio; unsigned int quant_tropas;
            iss >> nome_territorio; iss >> quant_tropas;
            try{
                main_war.get_territorio(nome_territorio)->set_tropas(quant_tropas);
                std::cout << "Tropas settadas para: " <<  main_war.get_territorio(nome_territorio)->get_num_tropas() << "\n";
            
            } catch(std::runtime_error& e){
                std::cout << std::endl << e.what() << std::endl;
            }

        } else if(comando == "trocar_territorio"){
            char nome_player; std::string nome_territorio;
            
            if (!(iss >> nome_player) || !(iss >> nome_territorio)) {
                std::cout << "Input inválido\n";
            } else {
                try{
                    Territorio* t = main_war.get_territorio(nome_territorio);
                    Jogador* j = main_war.get_jogador(nome_player);
                    main_war.recebe_territorio(j, t);
                    std::cout << "Operacao concluida, territorio atualizado\n";
                } catch(const std::runtime_error& e){
                    std::cout << e.what() <<"\n";
                }
            }

        } else if(comando == "sorteia_cartas"){
            char nome_player;
            
            if (!(iss >> nome_player)) {
                std::cout << "Input inválido\n";
            } else {
                try{
                    Jogador* j = main_war.get_jogador(nome_player);
                    j->sorteia_carta();
                    std::cout << "Carta adicionada" << std::endl;
                } catch(std::runtime_error& e){
                    std::cout << e.what() << std::endl;
                }
            }            

        } else if(comando == "remove_cartas"){
            char nome_player; unsigned int num_cartas;
            
            if (!(iss >> nome_player) || !(iss >> num_cartas)) {
                std::cout << "Input inválido\n";
            } else {
                try{
                    Jogador* j = main_war.get_jogador(nome_player);
                    j->remove_cartas(num_cartas);
                    std::cout << "Cartas foi settada para " << j->get_num_cartas() << std::endl;
                } catch(std::runtime_error& e){
                    std::cout << e.what() << std::endl;
                }
            }
        
        } else if(comando == "encontrar_pos"){
            char nome_player;
            if (!(iss >> nome_player)) {
                std::cout << "Input inválido\n";
            }
            try{
                main_war.get_jogador(nome_player);
                MonteCarloWar mc_war(main_war);
                War war_temp = mc_war.encontrar_posicionamento(nome_player, 50, 1000);
                std::cout << "Aceita posicionamento? (S/N) ";
                std::string reposta; std::cin >> reposta;
                if(reposta == "S" || reposta == "s"){
                    main_war = war_temp;
                }
            } catch(std::runtime_error& e){
                std::cout << "Player invalido\n";
            }
        } else if(comando == "encontrar_ataque"){
            char nome_player;
            if (!(iss >> nome_player)) {
                std::cout << "Input inválido\n";
            }
            try{
                main_war.get_jogador(nome_player);
                MonteCarloWar mc_war(main_war);
                mc_war.encontrar_ataque(nome_player, 30, 700);
            } catch(std::runtime_error& e){
                std::cout << "Player invalido\n";
            }
        
        } else if(comando == "encontrar_repos"){
            char nome_player;
            if (!(iss >> nome_player)) {
                std::cout << "Input inválido\n";
            }
            try{
                main_war.get_jogador(nome_player);
                MonteCarloWar mc_war(main_war);
                War war_temp = mc_war.encontrar_reposicionamento(nome_player, 30, 300);
                std::cout << "Aceita posicionamento? (S/N) ";
                std::string reposta; std::cin >> reposta;
                if(reposta == "S" || reposta == "s"){
                    main_war = war_temp;
                }
            } catch(std::runtime_error& e){
                std::cout << "Player invalido\n";
            }
        } else if(comando == "TESTE"){

        } else {
            std::cout << "comando invalido" << std::endl;
        }
    }

    return 0;
}
