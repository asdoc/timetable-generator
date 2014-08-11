#include "ForLoopTest.h"

ForLoopTest::ForLoopTest()
{
    this->reset( 5 );
}

void ForLoopTest::reset( int Count )
{
    this->zTpl.clear();
            
    this->zTpl[ "TITLE" ] = tr( "Display of %1 lines" ).arg( Count );
    
    for ( int i = 0; i < Count; i++ )
    {
        this->zTpl.enterSection( "FORLOOP" );        
        this->zTpl[ "LOOP_MESSAGE" ] = tr( "This is line number %1" ).arg( i  + 1 );          
        this->zTpl.exitSection();
    }        
}

QString ForLoopTest::toText()
{
    return this->zTpl.expandFile( ":/forloop_text.tpl" );
}

QString ForLoopTest::toHtml()
{
    return this->zTpl.expandFile( ":/forloop_html.tpl" );
}
