#include "value_label.h"
#include <QEFloating.h>
#include <math.h>

ValueLabel::ValueLabel( QWidget *parent ) :
    QLabel( parent ),
    QEWidget( this ),
    QESingleVariableMethods ( this, 0 ),
    valid(false)
{
    setup();
}

void ValueLabel::setup() {

    setNumVariables(1);

    setTextFormat(Qt::RichText);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setAllowDrop( false );

    setText("------------");
    isConnected = false;
    processConnectionInfo(isConnected, 0);

    hopr = 0;
    lopr = 0;
    digits = 0;
    prec = 0;

    exponent = 0;
    currentValue = 0;

    setupContextMenu();

    connectNewVariableNameProperty(SLOT(useNewVariableNameProperty(QString, QString, unsigned int)));
}

/*
    Implementation of QEWidget's virtual funtion to create the specific type of QCaObject required.
*/
qcaobject::QCaObject* ValueLabel::createQcaItem( unsigned int variableIndex ) {
    qcaobject::QCaObject* result = NULL;

    result = new QEFloating(getSubstitutedVariableName(variableIndex), this, &floatingFormatting, variableIndex);

    // Apply current array index to new QCaObject
    setQCaArrayIndex( result );

    return result;
}

void ValueLabel::establishConnection( unsigned int variableIndex ) {

    qcaobject::QCaObject * qca = createConnection(variableIndex);

    if (qca) {
        QObject::connect(qca, SIGNAL(floatingChanged(const double &, QCaAlarmInfo&, QCaDateTime&, const unsigned int &)),
                         this, SLOT(updateText(const double &, QCaAlarmInfo&, QCaDateTime&, const unsigned int &)));

        QObject::connect(qca, SIGNAL(connectionChanged(QCaConnectionInfo&, const unsigned int &)),
                         this, SLOT(connectionChanged(QCaConnectionInfo&, const unsigned int &)));
    }
}

void ValueLabel::connectionChanged( QCaConnectionInfo& connectionInfo, const unsigned int& variableIndex)
{
    isConnected = connectionInfo.isChannelConnected();
    updateToolTipConnection(isConnected, variableIndex);
    processConnectionInfo(isConnected, variableIndex);

    if (!isConnected)
        currentValue = 0;

    valid = false;

    refreshText();
}

void ValueLabel::setExponent(int _exponent)
{
    exponent = _exponent;
    refreshText();
}

void ValueLabel::shiftLeft()
{
    if (exponent < digits - 1) {
        ++exponent;
        refreshText();
    }
}

void ValueLabel::shiftRight()
{
    if (exponent > -prec) {
        --exponent;
        refreshText();
    }
}

void ValueLabel::updateText(const double &newValue, QCaAlarmInfo &, QCaDateTime &, const unsigned int &)
{
    currentValue = newValue;

    if (!valid) {
        // Determine the maximum number of digits before the decimal point.
        // Algorithm might be suboptimal :)
        QEFloating *qca = (QEFloating *) getQcaItem(0);
        if (qca) {
            hopr = qca->getDisplayLimitUpper();
            lopr = qca->getDisplayLimitLower();
            prec = qca->getPrecision();

            int hoprDigits = log10(fabs(hopr)) + 1;
            int loprDigits = log10(fabs(lopr)) + 1;
            int currentValueDigits = log10(fabs(currentValue)) + 1;
            digits = loprDigits > hoprDigits ? loprDigits : hoprDigits;
            digits = digits > currentValueDigits ? digits : currentValueDigits;
            if (digits < 1)
                digits = 1;
            // highlight third digit by default
            exponent = digits - 3;
            if (exponent < -prec)
                exponent = -prec;

            valid = true;
            emit dataValid();
        }
    }

    refreshText();
}

QString ValueLabel::formatNumber(bool richText, bool unit)
{
    if (!isConnected) {
        return QString("no PV");
    }

    char sign = '+';
    double displayValue = currentValue;
    if (displayValue < 0) {
        displayValue = -displayValue;
        sign = '-';
    }
    
    QString numberString;
    if (prec > 0)
        numberString = QString("%1%2").arg(sign).arg(displayValue, digits + prec + 1, 'f', prec, '0');
    else
        numberString = QString("%1%2").arg(sign).arg(displayValue, digits, 'f', prec, '0');

    if (richText) {
        int cursorPosition = digits - exponent;
        if (exponent < 0)
            ++cursorPosition;
        QString s1("<span style=\"background-color: #88ff88;\">");
        QString s2("</span>");
        
        numberString.insert(cursorPosition, s1);
        numberString.insert(cursorPosition + s1.size() + 1, s2);
    }

    if (unit)
        numberString.append(" ").append(((QEFloating *) getQcaItem(0))->getEgu());

    return numberString;
}

void ValueLabel::refreshText()
{
    setText(formatNumber(true, true));
}

void ValueLabel::setValue(double newValue)
{
    if (!isConnected)
        return;
    
    if ((hopr != 0) || (lopr != 0)) {
        if (newValue > hopr)
            newValue = hopr;
        if (newValue < lopr)
            newValue = lopr;
    }

    currentValue = newValue;
    refreshText();

    QEFloating *qca = (QEFloating *) getQcaItem(0);
    if (qca)
        qca->writeFloatingElement(newValue);
}

