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
#include <array>

/**
 * Screen borders that are tracked via mouse position
 */
enum class ScreenBorder {
    right = 0,
    bottom,
    left,
    top,

    totalBorders
};

/**
 * Class that binds all input handling together
 */
class InputController {

public:

    InputController(GLFWwindow* p_window);
    ~InputController() = default;

    static b2Vec2 getMousePosition();
    static bool getMouseButtonPressed(int p_button);
    static int getScrollY();
    static bool isMouseAtBorder(ScreenBorder p_border);

private:

    /// GLFW compatible mouse button press handler
    static void handleMousePress(GLFWwindow* p_window, int p_button, int p_action, int p_modbits);

    /// GLFW compatible mouse movement handler
    static void handleMouseMove(GLFWwindow* p_window, double p_positionX, double p_positionY);

    /// GLFW compatible mouse wheel scroll handler
    static void handleMouseWheel(GLFWwindow* p_window, double p_offsetX, double p_offsetY);

    static float m_mouseX;
    static float m_mouseY;
    static int m_scrollY;
    static std::array<bool, 2> m_mouseButton;
    static std::array<bool, 4> m_mouseAtBorder;

};
