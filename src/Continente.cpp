#include "Continente.hpp"
#include "Jogador.hpp"

        Continente::Continente(std::string nome, unsigned int pontos_conquista, std::vector<uint16_t> vertices):
        _nome(nome),
        _pontos_conquista(pontos_conquista),
        _vertices(vertices){

        }

        unsigned int Continente::get_pontos_conquista() const{
            return _pontos_conquista;
        }
        const std::vector<uint16_t>& Continente::get_vertices() const{
            return _vertices;
        }

        const std::string& Continente::get_nome() const{
            return _nome;
        }

        bool Continente::possui_continente(Jogador* j) const{
            const std::vector<uint16_t>& v =  j->get_id_territorios();
            // Conta quantos vértices do continente aparecem no vetor v
            unsigned int count = 0;

            for (auto id_cont : _vertices) {
                if (std::find(v.begin(), v.end(), id_cont) != v.end()) {
                    count++;
                }
            }

            // true se TODOS os vértices do continente estão em v
            return count == _vertices.size();
        }


        void Continente::info(){
            std::cout << "Nome: " << _nome << " Pontos conquista: " << _pontos_conquista << "\n" 
                << "Vertices: ";
            for(int i : _vertices){
                std::cout << i << " ";
            }
            std::cout << "\n\n";
        }
