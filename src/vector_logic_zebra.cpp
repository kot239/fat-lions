#include "vector_logic_zebra.h"

//bool get_sexcd() {
//     return this->sexcd == CD_SEX_TIME;
// }

//шаблонная проверка условия

int VectorLogicLion::dist(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); 
}
//Katya loh, Olesya lazha, A ya parasha
void VectorLogicLion::find_target(Animal::Zebra cur_zebra) {
    if (cur_zebra.get_age() >= MAX_AGE || cur_zebra.get_hunger() == 0) {
        //как удалять, если умер?
        //можно enum в классе животных
    }
    
    int res_x = cur_zebra.get_pos().x_, res_y = cur_zebra.get_pos().y_;

    for (auto lion : lions_array) {
        res_x += lion.get_pos().x_;
        res_y += lion.get_pos().y_;
    }
    bool sex_flag = true;
    if (res_x != cur_zebra.get_pos().x_ ||
        res_y != cur_zebra.get_pos().y_) {
       //установить направление
        //cur_zebra.get_dir().x_ = ge;
        //res_y = cur_zebra.get_dir().y_;
        sex_flag = false;
    }
    if (sex_flag) {
        
    }



}

void move (Animal::Zebra cur_zebra) {
    //??
    //поговорить про функцию проверки, временное вычисления в даблах и т д
}