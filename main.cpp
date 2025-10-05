#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

enum class CellState { Empty, Wall };

int main() {
    const int windowSize = 400;
    const float rows = 20;
    const float cols = 20;
    const float cellSize = windowSize / rows;

    // Grid state: all cells start as Empty
    std::vector<std::vector<CellState>> grid(rows, std::vector<CellState>(cols, CellState::Empty));

    sf::RenderWindow window(sf::VideoMode({windowSize, windowSize}), "Pathfinding Grid");

    while (window.isOpen()) {
        while (auto eventOpt = window.pollEvent()) {
            auto& event = *eventOpt;

            // Close window
            if (event.is<sf::Event::Closed>()) {
                window.close();
            }

            // Mouse click
            if (auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    int col = mouse->position.x / cellSize;
                    int row = mouse->position.y / cellSize;

                    // Toggle wall
                    if (row >= 0 && row < rows && col >= 0 && col < cols) {
                        if (grid[row][col] == CellState::Empty)
                            grid[row][col] = CellState::Wall;
                        else
                            grid[row][col] = CellState::Empty;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        // Draw grid
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition({col * cellSize, row * cellSize});

                if (grid[row][col] == CellState::Empty)
                    cell.setFillColor(sf::Color::White);
                else if (grid[row][col] == CellState::Wall)
                    cell.setFillColor(sf::Color::Black);

                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}
