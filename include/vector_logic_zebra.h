#include "World.hpp"

using namespace world;

struct VectorLogicZebra {
    bool ready_for_sex(const Zebra& curZebra);
    int dist(Point a, Point b);
    Vector find_correct_vec(const Zebra& curZebra, Vector resVector, const World& curWorld);
    void find_target(Zebra& curZebra, World& curWorld);
};

//пока что с классами, попозже решим что именно будем делать