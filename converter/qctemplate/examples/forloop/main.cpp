#include "ForLoopTest.h"
#include <QCoreApplication>
#include <QTranslator>
#include <QDebug>

int main( int argc, char **argv )
{
    QCoreApplication app( argc, argv );
    
    ForLoopTest test;

    qDebug() << "In English:";
    qDebug() << test.toText();
    qDebug() << test.toHtml();
    
    // load French translation
    QTranslator translator;
    translator.load( "forloop_fr");
    app.installTranslator( &translator );
         
    // regenerate template data
    test.reset(3);
    
    // display
    qDebug() << "In French:";    
    qDebug() << test.toText(); 
    qDebug() << test.toHtml();
}
