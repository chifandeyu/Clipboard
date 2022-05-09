#ifndef CLIPBOARDLIB_H
#define CLIPBOARDLIB_H

#include "ClipboardLib_global.h"
#include <QImage>

#define EXPORT extern "C" __declspec(dllexport)

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
};

#ifdef Q_OS_WIN
#include <Windows.h>
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/ );

#elif Q_OS_MACOS

#endif

EXPORT bool hasImage();
EXPORT bool hasRichText();
EXPORT bool hasText();
EXPORT bool hasUrls();

EXPORT void setText(char *text);
EXPORT void setRichText(const char* html);
EXPORT char* getText();
EXPORT char* getRichText();
EXPORT bool getImage(int *);

#endif // CLIPBOARDLIB_H