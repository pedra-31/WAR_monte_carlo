#include "Edge.hpp"

        Edge::Edge(uint16_t id_v1, uint16_t id_v2):
            _v1(id_v1),
            _v2(id_v2){
        }

        uint16_t Edge::get_v1(){
            return _v1;
        }
        uint16_t Edge::get_v2(){
            return _v2;
        }

        bool Edge::has_vertice(uint16_t id){
            if(_v1 == id || _v2 == id){
                return true;
            } else {
                return false;
            }
        }

        Edge::~Edge(){

        }