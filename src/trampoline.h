#include "main.h"

#ifndef Trampoline_H
#define Trampoline_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y, color_t color);
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

Trampoline::Trampoline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.0;
    static GLfloat vertex_buffer_data[9*360];
    double pi =3.1415926535897;
    double r = 0.25;
    double theta = 180;
    int j = 0;
    vertex_buffer_data[9 * j] = 0;
    vertex_buffer_data[9 * j + 1] = 0;
    vertex_buffer_data[9 * j + 2] = 0;
    vertex_buffer_data[9 * j + 3] = r * cos(((theta) * pi) / 180);
    vertex_buffer_data[9 * j + 4] = r * sin(((theta) * pi) / 180);
    vertex_buffer_data[9 * j + 5] = 0;
    vertex_buffer_data[9 * j + 6] = 0;
    vertex_buffer_data[9 * j + 7] = 0;
    vertex_buffer_data[9 * j + 8] = 0;
    for(int i = 1;i<180;i++)
    {
        vertex_buffer_data[9 * i] = 0;
        vertex_buffer_data[9 * i + 1] = 0;
        vertex_buffer_data[9 * i + 2] = 0;
        vertex_buffer_data[9 * i + 3] = r * cos(((theta) * pi) / 180);
        vertex_buffer_data[9 * i + 4] = r * sin(((theta) * pi) / 180);
        vertex_buffer_data[9 * i + 5] = 0;
        vertex_buffer_data[9 * i + 6] = r * cos(((theta + 1) * pi) / 180);
        vertex_buffer_data[9 * i + 7] = r * sin(((theta + 1) * pi) / 180);
        vertex_buffer_data[9 * i + 8] = 0;
        theta = theta + 1;
    }




    this->object = create3DObject(GL_TRIANGLES,180*3, vertex_buffer_data, color, GL_FILL);  
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate  (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Trampoline::tick() {
   // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
