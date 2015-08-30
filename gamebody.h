#ifndef GAMEBODY
#define GAMEBODY

#include <QObject>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QWidget>
#include <QSound>
#include "gamesection.h"

//Responsible for loading and drawing
class GameBody : public QWidget{
    Q_OBJECT
private:
    GameSection* gamesection;
    int max_sec_num;
    int current_sec;
    QDir sec_source;
    Unit* last_active_unit;
    QPoint cursor;
    bool show_cursor;
    int random_size;
    int random_colortype;

public:
    GameBody(QWidget *parent = 0);
    ~GameBody();
    int get_max_sec_num(){return max_sec_num;}
public slots:
    void next_sec();
    void past_sec();
    void restart_sec();
    void autosolve_sec();
    void load_section(int);
    void set_value(int max, QDir source);
    void init(){
        current_sec = 0;
        gamesection = 0;
        last_active_unit = 0;
        this->load_section(0);
    }
    void randomize();
    void set_size(int s){random_size = s;}
    void set_colortype(int ct){random_colortype = ct;}
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void currentSectionChanged(QString);
};

#endif // GAMEBODY

