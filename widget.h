#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QColor>
QT_BEGIN_NAMESPACE
class QGraphicsScene;
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QGraphicsScene *mScene;
    QIcon makeIcon(const QColor &color)const;
};
#endif // WIDGET_H
