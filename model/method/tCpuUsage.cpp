#include "tCpuUsage.h"

namespace SDPO {

/******************************************************************/

TCpuUsage::TCpuUsage(QObject *parent) :
    TTestMethod(TMethodID::CPU, parent)
{
    a_Computer = QString("localhost");
    a_OsSelect = QString("Linux");
    a_AlertWhen = 50;
    b_ConnectAs = false;
    a_Login = QString("UserName");
    a_Password = QString();
}

/******************************************************************/

void TCpuUsage::run()
{
    m_Status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TCpuUsage::clone()
{
    TCpuUsage *result = new TCpuUsage(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_Computer = a_Computer;
    result->a_OsSelect = a_OsSelect;
    result->a_AlertWhen = a_AlertWhen;
    result->b_ConnectAs = b_ConnectAs;
    result->a_Login = a_Login;
    result->a_Password = a_Password;
    return result;
}

/******************************************************************/

QString TCpuUsage::getTestMethod() const
{
    return QString("CPU %1").arg(a_Computer);
}

/******************************************************************/

QString TCpuUsage::getTestedObjectInfo() const
{
    return QString("CPU Usage on \\%1").arg(a_Computer);
}

/******************************************************************/

} // namespace SDPO
