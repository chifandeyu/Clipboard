// testcClipboard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

typedef struct StrList {
    char** list;
    int64_t size;
}StrList;

int main()
{
    HMODULE hModule = LoadLibrary(L"ClipboardLib.dll");
    DWORD dwError = 1;
    dwError = GetLastError();
    if (hModule) {
        std::cout << "LoadLibrary ok!\n";
        typedef bool(__stdcall* hasImageFunc)();
        hasImageFunc hasImage = (hasImageFunc)GetProcAddress(hModule, "hasImage");
        if (hasImage && hasImage()) {
            std::cout << "hasImage: " << hasImage() << std::endl;

            typedef char*(__stdcall* getImageFunc)(long long *);
            getImageFunc getImage = (getImageFunc)GetProcAddress(hModule, "getImage");
            if (getImage) {
                long long* size = (long long*)malloc(sizeof(long long));
                char* buffer = getImage(size);
                if (buffer) {
                    std::cout << "imae buffer: " << buffer << std::endl;
                    free(buffer);
                    free(size);
                }
            }
        }
        typedef bool(__stdcall* hasRichTextFunc)();
        hasRichTextFunc hasRichText = (hasRichTextFunc)GetProcAddress(hModule, "hasRichText");
        bool bHasRichText = hasRichText();

        typedef bool(__stdcall* hasTextFunc)();
        hasTextFunc hasText = (hasTextFunc)GetProcAddress(hModule, "hasText");

        typedef bool(__stdcall* hasUrlsFunc)();
        hasUrlsFunc hasUrls = (hasUrlsFunc)GetProcAddress(hModule, "hasUrls");

        if (bHasRichText) {
            std::cout << "hasRichText: " << hasRichText() << std::endl;
            typedef char* (__stdcall* getRichTextFunc)();
            getRichTextFunc getRichText = (getRichTextFunc)GetProcAddress(hModule, "getRichText");
            if (getRichText) {
                char* html = getRichText();
                std::string strHtml = html;
                free(html);
                std::cout << "strHtml: " << strHtml << std::endl;
            }
        } else if (hasUrls && hasUrls()) {
            std::cout << "hasUrls: " << hasText() << std::endl;
            typedef StrList(__stdcall* getFilesFunc)();
            getFilesFunc getFiles = (getFilesFunc)GetProcAddress(hModule, "getFiles");
            if (getFiles) {
                StrList strList = getFiles();
                for (int i = 0; i < strList.size; i++) {
                    char* strPath = strList.list[i];
                    std::cout << "strPath: " << strPath << std::endl;
                    free(strPath);
                }
                free(strList.list);
                strList.size = 0;
            }
        }
        else if (hasText && hasText()) {
            std::cout << "hasText: " << hasText() << std::endl;
            typedef char*(__stdcall* getTextFunc)();
            getTextFunc getText = (getTextFunc)GetProcAddress(hModule, "getText");
            if (getText) {
                char* text = getText();
                std::string strText = text;
                free(text);
                std::cout << "strText: " << strText << std::endl;
            }
        }
    }
    std::cout << "\n===========test finish===========\n";

    if (hModule) {
        FreeLibrary(hModule);
    }
    system("pause");
}
