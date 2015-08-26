#ifndef GAMEBODY
#define GAMEBODY

#include <QObject>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QWidget>
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
public:
    GameBody(QWidget *parent = 0);
    ~GameBody();
public slots:
    void next_sec();
    void past_sec();
    void restart_sec();
    void autosolve_sec();
    void load_section(int);
    void set_value(int max, QDir source);
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // GAMEBODY

