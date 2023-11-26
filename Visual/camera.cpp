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

/// how many sides a 'circle' should have
constexpr int kCircleResolution() { return 12; };

/// angular size of each circle segment
constexpr float kSegmentSize() { return (2.0f * M_PI) / static_cast<float>(kCircleResolution()); }

constexpr float kMinimumZoom() { return 0.01f; }
constexpr float kMaximumZoom() { return 0.2f; }

}; // end of namespace

namespace visual {

void Camera::moveBy(b2Vec2 p_position, float p_zoom) {
    m_position += p_position;
    m_zoom += p_zoom;
    catchZoom();
}

void Camera::placePoint(b2Vec2 p_position) const {
    p_position -= m_position;
    p_position *= m_zoom;
    glVertex2f(p_position.x, p_position.y);
}

void Camera::drawPolygon(b2Vec2 p_centre, float p_angle, std::vector<b2Vec2> &p_shape) const {
    glBegin(GL_POLYGON);
        for (auto &point : p_shape) {
            placePoint(p_centre + affineRotate(point, p_angle));
        }
    glEnd();
}

void Camera::drawCircle(b2Vec2 p_centre, float p_angle, float p_radius) const {
    glBegin(GL_POLYGON);
    for (int i=0; i < kCircleResolution(); i++) {
        float angle = (i * kSegmentSize()) + p_angle;
        placePoint(p_centre + affineRotate(b2Vec2(p_radius, 0.0f), angle));
    }
    glEnd();
}

void Camera::catchZoom() {
    if (m_zoom < kMinimumZoom()) {
        m_zoom = kMinimumZoom();
    } else if (m_zoom > kMaximumZoom()) {
        m_zoom = kMaximumZoom();
    }
}

}; // end of namespace visual
