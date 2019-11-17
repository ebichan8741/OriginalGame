#pragma once

#include "Sanctam3Project.h"

#define NUM_KEY_MAX        (256)    // �L�[�ő吔

#define CLICK_LEFT          (0)     //���N���b�N
#define CLICK_RIGHT         (1)     //�E�N���b�N
#define CLICK_CENTER        (2)     //�����{�^��

class CInput
{
public:
    CInput();
    virtual ~CInput();

    virtual HRESULT Init(HINSTANCE hInst, HWND hWnd);
    virtual void Uninit(void);
    virtual void Update(void) = 0;

protected:
    static LPDIRECTINPUT8 m_pDInput;    // DirectInput�I�u�W�F�N�g
    LPDIRECTINPUTDEVICE8 m_pDIDevice;    // Device�I�u�W�F�N�g(���͂ɕK�v)
};

class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();
    ~CInputKeyboard();

    HRESULT Init(HINSTANCE hInst, HWND hWnd);
    void Uninit(void);
    void Update(void);

    BOOL GetKeyPress(int nKey);
    BOOL GetKeyTrigger(int nKey);
    BOOL GetKeyRelease(int nKey);
    BOOL GetKeyRepeat(int nKey);
    void FlushKeyTrigger(int nKey);

private:
    BYTE    m_aKeyState[NUM_KEY_MAX];               // �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
    BYTE    m_aKeyStateTrigger[NUM_KEY_MAX];        // �g���K�[���[�N
    BYTE    m_aKeyStateRelease[NUM_KEY_MAX];        // �����[�X���[�N
    BYTE    m_aKeyStateRepeat[NUM_KEY_MAX];         // ���s�[�g���[�N
    int     m_aKeyStateRepeatCnt[NUM_KEY_MAX];      // ���s�[�g�J�E���^
};

class CInputMouse : public CInput
{
public:
    CInputMouse();
    ~CInputMouse();

    HRESULT Init(HINSTANCE hInst, HWND hWnd);
    void Uninit(void);
    void Update(void);
    void GetMouseState(void);

    DIMOUSESTATE2 m_pMouseState;

    void SetMousePos(D3DXVECTOR3 vPos);
    D3DXVECTOR3 GetMousePos(void);
    bool GetMousePress(int nClick);
    bool GetMouseTrigger(int nClick);

private:
    RECT    moveRect;     // ��ʏ�œ�����͈�
    int     x;            // X���W
    int     y;            // Y���W
    bool    lButton;      // ���{�^��
    bool    rButton;      // �E�{�^��
    bool    cButton;      // �^�񒆃{�^��
    int     moveAdd;      // �ړ���
    D3DXVECTOR3	m_vMousePos;
};