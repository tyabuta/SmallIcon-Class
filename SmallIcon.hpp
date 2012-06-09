/************************************************
 SmallIcon class

 �w��p�X����A�X���[���A�C�R�����擾����N���X

 SHGetFileInfo�֐����g�p�A
 CoInitialize���Ăяo���Ă����K�v����B

                                   2012 tyabuta
************************************************/
#pragma once
#include <windows.h>
#include <string>

namespace ty{

/*
 * class SmallIcon
 *
 * �R���X�g���N�^�܂��́AInit���\�b�h�ɂăA�C�R��PATH���w�肷��B
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

        // ���łɃA�C�R�����ǂݍ��܂�Ă�����A�j������B
        Destroy();

        // SHFILEINFO�\���̂̏�����
        SHFILEINFO info;
        ZeroMemory(&info, sizeof(info));

        // �X���[���A�C�R�����擾
        SHGetFileInfoA(path.c_str(), 0, &info, sizeof(info),
                       SHGFI_ICON | SHGFI_SMALLICON);
        hIcon_ = info.hIcon;

        // NULL�Ȃ�A�擾�Ɏ��s���Ă���B
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
