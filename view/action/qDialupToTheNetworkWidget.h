#ifndef QDIALUPTOTHENETWORKWIDGET_H
#define QDIALUPTOTHENETWORKWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class DialupToTheNetworkWidget;
}

namespace SDPO {

class DialupToTheNetworkWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit DialupToTheNetworkWidget(QWidget *parent = 0);
    ~DialupToTheNetworkWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::DialupToTheNetworkWidget *ui;
};

} // namespace SDPO

#endif // QDIALUPTOTHENETWORKWIDGET_H
