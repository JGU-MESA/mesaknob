#ifndef _VALUE_LABEL_H
#define _VALUE_LABEL_H

#include <QLabel>
#include <QEWidget.h>
#include <QESingleVariableMethods.h>
#include <QEFloatingFormatting.h>

class ValueLabel :
        public QLabel,
        public QEWidget,
        public QESingleVariableMethods
{
    Q_OBJECT

public:
    ValueLabel(QWidget *parent = 0);
    int getExponent() const { return exponent; }
    void setExponent(int _exponent);
    void setValue(double newValue);
    double getCurrentValue() const { return currentValue; }
    QString formatNumber(bool richText, bool unit);
signals:
    void requestResend();
protected:
    double currentValue;
    int exponent;
    double hopr;
    double lopr;
    int digits;
    int prec;
    bool valid;
    QEFloatingFormatting floatingFormatting;
    void refreshText();
private:
    void setup();
    void establishConnection( unsigned int variableIndex );
    qcaobject::QCaObject* createQcaItem( unsigned int variableIndex );

    bool isConnected;
private slots:
    void connectionChanged(QCaConnectionInfo& connectionInfo, const unsigned int&);
    void updateText(const double& newValue, QCaAlarmInfo&, QCaDateTime&, const unsigned int&);
    void useNewVariableNameProperty(QString variableNameIn, QString variableNameSubstitutionsIn, unsigned int variableIndex)
    {
        setVariableNameAndSubstitutions(variableNameIn, variableNameSubstitutionsIn, variableIndex);
    }
public slots:
    void shiftLeft();
    void shiftRight();

};

#endif // QE_LABEL_H
