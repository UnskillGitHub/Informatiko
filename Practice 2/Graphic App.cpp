#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>
#include <string>

void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); 

        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphs");

    sf::CircleShape userPoint(5);
    userPoint.setFillColor(sf::Color::Green);
    bool userPointExists = false;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300);
    xAxis[0].color = sf::Color::White;
    xAxis[1].position = sf::Vector2f(750, 300);
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50);
    yAxis[0].color = sf::Color::White;
    yAxis[1].position = sf::Vector2f(400, 550);
    yAxis[1].color = sf::Color::White;

    const float SCALE_X = 30.0f;
    const float SCALE_Y = 25.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    float mathX = (mousePos.x - 400) / SCALE_X;
                    float mathY = -(mousePos.y - 300) / SCALE_Y;

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    float y1 = std::abs(mathX);
                    float y2 = 3.0f;
                    std::string zone = "";

                    if (std::abs(mathY - y1) < 0.15f || std::abs(mathY - y2) < 0.15f) {
                        zone = "Granitsa";
                    }
                    else if (mathY > y1 && mathY < y2) {
                        zone = "Zone 1";
                    }
                    else if (mathY > y1 && mathY > y2) {
                        zone = "Zone 2";
                    }
                    else if (mathY < y1 && mathY > y2 && mathX < -3.0f) {
                        zone = "Zone 3";
                    }
                    else if (mathY < y1 && mathY > y2 && mathX > 3.0f) {
                        zone = "Zone 4";
                    }
                    else {
                        zone = "Zone 5";
                    }

                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + ") | " + zone);
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(xAxis);
        window.draw(yAxis);

        drawGraph(window, [](float x) { return std::abs(x); }, -10, 10, SCALE_X, SCALE_Y, sf::Color::Red);
        drawGraph(window, [](float x) { return 3.0f; }, -10, 10, SCALE_X, SCALE_Y, sf::Color::Blue);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        window.display();
    }

    return 0;
}
