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

#include <cmath>
#include "player.h"
#include "inputController.h"
#include <iostream>

Player::Player(b2World* p_world, b2Vec2 p_position):
    m_world(p_world), m_position(p_position) {

}

void Player::processEvents() {
    b2Vec2 mousePosition = InputController::getMousePosition();
    mousePosition;
    mousePosition.x /= 0.01f; // TODO ASSUMING CONSTANT ZOOM, ADDRESS THIS LATER
    mousePosition.y /= 0.01f;
    mousePosition -= m_position;

    m_angle = std::atan2(mousePosition.y, mousePosition.x);
}

void Player::draw(const visual::Camera &p_camera) {
    glColor4f(0.75f, 0.34f, 0.79f, 0.75f);
    p_camera.drawCircle(m_position, 0.0f, 1.0f);
    p_camera.drawPolygon(m_position, m_angle, m_arrow);

}
