#ifndef QRASTESTWIDGET_H
#define QRASTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class RasTestWidget;
}

namespace SDPO {

class RasTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit RasTestWidget(QWidget *parent = 0);
    ~RasTestWidget();

private:
    Ui::RasTestWidget *ui;
};

} // namespace SDPO

#endif // QRASTESTWIDGET_H
