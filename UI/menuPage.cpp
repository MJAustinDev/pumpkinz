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

namespace shadow_pumpkin_caster {

void resetPage(Page &p_page) {
    p_page.m_buttons.clear();
}

PageType processPage(Page &p_page) {
    for (auto &button : p_page.m_buttons) {
        PageType option = button.process();
        if (option != PageType::none) {
            return option;
        }
    }
    return PageType::none;
}

void drawPage(Page &p_page) {
    for (auto &button : p_page.m_buttons) {
        button.draw();
    }
}

void addButton(Page &p_page, MenuButton &p_button) {
    p_page.m_buttons.push_back(p_button);
}

}; // end of namespace shadow_pumpkin_caster
