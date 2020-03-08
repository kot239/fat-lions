using namespace world;

struct VectorLogicLion {
    bool ready_for_sex(const Animal::Lion& curLion);
    int dist(Point a, Point b);
    Vector find_correct_vec(const Animal::Lion& curLion, Vector resVector, const World& curWorld);
    void find_target(Animal::Lion& curLion, const World& curWorld);
}