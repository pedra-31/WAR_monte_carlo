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
                << "info_territorios - Mostra informações do territorio\n\n"
                << "adicionar_tropas [territorio] [tropas] - \nAdiciona tropas em um certo territorio de nome [territorio] com [tropas] como quantidade de tropas\n\n"
                << "trocar_territorio [player] [territorio] - \nEntrega um territorio de nome [territorio] para o player de nome [player]\n\n";

        } else if(comando == "clear" || comando == "cls" || comando == "limpar"){
            for(int i = 0; i < 50; i++){
                std::cout << "\n";
            }

        } else if(comando == "info"){
            main_war.info();
            
        } else if(comando == "info_territorios"){
            main_war.info_territorios();

        } else if(comando == "adicionar_tropas"){
            std::string nome_territorio; uint16_t quant_tropas;
            iss >> nome_territorio; iss >> quant_tropas;
            *main_war.get_territorio(nome_territorio) += quant_tropas;

        } else if(comando == "trocar_territorio"){
            char nome_player; std::string nome_territorio;
            iss >> nome_player; iss >> nome_territorio;
            try{
                main_war.recebe_territorio(nome_player, nome_territorio);
            } catch(const std::runtime_error& e){
                std::cout << e.what() <<"\n";
            }
        } else if(comando == "TESTE"){
            MonteCarloWar mc_war(main_war);
            mc_war.get_war()->info_territorios();
            mc_war.posicionar_tropas('a');
            mc_war.get_war()->info_territorios();
            
        } else {
            std::cout << "comando invalido" << std::endl;
        }
    }

    return 0;
}
