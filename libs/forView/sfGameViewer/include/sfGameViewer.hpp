#pragma once

#include "response.hpp"
#include "gameViewer.hpp"

#include <iostream>
#include <optional>
#include "sfViewerDetails.hpp"

class sfGameViewer : public GameViewer {
public:
    sfGameViewer();
    void render(std::shared_ptr<Response> data) override;
    Command handleButtonEvent() override;
    void close() override;

private:
    void renderRacer(std::shared_ptr<Response> data);
    void renderEnemies(std::shared_ptr<Response> data);
    void renderMap(std::shared_ptr<Response> data);
    void increaseStage(std::shared_ptr<Response> data);
    void displayWindow();

    std::unique_ptr<sfViewerDetails> details;
    int stage = 0;

    sf::RenderWindow dist;
};
