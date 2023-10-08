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

#include <vector>

#include "dynamicEntity.h"

namespace entity {

/**
 * Base polygon entity, defines the polygon shape of the entity
 */
class PolygonEntity : public DynamicEntity {

public:

    /**
     * @param p_world box2d world that the entity exists within
     * @param p_position entity's position in the world
     * @param p_radius radius of the targets circular shape
     */
    PolygonEntity(b2World &p_world, b2Vec2 p_position, std::vector<b2Vec2> p_shape);
    ~PolygonEntity() = default;

    /**
     * See base class
     */
    void processEvents() = 0;

    /**
     * See base class
     */
    void draw(const visual::Camera &p_camera) override;

private:

    std::vector<b2Vec2> m_shape;

};

}; // end of namespace entity