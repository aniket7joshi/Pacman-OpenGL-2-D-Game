#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float radius, float speed, int flag, color_t color, float inclination);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float inclination;
    float speed;
    float xBot, yBot, xTop, yTop;
    float l;
    int flagPlank;
    float rad;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *plank;
};

#endif // BALL_H
