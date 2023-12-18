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

#include "box2d/box2d.h"
#include <vector>

namespace shadow_pumpkin_caster {

/**
 * Wrapper for button's shape coordinates
 */
struct ButtonCoords {

    ButtonCoords(float p_minX, float p_maxX, float p_minY, float p_maxY):
        m_minX(p_minX), m_maxX(p_maxX), m_minY(p_minY), m_maxY(p_maxY) {
    }

    float m_minX;
    float m_maxX;
    float m_minY;
    float m_maxY;
};

class MenuButton {

public:

    MenuButton(ButtonCoords p_coordShape);
    ~MenuButton() = default;

    void process();

    /**
     * Draws the menu button to the screen
     */
    void draw();

private:

    ButtonCoords m_coordShape;
    std::vector<b2Vec2> m_drawShape;

    bool isMouseHovering();

};

}; // end of namespace shadow_pumpkin_caster
