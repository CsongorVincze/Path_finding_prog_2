// Csongor BG8SFC
#include "GrafMuveletek.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <cmath>
#include <ctime>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <tuple>
#include <vector>

int main() {
    try {
        srand(static_cast<unsigned int>(time(0)));

        // Ez a blokk az eredeti főprogram gráfkészítő része.
        Graf<Node> Graph_1 = SweepNodes(10);
        Graph_1[0].GetNumNodes();
        Graph_1[0].GetAllNodes();
        RndConnect(Graph_1, 10);

        std::cout << std::endl << std::endl;
        // Az eredeti program is konzolra írta a random kapcsolatrendszert.
        PrintGraph(Graph_1);
        // Kötelező perzisztencia: a random gráfot elmentjük szövegfájlba.
        SaveGraph(Graph_1, "graf_mentes.txt");

        // A Dijkstra algoritmus kiindulópontja változatlanul a 0. csúcs.
        Graph_1[0].Set_dist(0);
        Dijkstra(Graph_1, 0);

        int destination;
        std::cout << "What's your destination?" << std::endl;
        std::cin >> destination;
        // A Trace csak a célindexet kapja meg, ahogy az eredeti programban is.
        std::vector<int> tr = Trace(Graph_1, destination);

        sf::Font font;
        if (!font.openFromFile("Retro Floral.otf")) {
            throw std::runtime_error("Nem sikerült megnyitni a betűtípust.");
        }

        // Az SFML ablak és a rajzolási ciklus az eredeti vizuális rész megőrzése.
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Gráf Vizualizáció (SFML)");
        window.setFramerateLimit(60);

        while (window.isOpen()) {
            while (const std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
            }

            window.clear(sf::Color(35, 35, 45)); // Sötét háttér.

            // Az irányítatlan éleket csak egyszer gyűjtjük ki, hogy ne rajzolódjanak duplán.
            std::vector<std::tuple<int, int, int> > edges;
            for (int i = 0; i < Node::NumNodes; ++i) {
                std::vector<Ut> connections = Graph_1[i].GetConnections();
                for (std::vector<Ut>::iterator conn = connections.begin();
                     conn != connections.end(); ++conn) {
                    if (i < conn->GetCel()) {
                        edges.push_back(std::make_tuple(i, conn->GetCel(), conn->GetSuly()));
                    }
                }
            }

            // Szürke élek és rózsaszín súlyfeliratok rajzolása.
            for (std::vector<std::tuple<int, int, int> >::const_iterator edge = edges.begin();
                 edge != edges.end(); ++edge) {
                sf::VertexArray line(sf::PrimitiveType::Lines, 2);
                line[0].position = sf::Vector2f(Graph_1[std::get<0>(*edge)].GetX(),
                                                Graph_1[std::get<0>(*edge)].GetY());
                line[0].color = sf::Color(180, 180, 180, 150);

                line[1].position = sf::Vector2f(Graph_1[std::get<1>(*edge)].GetX(),
                                                Graph_1[std::get<1>(*edge)].GetY());
                line[1].color = sf::Color(180, 180, 180, 150);

                sf::Text text(font);
                text.setCharacterSize(12);
                // A feladatkérés szerint a gráf feliratai rózsaszínek.
                text.setFillColor(sf::Color(255, 105, 180));
                text.setString(std::to_string(std::get<2>(*edge)));

                // Az élsúly felirata az él két végpontja közé kerül.
                float midX = static_cast<float>(Graph_1[std::get<1>(*edge)].GetX() +
                                                Graph_1[std::get<0>(*edge)].GetX()) / 2;
                float midY = static_cast<float>(Graph_1[std::get<1>(*edge)].GetY() +
                                                Graph_1[std::get<0>(*edge)].GetY()) / 2;
                text.setPosition({midX, midY});

                window.draw(text);
                window.draw(line);
            }

            // A megtalált útvonal piros vastag vonallal jelenik meg.
            for (std::size_t k = 0; k + 1 < tr.size(); ++k) {
                int n1 = tr[k];
                int n2 = tr[k + 1];

                float x1 = static_cast<float>(Graph_1[n1].GetX());
                float y1 = static_cast<float>(Graph_1[n1].GetY());
                float x2 = static_cast<float>(Graph_1[n2].GetX());
                float y2 = static_cast<float>(Graph_1[n2].GetY());

                float length = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
                float angle = std::atan2(y2 - y1, x2 - x1) * 180.f / 3.14159265f;

                // Vastag téglalapból lesz az útvonal szakasza.
                sf::RectangleShape thickLine(sf::Vector2f(length, 5.f));
                thickLine.setOrigin({0.f, 2.5f});
                thickLine.setPosition({x1, y1});
                thickLine.setRotation(sf::degrees(angle));
                thickLine.setFillColor(sf::Color(255, 50, 50, 200));

                window.draw(thickLine);
            }

            // Csúcsok és a Dijkstra távolságértékek kirajzolása.
            double node_radius = 5.0;
            for (int i = 0; i < Node::NumNodes; ++i) {
                sf::CircleShape circle(static_cast<float>(node_radius));
                circle.setFillColor(sf::Color(70, 200, 120));
                circle.setOutlineThickness(3.0);
                circle.setOutlineColor(sf::Color(255, 255, 255));

                circle.setPosition({
                    static_cast<float>(Graph_1[i].GetX() - node_radius),
                    static_cast<float>(Graph_1[i].GetY() - node_radius)
                });
                window.draw(circle);

                int node_label = Graph_1[i].GetIndexScilent();
                int dist_val = static_cast<int>(Graph_1[i].Get_dist());
                const sf::Vector2f node_label_position(
                    static_cast<float>(Graph_1[i].GetX() + node_radius + 8.0),
                    static_cast<float>(Graph_1[i].GetY() - node_radius - 4.0)
                );
                const sf::Vector2f dist_label_position(
                    static_cast<float>(Graph_1[i].GetX() + node_radius + 8.0),
                    static_cast<float>(Graph_1[i].GetY() + node_radius + 2.0)
                );

                // A csúcs saját indexcímkéje sötétkék, hogy elkülönüljön a távolságtól.
                sf::Text node_shadow(font);
                node_shadow.setCharacterSize(22);
                node_shadow.setFillColor(sf::Color(245, 245, 255, 230));
                node_shadow.setString(std::to_string(node_label));
                node_shadow.setPosition({node_label_position.x + 2.f, node_label_position.y + 2.f});
                window.draw(node_shadow);

                sf::Text node_text(font);
                node_text.setCharacterSize(22);
                node_text.setFillColor(sf::Color(0, 0, 128));
                node_text.setString(std::to_string(node_label));
                node_text.setPosition(node_label_position);
                window.draw(node_text);

                // A Dijkstra-távolság rózsaszín címkeként, külön sorban jelenik meg.
                sf::Text dist_shadow(font);
                dist_shadow.setCharacterSize(18);
                dist_shadow.setFillColor(sf::Color(10, 10, 15, 230));
                dist_shadow.setString(std::to_string(dist_val));
                dist_shadow.setPosition({dist_label_position.x + 2.f, dist_label_position.y + 2.f});
                window.draw(dist_shadow);

                sf::Text dist_text(font);
                dist_text.setCharacterSize(18);
                dist_text.setFillColor(sf::Color(255, 105, 180));
                dist_text.setString(std::to_string(dist_val));
                dist_text.setPosition(dist_label_position);
                window.draw(dist_text);
            }

            window.display();
        }
    } catch (const std::exception& hiba) {
        std::cerr << "Hiba: " << hiba.what() << std::endl;
        return 1;
    }

    return 0;
}
