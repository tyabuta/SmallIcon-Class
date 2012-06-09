/************************************************
 SmallIcon class

 指定パスから、スモールアイコンを取得するクラス

 SHGetFileInfo関数を使用、
 CoInitializeを呼び出しておく必要あり。

                                   2012 tyabuta
************************************************/
#pragma once
#include <windows.h>
#include <string>

namespace ty{

/*
 * class SmallIcon
 *
 * コンストラクタまたは、InitメソッドにてアイコンPATHを指定する。
 * SmallIcon(const std::string& path)
 * bool Init(const std::string& path)
 * void Destroy();
 * 
 * bool IsNothing()const;
 * const std::string& GetPath()const;
 * 
 * void DrawIcon(HDC hdc, int x, int y, int w, int h)const;
 * void DrawIcon(HDC hdc, const RECT& rc)const;
 *
 */
class SmallIcon{
    HICON       hIcon_;
    std::string path_;

public:
    SmallIcon(): hIcon_(NULL){
    }
    SmallIcon(const std::string& path): hIcon_(NULL){
        Init(path);
    }
    ~SmallIcon(){
        Destroy();
    }

    bool Init(const std::string& path){
        path_ = path; 

        // すでにアイコンが読み込まれていたら、破棄する。
        Destroy();

        // SHFILEINFO構造体の初期化
        SHFILEINFO info;
        ZeroMemory(&info, sizeof(info));

        // スモールアイコンを取得
        SHGetFileInfoA(path.c_str(), 0, &info, sizeof(info),
                       SHGFI_ICON | SHGFI_SMALLICON);
        hIcon_ = info.hIcon;

        // NULLなら、取得に失敗している。
        return hIcon_ != NULL;
    }

    bool IsNothing()const{
        return hIcon_ == NULL;
    }

    const std::string& GetPath()const{
        return path_;
    }

    void Destroy(){
        if (hIcon_){
            DestroyIcon(hIcon_);
            hIcon_ = NULL;
        }
    }

    void DrawIcon(HDC hdc, int x, int y, int w, int h)const{
        if (hIcon_)
            DrawIconEx(hdc, x,y, hIcon_, w, h, 0, NULL, DI_NORMAL);
    }
  
    void DrawIcon(HDC hdc, const RECT& rc)const{
        DrawIcon(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
    }
};


}// namespace ty
