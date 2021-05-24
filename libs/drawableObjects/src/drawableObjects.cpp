//
// Created by Kseny
//

#include "drawableObjects.hpp"
#include "sfColor.hpp"
#include <cmath>

static sfColor chooseColor;

static float getAngle(Point &rad, Point &center);
static float calcRadius(Point &one, Point &two);

DrawableArc::DrawableArc(Point _start, Point _end, Point _center)
    : DrawableObject(_start, _end, _center) {
    sf::Color color = chooseColor.getWall(1);
    float radius = calcRadius(start, center);
    if (radius != calcRadius(end, center)) {
        std::cout << "wrong arc radius = " << radius << " " << calcRadius(end, center) << std::endl;
        return;
    }
    float angleStart = getAngle(center, end);  //поменято сознательно тк испраили направление
    float angleEnd = getAngle(center, start);
    if (angleStart < angleEnd) {
        angleStart += 2 * M_PI;
    }
    //    std::cout << "arc " << center.x << ", " << center.y << " : angles st, e : ";
    //    std::cout << angleStart / M_PI * 180 << " " << angleEnd / M_PI * 180 << std::endl;
    int vertexCount = (int)(radius);
    float angleStep = (angleEnd - angleStart) / (float)(vertexCount - 1);
    //    std::cout << " angleStep " << angleStep << std::endl;
    for (int j = -1; j <= 1; j++) {
        float angle = angleStart;
        arcs[j + 1] = sf::VertexArray(sf::LineStrip, vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            arcs[j + 1][i].position = sf::Vector2f(center.x - (radius + j * weightK ) * cosf(angle), center.y - (radius + weightK  * j ) * sinf(angle));
            arcs[j + 1][i].color = color;
            angle += angleStep;
        }
    }
}

void DrawableArc::draw(sf::RenderWindow &window) {
    for (auto &arc : arcs) {
        window.draw(arc);
    }
}

float DrawableArc::calcRadius(Point &one, Point &two) { return sqrtf(powf(one.x - two.x, 2) + powf(one.y - two.y, 2)); }

float DrawableArc::getAngle(Point &_center, Point &rad) {
    float angle;
    if (_center.y - rad.y == 0) {
        if (_center.x > rad.x) {
            angle = 0;
        } else {
            angle = M_PI;
        }
        return angle;
    } else if (_center.x - rad.x == 0) {
        if (_center.y < rad.y) {
            angle = 3 * M_PI / 2;
        } else {
            angle = M_PI / 2;
        }
        return angle;
    }
    angle = acosf((_center.x - rad.x) / calcRadius(_center, rad));
    if (_center.y < rad.y) {
        angle = 2 * M_PI - angle;
    }
    return angle;
}

void DrawableArc::change(int stage) {
    for(auto arc: arcs){
        int linesAmount = arc.getVertexCount();
        for(int i = 0; i < linesAmount; i++){
            arc[i].color = chooseColor.getWall(stage);
        }
    }
}

DrawableLine::DrawableLine(Point _start, Point _end, Point _center)
    : DrawableObject(_start, _end, _center) {
    sf::Color color = chooseColor.getWall(1);
//    // только для вертикальных и гозизонтальных линий
//    if (end.y == start.y) {
//        for (int j = -1; j <= 1; j++) {
//            lines[j + 1] = sf::VertexArray(sf::Lines, 2);
//            lines[j + 1][0].position = sf::Vector2f(start.x, start.y + j * weightK );
//            lines[j + 1][0].color = color;
//            lines[j + 1][1].position = sf::Vector2f(end.x, end.y + j * weightK );
//            lines[j + 1][1].color = color;
//        }
//    } else if (end.x == start.x) {
//        for (int j = -1; j <= 1; j++) {
//            lines[j + 1] = sf::VertexArray(sf::Lines, 2);
//            lines[j + 1][0].position = sf::Vector2f(start.x + j * weightK , start.y);
//            lines[j + 1][0].color = color;
//            lines[j + 1][1].position = sf::Vector2f(end.x + j * weightK , end.y);
//            lines[j + 1][1].color = color;
//        }
//    } else {
//        // для остальных - некрасиво
//        for (int j = -1; j <= 1; j++) {
//            lines[j + 1] = sf::VertexArray(sf::Lines, 2);
//            lines[j + 1][0].position = sf::Vector2f(start.x + j * weightK , start.y);
//            lines[j + 1][0].color = sf::Color::Magenta;
//            lines[j + 1][1].position = sf::Vector2f(end.x + j * weightK , end.y);
//            lines[j + 1][1].color = sf::Color::Magenta;
//        }
//    }
    // только для вертикальных и гозизонтальных линий
    if (end.y == start.y) {
        for (int j = -1; j <= 1; j = j+2) {
            lines[j + 1] = sf::VertexArray(sf::Quads, 4);
            lines[j + 1][0].position = sf::Vector2f(start.x, start.y );
            lines[j + 1][0].color = color + sf::Color::Transparent;
            lines[j + 1][1].position = sf::Vector2f(start.x, start.y + j * weightK );
            lines[j + 1][1].color = sf::Color::Transparent;
            lines[j + 1][2].position = sf::Vector2f(end.x, end.y + j * weightK );
            lines[j + 1][2].color = sf::Color::Transparent;
            lines[j + 1][3].position = sf::Vector2f(end.x, end.y );
            lines[j + 1][3].color = color;
        }
        lines[0] = sf::VertexArray(sf::Quads, 4);
        lines[0][0].position = sf::Vector2f(start.x, start.y + weightK/3);
        lines[0][0].color = color;
        lines[0][1].position = sf::Vector2f(start.x, start.y - weightK/3 );
        lines[0][1].color = color;
        lines[0][2].position = sf::Vector2f(end.x, end.y -weightK/3 );
        lines[0][2].color = color;
        lines[0][3].position = sf::Vector2f(end.x, end.y + weightK/3 );
        lines[0][3].color = color;
    } else if (end.x == start.x) {
        for (int j = -1; j <= 1; j++) {
            lines[j + 1] = sf::VertexArray(sf::Lines, 2);
            lines[j + 1][0].position = sf::Vector2f(start.x + j * weightK , start.y);
            lines[j + 1][0].color = color;
            lines[j + 1][1].position = sf::Vector2f(end.x + j * weightK , end.y);
            lines[j + 1][1].color = color;
        }
    } else {
        // для остальных - некрасиво
        for (int j = -1; j <= 1; j++) {
            lines[j + 1] = sf::VertexArray(sf::Lines, 2);
            lines[j + 1][0].position = sf::Vector2f(start.x + j * weightK , start.y);
            lines[j + 1][0].color = sf::Color::Magenta;
            lines[j + 1][1].position = sf::Vector2f(end.x + j * weightK , end.y);
            lines[j + 1][1].color = sf::Color::Magenta;
        }
    }

}

static sf::RectangleShape generateStdRect(Point start, Point end) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(start.x - end.x, start.y - end.y));
    rect.setPosition(sf::Vector2f(end.x, end.y));
    rect.setFillColor(sf::Color::Yellow);
    return rect;
}

void DrawableLine::draw(sf::RenderWindow &window) {
    for (auto &line : lines) {
        window.draw(line);
    }
}

void DrawableLine::change(int stage) {
    for (auto &line : lines) {
        line[0].color = chooseColor.getWall(stage);
        line[1].color = chooseColor.getWall(stage);
    }
}

DrawablePropeller::DrawablePropeller(Point start, Point end, Point center)
    : DrawableObject(start, end, center) {
    rect = generateStdRect(start, end);
}

void DrawablePropeller::draw(sf::RenderWindow &window) { window.draw(rect); }

void DrawablePropeller::drawDynamic(sf::RenderWindow& window,  Point _start, Point _end, Point _center){
    //посчитать поворот от данных!
    rect.rotate(0.1); // rect.setRotation(angle);
    window.draw(rect);
}

DrawableFinish::DrawableFinish(Point start, Point end, Point center)
    : DrawableObject(start, end, center) {
    rect = generateStdRect(start, end);
}

void DrawableFinish::draw(sf::RenderWindow &window) { window.draw(rect); }

DrawablePortal::DrawablePortal(Point start, Point end, Point center)
    : DrawableObject(start, end, center) {
    rect = generateStdRect(start, end);
}

void DrawablePortal::draw(sf::RenderWindow &window) { window.draw(rect); }

DrawableDelayer::DrawableDelayer(Point start, Point end, Point center)
    : DrawableObject(start, end, center) {
    rect = generateStdRect(start, end);
}

void DrawableDelayer::draw(sf::RenderWindow &window) { window.draw(rect); }

DrawableAccelerator::DrawableAccelerator(Point start, Point end, Point center)
    : DrawableObject(start, end, center) {
    rect = generateStdRect(start, end);
}

void DrawableAccelerator::draw(sf::RenderWindow &window) { window.draw(rect); }

