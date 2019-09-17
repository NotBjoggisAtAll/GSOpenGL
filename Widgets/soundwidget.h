#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include <QWidget>

class SoundComponent;

namespace Ui {
class SoundWidget;
}

class SoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoundWidget(unsigned int EntityID, QWidget *parent = nullptr);
    ~SoundWidget();

private:

    SoundComponent* Component{nullptr};

    Ui::SoundWidget *ui;
};

#endif // SOUNDWIDGET_H