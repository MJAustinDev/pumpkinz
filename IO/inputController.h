/**
 * MIT License
 *
 * Copyright (c) 2023-2024 Matthew James Austin
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
#include "camera.h"

namespace io::input {

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

    InputController(GLFWwindow* p_window, visual::Camera* p_camera);
    ~InputController() = default;

    static b2Vec2 getMousePosition();
    static b2Vec2 getMousePositionInWorld();
    static bool getMouseButtonPressed(int p_button);
    static int getScrollY();
    static bool isMouseAtBorder(ScreenBorder p_border);
    static bool isKeyPressed(int p_key);

    static const int kSupportedKeys = 10 + 26 + 4; // 0-9 + a-z + escape-enter-tab-backspace

private:

    /// GLFW compatible mouse button press handler
    static void handleMousePress(GLFWwindow* p_window, int p_button, int p_action, int p_modbits);

    /// GLFW compatible mouse movement handler
    static void handleMouseMove(GLFWwindow* p_window, double p_positionX, double p_positionY);

    /// GLFW compatible mouse wheel scroll handler
    static void handleMouseWheel(GLFWwindow* p_window, double p_offsetX, double p_offsetY);

    /// GLFW compatible key press handler
    static void handleKeyboardInput(GLFWwindow* p_window, int p_key, int p_scancode, int p_action,
                                    int p_modbits);

    /// GLFW compatible handler that resizes the view port
    static void handleScreenChange(GLFWwindow* p_window, int p_width, int p_height);

    static float m_mouseX;
    static float m_mouseY;
    static float m_screenWidth;
    static float m_screenHeight;
    static float m_viewportRatioX;
    static float m_viewportRatioY;
    static int m_scrollY;
    static std::array<bool, 3> m_mouseButton;
    static std::array<bool, 4> m_mouseAtBorder;
    static std::array<bool, kSupportedKeys> m_keys;
    static visual::Camera* m_camera; // none owning

};

}; // end of namespace io::input
