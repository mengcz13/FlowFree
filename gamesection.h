#ifndef GAMESECTION
#define GAMESECTION

struct Unit{
    int x;
    int y;
    int color;
    int if_fixed;
    Unit* succ;
};

class GameSection{
    friend class GameBody;
private:
    Unit** playarea;
    int size;
    int colortype;
    Unit*** fixed_point_series;
public:
    GameSection(Unit**, int, int);
    ~GameSection();
    void init();
    bool autosolve();
protected:
    bool find_route_for_ncolor(int colortype, Unit* start);
    bool if_unit_uncolored(int x, int y);
};

#endif // GAMESECTION

