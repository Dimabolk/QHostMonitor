#ifndef TRESTARTSERVICEACTION_H
#define TRESTARTSERVICEACTION_H

#include "tTestAction.h"

namespace SDPO {

class RestartServiceAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, RestartServiceOn) // Restart service on
    AUTO_PROPERTY(QString, ServiceName) // Service name
    BOOL_PROPERTY(DoNotStartService) // Do not start service if it stop prior to  execution of the action
    BOOL_PROPERTY(ConnectAs) // Connect as
    AUTO_PROPERTY(QString, ConnectAsLogin) // Login
    AUTO_PROPERTY(QString, ConnectAsPassword) // Password

public:
    explicit RestartServiceAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

}// namespace SDPO
#endif // TRESTARTSERVICEACTION_H
