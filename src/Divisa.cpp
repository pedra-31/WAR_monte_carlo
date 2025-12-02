#include "Divisa.hpp"

        Divisa::Divisa(uint16_t id_v1, uint16_t id_v2):
            _v1(id_v1),
            _v2(id_v2){
        }

        uint16_t Divisa::get_v1() const{
            return _v1;
        }
        uint16_t Divisa::get_v2() const{
            return _v2;
        }

        bool Divisa::tem_territorio(uint16_t id_vertice) const{
            if(_v1 == id_vertice || _v2 == id_vertice){
                return true;
            } else {
                return false;
            }
        }

        Divisa::~Divisa(){

        }