#include "widget.h"
#include <QDesktopServices>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);
    this->setWindowOpacity(0.5);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowTitle("IRuler by Awesomez V1.2");
    this->setFixedSize(600,120);

    createContentMenu();
}

Widget::~Widget()
{
    //delete ui;
}

void Widget::mousePressEvent(QMouseEvent * event){
    if (event->button() == Qt::LeftButton){
        if(event->x()>this->width()-5){
            changeWidth=true;
        }else{
            changeWidth=false;
        }

        if(event->y()>this->height()-5){
            changeHeight=true;
        }else{
            changeHeight=false;
        }

        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }else if(event->button() == Qt::RightButton){
        contentMenu->exec(this->cursor().pos());
    }
}

void Widget::mouseMoveEvent(QMouseEvent * event){
    if(event->x()>this->width()-5){
        this->setCursor(Qt::SizeHorCursor);
    }else if(event->y()>this->height()-5){
        this->setCursor(Qt::SizeVerCursor);
    }else{
        this->setCursor(Qt::ArrowCursor);
    }

    if (event->buttons() == Qt::LeftButton){
        if((changeWidth&&!changeHeight)){
            int thisx=event->pos().x();
            if(thisx>30){
                this->setFixedWidth(thisx);
            }
        }else if(!changeWidth&&changeHeight){
            int thisy=event->pos().y();
            if(thisy>30){
                this->setFixedHeight(thisy);
            }
        }else{
            move(event->globalPos()-dragPosition);
            event->accept();
        }
    }
}

void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(rect(), QColor(255,255,255,150));

    drawXLine();
    drawYLine();

    int iwidth=this->width();
    int iheight=this->height();

    QPainter p2(this);
    p2.setPen(QPen(QColor("#ddd"), 1, Qt::SolidLine));
    p2.drawRect(0,0,iwidth-1,iheight-1);

    QString showText="W:"+QString::number(iwidth)+"px\r\nH:"+QString::number(iheight)+"px";

    p2.setPen(QPen(QColor("#940080"), 1, Qt::SolidLine));
    p2.setFont(QFont("Arial", 10));
    p2.drawText(this->rect(),  Qt::AlignCenter,showText);
}

void Widget::drawXLine(){
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, false);
    p.setPen(QPen(QColor("#000"), 1, Qt::SolidLine));

    int lineHeight = 5;

    int iwidth=this->width();
    for (int i = 0; i < iwidth; i+=2) {

        lineHeight = 5;

        if(i % 10 == 0){
            lineHeight = 10;
        }

        if (i % 50 == 0 && i>0) {
            p.setFont(QFont("Arial", 7, QFont::Bold));
            p.drawText( i, 20, 25, 10, Qt::AlignLeft, QString::number(i));
            lineHeight = 15;
        }
        p.drawLine(QPoint(i, 0), QPoint(i, lineHeight));
    }
}

void Widget::drawYLine(){
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, false);
    p.setPen(QPen(QColor("#000"), 1, Qt::SolidLine));

    int lineHeight = 5;

    int iheight=this->height();
    for (int i = 0; i <iheight; i+=2) {
        lineHeight = 5;

        if(i % 10 == 0){
            lineHeight = 10;
        }

        if (i % 50 == 0 && i>0) {
            p.setFont(QFont("Arial", 7, QFont::Bold));
            p.drawText(20, i, 25, 10, Qt::AlignLeft, QString::number(i));
            lineHeight = 15;
        }

        p.drawLine(QPoint(0,  i), QPoint(lineHeight, i));
    }
}

void Widget::createContentMenu(){
    QAction *Tray_quit = new QAction("Quit", this);
    //Tray_quit->setIcon(QIcon(":/image/image/delete.png"));
    connect(Tray_quit, SIGNAL(triggered(bool)), this, SLOT(slotQuit()));

    QAction *Tray_homepage = new QAction("Homepage", this);
    connect(Tray_homepage, SIGNAL(triggered(bool)), this, SLOT(slotHomepage()));

    QAction *Tray_changelog = new QAction("Changelog", this);
    connect(Tray_changelog, SIGNAL(triggered(bool)), this, SLOT(slotChangelog()));

    QAction *menuAbout = new QAction("About", this);
    connect(menuAbout, SIGNAL(triggered(bool)), this, SLOT(soltAbout()));

    contentMenu = new QMenu(this);
    contentMenu->addAction(Tray_homepage);
    contentMenu->addAction(Tray_changelog);
    contentMenu->addAction(menuAbout);
    contentMenu->addSeparator();
    contentMenu->addAction(Tray_quit);
}

void Widget::slotQuit(){
    this->close();
   // QApplication::quit();
}

void Widget::slotHomepage(){
    QDesktopServices::openUrl(QUrl("https://github.com/Awesomez-Qt/IRuler"));
}

void Widget::slotChangelog(){
    QDesktopServices::openUrl(QUrl("https://github.com/Awesomez-Qt/IRuler/commits/master"));
}

void Widget::soltAbout(){
    QMessageBox::information(this,"About","IRuler by Awesomez V1.2.20130814",QMessageBox::Yes);
}
