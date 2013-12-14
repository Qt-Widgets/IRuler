#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPen>
#include <QFont>
#include <QPainter>
#include <QMenu>


class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    QPoint dragPosition;
    void drawXLine();
    void drawYLine();

    bool changeWidth;
    bool changeHeight;

    QMenu *contentMenu;
    void createContentMenu();
private slots:
    void slotQuit();
    void slotChangelog();
    void slotHomepage();
    void soltAbout();
};

#endif // WIDGET_H
