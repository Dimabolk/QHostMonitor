#ifndef IOMYSQLCONVERTER_H
#define IOMYSQLCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {


class IOMySqlConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOMySqlConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
};

} //namespace SDPO

#endif // IOMYSQLCONVERTER_H
