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

#include "inputController.h"

float InputController::m_mouseX = 0.0f;
float InputController::m_mouseY = 0.0f;
std::array<bool, 2> InputController::m_mouseButton = {false, false};
int InputController::m_scrollY = 0;

InputController::InputController(GLFWwindow* p_window) {
    glfwSetMouseButtonCallback(p_window, handleMousePress);
    glfwSetCursorPosCallback(p_window, handleMouseMove);
    glfwSetScrollCallback(p_window, handleMouseWheel);
};

b2Vec2 InputController::getMousePosition() {
    return b2Vec2(m_mouseX, m_mouseY);
};

bool InputController::getMouseButtonPressed(int p_button) {
    return (isMouseButtonValid(p_button)) && (m_mouseButton.at(p_button));
};

int InputController::getScrollY() {
    int scroll = m_scrollY;
    m_scrollY = 0;
    return scroll;
};

void InputController::handleMousePress(GLFWwindow* p_window, int p_button, int p_action,
                                       int p_modbits) {
    if (isMouseButtonValid(p_button)) {
        switch (p_action) {
            case GLFW_PRESS: { m_mouseButton.at(p_button) = true; break; }
            case GLFW_RELEASE: { m_mouseButton.at(p_button) = false; break;}
            default: { break; }
        }
    }
};

void InputController::handleMouseMove(GLFWwindow* p_window, double p_positionX,
                                      double p_positionY) {
    m_mouseX = calcScreenPosition(static_cast<float>(p_positionX), 1600, true);
    m_mouseY = calcScreenPosition(static_cast<float>(p_positionY), 900, false);
};

void InputController::handleMouseWheel(GLFWwindow* p_window, double p_offsetX, double p_offsetY) {
    m_scrollY += static_cast<int>(p_offsetY);
};
