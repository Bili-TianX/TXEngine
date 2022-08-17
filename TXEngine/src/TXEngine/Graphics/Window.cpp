#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <al/alut.h>

#include <TXEngine/Event.hpp>
#include <TXEngine/Graphics/Window.hpp>
#include <TXEngine/OpenGL/GLUtil.hpp>
#include <TXEngine/Audio/AlUtil.hpp>

namespace tx
{

inline GLFWwindow* getGLFWWindow(void* pointer)
{
    return static_cast<GLFWwindow*>(pointer);
}

Window::Window(int width, int height, const std::string& title)
    : m_width(width)
    , m_height(height)
    , m_title(title)
    , eventList(new EventList())
    , m_data(new WindowData())
{
    initGLFW();
    initWindow();
    initCallback();
    initGLAD();
    initOpenAL();

    setVSync(true);
    this->m_open = true;
    initShader();
}

Window::~Window()
{
    glfwTerminate();
    alutExit();
    delete eventList;
    delete m_data;
}

void Window::initGLFW()
{
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Unable to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::initWindow()
{
    this->m_windowHandle =
            reinterpret_cast<void*>(glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr));

    if (getGLFWWindow(m_windowHandle) == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Unable to init window");
    }

    glfwMakeContextCurrent(getGLFWWindow(m_windowHandle));

    this->m_data->window = this;
    glfwSetWindowUserPointer(getGLFWWindow(this->m_windowHandle), this->m_data);
}

void Window::initCallback() const
{
    auto window = getGLFWWindow(m_windowHandle);

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                ->window->eventList->push_back(new CloseEvent());
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                ->window->eventList->push_back(new ResizeEvent(width, height));
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                    ->window->eventList->push_back(new KeyPressEvent(key));
        }
        else if (action == GLFW_RELEASE) {
            static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                    ->window->eventList->push_back(new KeyReleaseEvent(key));
        }
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        if (action == GLFW_PRESS) {
            static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                    ->window->eventList->push_back(new MouseButtonPressEvent(button));
        }
        else if (action == GLFW_RELEASE) {
            static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                    ->window->eventList->push_back(new MouseButtonReleaseEvent(button));
        }
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                ->window->eventList->push_back(new MouseMoveEvent(xpos, ypos));
    });

    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
        static_cast<Window::WindowData*>(glfwGetWindowUserPointer(window))
                ->window->eventList->push_back(new TextEnterEvent(codepoint));
    });
}

void Window::initGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Unable to init glad");
    }

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Window::initOpenAL()
{
    if (!alutInit(nullptr, nullptr)) {
        throw std::runtime_error("Unable to init alut");
    }

    alCall(alListener3f(AL_POSITION, 0, 0, 0));
    alCall(alListener3f(AL_VELOCITY, 0, 0, 0));
}

void Window::initShader()
{
    shader = getDefaultShader();
    
    setViewport({0, 0, (float) m_width, (float) m_height});
}

void Window::setViewport(const Viewport& viewport)
{
    this->viewport = viewport;

    shader->bind();

    // 缩放
    auto mat1 = glm::mat3x3(2.0 / viewport.width, 0, 0, 0, -2.0 / viewport.height, 0, 0, 0, 1);
    // 平移
    auto mat2 = glm::mat3x3(1, 0, 0, 0, 1, 0, -1, 1, 1);

    auto pos = mat1 * glm::vec3(viewport.x, viewport.y, 1);
    // 平移
    auto mat3 = glm::mat3x3(1, 0, 0, 0, 1, 0, -pos.x, -pos.y, 1);

    glCall(glUniformMatrix3fv(shader->getUniform("windowMatrix"), 1, GL_FALSE, glm::value_ptr(mat3 * mat2 * mat1)));

    shader->unbind();
}

void Window::setVSync(bool enable)
{
    if (enable) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }
}

bool Window::isOpen() const
{
    return m_open;
}

void TX_API Window::close()
{
    m_open = false;
}

void Window::display() const
{
    glfwSwapBuffers(getGLFWWindow(m_windowHandle));
}

void Window::clear(Color color)
{
    auto [r, g, b, a] = color.normalize();

    glCall(glClear(GL_COLOR_BUFFER_BIT));
    glCall(glClearColor(r, g, b, a));
}

const EventList* Window::pollEvents() const
{
    for (const auto event : *eventList) {
        delete event;
    }
    eventList->clear();
    glfwPollEvents();

    return eventList;
}

void Window::draw(Drawable* drawable)
{
    shader->bind();
    drawable->draw(shader);
    shader->unbind();
}

}// namespace tx