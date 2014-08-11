#include <QCTemplate.h>
#include <QDebug>

const char * template_string = "The message is: {{MESSAGE}}";

int main()
{
    QCTemplate tpl;
    
    tpl[ "MESSAGE" ] = "Hello World";
   
    qDebug() << tpl.expandString( template_string );
}
