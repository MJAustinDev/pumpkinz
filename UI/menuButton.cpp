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

#include "menuButton.h"
#include "camera.h"
#include "inputController.h"

namespace shadow_pumpkin_caster {

MenuButton::MenuButton(ButtonCoords p_coordShape, PageReturnData p_pressedData):
    m_pressedData(p_pressedData), m_coordShape(p_coordShape) {

    m_drawShape = {b2Vec2(m_coordShape.m_minX, m_coordShape.m_maxY),
                   b2Vec2(m_coordShape.m_minX, m_coordShape.m_minY),
                   b2Vec2(m_coordShape.m_maxX, m_coordShape.m_minY),
                   b2Vec2(m_coordShape.m_maxX, m_coordShape.m_maxY)
    };
}

PageReturnData MenuButton::process() {
    if (!isMouseHovering()) {
        m_isHeld = false;
        return kEmptyPageData();
    }

    if (!m_isHeld) {
        m_isHeld = io::input::InputController::getMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
    } else {
        if (!io::input::InputController::getMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            m_isHeld = false;
            return m_pressedData;
        }
    }
    return kEmptyPageData();
}

void MenuButton::draw() {
    float transparency = (isMouseHovering()) ? 1.0f : 0.5f;
    glColor4f(1.0f, 0.6f, 0.1f, transparency);
    io::visual::drawAbsolutePolygon(m_drawShape);
}

bool MenuButton::isMouseHovering() {
    b2Vec2 pos = io::input::InputController::getMousePosition();
    bool isInside = pos.x >= m_coordShape.m_minX && pos.x <= m_coordShape.m_maxX &&
                    pos.y >= m_coordShape.m_minY && pos.y <= m_coordShape.m_maxY;

    return isInside;
}

}; // end of namespace shadow_pumpkin_caster
