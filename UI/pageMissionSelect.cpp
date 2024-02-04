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

#include "menuPage.h"
#include "menuButton.h"

namespace {

using ButtonCoords = shadow_pumpkin_caster::ButtonCoords;
using PageReturnData = shadow_pumpkin_caster::PageReturnData;
using PageAction = shadow_pumpkin_caster::PageAction;
using Regions = shadow_pumpkin_caster::Regions;

ButtonCoords shift(ButtonCoords p_coord, float p_shiftX, float p_shiftY) {
    p_coord.m_minX += p_shiftX;
    p_coord.m_maxX += p_shiftX;
    p_coord.m_minY += p_shiftY;
    p_coord.m_maxY += p_shiftY;
    return p_coord;
}

constexpr ButtonCoords kLvlButtonShape() {
    const float kRatioX = 900.0f / 1600.0f;
    const float kLvlButtonLength = 0.125f;
    return {.m_minX = -kLvlButtonLength * kRatioX, .m_maxX = kLvlButtonLength * kRatioX,
            .m_minY = -kLvlButtonLength, .m_maxY = kLvlButtonLength};
}

constexpr ButtonCoords kButtonShape() {
    return {.m_minX = -0.9f, .m_maxX = -0.4f, .m_minY = -0.9f, .m_maxY = -0.65f};
}

constexpr PageReturnData kReturnButtonData() {
    return {.m_action = PageAction::goLevelSelect};
}

constexpr PageReturnData kMainMenuButtonData() {
    return {.m_action = PageAction::goMainMenu};
}

constexpr PageReturnData kLevelButtonData(Regions p_region, unsigned int p_mission) {
    return {.m_action = PageAction::startLevel, .m_region = p_region, .m_mission = p_mission};
}

} // end of namespace

namespace shadow_pumpkin_caster {

void turnToMission(Page &p_page, Regions p_region) {

    resetPage(p_page);
    float shiftY = 0.75f;
    unsigned int levelNumber = 1;
    // set up all 15 level selection buttons
    for (int j = 0; j < 3 ;j++) {
        float shiftX = -0.6f;
        for (int i = 0; i < 5; i++) {
            MenuButton level(shift(kLvlButtonShape(), shiftX, shiftY),
                           kLevelButtonData(p_region, levelNumber));
            shiftX += 0.3;
            addButton(p_page, level);
            levelNumber++;
        }
        shiftY -= 0.5f;
    }
    MenuButton prev(shift(kLvlButtonShape(), -0.9f, 0.25f)); // TODO -- Use different shape
    addButton(p_page, prev);

    MenuButton next(shift(kLvlButtonShape(), 0.9f, 0.25f)); // TODO -- Use different shape
    addButton(p_page, next);

    MenuButton levelSelect(kButtonShape(), kReturnButtonData());
    addButton(p_page, levelSelect);

    MenuButton mainMenu(shift(kButtonShape(), 1.3f, 0.0f), kMainMenuButtonData());
    addButton(p_page, mainMenu);
}

}; // end of namespace shadow_pumpkin_caster
