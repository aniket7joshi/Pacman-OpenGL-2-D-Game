#include "main.h"

#ifndef MagnetRectangle_H
#define MagnetRectangle_H


class MagnetRectangle {
public:
    MagnetRectangle() {}
    MagnetRectangle(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H

MagnetRectangle::MagnetRectangle(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.0;
    
    static GLfloat vertex_buffer_data[] = {
        -2.5, 3.75, 0,
        -2.25, 3.75, 0,
        -2.25, 3.5, 0,
        -2.25, 3.5, 0,
        -2.5, 3.5, 0,
        -2.5, 3.75, 0,
        -2.5, 2.5, 0,
        -2.25, 2.5, 0,
        -2.25, 2.25, 0,
        -2.25, 2.25, 0,
        -2.5, 2.25, 0,
        -2.5, 2.5, 0
    };
 
    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color, GL_FILL);
}

void MagnetRectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate  (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void MagnetRectangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void MagnetRectangle::tick() {
   // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t MagnetRectangle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
