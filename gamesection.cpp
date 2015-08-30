#include "gamesection.h"
#include <queue>
#include <QDebug>

//fps:fixed point series read from txt
GameSection :: GameSection(Unit** fps, int s, int ct){
    this->size = s;
    this->colortype = ct;
    this->playarea = new Unit*[size];
    for (int i=0;i<size;++i)
        playarea[i] = new Unit[size];
    for (int i=0;i<size;++i)
        for (int j=0;j<size;++j){
            playarea[i][j].color = -1;
            playarea[i][j].x = i;
            playarea[i][j].y = j;
            playarea[i][j].if_fixed = false;
            playarea[i][j].succ = 0;
        }
    this->fixed_point_series = new Unit**[colortype];
    for (int i=0;i<colortype;++i)
        fixed_point_series[i] = new Unit*[2];
    for (int i=0;i<colortype;++i)
        for (int j=0;j<2;++j){
            playarea[fps[i][j].x][fps[i][j].y].if_fixed = true;
            playarea[fps[i][j].x][fps[i][j].y].color = fps[i][j].color;
            fixed_point_series[i][j] = &playarea[fps[i][j].x][fps[i][j].y];
        }
}

GameSection :: ~GameSection(){
    for (int i=0;i<colortype;++i)
        delete []fixed_point_series[i];
    delete []fixed_point_series;
    for (int i=0;i<size;++i)
        delete []playarea[i];
    delete []playarea;
}

void GameSection :: init(){
    for (int i=0;i<size;++i)
        for (int j=0;j<size;++j){
            playarea[i][j].color = -1;
            playarea[i][j].x = i;
            playarea[i][j].y = j;
            playarea[i][j].if_fixed = false;
            playarea[i][j].succ = 0;
        }
    for (int i=0;i<colortype;++i)
        for (int j=0;j<2;++j){
            playarea[fixed_point_series[i][j]->x][fixed_point_series[i][j]->y].if_fixed = true;
            playarea[fixed_point_series[i][j]->x][fixed_point_series[i][j]->y].color = i;
        }
}

bool GameSection :: autosolve(){
    init();
    steps_of_auto_solve = 0;
    return find_route_for_ncolor(colortype, fixed_point_series[0][0]);
}

bool GameSection :: find_route_for_ncolor(int nctype, Unit* start){
    steps_of_auto_solve++;
    if (steps_of_auto_solve > 1000000)
        return false;
    std::queue <Unit*> dire_queue;
    int tarx = fixed_point_series[colortype - nctype][1]->x; int tary = fixed_point_series[colortype - nctype][1]->y;
        if ((start->x == tarx && start->y == tary + 1) || (start->x == tarx && start->y == tary - 1) || (start->x == tarx + 1 && start->y == tary) || (start->x == tarx - 1 && start->y == tary))
            if (nctype == 1){
                start->succ = fixed_point_series[colortype - nctype][1];
                return true;
            }
            else
                if (find_route_for_ncolor(nctype - 1, fixed_point_series[colortype - nctype + 1][0])){
                    start->succ = fixed_point_series[colortype - nctype][1];
                    return true;
                }
                else
                    return false;
        if (if_unit_uncolored(start->x, start->y + 1))
            dire_queue.push(&playarea[start->x][start->y + 1]);
        if (if_unit_uncolored(start->x, start->y - 1))
            dire_queue.push(&playarea[start->x][start->y - 1]);
        if (if_unit_uncolored(start->x - 1, start->y))
            dire_queue.push(&playarea[start->x - 1][start->y]);
        if (if_unit_uncolored(start->x + 1, start->y))
            dire_queue.push(&playarea[start->x + 1][start->y]);
        while (!dire_queue.empty()) {
            dire_queue.front()->color = colortype - nctype;
            if (find_route_for_ncolor(nctype, dire_queue.front())){
                start->succ = dire_queue.front();
                return true;
            }
            else {
                dire_queue.front()->color = -1;
                dire_queue.pop();
            }
        }
        return false;
}

bool GameSection :: if_unit_uncolored(int x, int y){
    if (x < 0 || x >= size || y < 0 || y >= size)
        return false;
    else if (playarea[x][y].color == -1)
        return true;
    else
        return false;
}

bool GameSection :: if_color_connected(int colorx){
    Unit *p = fixed_point_series[colorx][0];
    while (p->succ!=0)
        p = p->succ;
    if (p == fixed_point_series[colorx][1])
        return true;
    else{
        p = fixed_point_series[colorx][1];
        while (p->succ!=0)
            p = p->succ;
        if (p == fixed_point_series[colorx][0])
            return true;
        else
            return false;
    }
}

bool GameSection :: if_all_color_connected(){
    for (int i=0;i<colortype;++i)
        if (!if_color_connected(i))
            return false;
    return true;
}
