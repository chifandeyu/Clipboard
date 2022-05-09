#include "clipboardlib.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>

Clipboard::Clipboard()
{
}

void Clipboard::setText(const QString &text)
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}

void Clipboard::setRichText(const QString &richText)
{
    QMimeData richTextMime;
    richTextMime.setHtml(richText);
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setMimeData(&richTextMime);
}

bool Clipboard::hasImage()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->mimeData()->hasImage();
}

bool Clipboard::hasRichText()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->mimeData()->hasHtml();
}

bool Clipboard::hasText()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->mimeData()->hasText();
}

bool Clipboard::hasUrls()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->mimeData()->hasUrls();
}

QString Clipboard::getText()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->mimeData()->text();
}

QString Clipboard::getRichText()
{
   QClipboard* clipboard = QGuiApplication::clipboard();
   QString html = clipboard->mimeData()->html();
   qDebug() << "html: " << html;
   return html;
}

QImage Clipboard::getImage()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->image();
}

//C function
EXPORT void setText(char *text)
{
    if(text){
        QString strText = text;
        Clipboard::setText(strText);
    }
}

EXPORT void setRichText(const char* html)
{
    if(html){
        QString strHtml = html;
        Clipboard::setRichText(strHtml);
    }
}

EXPORT char* getRichText()
{
    QString html = Clipboard::getRichText();
    auto strHtml = html.toStdString();
    return strdup(strHtml.c_str());
}

EXPORT char *getText()
{
    QString text = Clipboard::getText();
    qInfo() << "Qt text: " << text;
    auto str = text.toStdString();
    qInfo() << "str: " << str.c_str();
    return strdup(str.c_str());
}

bool hasImage()
{
    return Clipboard::hasImage();
}

bool hasRichText()
{
    return Clipboard::hasRichText();
}

bool hasText()
{
    return Clipboard::hasText();
}

bool hasUrls()
{
    return Clipboard::hasUrls();
}
