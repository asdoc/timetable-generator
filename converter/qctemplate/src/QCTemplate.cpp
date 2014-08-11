// Copyright (c) 2009, Aurelien Regat-Barrel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of QCTemplate nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "QCTemplate.h"

#include <QFile>
#include <QDebug>
#include <ctemplate/template.h>

namespace // anonymous
{
    inline std::string toStdString( const QString & Str )
    {
#ifdef QT_NO_STL
        const QByteArray asc = Str.toAscii();
        return std::string(asc.constData(), asc.length());
#else
        return Str.toStdString();
#endif
    }

    inline QString toQString( const std::string & Str )
    {
#ifdef QT_NO_STL
        return QString::fromAscii(Str.data(), static_cast<int>(Str.size()));
#else
        return QString::fromStdString( Str );
#endif
    }
}

QCTemplate::QCTemplate()
{
	this->zMainDict.reset( new ctemplate::TemplateDictionary("") );
}

QCTemplate::~QCTemplate()
{
	// we need to provide a destructor implementation because of the use auto_ptr
}

QString & QCTemplate::operator[]( const QString & VariableName )
{
	if ( this->zSections.isEmpty() )
	{
		return this->zMainValues[ VariableName ];
	}
	else
	{
		QStringMap & map = this->zSections.top().second;
		return map[ VariableName ];
	}
}

const QString QCTemplate::operator[]( const QString & VariableName ) const
{
	if ( this->zSections.isEmpty() )
	{
		return this->zMainValues[ VariableName ];
	}
	else
	{
		const QStringMap & map = this->zSections.top().second;
		return map[ VariableName ];
	}
}

void QCTemplate::enterSection( const QString & SectionName )
{
	ctemplate::TemplateDictionary *dict =
		this->zMainDict->AddSectionDictionary( toStdString( SectionName ) );

	this->zSections.push(
		Section( dict, QStringMap() ) );
}

void QCTemplate::exitSection()
{
	Section section = this->zSections.pop();
	ctemplate::TemplateDictionary *dict = section.first;
	QStringMap values = section.second;

	for ( QStringMap::const_iterator i = values.begin(); i != values.end(); i++ )
	{
		dict->SetValue( toStdString( i.key() ), toStdString( i.value() ) );
	}
}

void QCTemplate::clear()
{
    this->zSections.clear();
    this->zMainValues.clear();
    this->zMainDict.reset( new ctemplate::TemplateDictionary("") );
}

QString QCTemplate::expandString( const QString & TemplateString )
{
	while ( !this->zSections.isEmpty() )
	{
		this->exitSection();
	}

	// TODO: test data alteration after an expand
	for ( QStringMap::const_iterator i = this->zMainValues.begin(); i != this->zMainValues.end(); i++ )
	{
		this->zMainDict->SetValue( toStdString( i.key() ), toStdString( i.value() ) );
	}
	this->zMainValues.clear();
	
	ctemplate::Template* tpl = ctemplate::Template::StringToTemplate(
		toStdString( TemplateString ), ctemplate::DO_NOT_STRIP);
    if ( !tpl )
    {
        qWarning() << "Failed to parse template string";
        return QString::null;
    }

    std::string result;
    tpl->Expand( &result, this->zMainDict.get() );

	return toQString( result );
}

QString QCTemplate::expandFile( const QString & TemplateFilePath )
{
    QFile file( TemplateFilePath );
    if ( !file.open( QIODevice::ReadOnly ) )
    {
        qWarning() << "Could not find file" << TemplateFilePath;
		return QString::null;
    }
    QString fileContent = QString::fromUtf8( file.readAll().data() );
    file.close();

	return this->expandString( fileContent );
}
