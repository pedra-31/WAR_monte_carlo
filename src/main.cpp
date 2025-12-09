#include <iostream>
#include <sstream>
#include <string>

#include "War.hpp"
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
            std::cout << "\najuda/help - Mostra todos os comandos disponiveis\n" 
                << "";

        } else if(comando == "info"){
            main_war.info();
        } else if(comando == "info_territorios"){
            main_war.info_territorios();
        } else if(comando == "adicionar_tropas"){
            std::string nome_territorio; uint16_t quant_tropas;
            iss >> nome_territorio; iss >> quant_tropas;

            *main_war.get_territorio(nome_territorio) += quant_tropas;
            
        } else if(comando == "adicionar_tropas"){
            std::string nome_territorio; uint16_t quant_tropas;
            iss >> nome_territorio; iss >> quant_tropas;

            *main_war.get_territorio(nome_territorio) += quant_tropas;
        }
        
        
        
        
        
        
        else {
            std::cout << "comando invalido" << std::endl;
        }
    }

    return 0;
}
