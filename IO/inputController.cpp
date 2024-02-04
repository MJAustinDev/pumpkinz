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

namespace {

using scrBdr = io::input::ScreenBorder;

constexpr float kScreenBorder() { return 0.9f; }
constexpr float kResolutionWidth() { return 1600.0f; }
constexpr float kResolutionHeight() { return 960.0f; }

/**
 * Converts raw pixel position coordinate to GLFW screen coordinate (-1.0f to 1.0f)
 * @param p_position raw pixel position, assumes 0 is left/top
 * @param p_pixels total size of the screen's dimension in pixels
 * @param p_isAxisX if conversion is horizontal or vertical
 * @return equivalent GLFW screen coordinate
 */
float calcScreenPosition(float p_position, float p_pixels, bool p_isAxisX) {
    p_position /= p_pixels; // calculate percentage of screen, range 0 -> 1
    p_position *= 2.0f; // stretch value to 0 -> 2 range
    p_position -= 1.0f; // shift back to -1 -> 1 range
    return (p_isAxisX) ? p_position : -p_position; // y axis has top as positive
}

/**
 * Checks if the mouse button is currently handled
 * @param p_button button to verify
 * @return if the button is currently handled
 */
bool isMouseButtonValid(int p_button) {
    return (p_button >= GLFW_MOUSE_BUTTON_LEFT) && (p_button <= GLFW_MOUSE_BUTTON_MIDDLE);
}

/**
 * Calculates if a GLFW coordinate is within the border region
 * @param p_position GLFW position to check
 * @param p_threshold GLFW position where the border starts (inclusive)
 * @return true if the coordinate is within the border region
 */
bool isAtBorder(float p_position, float p_threshold = kScreenBorder()) {
    return (p_position >= p_threshold);
}

/**
 * Converts a screen boarder enumeration to an equivalent integer index
 * @param p_border border enumeration to be converted
 * @return the corresponding integer index
 */
int borderToIndex(scrBdr p_border) {
    assert(p_border >= scrBdr::right && p_border < scrBdr::totalBorders); // border out of range
    return static_cast<int>(p_border);
}

/**
 * Given a key code, returns the corresponding position in the boolean key array
 * @param p_key GLFW key code
 * @return index within m_keys if key is supported, -1 if not
 */
int getKeyIndex(int p_key) {
    const int kNumberBeginIndex = 0;
    const int kAlphabetBeginIndex = 10;
    const int kUtilityBeginIndex = 36;

    if (p_key >= GLFW_KEY_0 && p_key <= GLFW_KEY_9) {
        return p_key - GLFW_KEY_0 + kNumberBeginIndex;
    }
    if (p_key >= GLFW_KEY_A && p_key <= GLFW_KEY_Z) {
        return p_key - GLFW_KEY_A + kAlphabetBeginIndex;
    }
    if (p_key >= GLFW_KEY_ESCAPE && p_key <= GLFW_KEY_BACKSPACE) {
        return p_key - GLFW_KEY_ESCAPE + kUtilityBeginIndex;
    }

    return -1; // default not supported
}

}; // end of namespace

namespace io::input {

float InputController::m_mouseX = 0.0f;
float InputController::m_mouseY = 0.0f;
float InputController::m_screenWidth = 0.0f;
float InputController::m_screenHeight = 0.0f;
float InputController::m_viewportRatioX = 0.0f;
float InputController::m_viewportRatioY = 0.0f;
int InputController::m_scrollY = 0;
std::array<bool, 3> InputController::m_mouseButton = {false, false, false};
std::array<bool, 4> InputController::m_mouseAtBorder = {false, false, false, false};
std::array<bool, InputController::kSupportedKeys> InputController::m_keys; // set in constructor
visual::Camera* InputController::m_camera = nullptr;

InputController::InputController(GLFWwindow* p_window, visual::Camera* p_camera) {
    m_camera = p_camera;
    InputController::m_keys.fill(false);
    glfwSetMouseButtonCallback(p_window, handleMousePress);
    glfwSetCursorPosCallback(p_window, handleMouseMove);
    glfwSetScrollCallback(p_window, handleMouseWheel);
    glfwSetKeyCallback(p_window, handleKeyboardInput);
    glfwSetWindowSizeCallback(p_window, handleScreenChange);

    // force screen resolution to be correct
    int screenWidth, screenHeight;
    glfwGetWindowSize(p_window, &screenWidth, &screenHeight);
    handleScreenChange(p_window, screenWidth, screenHeight);
}

b2Vec2 InputController::getMousePosition() {
    return b2Vec2(m_mouseX, m_mouseY);
}

b2Vec2 InputController::getMousePositionInWorld() {
    b2Vec2 mousePosition = b2Vec2(m_mouseX, m_mouseY);
    mousePosition *= (1.0f / m_camera->getZoom()); // divide by camera zoom
    mousePosition += m_camera->getPosition(); // shift by camera's position

    return mousePosition;
}

bool InputController::getMouseButtonPressed(int p_button) {
    return (isMouseButtonValid(p_button)) && (m_mouseButton.at(p_button));
}

int InputController::getScrollY() {
    int scroll = m_scrollY;
    m_scrollY = 0;
    return scroll;
}

bool InputController::isMouseAtBorder(ScreenBorder p_border) {
    return m_mouseAtBorder.at(borderToIndex(p_border));
}

bool InputController::isKeyPressed(int p_key) {
    int keyIndex = getKeyIndex(p_key);
    return (keyIndex != -1) ? m_keys.at(keyIndex) : false;
}

void InputController::handleMousePress(GLFWwindow* p_window, int p_button, int p_action,
                                       int p_modbits) {
    if (isMouseButtonValid(p_button)) {
        switch (p_action) {
            case GLFW_PRESS: { m_mouseButton.at(p_button) = true; break; }
            case GLFW_RELEASE: { m_mouseButton.at(p_button) = false; break;}
            default: { break; }
        }
    }
}

void InputController::handleMouseMove(GLFWwindow* p_window, double p_positionX,
                                      double p_positionY) {
    m_mouseX = calcScreenPosition(static_cast<float>(p_positionX), m_screenWidth, true);
    m_mouseY = calcScreenPosition(static_cast<float>(p_positionY), m_screenHeight, false);

    // shift mouse coordinates relative to view port
    m_mouseX *= m_viewportRatioX;
    m_mouseY *= m_viewportRatioY;

    m_mouseAtBorder.at(borderToIndex(scrBdr::right)) = isAtBorder(m_mouseX);
    m_mouseAtBorder.at(borderToIndex(scrBdr::left)) = isAtBorder(-m_mouseX);
    m_mouseAtBorder.at(borderToIndex(scrBdr::top)) = isAtBorder(m_mouseY);
    m_mouseAtBorder.at(borderToIndex(scrBdr::bottom)) = isAtBorder(-m_mouseY);
}

void InputController::handleMouseWheel(GLFWwindow* p_window, double p_offsetX, double p_offsetY) {
    m_scrollY += static_cast<int>(p_offsetY);
}

void InputController::handleKeyboardInput(GLFWwindow* p_window, int p_key, int p_scancode,
                                          int p_action, int p_modbits) {
    int keyindex = getKeyIndex(p_key);

    if (keyindex != -1) {
        m_keys.at(keyindex) = (p_action == GLFW_PRESS) || (p_action == GLFW_REPEAT);
    }
}

void InputController::handleScreenChange(GLFWwindow* p_window, int p_width, int p_height) {
    float screenWidth = static_cast<float>(p_width);
    float screenHeight = static_cast<float>(p_height);
    float widthRatio = screenWidth / kResolutionWidth();
    float heightRatio = screenHeight / kResolutionHeight();

    float stretch = (widthRatio >= heightRatio) ? heightRatio : widthRatio; // use smallest ratio
    // set view port dimensions
    float vpW = stretch * kResolutionWidth();
    float vpH = stretch * kResolutionHeight();
    // set view port starting points (half of the empty space to centre the screen)
    float vpX = (screenWidth - vpW) / 2.0f;
    float vpY = (screenHeight - vpH) / 2.0f;

    // set tracker variables and resize view port
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_viewportRatioX = screenWidth / vpW;
    m_viewportRatioY = screenHeight / vpH;
    glViewport(vpX, vpY, vpW, vpH);
}

}; // end of namespace io::input
