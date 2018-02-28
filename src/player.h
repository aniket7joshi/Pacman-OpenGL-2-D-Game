#include "main.h"
#ifndef Player_H
#define Player_H


class Player {
public:
    Player() {}
    Player(float x, float y, float radius, float speed, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    float accy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    int tick(int flag);
    float speedx;
    float speedy;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;

};

#endif // Player_H

Player::Player(float x, float y, float radius, float s, color_t color) 
{
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    this->radius = radius;
    speedx = 0;
    speedy = 0;
    accy = -0.0025;
    static GLfloat vertex_buffer_data1[9*60];
    static GLfloat vertex_buffer_data2[9*60];
    static GLfloat vertex_buffer_data3[9*60];
    static GLfloat vertex_buffer_data4[9*60];
    static GLfloat vertex_buffer_data5[9*60];
    static GLfloat vertex_buffer_data6[9*60];
    double pi =3.1415926535897;
    float r = radius;
     double theta = 0;
    //this->inclination = 0;
    int i = 0;
    for(i = 0;i<60;i++)
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
    for(i = 0;i<60;i++)
    {
        vertex_buffer_data2[9 * i] = 0;
        vertex_buffer_data2[9 * i + 1] = 0;
        vertex_buffer_data2[9 * i + 2] = 0;
        vertex_buffer_data2[9 * i + 3] = r * cos(((theta) * pi) / 180);
        vertex_buffer_data2[9 * i + 4] = r * sin(((theta) * pi) / 180);
        vertex_buffer_data2[9 * i + 5] = 0;
        vertex_buffer_data2[9 * i + 6] = r * cos(((theta + 1) * pi) / 180);
        vertex_buffer_data2[9 * i + 7] = r * sin(((theta + 1) * pi) / 180);
        vertex_buffer_data2[9 * i + 8] = 0;
        theta = theta + 1;
    }
    for(i = 0;i<60;i++)
    {
        vertex_buffer_data3[9 * i] = 0;
        vertex_buffer_data3[9 * i + 1] = 0;
        vertex_buffer_data3[9 * i + 2] = 0;
        vertex_buffer_data3[9 * i + 3] = r * cos(((theta) * pi) / 180);
        vertex_buffer_data3[9 * i + 4] = r * sin(((theta) * pi) / 180);
        vertex_buffer_data3[9 * i + 5] = 0;
        vertex_buffer_data3[9 * i + 6] = r * cos(((theta + 1) * pi) / 180);
        vertex_buffer_data3[9 * i + 7] = r * sin(((theta + 1) * pi) / 180);
        vertex_buffer_data3[9 * i + 8] = 0;
        theta = theta + 1;
    }
    for(i = 0;i<60;i++)
    {
        vertex_buffer_data4[9 * i] = 0;
        vertex_buffer_data4[9 * i + 1] = 0;
        vertex_buffer_data4[9 * i + 2] = 0;
        vertex_buffer_data4[9 * i + 3] = r * cos(((theta) * pi) / 180);
        vertex_buffer_data4[9 * i + 4] = r * sin(((theta) * pi) / 180);
        vertex_buffer_data4[9 * i + 5] = 0;
        vertex_buffer_data4[9 * i + 6] = r * cos(((theta + 1) * pi) / 180);
        vertex_buffer_data4[9 * i + 7] = r * sin(((theta + 1) * pi) / 180);
        vertex_buffer_data4[9 * i + 8] = 0;
        theta = theta + 1;
    }
    for(i = 0;i<60;i++)
    {
        vertex_buffer_data5[9 * i] = 0;
        vertex_buffer_data5[9 * i + 1] = 0;
        vertex_buffer_data5[9 * i + 2] = 0;
        vertex_buffer_data5[9 * i + 3] = r * cos(((theta) * pi) / 180);
        vertex_buffer_data5[9 * i + 4] = r * sin(((theta) * pi) / 180);
        vertex_buffer_data5[9 * i + 5] = 0;
        vertex_buffer_data5[9 * i + 6] = r * cos(((theta + 1) * pi) / 180);
        vertex_buffer_data5[9 * i + 7] = r * sin(((theta + 1) * pi) / 180);
        vertex_buffer_data5[9 * i + 8] = 0;
        theta = theta + 1;
    }
    for(i = 0;i<60;i++)
    {
        vertex_buffer_data6[9 * i] = 0;
        vertex_buffer_data6[9 * i + 1] = 0;
        vertex_buffer_data6[9 * i + 2] = 0;
        vertex_buffer_data6[9 * i + 3] = r * cos(((theta) * pi) / 180);
        vertex_buffer_data6[9 * i + 4] = r * sin(((theta) * pi) / 180);
        vertex_buffer_data6[9 * i + 5] = 0;
        vertex_buffer_data6[9 * i + 6] = r * cos(((theta + 1) * pi) / 180);
        vertex_buffer_data6[9 * i + 7] = r * sin(((theta + 1) * pi) / 180);
        vertex_buffer_data6[9 * i + 8] = 0;
        theta = theta + 1;
    }    
    this->object1 = create3DObject(GL_TRIANGLES,60*3, vertex_buffer_data1, COLOR_DARKORANGE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES,60*3, vertex_buffer_data2, COLOR_PEACHPU, GL_FILL);    
    this->object3 = create3DObject(GL_TRIANGLES,60*3, vertex_buffer_data3, COLOR_BROWN, GL_FILL);    
    this->object4 = create3DObject(GL_TRIANGLES,60*3, vertex_buffer_data4, COLOR_LIGHTSEAGREEN, GL_FILL);    
    this->object5 = create3DObject(GL_TRIANGLES,60*3, vertex_buffer_data5, COLOR_LAWNGREEN, GL_FILL);    
    this->object6 = create3DObject(GL_TRIANGLES,60*3, vertex_buffer_data6, COLOR_DARKBLUE, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate  (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);  
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);    
}

int Player::tick(int flag) 
{
    // if(this->position.x>=2 && this->position.x<=2.17 && this->position.y == -1.75)
    //     printf("if\n");
    // else 
        this->position.x += speedx;
    //printf("speedx = %f speedy = %f\n",speedx,speedy);
    // if(this->position.y>=-1.75)
    // {
    //     this->position.y = this->position.y + speedy;
    //     if(this->position.y<=-1.75)
    //     {
    //         this->position.y = -1.75;
    //     }
    //     speedy = speedy + accy;
    // }
    // else
    // {
    //     speedy = 0;
    //     accy = 0;
    // }
    if(flag == 1 && this->position.x>=-1 && this->position.x<=0.6)
    {
        //printf("flag inside if %d\n",flag);
        
           
        this->position.y = this->position.y+speedy;
        speedy = speedy + accy;
        float x = this->position.x;
        float y = sqrt(((0.75*0.75)-((x+0.25)*(x+0.25)))) - 2;
        float diff = y + 2;
        y = -2 - diff;
        if(this->position.y<y)
        {
            this->position.y = y;
            speedy = 0;
            accy = 0;
            return 0;
        }
        // else if(speedy<0 && this->position.y>=-1.75)
        // {
        //     this->position.y = this->position.y + speedy;
        //     if(this->position.y<=-1.75)
        //     {
        //         this->position.y = -1.75;
        //         flag = 0;
        //         return flag;
        //     }
        //     speedy = speedy + accy;
        // }    
    }
    else
    {
        if(this->position.y>=-1.75)
        {
            this->position.y = this->position.y + speedy;
            if(this->position.y<=-1.75)
            {
                this->position.y = -1.75;
            }
            speedy = speedy + accy;
        }
        else
        {
            speedy = 0;
            accy = 0;
        }
        // if(this->position.x == 1.1)
        // {
        //     printf("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n");
        //     this->position.x = 1.25;
        // }
        if(this->position.x>-1.23 && this->position.x<=-1 && this->position.y == -1.75) //going into the pool from left
        {
            //printf("dddddddddddddddddddddddddddddddd\n");
            this->position.x = -1;
            this->position.y = -2;
        }
        if(this->position.x>=-1 && this->position.x<=-0.25 && this->position.y<=-1.75) //for downward motion along the pond on left side
        {
            speedx = 0.005;
            float x = this->position.x;
            //printf("x = %f\n",x);
            //printf("val = %f\n",(0.75*0.75)-((x+0.25)*(x+0.25)));
            float y = sqrt(((0.75*0.75)-((x+0.25)*(x+0.25)))) - 2;
            //this->position.y = sqrt(((0.75*0.75)-((x+0.25)*(x+0.25)))) - 2; 
            //printf("y = %f\n",this->position.y);
            //exit(0);
            speedy = -0.07 ;
            //printf("haha\n");
            //printf("y = %f\n",y);
            float diff = y + 2;
            y = -2 - diff;
            //printf("this->position.y eariler = %f\n",this->position.y );
            //this->position.y = this->position.y + speedy;
            //float y = this->position.y;
            //float x = this->position.x;
            if(this->position.y>y)
            {
                this->position.y = this->position.y +speedy;
            }
            else if(this->position.y<y)
            {
                this->position.y = this->position.y - speedy;
            }
            else if(this->position.y>=y)
            {
                speedy = 0;
            }
            //printf("this->position.y later = %f\n",this->position.y );
        }
        else if(this->position.x>=-0.25 && this->position.x<0.5 && this->position.y<=-1.75)//for upward motion of the ball inside the pool
        {
            speedx = 0.005;
            float x = this->position.x;
            float y = sqrt(((0.75*0.75)-((x+0.25)*(x+0.25)))) - 2;
            speedy = 0.07;
            //printf("cool\n");
            //printf("y = %f\n",y);
            //printf("this = %f\n",this->position.y);
            float diff = y + 2;
            y = -2 - diff;
            if(this->position.y<y)
            {
                this->position.y = this->position.y +speedy;
            }
            else if(this->position.y>y)
            {
                this->position.y = this->position.y - speedy;
            }
            else if(this->position.y>=y)
            {
                speedy = 0;
            }
        }
    }
    return 0;

}

bounding_box_t Player::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
