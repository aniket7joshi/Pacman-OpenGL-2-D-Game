#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float radius, float s, int flag, color_t color, float inclination) {
    // this->position = glm::vec3(x, y, 0);
    // this->rotation = 0;
    // speed = 0.005;
    // static const GLfloat vertex_buffer_data[] = {
    //     -0.2, -0.2, 0, // vertex 1
    //     0.2,  -0.2, 0, // vertex 2
    //     0.2,  0.2, 0, // vertex 3

    //     0.2,  0.2, 0, // vertex 3
    //     -0.2, 0.2, 0, // vertex 4
    //     -0.2, -0.2, 0 // vertex 1
    // };
 
    // this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    speed = s;
    static GLfloat vertex_buffer_data1[9*60];
    static GLfloat vertex_buffer_data2[9*60];
    static GLfloat vertex_buffer_data3[9*60];
    static GLfloat vertex_buffer_data4[9*60];
    static GLfloat vertex_buffer_data5[9*60];
    static GLfloat vertex_buffer_data6[9*60];
    double pi =3.1415926535897;
    float r = radius;
    this->rad = radius;
    this->l = 2*rad;
    this->flagPlank = flag;
    double theta = 0;
    //this->inclination = 0;
    int i = 0;
    for(i = 0;i<360;i++)
    {
        vertex_buffer_data1[9 * i] = 0;
        vertex_buffer_data1[9 * i + 1] = 0;
        vertex_buffer_data1[9 * i + 2] = 0;
        vertex_buffer_data1[9 * i + 3] = r * cos(((theta) * pi) / 180);
        vertex_buffer_data1[9 * i + 4] = r * sin(((theta) * pi) / 180);
        vertex_buffer_data1[9 * i + 5] = 0;
        vertex_buffer_data1[9 * i + 6] = r * cos(((theta + 1) * pi) / 180);
        vertex_buffer_data1[9 * i + 7] = r * sin(((theta + 1) * pi) / 180);
        vertex_buffer_data1[9 * i + 8] = 0;
        theta = theta + 1;
    }

    if(flagPlank)    //for the plank
    {
        this->inclination = inclination;
        double l = this->rad;
        this->xBot = (this->rad+0.07)*cos(this->inclination)+ l*sin(this->inclination);
        this->yBot =  (this->rad+0.07)*sin(this->inclination)-l*cos(this->inclination);
        this->xTop = (this->rad+0.07)*cos(this->inclination)- l*sin(this->inclination);
        this->yTop = (this->rad+0.07)*sin(this->inclination)+l*cos(this->inclination);
        GLfloat plank[] = {
            this->rad*cos(this->inclination)- l*sin(this->inclination), this->rad*sin(this->inclination)+l*cos(this->inclination), 0, // vertex 1
            this->rad*cos(this->inclination)+ l*sin(this->inclination), this->rad*sin(this->inclination)-l*cos(this->inclination), 0, // vertex 1
            (this->rad+0.07)*cos(this->inclination)+ l*sin(this->inclination), (this->rad+0.07)*sin(this->inclination)-l*cos(this->inclination) , 0, // vertex 2
    
            (this->rad+0.07)*cos(this->inclination)+ l*sin(this->inclination), (this->rad+0.07)*sin(this->inclination)-l*cos(this->inclination) , 0, // vertex 2
            (this->rad+0.07)*cos(this->inclination)- l*sin(this->inclination), (this->rad+0.07)*sin(this->inclination)+l*cos(this->inclination), 0, // vertex 1
            this->rad*cos(this->inclination)- l*sin(this->inclination), this->rad*sin(this->inclination)+l*cos(this->inclination), 0, // vertex 1
        };
        this->plank = create3DObject(GL_TRIANGLES,6, plank, color, GL_FILL);    

    }

    this->object1 = create3DObject(GL_TRIANGLES,360*3, vertex_buffer_data1, color, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate  (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);

    if(flagPlank)
        draw3DObject(this->plank);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);    
}

void Ball::tick() {
    this->position.x += speed;
    // this->position.y -= speed;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
