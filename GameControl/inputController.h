/**
 * MIT License
 *
 * Copyright (c) 2023 Matthew James Austin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "GLFW/glfw3.h"
#include "box2d/box2d.h"

class InputController {

public:

    InputController(GLFWwindow* p_window) {
        glfwSetMouseButtonCallback(p_window, handleMousePress);
        glfwSetCursorPosCallback(p_window, handleMouseMove);
        glfwSetScrollCallback(p_window, handleMouseWheel);
    };
    ~InputController() = default;

    b2Vec2 getMousePosition() { return b2Vec2(m_mouseX, m_mouseY); };

private:

    static void handleMousePress(GLFWwindow* p_window, int p_button, int p_action, int p_modbits) {
    };

    static void handleMouseMove(GLFWwindow* p_window, double p_positionX, double p_positionY) {
        m_mouseX = static_cast<float>(p_positionX);
        m_mouseY = static_cast<float>(p_positionY);
    };

    static void handleMouseWheel(GLFWwindow* p_window, double p_offsetX, double p_offsetY) {
    };

    static float m_mouseX;
    static float m_mouseY;

};

float InputController::m_mouseX = 0.0f;
float InputController::m_mouseY = 0.0f;
