#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsScene>
#include <QPainter>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene(0.0,0.0,300.0,300.0,this);
    mScene->addRect(0.0,0.0,300.0,300.0,QPen(Qt::black));
    ui->graphicsView->setScene(mScene);
    ui->listWidget->setIconSize(QSize(50,50));


    QMap<QString, QIcon> TextIcon;
    TextIcon["Rojo"] = makeIcon(Qt::red);
    TextIcon["Amarillo"] = makeIcon(Qt::yellow);
    TextIcon["Azul"] = makeIcon(Qt::blue);
    TextIcon["blanco"] = makeIcon(Qt::white);
    TextIcon["Amarillo"] = makeIcon(Qt::black);

    QMap<QString, QIcon>::iterator ax = TextIcon.begin();
    const QMap<QString, QIcon>::iterator TextIconEnd = TextIcon.end();
    for(;ax != TextIconEnd;ax++){
        QIcon icon = ax.value();
        QString text = ax.key();

        QListWidgetItem *item = new QListWidgetItem(icon,text);
        ui->listWidget->addItem(item);
    }


}

Widget::~Widget()
{
    delete ui;
}

QIcon Widget::makeIcon(const QColor &color) const
{
    QImage image(512,512,QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.fillRect(0,0,512,512,color);
    QRgb rgb = color.rgb();
    if(rgb == QColor(Qt::white).rgb()){
        QPen pen(Qt::black);
        pen.setWidth(20);
        painter.setPen(pen);
        painter.drawRect(0,0,512,512);
    }

    QPixmap pixmap;
    pixmap.convertFromImage(image);
    QIcon icon(pixmap);
    return icon;
}


void Widget::on_listWidget_clicked(const QModelIndex &index)
{
    QListWidgetItem *item = ui->listWidget->item(index.row());
    QIcon icon = item->icon();
    QPixmap pixmap = icon.pixmap(512,512);
    QImage image = pixmap.toImage();
    QColor color = image.pixelColor(image.width()/2,image.height()/2);
    mScene->clear();
    mScene->addRect(0.0,0.0,300.0,300.0, QPen(color),QBrush(color));
    QRgb rgb = color.rgb();
    if (rgb == QColor(Qt::white).rgb()){
        mScene->addRect(0.0,0.0,300.0,300.0,QPen(Qt::black));
    }
}

