#ifndef GAMESECTION
#define GAMESECTION

struct Unit{
    int x;
    int y;
    int color;
    int if_fixed;
    Unit* succ;
    void clear_succ(){
        if (!this->if_fixed)
            color = -1;
        if (this->succ!=0)
            this->succ->clear_succ();
        this->succ = 0;
    }
};

class GameSection{
    friend class GameBody;
private:
    Unit** playarea;
    int size;
    int colortype;
    Unit*** fixed_point_series;
    int steps_of_auto_solve;
public:
    GameSection(Unit**, int, int);
    ~GameSection();
    void init();
    bool autosolve();
protected:
    bool find_route_for_ncolor(int colortype, Unit* start);
    bool if_unit_uncolored(int x, int y);
    bool if_color_connected(int colorx);
    bool if_all_color_connected();
};

#endif // GAMESECTION

