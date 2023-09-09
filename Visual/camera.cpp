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

#include "camera.h"

namespace {

/**
 * Rotates a point around (0, 0)
 * @param p_point point to be rotated
 * @param p_angle angle to rotate the point by
 * @return the rotated point
 */
b2Vec2 affineRotate(b2Vec2 p_point, float p_angle) {
    return b2Vec2((p_point.x * cos(p_angle)) - (p_point.y * sin(p_angle)),
                  (p_point.y * cos(p_angle)) + (p_point.x * sin(p_angle)));
};

}; // end of namespace

namespace visual {

void Camera::placePoint(b2Vec2 p_pos) const {
    p_pos -= m_pos;
    p_pos *= m_zoom;
    glVertex2f(p_pos.x, p_pos.y);
}

void Camera::drawPolygon(b2Vec2 p_centre, float p_ang, std::vector<b2Vec2> &p_shape) const {
    glBegin(GL_POLYGON);
        for (auto &point : p_shape) {
            placePoint(p_centre + affineRotate(point, p_ang));
        }
    glEnd();
}

void Camera::drawCircle(b2Vec2 p_centre, float p_radius) const {
    // TODO ACTUAL CIRCLE...
    glBegin(GL_POLYGON);
        placePoint(p_centre + b2Vec2(p_radius, 0.0f));
        placePoint(p_centre + b2Vec2(0.0f, p_radius));
        placePoint(p_centre + b2Vec2(-p_radius, 0.0f));
        placePoint(p_centre + b2Vec2(0.0f, -p_radius));
    glEnd();
}

}; // end of namespace visual
