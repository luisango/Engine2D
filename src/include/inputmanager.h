/************************************************************************************************************/
//
//
/************************************************************************************************************/

#ifndef UGINE_INPUTMANAGER_H
#define UGINE_INPUTMANAGER_H

#include "String.h"

// códigos que representan los distintos tipos de inputs posibles
enum eInputCode
{
  // Teclado
  Key_0,
  Key_1,
  Key_2,
  Key_3,
  Key_4,
  Key_5,
  Key_6,
  Key_7,
  Key_8,
  Key_9,
  Key_AltGr,
  Key_Ampersand,
  Key_Asterisk,
  Key_At,
  Key_BackQuote,
  Key_Backslash,
  Key_Backspace,
  Key_Break,
  Key_CapsLock,
  Key_Caret,
  Key_Clear,
  Key_Colon,
  Key_Comma,
  Key_Delete,
  Key_Dollar,
  Key_DoubleQuote,
  Key_DownArrow,
  Key_End,
  Key_Equals,
  Key_Escape,
  Key_Exclaim,
  Key_F1,
  Key_F2,
  Key_F3,
  Key_F4,
  Key_F5,
  Key_F6,
  Key_F7,
  Key_F8,
  Key_F9,
  Key_F10,
  Key_F11,
  Key_F12,
  Key_F13,
  Key_F14,
  Key_F15,
  Key_Greater,
  Key_Hash,
  Key_Help,
  Key_Home,
  Key_Insert,
  Key_Keypad0,
  Key_Keypad1,
  Key_Keypad2,
  Key_Keypad3,
  Key_Keypad4,
  Key_Keypad5,
  Key_Keypad6,
  Key_Keypad7,
  Key_Keypad8,
  Key_Keypad9,
  Key_KeypadDivide,
  Key_KeypadEnter,
  Key_KeypadEquals,
  Key_KeypadMinus,
  Key_KeypadMultiply,
  Key_KeypadPeriod,
  Key_KeypadPlus,
  Key_LeftAlt,
  Key_LeftApple,
  Key_LeftArrow,
  Key_LeftBracket,
  Key_LeftControl,
  Key_LeftParen,
  Key_LeftShift,
  Key_LeftWindows,
  Key_Less,
  Key_Menu,
  Key_Minus,
  Key_Numlock,
  Key_PageDown,
  Key_PageUp,
  Key_Pause,
  Key_Period,
  Key_Plus,
  Key_Print,
  Key_Question,
  Key_Quote,
  Key_Return,
  Key_RightAlt,
  Key_RightApple,
  Key_RightArrow,
  Key_RightBracket,
  Key_RightControl,
  Key_RightParen,
  Key_RightShift,
  Key_RightWindows,
  Key_ScrollLock,
  Key_Semicolon,
  Key_Slash,
  Key_Space,
  Key_SysReq,
  Key_Tab,
  Key_Underscore,
  Key_UpArrow,
  Key_A,
  Key_B,
  Key_C,
  Key_D,
  Key_E,
  Key_F,
  Key_G,
  Key_H,
  Key_I,
  Key_J,
  Key_K,
  Key_L,
  Key_M,
  Key_N,
  Key_O,
  Key_P,
  Key_Q,
  Key_R,
  Key_S,
  Key_T,
  Key_U,
  Key_V,
  Key_W,
  Key_X,
  Key_Y,
  Key_Z,

  // Ratón
  Mouse_Button0,
  Mouse_Button1,
  Mouse_Button2,
  Mouse_WheelDown,
  Mouse_WheelUp,
  Mouse_Down,
  Mouse_Up,
  Mouse_Left,
  Mouse_Right,
};


class InputManager
{
public:
    // Inicialición: deteccción de dispostivos, inicialización de los mismos... etc
    bool Init();

    // Cierre
    void End();

    // Devuelve true si el manager ha sido inicializado correctamente
    bool IsOk();

    // Función de actualización, actualización de estados entre frames
    void Update();

    // Crea un botón virtual
    void CreateVirtualButton(const String& name, eInputCode button);

    // Crea un eje virtual
    void CreateVirtualAxis(const String& name, eInputCode positiveAxis, eInputCode negativeAxis);

    // Está el botón pulsado en este momento?
    bool IsVirtualButtonPressed(const String& name) const;

    // Devuelve true durante el frame que que el usuario ha comenzaco la pulsación de un botón
    bool IsVirtualButtonDown(const String& name) const;

    // Devuelve true durante el frame que que el usuario ha dejado de pulsar un botón
    bool IsVirtualButtonUp(const String& name) const;

    // Estado de ejes virtuales normalizado de -1 a +1
    float GetVirtualAxis(String name) const;

    // Está el la tecla pulsada en este momento?
    bool IsKeyPressed(eInputCode vkCode);

    // Devuelve true durante el frame que que el usuario ha comenzaco la pulsación de una tecla (***OPCIONAL***)
    bool IsKeyDown(eInputCode vkCode);

    // Devuelve true durante el frame que que el usuario ha dejado de pulsar una tecla (***OPCIONAL***)
    bool IsKeyUp(eInputCode vkCode);

    // Está el la el botón del ratón tecla pulsado en este momento?
    bool IsMouseButtonPressed(eInputCode button);

    // Devuelve true durante el frame que que el usuario ha comenzaco la pulsación del botón del ratón dado
    bool GetMouseButtonDown(eInputCode button);

    // Devuelve true durante el frame que que el usuario ha dejado de pulsar el botón del ratón dado
    bool GetMouseButtonUp(eInputCode button);
};


#endif