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
#include <vector>

namespace visual {

class Camera {

public:

    Camera() = default;
    ~Camera() = default;

    float getZoom() { return m_zoom; };

    b2Vec2 getPosition() { return m_pos; };

    /**
     * Draws a polygon to the screen
     * @param p_centre polygons centre in the world
     * @param p_angle of the polygon
     * @param p_shape all coordinates of the polygon
     */
    void drawPolygon(b2Vec2 p_centre, float p_angle, std::vector<b2Vec2> &p_shape) const;

    /**
     * Draws a circle to the screen
     * @param p_centre circles centre in the world
     * @param p_angle angle of the circle
     * @param p_radius radius of the circle
     */
    void drawCircle(b2Vec2 p_centre, float p_angle, float p_radius) const;

private:

    /**
     * Places a point to the screen relative to the camera's position
     * @param p_pos position of the point in the world
     */
    void placePoint(b2Vec2 p_pos) const;

    float m_zoom = 0.01f;
    b2Vec2 m_pos = b2Vec2(40.0f, 0.0f);

};

}; // end of namespace visual
