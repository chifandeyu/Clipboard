#include "clipboardlib.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>
#include <QBuffer>
#include <QUrl>

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
   return html;
}

QImage Clipboard::getImage()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->image();
}

QStringList Clipboard::getUrls()
{
    QStringList strList;
    QClipboard* clipboard = QGuiApplication::clipboard();
    for(QUrl url : clipboard->mimeData()->urls()){
        strList.append(url.toString());
    }
    return strList;
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
    qDebug() << "Qt html:" << strHtml.c_str();
    return strdup(strHtml.c_str());
}

EXPORT char *getText()
{
    QString text = Clipboard::getText();
    auto strText = text.toStdString();
    qDebug() << "Qt text:" << strText.c_str();
    return strdup(strText.c_str());
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

char *getImage(long long *size)
{
    QImage image = Clipboard::getImage();
    if(image.isNull())
        return nullptr;
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer, "PNG");
    size_t iSize = buffer.size();
    if(iSize <= 0)
        return nullptr;
    qDebug() << "Qt image size:" << iSize;
    char* data = byteArray.data();
    char* newBuffer = (char*)malloc(iSize);
    memcpy(newBuffer, data, iSize);
    *size = iSize;
    return newBuffer;
}

StrList getFiles()
{
    StrList strList;
    const QStringList& urls = Clipboard::getUrls();
    strList.size = urls.size();
    strList.list = (char**)malloc(sizeof(char*) * urls.size());
    for(int i = 0; i < urls.size(); i++){
        strList.list[i] = strdup(urls.at(i).toStdString().c_str());
    }
    return strList;
}
