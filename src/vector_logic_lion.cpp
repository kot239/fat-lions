#include "vector_logic_lion.h"

// bool get_sexcd() {
//     return this->sexcd == CD_SEX_TIME;
// }

//шаблонная проверка условия

int VectorLogicLion::dist(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); 
}

void VectorLogicLion::find_target(Animal::Lion cur_lion) {
    if (cur_lion.get_age() >= MAX_AGE || cur_lion.get_hunger() == 0) {
        //как удалять, если умер?
        //можно enum в классе животных
    }
    int not_sex = true;
    if (cur_lion.get_age() >= AGE_FOR_SEX || cur_lion.get_hunger() > HUNGER_FOR_SEX) { //sex
    	bool flag = true;
        for (auto lion : LionArray) {
            int tmp_dist = dist(lion.get_pos().x_, lion.get_pos().y_, cur_lion.get_pos().x_, cur_lion.get_pos().x_);
            int min_dist = dist(cur_lion.get_pos().x_, cur_lion.get_pos().y_, cur_lion.get_dir().x_, cur_lion.get_dir().x_);
            if (lion.get_sex() != cur_lion.get_sex() &&
                lion.get_age() >= AGE_FOR_SEX &&
                lion.get_hunger() > HUNGER_FOR_SEX &&
                lion.get_sexcd() && cur_lion.get_sexcd() &&
                tmp_dist < cur_lion.vision * cur_lion.vision && 
                (flag || tmp_dist < min_dist)) 
            {
                flag = false; //нужно добавить  change_dir
                cur_lion.change_dir_x(lion.get_pos().x_);
                cur_lion.change_dir_y(lion.get_pos().y_);   
            }
        }
        not_sex = flag;
    }
    if (not_sex) {
        for (auto zebra : zebras_array) {
            bool flag = true;
            int tmp_dist = dist(zebra.get_pos().x_, zebra.get_pos().y_, cur_lion.get_pos().x_, cur_lion.get_pos().x_);
            int min_dist = dist(cur_lion.get_pos().x_, cur_lion.get_pos().y_, cur_lion.get_dir().x_, cur_lion.get_dir().x_);
            if (tmp_dist < cur_lion.vision * cur_lion.vision && 
                (flag || tmp_dist < min_dist)) 
            {
                flag = false; //нужно добавить  change_dir
                cur_lion.change_dir_x(zebra.get_pos().x_);
                cur_lion.change_dir_y(zebra.get_pos().y_);   
            }
        }  
    }
}

void move (Animal::Lion cur_lion) {
    //??
    //поговорить про функцию проверки, временное вычисления в даблах и т д
}