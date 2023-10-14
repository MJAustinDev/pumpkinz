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
#include <iostream> // TODO REMOVE LATER ON

class InputController {

public:

    InputController(GLFWwindow* p_window) {
        assert((++m_instances) <= 1); // should only have 1 input controller
        glfwSetMouseButtonCallback(p_window, handleMousePress);
        glfwSetCursorPosCallback(p_window, cursor_position_callback);
        glfwSetScrollCallback(p_window, scroll_callback);
    };
    ~InputController() = default;

private:

    static void handleMousePress(GLFWwindow* window, int button, int action, int mods) {
        std::cout << "B: " << button << ", " << action << "\n";
    };

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        std::cout << xpos << ", " << ypos << '\n';
    }

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        std::cout << "X: " << xoffset << ", " << yoffset << "\n";
    }

    static unsigned int m_instances;

};

unsigned int InputController::m_instances = 0u;
