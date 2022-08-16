// MIT License
//
// Copyright (c) 2022 Bili-TianX
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <TXEngine/Export.hpp>

namespace tx
{

/**
 * @breif 计时器, 使用glfwGetTime()计时
 *
 */
class TX_API Clock
{
private:
    /**
     * 开始时间
     */
    float m_start;

public:
    /**
     * 创建计时器，并开始计时
     */
    Clock();

    /**
     * 重启计时器，并返回经过的时间
     * @return 经过的时间
     * @see Clock::getElapsedTime()
     */
    float restart();

    /**
     * @return 从开始计时到现在所经过的时间
     * @see Clock::restart()
     */
    float getElapsedTime();
};

}// namespace tx
