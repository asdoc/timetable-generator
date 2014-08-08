#ifndef FORLOOPTEST_H
#define FORLOOPTEST_H

#include <QCTemplate.h>
#include <QObject>
#include <QString>

class ForLoopTest : private QObject
{
    Q_OBJECT
public:
    ForLoopTest();
    
    void reset( int Count );
    
    QString toText();
    
    QString toHtml();

private:
    QCTemplate zTpl;
};

#endif
 