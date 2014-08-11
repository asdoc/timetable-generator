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
#ifndef QCTEMPLATE_H
#define QCTEMPLATE_H

#include <QStack>
#include <QMap>
#include <QString>
#include <QPair>
#include <memory>

#if defined( BUILD_QCTEMPLATE_DLL )
# define QCTEMPLATE_DLL_DECL __declspec(dllexport)
#elif defined( USE_QCTEMPLATE_DLL )
# define QCTEMPLATE_DLL_DECL __declspec(dllexport)
#else
# define QCTEMPLATE_DLL_DECL
#endif

namespace ctemplate
{
    class TemplateDictionary;
}

class QCTEMPLATE_DLL_DECL QCTemplate
{
public:
    QCTemplate();
    ~QCTemplate();

    QString & operator[]( const QString & VariableName );
    const QString operator[]( const QString & VariableName ) const;

    void enterSection( const QString & SectionName );
    void exitSection();

    void clear();
  
    QString expandString( const QString & TemplateString );

    /// Template file must be UTF-8 encoded
    QString expandFile( const QString & TemplateFilePath );

private:
    // noncopiable
    QCTemplate( const QCTemplate & );
    QCTemplate & operator=( const QCTemplate & );

private:
    typedef QMap<QString, QString> QStringMap;
    typedef QPair<ctemplate::TemplateDictionary*, QStringMap> Section;
    QStack<Section> zSections;
    std::auto_ptr<ctemplate::TemplateDictionary> zMainDict;
    QStringMap zMainValues;
};

#endif
