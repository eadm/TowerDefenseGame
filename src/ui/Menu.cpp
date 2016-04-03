//
// Created by Руслан Давлетшин on 02/04/16.
//

#include "../../include/ui/Menu.h"

bool contains(RectangleShape &rect, Vector2f &pos) {
    FloatRect f = rect.getGlobalBounds();
    return (f.left <= pos.x && pos.x <= f.left + f.width) &&
           (f.top <= pos.y && pos.y <= f.top + f.height);
}

Menu::Menu() : window(VideoMode(Menu::wX, Menu::wY), "Menu", Style::Titlebar | Style::Close) {
    window.setFramerateLimit(30);
    Image icon;
    if (!icon.loadFromFile("assets/Textures/icon.png")) {
        return;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Menu::start() {
    Texture left_t, right_t;
    if (!left_t.loadFromFile("assets/Textures/left.png")) {
        return;
    }

    if (!right_t.loadFromFile("assets/Textures/right.png")) {
        return;
    }

    Sprite left, right;
    left.setTexture(left_t);
    left.setOrigin(32 / 2, 32 / 2);
    right.setTexture(right_t);
    right.setOrigin(32 / 2, 32 / 2);


    Font font;
    if (!font.loadFromFile("assets/Fonts/SF-UI-Text-Regular.otf")) {
        return;
    }
    Text text("", font, Settings::S_32.font);

    RectangleShape rect(Vector2f(wX, 100));
    rect.setOrigin(wX / 2, 50);
    rect.setFillColor(Color(62, 96, 111));

    RectangleShape btn_rect(Vector2f(20 * 3, 100));
    btn_rect.setOrigin(20 * 3 / 2, 50);
    btn_rect.setFillColor(Color(62, 96, 111));

    Vector2f mouseMove(-1, -1);
    Vector2f mousePress(-1, -1);

    bool clicked = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseMoved) {
                mouseMove.x = event.mouseMove.x;
                mouseMove.y = event.mouseMove.y;
            }

            if (event.type == Event::MouseButtonPressed) {
                mousePress.x = event.mouseButton.x;
                mousePress.y = event.mouseButton.y;
                clicked = true;
            }

            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        window.clear(Color(25, 52, 65));

        text.setColor(Color(209, 219, 189));
        for (size_t i = 0; i < 2; i++) {
            btn_rect.setPosition(32, 100 * i + 50);
            if (contains(btn_rect, mouseMove)) { // hover effect
                window.draw(btn_rect);
            }

            if (contains(btn_rect, mousePress) && clicked) { // click left effect
                clicked = false;
                if (positions[i] == 0) {
                    positions[i] = sizes[i] - 1;
                } else {
                    positions[i]--;
                }
            }

            left.setPosition(32, 100 * i + 50);
            window.draw(left);

            btn_rect.setPosition(wX - 32, 100 * i + 50);
            if (contains(btn_rect, mouseMove)) { // hover effect
                window.draw(btn_rect);
            }

            if (contains(btn_rect, mousePress) && clicked) { // click right effect
                clicked = false;
                if (positions[i] == sizes[i] - 1) {
                    positions[i] = 0;
                } else {
                    positions[i]++;
                }
            }

            right.setPosition(wX - 32, 100 * i + 50);
            window.draw(right);

            text.setPosition(wX / 2, 100 * i + 20);
            text.setString(fields[i]);
            text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2 + 5);
            window.draw(text);

            text.setPosition(wX / 2, 100 * i + 70);
            text.setString(values[i][positions[i]]);
            text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2 + 5);
            window.draw(text);
        }

        rect.setPosition(wX / 2, 100 * 2 + 50);
        if (contains(rect, mouseMove)) { // hover effect
            window.draw(rect);
        }

        if (contains(rect, mousePress) && clicked) { // click effect
            clicked = false;

            switch (positions[0]) {
                case 0:
                    CURRENT_SIZES = &Settings::S_48;
                break;
                case 1:
                    CURRENT_SIZES = &Settings::S_32;
                break;
                default:
                    CURRENT_SIZES = &Settings::S_24;
            }
            window.close();

            char** map = readLevel("assets/Levels/01/map");
            Level level("Level 1", map);
            level.start();
        }

        text.setPosition(wX / 2, 100 * 2 + 50);
        text.setString(start_button);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2 + 5);
        window.draw(text);

        window.display();
    }
}