/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QPainter>
#include <QTextBlock>
#include <fstream>
#include "textForm.h"

TextForm::TextForm(QWidget *parent)
    : QMainWindow(parent)
{
    setupEditor();
    setCentralWidget(editor);
    setWindowTitle(tr("QuickLook"));
    resize(600,400);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void TextForm::openFile(const QString &path)
{
    QString fileName = path;

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        switch (GetEncode(fileName.toStdString())) {
            case UNICODETYPE:
            {
                if (file.open(QFile::ReadOnly | QFile::Text))
                {
                    QTextStream toText(&file);
                    toText.setCodec("Unicode");
                     editor->setPlainText(toText.readAll());

                }
                break;
            }
            case UNICODEBIGTYPE:
            {
                if (file.open(QFile::ReadOnly | QFile::Text))
                {
                    QTextStream toText(&file);
                    toText.setCodec("Unicode");
                     editor->setPlainText(toText.readAll());
                }
                break;
            }
            case UTF8BOMTYPE:
            {
                if (file.open(QFile::ReadOnly | QFile::Text))
                {
                    QTextStream toText(&file);
                     toText.setCodec("UTF-8");
                    editor->setPlainText(toText.readAll());
                }
                break;
            }
            case UTF8TYPE:
            {
                if (file.open(QFile::ReadOnly | QFile::Text))
                {
                    QTextStream toText(&file);
                     toText.setCodec("UTF-8");
                    editor->setPlainText(toText.readAll());
                }
                break;
            }
            case ANSITYPE:
            {
                if (file.open(QFile::ReadOnly | QFile::Text))
                {
                    QTextStream toText(&file);
                       toText.setCodec("GBK");
                    editor->setPlainText(toText.readAll());
                }
                break;
            }
            default:
            {
                if (file.open(QFile::ReadOnly | QFile::Text))
                    editor->setPlainText(file.readAll());
                break;
            }
        }
    }
}

void TextForm::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new QEditor;
    editor->setFont(font);

    highlighter = new Highlighter(editor->document());
    editor->setReadOnly(true);
}

QString TextForm::GetCorrectUnicode(const QByteArray &ba)
{
    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString text = codec->toUnicode( ba.constData(), ba.size(), &state);
    qDebug() <<state.invalidChars;
    //等于是是GBK
    if (state.invalidChars == 4)
    {
        text = QTextCodec::codecForName( "GBK" )->toUnicode(ba);
    }else if(state.invalidChars == 3){//>>.3是unicode
        text = QTextCodec::codecForName( "Unicode" )->toUnicode(ba);
    }
    else
    {
        text = ba;
    }

    return text;
}

int TextForm::GetEncode(std::string path ){
    std::ifstream fin(path , std::ios::binary);
    unsigned char s2;
    fin.read((char*)&s2 , sizeof(s2));//读取第一个字节，然后左移8位
    int p = s2<<8;
    fin.read((char*)&s2 , sizeof(s2));
    p |= s2;

    int code = ANSITYPE;

          switch(p){
        case 0xfffe: //65534
            code = UNICODETYPE;//Unicode
            break;
        case 0xfeff: //65279
            code = UNICODEBIGTYPE;//Unicode big endian
            break;
        case 0xefbb: //61371
            code = UTF8BOMTYPE;//UTF-8
            break;
        case 0xe59b: //58779
            code = UTF8BOMTYPE;
            break;
        default:
            code = ANSITYPE;
            break;
    }
    return code;
}

QEditor::QEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &QEditor::blockCountChanged, this, &QEditor::updateLineNumberAreaWidth);
    connect(this, &QEditor::updateRequest, this, &QEditor::updateLineNumberArea);

    updateLineNumberAreaWidth(0);
}

int QEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void QEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void QEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void QEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::gray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
