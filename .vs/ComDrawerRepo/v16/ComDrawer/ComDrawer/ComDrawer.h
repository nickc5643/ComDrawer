#pragma once

#include <QtWidgets/QWidget>
#include "ui_ComDrawer.h"

class ComDrawer : public QWidget
{
    Q_OBJECT

public:
    ComDrawer(QWidget *parent = nullptr);
    ~ComDrawer();

private:
    Ui::ComDrawerClass ui;
};
