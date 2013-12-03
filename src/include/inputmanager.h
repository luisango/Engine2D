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
KEY_ESC             = GLFW_KEY_SPECIAL + 1,
KEY_F1              = GLFW_KEY_SPECIAL + 2,
KEY_F2              = GLFW_KEY_SPECIAL + 3,
KEY_F3              = GLFW_KEY_SPECIAL + 4,
KEY_F4              = GLFW_KEY_SPECIAL + 5,
KEY_F5              = GLFW_KEY_SPECIAL + 6,
KEY_F6              = GLFW_KEY_SPECIAL + 7,
KEY_F7              = GLFW_KEY_SPECIAL + 8,
KEY_F8              = GLFW_KEY_SPECIAL + 9,
KEY_F9              = GLFW_KEY_SPECIAL + 10,
KEY_F10             = GLFW_KEY_SPECIAL + 11,
KEY_F11             = GLFW_KEY_SPECIAL + 12,
KEY_F12             = GLFW_KEY_SPECIAL + 13,
KEY_F13             = GLFW_KEY_SPECIAL + 14,
KEY_F14             = GLFW_KEY_SPECIAL + 15,
KEY_F15             = GLFW_KEY_SPECIAL + 16,
KEY_F16             = GLFW_KEY_SPECIAL + 17,
KEY_F17             = GLFW_KEY_SPECIAL + 18,
KEY_F18             = GLFW_KEY_SPECIAL + 19,
KEY_F19             = GLFW_KEY_SPECIAL + 20,
KEY_F20             = GLFW_KEY_SPECIAL + 21,
KEY_F21             = GLFW_KEY_SPECIAL + 22,
KEY_F22             = GLFW_KEY_SPECIAL + 23,
KEY_F23             = GLFW_KEY_SPECIAL + 24,
KEY_F24             = GLFW_KEY_SPECIAL + 25,
KEY_F25             = GLFW_KEY_SPECIAL + 26,
KEY_UP              = GLFW_KEY_SPECIAL + 27,
KEY_DOWN            = GLFW_KEY_SPECIAL + 28,
KEY_LEFT            = GLFW_KEY_SPECIAL + 29,
KEY_RIGHT           = GLFW_KEY_SPECIAL + 30,
KEY_LSHIFT          = GLFW_KEY_SPECIAL + 31,
KEY_RSHIFT          = GLFW_KEY_SPECIAL + 32,
KEY_LCTRL           = GLFW_KEY_SPECIAL + 33,
KEY_RCTRL           = GLFW_KEY_SPECIAL + 34,
KEY_LALT            = GLFW_KEY_SPECIAL + 35,
KEY_RALT            = GLFW_KEY_SPECIAL + 36,
KEY_TAB             = GLFW_KEY_SPECIAL + 37,
KEY_ENTER           = GLFW_KEY_SPECIAL + 38,
KEY_BACKSPACE       = GLFW_KEY_SPECIAL + 39,
KEY_INSERT          = GLFW_KEY_SPECIAL + 40,
KEY_DEL             = GLFW_KEY_SPECIAL + 41,
KEY_PAGEUP          = GLFW_KEY_SPECIAL + 42,
KEY_PAGEDOWN        = GLFW_KEY_SPECIAL + 43,
KEY_HOME            = GLFW_KEY_SPECIAL + 44,
KEY_END             = GLFW_KEY_SPECIAL + 45,
KEY_KP_0            = GLFW_KEY_SPECIAL + 46,
KEY_KP_1            = GLFW_KEY_SPECIAL + 47,
KEY_KP_2            = GLFW_KEY_SPECIAL + 48,
KEY_KP_3            = GLFW_KEY_SPECIAL + 49,
KEY_KP_4            = GLFW_KEY_SPECIAL + 50,
KEY_KP_5            = GLFW_KEY_SPECIAL + 51,
KEY_KP_6            = GLFW_KEY_SPECIAL + 52,
KEY_KP_7            = GLFW_KEY_SPECIAL + 53,
KEY_KP_8            = GLFW_KEY_SPECIAL + 54,
KEY_KP_9            = GLFW_KEY_SPECIAL + 55,
KEY_KP_DIVIDE       = GLFW_KEY_SPECIAL + 56,
KEY_KP_MULTIPLY     = GLFW_KEY_SPECIAL + 57,
KEY_KP_SUBTRACT     = GLFW_KEY_SPECIAL + 58,
KEY_KP_ADD          = GLFW_KEY_SPECIAL + 59,
KEY_KP_DECIMAL      = GLFW_KEY_SPECIAL + 60,
KEY_KP_EQUAL        = GLFW_KEY_SPECIAL + 61,
KEY_KP_ENTER        = GLFW_KEY_SPECIAL + 62,
KEY_KP_NUM_LOCK     = GLFW_KEY_SPECIAL + 63,
KEY_CAPS_LOCK       = GLFW_KEY_SPECIAL + 64,
KEY_SCROLL_LOCK     = GLFW_KEY_SPECIAL + 65,
KEY_PAUSE           = GLFW_KEY_SPECIAL + 66,
KEY_LSUPER          = GLFW_KEY_SPECIAL + 67,
KEY_RSUPER          = GLFW_KEY_SPECIAL + 68,
KEY_MENU            = GLFW_KEY_SPECIAL + 69,

/* Letters */
KEY_A               = 'A',
KEY_B               = 'B',
KEY_C               = 'C',
KEY_D               = 'D',
KEY_E               = 'E',
KEY_F               = 'F',
KEY_G               = 'G',
KEY_H               = 'H',
KEY_I               = 'I',
KEY_J               = 'J',
KEY_K               = 'K',
KEY_L               = 'L',
KEY_M               = 'M',
KEY_N               = 'N',
KEY_NTILDE          = 'Ñ',
KEY_O               = 'O',
KEY_P               = 'P',
KEY_Q               = 'Q',
KEY_R               = 'R',
KEY_S               = 'S',
KEY_T               = 'T',
KEY_U               = 'U',
KEY_V               = 'V',
KEY_W               = 'W',
KEY_X               = 'X',
KEY_Y               = 'Y',
KEY_Z               = 'Z',

/* Mouse button definitions */
MOUSE_BUTTON_LEFT   = 0,
MOUSE_BUTTON_RIGHT  = 1,
MOUSE_BUTTON_MIDDLE = 2,
MOUSE_BUTTON_4      = 3,
MOUSE_BUTTON_5      = 4,
MOUSE_BUTTON_6      = 5,
MOUSE_BUTTON_7      = 6,
MOUSE_BUTTON_8      = 7,

/* Joystick identifiers */
JOYSTICK_1          = 0,
JOYSTICK_2          = 1,
JOYSTICK_3          = 2,
JOYSTICK_4          = 3,
JOYSTICK_5          = 4,
JOYSTICK_6          = 5,
JOYSTICK_7          = 6,
JOYSTICK_8          = 7,
JOYSTICK_9          = 8,
JOYSTICK_10         = 9,
JOYSTICK_11         = 10,
JOYSTICK_12         = 11,
JOYSTICK_13         = 12,
JOYSTICK_14         = 13,
JOYSTICK_15         = 14,
JOYSTICK_16         = 15
};

struct VirtualButton{
	String name;
	eInputCode button;
	bool pressed;
};

struct VirtualAxis{
	String name;
	eInputCode positiveAxis;
	eInputCode negativeAxis;
	bool pressed;
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

private: 
    const VirtualButton * findVirtualButton(const String& name) const;
    const VirtualAxis * findVirtualAxis(const String& name) const;

    Array<VirtualButton> vbtn;
    Array<VirtualAxis> vax;
};

#endif