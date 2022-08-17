#include <TXEngine/TXEngine.hpp>
#include <iostream>

using namespace tx;

void testWindow()
{
    Window* w = new Window(1280, 720, "Hello, TXEngine!");

    while (w->isOpen()) {
        for (const auto& event : *(w->pollEvents())) {
            if (event->getType() == EventType::Closed) {
                w->close();
            }
            else if (event->getType() == EventType::TextEntered) {
                auto c = static_cast<TextEnterEvent*>(event)->getUnicode();
                std::wstring s;
                s.push_back(c);
                std::cout << tx::wstring_to_string(s) << std::endl;
            }
        }

        w->clear();
        w->display();
    }

    delete w;
}

void testShape()
{
    Window* w = new Window(1280, 720, "Hello, TXEngine!");
    w->setViewport({100, 100, 100, 100});

    RectangleShape* r = new RectangleShape(100, 100, 100, 100);
    r->setColor(Color(128, 128, 128));

    Texture* tex = new Texture();
    tex->loadFromFile("wall.png");
    r->setTexture(tex);

    while (w->isOpen()) {
        for (const auto& event : *(w->pollEvents())) {
            if (event->getType() == EventType::Closed) {
                w->close();
            }
        }

        w->clear();
        w->draw(r);
        w->display();
    }
    
    delete tex;
    delete r;
    delete w;
}

void testAudio()
{
    Window* w    = new Window(1280, 720, "testAudio");
    Sound* sound = new Sound();
    sound->loadFromFile("button_click.wav");
    Clock clock;
    bool flag = false;
    while (w->isOpen()) {
        for (const auto* e : *(w->pollEvents())) {
            if (e->getType() == tx::EventType::Closed) {
                w->close();
            }
            else if (e->getType() == tx::EventType::KeyPressed) {
                if (!flag) {
                    sound->play();
                }
                else if (clock.getElapsedTime() > 0.5) {
                    flag = false;
                    clock.restart();
                    
                }
            }
        }

        w->clear();
        w->display();
    }

    delete sound;
    delete w;
}

void testFont()
{
    Window* w  = new Window(640, 360, "testFont");
    Font* font = new Font();
    font->loadFromFile("font.ttc");
    Text* text = new Text(L"Hello, \n\tworldÖÐÎÄ", 100, 100);
    text->setFont(font);
    text->setColor(Color(255, 0, 0));

    RectangleShape* r = new RectangleShape(100, 100, 100, 100);
    r->setColor(Color(128, 128, 128));

    Texture* tex = new Texture();
    tex->loadFromFile("wall.png");
    r->setTexture(tex);

    while (w->isOpen()) {
        for (const auto* e : *(w->pollEvents())) {
            if (e->getType() == tx::EventType::Closed) {
                w->close();
            }
        }

        w->clear();
        w->draw(text);
        w->draw(r);
        w->display();
    }

    delete text;
    delete font;
    delete tex;
    delete r;
    delete w;
}

int main()
{
    testWindow();
    return 0;
}