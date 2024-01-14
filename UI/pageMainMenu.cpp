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

#include "menuPage.h"
#include "menuButton.h"

namespace {

using ButtonCoords = shadow_pumpkin_caster::ButtonCoords;
using PageReturnData = shadow_pumpkin_caster::PageReturnData;
using PageAction = shadow_pumpkin_caster::PageAction;

ButtonCoords shift(ButtonCoords p_coord, float p_shift) {
    p_coord.m_minY += p_shift;
    p_coord.m_maxY += p_shift;
    return p_coord;
}

constexpr ButtonCoords kButtonShape() {
    return {.m_minX = -0.5f, .m_maxX = 0.5f, .m_minY = -0.1f, .m_maxY = 0.2f};
}

constexpr float kPlayGamePos() { return 0.7f; }
constexpr float kLevelSelectPos() { return 0.2f; }
constexpr float kHelpPos() { return -0.3f; }
constexpr float kQuitPos() { return -0.8f; }

PageReturnData selectLevel() {
    return {.m_action = PageAction::goLevelSelect};
}

PageReturnData quitGame() {
    return {.m_action = PageAction::quit};
}

} // end of namespace

namespace shadow_pumpkin_caster {

void turnToMainMenu(Page &p_page) {
    resetPage(p_page);

    MenuButton playGame(shift(kButtonShape(), kPlayGamePos()));
    addButton(p_page, playGame);

    MenuButton levelSelect(shift(kButtonShape(), kLevelSelectPos()), selectLevel);
    addButton(p_page, levelSelect);

    MenuButton help(shift(kButtonShape(), kHelpPos()));
    addButton(p_page, help);

    MenuButton quit(shift(kButtonShape(), kQuitPos()), quitGame);
    addButton(p_page, quit);
}

}; // end of namespace shadow_pumpkin_caster
