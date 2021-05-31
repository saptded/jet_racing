//
// Created by Kseny
//

#include "drawableObjects.hpp"

#include "sfColor.hpp"
#include <cmath>

static sfColor colorChoose;

void DrawableArc::draw(sf::RenderWindow &window) {
    for (auto &arc : arcs) {
        window.draw(arc);
    }
}

void DrawableArc::init(int stage) {
    sf::Color color = colorChoose.getWall(stage);
    sf::Color colorTrans = color;
    colorTrans.a -= 55;
    float radius = calcRadius(start, center);
    if (radius != calcRadius(end, center)) {
        std::cout << "wrong arc radius = " << radius << " " << calcRadius(end, center) << std::endl;
    }
    float angleStart = getAngle(center, end);  //поменято сознательно тк исправили направление
    float angleEnd = getAngle(center, start);
    if (angleStart <= angleEnd) {
        angleStart += 2 * M_PI;
    }
    int anglePartsCount = (int)(radius)/2;
    int vertexCount = anglePartsCount*2 + 2;
    float angleStep = (angleEnd - angleStart) / (float)anglePartsCount;
    arcs.resize(3);
    int counter = 0;
    for (int j = -1; j <= 1; j = j+2) {
        float angle = angleStart;
        arcs[counter] = sf::VertexArray(sf::TriangleStrip, vertexCount);
        for (int i = 0; i < vertexCount; i = i+2) {
            arcs[counter][i].position = sf::Vector2f(center.x - radius * cosf(angle), center.y - radius * sinf(angle));
            arcs[counter][i].color = colorTrans;
            arcs[counter][i+1].position = sf::Vector2f(center.x - (radius + j * weightK) * cosf(angle), center.y - (radius + weightK * j) * sinf(angle));
            arcs[counter][i+1].color = sf::Color::Transparent;
            angle += angleStep;
        }
        counter++;
    }
    float angle = angleStart;
    arcs[counter] = sf::VertexArray(sf::TriangleStrip, vertexCount);
    for (int i = 0; i < vertexCount; i = i+2) {
        arcs[counter][i].position = sf::Vector2f(center.x - (radius + weightK/8) * cosf(angle), center.y - (radius + weightK/8) * sinf(angle));
        arcs[counter][i].color = color;
        arcs[counter][i+1].position = sf::Vector2f(center.x - (radius - weightK/8) * cosf(angle), center.y - (radius - weightK/8) * sinf(angle));
        arcs[counter][i+1].color = color;
        angle += angleStep;

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

void DrawableLine::draw(sf::RenderWindow &window) {
    for (auto &line : lines) {
        window.draw(line);
    }
}

void DrawableLine::init(int stage) {
    sf::Color color = colorChoose.getWall(stage);
    initFromColor(color);
}

void DrawableLine::initFromColor(sf::Color color) {
    sf::Color colorTrans = color;
    colorTrans.a -= 55;
    // только для вертикальных и гозизонтальных линий
    if (end.y == start.y) { // вертикальные
        int i = 0;
        for (int j = -1; j <= 1; j = j+2) {
            lines[i] = sf::VertexArray(sf::Quads, 4);
            lines[i][0].position = sf::Vector2f(start.x, start.y );
            lines[i][0].color = colorTrans;
            lines[i][1].position = sf::Vector2f(start.x, start.y + j * weightK );
            lines[i][1].color = sf::Color::Transparent;
            lines[i][2].position = sf::Vector2f(end.x, end.y + j * weightK );
            lines[i][2].color = sf::Color::Transparent;
            lines[i][3].position = sf::Vector2f(end.x, end.y );
            lines[i][3].color = colorTrans;
            i++;
        }
        lines[i] = sf::VertexArray(sf::Quads, 4);
        lines[i][0].position = sf::Vector2f(start.x, start.y + weightK/8);
        lines[i][0].color = color;
        lines[i][1].position = sf::Vector2f(start.x, start.y - weightK/8 );
        lines[i][1].color = color;
        lines[i][2].position = sf::Vector2f(end.x, end.y -weightK/8 );
        lines[i][2].color = color;
        lines[i][3].position = sf::Vector2f(end.x, end.y + weightK/8 );
        lines[i][3].color = color;
    } else if (end.x == start.x) { // горизонтальные
        int i = 0;
        for (int j = -1; j <= 1; j = j+2) {
            lines[i] = sf::VertexArray(sf::Quads, 4);
            lines[i][0].position = sf::Vector2f(start.x, start.y );
            lines[i][0].color = colorTrans;
            lines[i][1].position = sf::Vector2f(start.x + j * weightK, start.y );
            lines[i][1].color = sf::Color::Transparent;
            lines[i][2].position = sf::Vector2f(end.x + j * weightK, end.y );
            lines[i][2].color = sf::Color::Transparent;
            lines[i][3].position = sf::Vector2f(end.x, end.y );
            lines[i][3].color = colorTrans;
            i++;
        }
        lines[i] = sf::VertexArray(sf::Quads, 4);
        lines[i][0].position = sf::Vector2f(start.x + weightK/8, start.y);
        lines[i][0].color = color;
        lines[i][1].position = sf::Vector2f(start.x - weightK/8, start.y );
        lines[i][1].color = color;
        lines[i][2].position = sf::Vector2f(end.x -weightK/8, end.y );
        lines[i][2].color = color;
        lines[i][3].position = sf::Vector2f(end.x + weightK/8, end.y );
        lines[i][3].color = color;
    } else {
        // для остальных - некрасиво
        for (int j = -1; j <= 1; j++) {
            lines[j + 1] = sf::VertexArray(sf::Lines, 2);
            lines[j + 1][0].position = sf::Vector2f(start.x + j * weightK, start.y);
            lines[j + 1][0].color = sf::Color::Magenta;
            lines[j + 1][1].position = sf::Vector2f(end.x + j * weightK, end.y);
            lines[j + 1][1].color = sf::Color::Magenta;
        }
    }
}

void DrawableLine::setWeightK(float k) {
    weightK = k;
}

DrawablePropeller::DrawablePropeller(Point start, Point end, Point center) // пропеллер начинается в горизонтальном положении начало слева
: DrawableObject(start, end, center)
, line(start, end, center)
, arc({center.x, center.y + (end.x - start.x)/6}, {start.x - (end.x - start.x)/6, center.y}, center)
{}

void DrawablePropeller::init(int stage) {
    arc.init(stage);
    line.init(stage);
}

void DrawablePropeller::draw(sf::RenderWindow &window) {
    arc.draw(window);
    line.draw(window);
}

void DrawableLineRect::init(int stage) {
for(auto &line: lineRect){
    line.init(stage);
}
}

void DrawableLineRect::initFromColor(sf::Color color) {
    for(auto &line: lineRect){
        line.initFromColor(color);
    }
}

void DrawableLineRect::draw(sf::RenderWindow &window) {
    for(auto &lines: lineRect){
        lines.draw(window);
    }
}

DrawableLineRect::DrawableLineRect(Point start, Point end, Point center) : DrawableObject(start, end, center) {
    lineRect = {
            DrawableLine(start, {start.x, end.y}, center),
            DrawableLine({start.x, end.y}, end, center),
            DrawableLine({end.x, start.y}, end, center),
            DrawableLine(start, {end.x, start.y}, center),
    };
}

void DrawableLineRect::setWeightK(float k) {
    for(auto &line: lineRect){
        line.setWeightK(k);
    }
}

void DrawableFinish::init(int stage) {
    sf::Color color = colorChoose.finish;
    for(auto &line: lineRect){
        line.initFromColor(color);
    }
}

void DrawablePortal::init(int stage) {
    sf::Color color = colorChoose.finish;
    for(auto &line: lineRect){
        line.initFromColor(color);
    }
}

DrawableDelayer::DrawableDelayer(Point start, Point end, Point center)
    : DrawableObject(start, end, center) {
    rect.setSize(sf::Vector2f(start.x - end.x, start.y - end.y));
    rect.setPosition(sf::Vector2f(end.x, end.y));
    rect.setFillColor(colorChoose.delayer);
}

void DrawableDelayer::draw(sf::RenderWindow &window) { window.draw(rect); }

DrawableAccelerator::DrawableAccelerator(Point start, Point end, Point center)
    : DrawableObject(start, end, center) {
    rect.setSize(sf::Vector2f(start.x - end.x, start.y - end.y));
    rect.setPosition(sf::Vector2f(end.x, end.y));
    rect.setFillColor(colorChoose.accelerator);
}

void DrawableAccelerator::draw(sf::RenderWindow &window) { window.draw(rect); }

DrawableButton::DrawableButton(Point start, Point end, sf::Text& text):
        active(start, end, {0,0}),
        passive(start, end, {0,0}),
        textAct(text),
        textPass(text) {

    float width = textAct.getLocalBounds().width;
    float height = textAct.getLocalBounds().height;

    textAct.setOrigin(width/2, height-10);
    textAct.setPosition((end.x+start.x)/2, (end.y+start.y)/2);
    textAct.setFillColor(colorChoose.menuBright);

    textPass.setOrigin(width/2, height-10);
    textPass.setPosition((end.x+start.x)/2, (end.y+start.y)/2);
    textPass.setFillColor(colorChoose.menuDark);

    init();
}

void DrawableButton::init() {
    active.setWeightK(10.0f);
    active.initFromColor(colorChoose.menuBright);

    passive.setWeightK(10.0f);
    passive.initFromColor(colorChoose.menuDark);
}

void DrawableButton::draw(bool isActive, sf::RenderWindow &window) {
    if(isActive){
        window.draw(textAct);
        active.draw(window);
    }else{
        window.draw(textPass);
        passive.draw(window);
    }
}
