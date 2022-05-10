#ifndef CLIPBOARDLIB_H
#define CLIPBOARDLIB_H

#include "ClipboardLib_global.h"
#include "export.h"
#include <QImage>

typedef struct StrList{
    char **list;
    int64_t size;
}StrList;

class CLIPBOARDLIB_EXPORT Clipboard
{
public:
    Clipboard();
    static void setText(const QString& text);
    static void setRichText(const QString& richText);
    static bool hasImage();
    static bool hasRichText();
    static bool hasText();
    static bool hasUrls();
    static QString getText();
    static QString getRichText();
    static QImage getImage();
    static QStringList getUrls();
};

EXPORT bool hasImage();
EXPORT bool hasRichText();
EXPORT bool hasText();
EXPORT bool hasUrls();

EXPORT void setText(char *text);
EXPORT void setRichText(const char* html);
EXPORT char* getText();
EXPORT char* getRichText();
EXPORT char* getImage(long long *size);
EXPORT StrList getFiles();

#endif // CLIPBOARDLIB_H
