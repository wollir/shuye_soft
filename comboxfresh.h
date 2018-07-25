#ifndef COMBOXFRESH_H
#define COMBOXFRESH_H
#include<QMouseEvent>
#include<qcombobox.h>
class comboxFresh:public QComboBox
{
public:
    comboxFresh();
     void mousePressEvent(QMouseEvent *event);
signals:
     void add_com();
};

#endif // COMBOXFRESH_H
