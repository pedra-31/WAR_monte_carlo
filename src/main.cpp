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
                << "info - Mostra informações do jogo\n\n"
                << "info_territorios - Mostra informações dos territorios\n\n"
                << "territorio [territorio] - Mostra informação sobre um territorio especifico\n\n" 
                << "adicionar_tropas [territorio] [tropas] - \nAdiciona tropas em um certo territorio de nome [territorio] com [tropas] como quantidade de tropas\n\n"
                << "trocar_territorio [player] [territorio] - \nEntrega um territorio de nome [territorio] para o player de nome [player]\n\n"
                << "remove_cartas [player] [cartas] - \nRetira a quantidade [cartas] de cartas para o player de nome [player]\n\n";

        } else if(comando == "clear" || comando == "cls" || comando == "limpar"){
            for(int i = 0; i < 50; i++){
                std::cout << "\n";
            }

        } else if(comando == "info"){
            main_war.info();
            
        } else if(comando == "info_territorios" || comando == "info_territórios"){
            main_war.info_territorios();

        } else if(comando == "territorio" || comando == "território"){
            std::string nome_territorio; iss >> nome_territorio;
            Territorio* t = main_war.get_territorio(nome_territorio);

            if(t != nullptr){
                main_war.get_territorio(nome_territorio)->info();
            } else {
                std::cout << "Territorio nao encontrado\n";
            }

        } else if(comando == "adicionar_tropas"){
            std::string nome_territorio; unsigned int quant_tropas;
            iss >> nome_territorio; iss >> quant_tropas;
            *main_war.get_territorio(nome_territorio) += quant_tropas;

            std::cout << "Tropas adicionadas\n";

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
        
        } else if(comando == "TESTE"){
            MonteCarloWar mc_war(main_war);
            mc_war.encontrar_posicionamento('b', 100, 100);
            
        } else {
            std::cout << "comando invalido" << std::endl;
        }
    }

    return 0;
}
