using namespace world;

struct VectorLogicZebra {
    bool ready_for_sex(const Animal::Zebra& curZebra);
    int dist(Point a, Point b);
    Vector find_correct_vec(const Animal::Zebra& curZebra, Vector resVector, const World& curWorld);
    void find_target(Animal::Zebra& curZebra, const World& curWorld);
}

//пока что с классами, попозже решим что именно будем делать