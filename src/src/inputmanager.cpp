#include "../include/glinclude.h"
#include "../include/inputmanager.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include <math.h>
#include <stdlib.h>

bool InputManager::Init()
{
    return true;
}

void InputManager::End()
{
}

bool InputManager::IsOk()
{
    return true;
}

void InputManager::Update()
{
}

void InputManager::CreateVirtualButton(const String& name, eInputCode button)
{
    //recorre el array para editar una tecla si se repite la acción
    for (int i = 0; i < vbtn.Size(); i++){
        if (vbtn[i].name == name)
            vbtn[i].button == button;
        else{
            //crea un boton virtual
            VirtualButton vb = {name, button, false};
            //inserta el boton virtual en el array
            vbtn.Add(vb);
        }
    }
}

void InputManager::CreateVirtualAxis(const String& name, eInputCode positiveAxis, eInputCode negativeAxis)
{
    //recorre el array para editar un eje si se repite la acción
    for (int i = 0; i < vax.Size(); i++){
        if (vax[i].name == name){
            vax[i].positiveAxis == positiveAxis;
            vax[i].negativeAxis == negativeAxis;
        }
        else{
            //crea un boton virtual
            VirtualAxis va = {name, positiveAxis,negativeAxis, false};
            //inserta el boton virtual en el array
            vax.Add(va);
        }
    }
}

bool InputManager::IsVirtualButtonPressed(const String& name) const
{
    const VirtualButton * vb = NULL;

    if (vb = findVirtualButton(name))
        return vb->pressed;

    return false;
}

bool InputManager::IsVirtualButtonDown(const String& name) const
{
    return IsVirtualButtonPressed(name);
}

bool InputManager::IsVirtualButtonUp(const String& name) const
{
    return !IsVirtualButtonPressed(name);
}

float InputManager::GetVirtualAxis(String name) const
{
    return 0.f;
}

bool InputManager::IsKeyPressed(eInputCode vkCode)
{
    return glfwGetKey(vkCode) == GLFW_PRESS;
}

bool InputManager::IsKeyDown(eInputCode vkCode)
{
    return IsKeyPressed(vkCode);
}

bool InputManager::IsKeyUp(eInputCode vkCode)
{
    return !IsKeyPressed(vkCode);
}

bool InputManager::IsMouseButtonPressed(eInputCode button)
{
    return glfwGetMouseButton(button) == GLFW_PRESS;
}

bool InputManager::GetMouseButtonDown(eInputCode button)
{
    return IsMouseButtonPressed(button);
}

bool InputManager::GetMouseButtonUp(eInputCode button)
{
    return !IsMouseButtonPressed(button);
}

const VirtualButton * InputManager::findVirtualButton(const String& name) const
{
    for (int i = 0; i < vbtn.Size(); i++)
    {
        if (name == vbtn[i].name)
            return &vbtn[i];
    }
}

const VirtualAxis * InputManager::findVirtualAxis(const String& name) const
{
    for (int i = 0; i < vax.Size(); i++)
    {
        if (name == vax[i].name)
            return &(vax[i]);
    }
}