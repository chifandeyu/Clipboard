// testcClipboard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

int main()
{
    HMODULE hModule = LoadLibrary(L"ClipboardLib.dll");
    DWORD dwError = 1;
    dwError = GetLastError();
    if (hModule) {
        std::cout << "LoadLibrary ok!\n";
        typedef bool(__stdcall* hasImageFunc)();
        hasImageFunc hasImage = (hasImageFunc)GetProcAddress(hModule, "hasImage");
        std::cout << "hasImage: " << hasImage() << std::endl;

        typedef bool(__stdcall* hasRichTextFunc)();
        hasRichTextFunc hasRichText = (hasRichTextFunc)GetProcAddress(hModule, "hasRichText");
        bool bHasRichText = hasRichText();
        typedef bool(__stdcall* hasTextFunc)();
        hasTextFunc hasText = (hasTextFunc)GetProcAddress(hModule, "hasText");

        if (bHasRichText) {
            std::cout << "hasRichText: " << hasRichText() << std::endl;
            typedef char* (__stdcall* getRichTextFunc)();
            getRichTextFunc getRichText = (getRichTextFunc)GetProcAddress(hModule, "getRichText");
            if (getRichText) {
                char* html = getRichText();
                std::string strHtml = html;
                std::cout << "strHtml: " << strHtml << std::endl;
            }
        } else if (hasText && hasText()) {
            std::cout << "hasText: " << hasText() << std::endl;
            typedef char*(__stdcall* getTextFunc)();
            getTextFunc getText = (getTextFunc)GetProcAddress(hModule, "getText");
            if (getText) {
                char* text = getText();
                std::string strText = text;
                std::cout << "strText: " << strText << std::endl;
            }
        }

        typedef bool(__stdcall* hasUrlsFunc)();
        hasUrlsFunc hasUrls = (hasUrlsFunc)GetProcAddress(hModule, "hasUrls");
        if (hasUrls && hasUrls()) {
            std::cout << "hasUrls: " << hasUrls() << std::endl;
        }
    }
    std::cout << "Hello World!\n";

    if (hModule) {
        FreeLibrary(hModule);
    }
    system("pause");
}
