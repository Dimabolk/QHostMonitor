#ifndef QSTARTUPOPTIONSWIDGET_H
#define QSTARTUPOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class StartupOptionsWidget;
}

namespace SDPO {

class StartupOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit StartupOptionsWidget(QWidget *parent = 0);
    ~StartupOptionsWidget();
    int s;

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private slots:
    void onTestListChanged();

    void on_btnStartupFileDlg_clicked();

private:
    Ui::StartupOptionsWidget *ui;
};

} // namespace SDPO

#endif // QSTARTUPOPTIONSWIDGET_H
