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

#include <vector>
#include <string>

#include <TXEngine/Export.hpp>
#include <TXEngine/Event/EventBase.hpp>
#include <TXEngine/Graphics/Color.hpp>
#include <TXEngine/Graphics/Drawable.hpp>
#include <TXEngine/OpenGL/Shader.hpp>

namespace tx
{

/**
 * 窗口
 */
class TX_API Window
{
private:
    struct WindowData {
        Window* window;
    } * m_data;

    void* m_windowHandle;

    int m_width, m_height;
    std::string m_title;
    bool m_open;

    EventList* eventList;

    Shader* shader;

    static void initGLFW();
    static void initGLAD();
    void initOpenAL();
    void initWindow();
    void initCallback() const;
    void initShader();

public:
    Window(int width, int height, const std::string& title);
    ~Window();

    /**
     * 窗口是否处于开启状态
     */
    [[nodiscard]] bool isOpen() const;

    /**
     * 是否启用垂直同步
     */
    void setVSync(bool enable);

    /**
     * 处理事件
     * @return 事件列表
     */
    const EventList* pollEvents() const;

    /**
     * 关闭窗口
     */
    void close();

    /**
     * 绘制对象
     */
    void draw(Drawable* drawable);

    /**
     * 清空屏幕
     */
    void clear(Color color = Color::Black);

    /**
     * 将所有绘制渲染到窗口上
     */
    void display() const;
};

}// namespace tx