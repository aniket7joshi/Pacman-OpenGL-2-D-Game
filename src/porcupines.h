#include "main.h"

#ifndef Porcupine_H
#define Porcupine_H


class Porcupine {
public:
    Porcupine() {}
    Porcupine(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tickleft();
    void tickright();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H

Porcupine::Porcupine(float x, float y) {
    this->position = glm::vec3(x,y,0);
    this->rotation = 0;
    printf("x = %f\n",x);
    speed = 0.005;
    float l = 0.0;
    static GLfloat vertex_buffer_data[36];
    for(int i = 0;i<4;i++)
    {
        vertex_buffer_data[9*i] = i*0.2;
        vertex_buffer_data[9*i+1] = 0;
        vertex_buffer_data[9*i+2] = 0;

        vertex_buffer_data[9*i+3] = i*0.2 + 0.1;
        vertex_buffer_data[9*i+4] = 0.1;
        vertex_buffer_data[9*i+5] = 0;

        vertex_buffer_data[9*i+6] = (i+1)*0.2;
        vertex_buffer_data[9*i+7] = 0;
        vertex_buffer_data[9*i+8] = 0;

         
    }
 
    this->object = create3DObject(GL_TRIANGLES,12, vertex_buffer_data,COLOR_GREY, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate  (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Porcupine::tickleft() {
    this->position.x -= speed;
    // this->position.y -= speed;
}
void Porcupine::tickright() {
    this->position.x += speed;
    // this->position.y -= speed;
}

bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
