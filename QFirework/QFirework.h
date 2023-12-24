#pragma once

#include "QDrawMap.h"
#include "QGravity.h"
#include "QMainFirework.h"
#include "ui_QFirework.h"
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QQueue>
#include <QTimer>

class QFirework : public QMainWindow
{
    Q_OBJECT

public:
    QFirework(QWidget *parent = nullptr);
    ~QFirework();

private:
    Ui::QFireworkClass ui;

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void initializePainting();

    QPixmap bg_map;
    QPixmap text_map;
    bool show_text = false;

private:
    QTimer* timer = nullptr;
    QList<HI::QGravity*> list;
    void cleanList();

private:
    QDrawMap map_painter;
    QQueue<QPixmap> map_queue;
    void requestMap();

    const int MAX_MAPS = 10;
    QPainter* painter = nullptr;

private:
    int add_firework_cycle = 25;

private slots:
    void proceed();
};
