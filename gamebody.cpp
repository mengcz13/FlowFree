#include "gamebody.h"
#include <QDebug>
#include <QPainter>

GameBody :: GameBody(QWidget *parent):
    QWidget(parent)
{
    set_value(6,QDir::current());
}

GameBody :: ~GameBody(){
    delete gamesection;
}

void GameBody :: next_sec(){
    if (current_sec<max_sec_num-1){
        current_sec++;
        //delete gamesection;
        load_section(current_sec);
    }
}

void GameBody :: past_sec(){
    if (current_sec>0){
        current_sec--;
        //delete gamesection;
        load_section(current_sec);
    }
}

void GameBody :: restart_sec(){
    gamesection->init();
    update();
}

void GameBody :: autosolve_sec(){
    bool solved = gamesection->autosolve();
    if (solved){
        update();
    }
    else {
        //Warning: No Solution!
    }
}

/*File Format:
 * (Num of Size) (Num of ColorType)
 * (point 0 of color0)
 * (point 1 of color0)
 * ...
 * (point 0 of colorN)
 * (point 1 of colorN)
 */
void GameBody :: load_section(int sec){
    if (gamesection!=0)
        delete gamesection;
    QString filepath = QString("C:\\Users\\Chuizheng\\Documents\\QT_Projects\\FlowFree\\%1.txt").arg(sec);
    QFile f(filepath);
    if (!f.open(QIODevice::ReadOnly))
        qFatal("Cannot Open!");
    QTextStream in(&f);
    int sz=0; int ct=0;
    in>>sz>>ct;
    Unit **cps = new Unit*[sz];
    for (int i=0;i<ct;++i)
        cps[i]= new Unit[2];
    for (int i=0;i<ct;++i)
        for (int j=0;j<2;++j){
            in>>cps[i][j].x>>cps[i][j].y;
            cps[i][j].color = i;
            cps[i][j].if_fixed = true;
            cps[i][j].succ = 0;
        }
    gamesection = new GameSection(cps,sz,ct);
    for (int i=0;i<sz;++i)
        delete []cps[i];
    delete []cps;
    update();
}

void GameBody :: set_value(int max, QDir source){
    max_sec_num = max;
    current_sec = 0;
    sec_source = source;
    gamesection = 0;
    load_section(current_sec);
}

void GameBody :: paintEvent(QPaintEvent *ev){
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);
    //Draw the grid
    for (int i=0;i<=420;i+=420/(gamesection->size)){
        p.drawLine(0,i,420,i);
        p.drawLine(i,0,i,420);
    }

    //Draw the fixed points
    int inteval = 420/(gamesection->size);
    for (int i=0;i<gamesection->colortype;++i)
        for (int j=0;j<2;++j){
            //Pattern1
            //p.setBrush(QColor(i*255/gamesection->colortype,i*255/gamesection->colortype,i*255/gamesection->colortype));
            //Pattern2
            //p.setBrush(QColor(QColor::colorNames()[i]));
            //Pattern3
            p.setBrush(QColor::fromHsv(i*359/gamesection->colortype,255,255));
            p.drawEllipse(inteval*(gamesection->fixed_point_series[i][j]->y),inteval*(gamesection->fixed_point_series[i][j]->x),inteval,inteval);
        }

    //Draw the tubes
    for (int i=0;i<gamesection->colortype;++i)
        for (int j=0;j<2;++j){
            Unit *startpoint = gamesection->fixed_point_series[i][j];
            while (startpoint->succ!=0){
                QPen pen(QColor::fromHsv(i*359/gamesection->colortype,255,255));
                pen.setWidth(inteval/5);
                pen.setCapStyle(Qt::RoundCap);
                pen.setJoinStyle(Qt::RoundJoin);
                p.setPen(pen);
                p.drawLine((startpoint->y)*inteval+inteval/2,(startpoint->x)*inteval+inteval/2,(startpoint->succ->y)*inteval+inteval/2,(startpoint->succ->x)*inteval+inteval/2);
                startpoint = startpoint->succ;
            }
        }
}
