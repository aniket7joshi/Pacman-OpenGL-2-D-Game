#include "main.h"
#include "timer.h"
#include "ball.h"
#include "back.h"
#include "grass.h"
#include "trampoline.h"
#include "pond.h"
#include "trampolineRectangle.h"
#include "magnet.h"
#include "magnetRectangle.h"
#include "player.h"
#include "porcupines.h"
using namespace std;
#define PI 3.14159265
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball[15];
Back b;
Grass g;
Trampoline t;
TrampolineRectangle r; 
Pond p;
Magnet m1;
Magnet m2;
MagnetRectangle m3;
Player virat;
Porcupine p1;
Porcupine p2;
float accx = -0.002;
float insidemagnet = 0;
long long int ti = 0;
int score = 0;
int level = 1;
int lastScore = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);
int flag = 0;
float LO = -1;
float HI = 3.5;
float RLO = 0.12;
float RHI = 0.25;
int mg = 0;
int jump = 0;
int p1f = 0;
int p2f = 0;

void dispScore(){
//    cout << ball2.score << endl;
    string e = "Virat | Score: ";
    string s = to_string(score);
    string p = "  Level: ";
    string l = to_string(level);
    s = e+s+p+l;
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */

void draw() {
    // clear the color and depth in the frame buffer
    //glClearColor(0.3, 0.25, 0.5, 0.0);
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i = 0;i<15-level+1;i++)
        ball[i].draw(VP);
    b.draw(VP);
    g.draw(VP);
    t.draw(VP);
    r.draw(VP);
    p.draw(VP);
    if(ti%1000>=600)
    {
        m1.draw(VP);
        m2.draw(VP);
        m3.draw(VP);
    }    
    virat.draw(VP);
    if(ti%1000>=300)
    {
        p1.draw(VP);
        p1.position.y = -2;
        p2.draw(VP);
        p2.position.y = -2;
    }
}
bool collidingPlank(int i)
{  
    double slope = -cos(ball[i].inclination)/sin(ball[i].inclination);
    
    if(virat.speedy<=0 && virat.position.x <= ball[i].position.x+ball[i].xBot && virat.position.x >= ball[i].position.x+ball[i].xTop)
    {
    
        if(abs(virat.position.y - (slope*(virat.position.x - ball[i].position.x+ball[i].xTop) + ball[i].position.y+ball[i].yTop)) <= 0.4)
        {
            return true;
        }
    }
    return false;
}
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int plus = glfwGetKey(window, GLFW_KEY_KP_ADD);
    int minus = glfwGetKey(window, GLFW_KEY_KP_SUBTRACT);
    int rightside = glfwGetKey(window, GLFW_KEY_RIGHT);
    int leftside = glfwGetKey(window, GLFW_KEY_LEFT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    //cout<<ball[i].position.x<<endl;
    if(right && virat.position.y<=-1.75 && virat.position.x>=0.50 && virat.position.x<0.75)//for the motion of the player coming out of the right while pressing right
    {
        virat.position.x = 0.75;
        virat.position.y = -1.75;
        virat.speedy = 0;
        virat.rotation+=20;
    }
    if(right && virat.position.y ==-1.75 && virat.position.x>=2.0 && virat.position.x<=2.2) //for the ball not going inside trampoline
    {
        //printf("haha\n");
        //cout<<virat.position.x<<"\n";
        virat.position.x = 2.17;
        //cout<<virat.position.x<<"\n";
        virat.rotation+=20;

        virat.speedx = 0;
    }
    else if (right) {
        virat.rotation+=20;

    	//if(virat.speedx<=0)
    		virat.speedx = 0.025;
        // Do something
    }
    //cout<<"virat pos x "<<virat.position.x<<endl;
    //cout<<"virat pos y"<<virat.position.y<<endl;
    if(left && virat.position.y<=-1.75 && virat.position.x<=-1 && virat.position.x>-1.1)//for the motion of the player coming out of the pool to his left while pressing left
    {
        virat.rotation-=20;

        //cout<<"*******************************\n";
        virat.position.x = -1.25;
        virat.position.y = -1.75;
        virat.speedy = 0;
    }
    if(left && virat.position.y==-1.75 && virat.position.x>0.70 && virat.position.x<0.75)//going into the pool from the right
    {
        virat.rotation-=20;

        virat.position.x = 0.5;
        virat.position.y = -2;
        virat.speedy = 0;
    }
    if(left && virat.position.y == -1.75 && virat.position.x>=3.3 && virat.position.x<=3.5) //not going into trampoline from right
    {
        virat.rotation-=20;

        virat.position.x = 3.33;
        virat.speedx = 0;
    }
    if(virat.position.x<=-3.75)
    {
        virat.position.x = -3.75;
    }
    else if(left){
        virat.rotation-=20;

    	//if(virat.speedx>=0)
    		virat.speedx = -0.025;
	}
    if(space && virat.position.y<-1.7 && virat.position.x>=-1 && virat.position.x<=0.5 && jump == 0)  //jumping inside the pool
    {
       // printf("yo\n");
        //printf("jump before %d\n",jump);
        virat.speedy = 0.1;
        virat.accy = -0.009;
        jump = 1;
    }
    else if(space && virat.position.y==-1.75 && (virat.position.x<=-1 || virat.position.x>=0.5)) //normal jump
    {
        //printf("not yo\n");
        virat.speedy = 0.1;
        virat.accy = -0.0025;
        //jump = 1;
    }
    if(!left && !right && insidemagnet!=1 && ((virat.position.y == -1.75) || (virat.position.x>=-1 && virat.position.x<=0.5 && virat.position.y<-1.75)))   //not decreasing the x velocity if ball is in air
    {
        virat.speedx = 0;
    }
    if(plus)
    {
        reset_screen(0.02);

        //screen_zoom = screen_zoom + 0.02;
        if(screen_zoom>=4)
        {
            screen_zoom = 4;
        }
    }
    if(minus)
    {
        reset_screen(-0.02);

        //screen_zoom = screen_zoom - 0.02;
        if(screen_zoom<=1)
        {
            screen_zoom = 1;
        }
    }
    if(rightside)
    {
        screen_center_x+=0.05;
       // cout<<"x "<<screen_center_x<<endl;
        //check_pan();
        reset_screen(0);
    }
    if(leftside)
    {
        //printf("leftside\n");
        screen_center_x-=0.05;
        //cout<<"x "<<screen_center_y<<endl;
        reset_screen(0);
    //    check_pan();
    }
    if(up)
    {
        screen_center_y+=0.05;
        reset_screen(0);
    }
    if(down)
    {
        screen_center_y-=0.05;
        reset_screen(0);
    }
    //panning
    float leftmost = screen_center_x - 4;
    float rightmost = screen_center_x + 4;
    if(right && virat.position.x >= leftmost + 7.5)
    {
        screen_center_x += virat.speedx+0.01;
        reset_screen(0.0);
    }
    if(left && virat.position.x <= leftmost + 0.5)
    {
        screen_center_x += (virat.speedx-0.01);
        reset_screen(0.0);   
    }
    // if(left && virat.position.x <= leftmost + 1)
    // {
    //     screen_center_x -= virat.speedx+0.01;
    //     reset_screen(0.0);
    // }
    // if(right && virat.position.x <= leftmost + 3)
    // {
    //     screen_center_x -= virat.speedx+0.01;
    //     reset_screen(0.0);
    // }
}
void collisionPorcupine()
{
    if(virat.position.y<=-1.6)
    {
        if(virat.position.x>=(p1.position.x-0.25) && virat.position.x<=(p1.position.x+1.05))
        {
            //printf("p1 collision\n");
            score = score - 5*level;
            dispScore();
            p1.position.y = 100;
        }
        if(virat.position.x>=(p2.position.x-0.25) && virat.position.x<=(p2.position.x+1.05))
        {
           // printf("p2 collision\n");
            score = score - 2;
            dispScore();
            p2.position.y = 100;
        }
    }
}
void tick_elements() 
{
    for(int i = 0;i<15-level+1;i++)
    {
        ball[i].tick();
        if(ball[i].position.x >=4)
        {
            //Regenerate the ball if it crosses the screen
            ball[i].position.x = -4;
            ball[i].position.y = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            ball[i].speed = 0.009 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.015-0.005)));
        }
    }
    //printf("jump inside main earlier %d\n",jump);
    jump = virat.tick(jump);
    //printf("jump inside main later %d\n",jump);

    // if(virat.position.x>=4 - virat.radius)
    // {
    //     screen_center_x+=0.05;
    //     reset_screen(0);
    //     virat.position.x = 4 - virat.radius;
    // }
    // if(virat.position.x<=-4 + virat.radius)
    // {
    //     screen_center_x-=0.05;
    //     reset_screen(0);
    //     virat.position.x = -4 + virat.radius;
    // }
    for(int i = 0;i<15-level+1;i++)
    {
        //Detect collision between player and the Balls
        float x1 = ball[i].position.x;
        float y1 = ball[i].position.y;
        float x2 = virat.position.x;
        float y2 = virat.position.y;
        float r1 = ball[i].rad;
        float r2 = 0.25;
        //float theta = 45;
        float width = 0.07;
        float l = r1;
        //double alpha = atan(virat.speedy/virat.speedx)*180/PI;
        //double v = sqrt(virat.speedy*virat.speedy + virat.speedx*virat.speedx);
        if(ball[i].flagPlank)    //collision with the ball having plank
        {
            if(collidingPlank(i))
            {
                //cout<<"y before"<<virat.speedy;
                //cout<<"x before"<<virat.speedx;
                
                double theta=atan2(virat.speedy,virat.speedx);
                double speed=sqrt(virat.speedx*virat.speedx+virat.speedy*virat.speedy);
                //virat.speedx=speed*cos(2*ball[i].inclination-theta);
                //virat.speedy=speed*sin(2*ball[i].inclination-theta);
                //virat.speedy = 0.3;
                score = score + 20;
                virat.speedy = 0.08;
                virat.speedx = 0.03 ;
                //cout<<"collision\n";
                //printf("y = %f\n",virat.speedy);
                //printf("x = %f\n",virat.speedx);
                //virat.speedy = 0.2;
                ball[i].position.x = -4;
                //virat.accy = -0.0025;

            }
        } 
        else if(ball[i].flagPlank == 0 && sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))<=(r1+0.25) && (y2>y1) && virat.speedy<0) //only if the ball is in downlward motion it will kill the enemy
        {
            virat.speedy = 0.08; //change the y velocity of the player
            //virat.speedx = 0.05;

            score = score + 10;
            dispScore();
            ball[i].position.x = -4; //regenerating the destroyed balls
            ball[i].position.y = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            ball[i].speed = 0.009 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.015-0.005)));
        }
        // if (ball[i].flagPlank == 1 && sqrt(pow(virat.position.x - ball[i].position.x, 2) + pow(virat.position.y - ball[i].position.y, 2)) <=r1+r2+0.07) 
        // {
        //     if (virat.position.x >= ball[i].position.x && virat.position.y >= ball[i].position.y && virat.speedy<0)
        //     {
        //         printf("entered\n");
        //         //cout<<"v = "<<v<<"\n";
        //         //cout<<"vx = "<<v*cos(2*theta - alpha)<<"\n";
        //         //cout<<"vy = "<<v*sin(2*theta - alpha)<<"\n";
        //         //ball[i].position.y = -3;
        //         //ball[i].position.x = -3;
        //         virat.speedy = 0.08;
        //         virat.speedx = 0.05;
        //     }
        // }
          //virat.speedx = 0.025;

    }
    if(virat.position.x>2.2 && virat.position.x<3.3 && virat.position.y<=-1.35 && virat.position.y>=-1.55) //Trampoline Interaction
    {
        virat.speedy = 0.15;
    }
    insidemagnet = 0;
    if(ti%1000>=600 && virat.position.x>=-3 && virat.position.x<=3.00 && virat.position.y<=3.75 && virat.position.y>=2.25) //Magnet Interaction
    {
        //printf("**********************************magnet********************************\n");
        //cout<<virat.speedx<<endl;
        insidemagnet = 1;
        virat.speedx = virat.speedx + accx;
        //mg = 1;
    }
    //Movement of Porcupines
    if(p1f == 0 && p1.position.x<=-2.2)
    {
        p1.tickright();
    }
    if(p1.position.x>=-2.2)
    {
        p1f = 1;
    }
    if(p1f == 1 && p1.position.x>=-3.5)
    {
        p1.tickleft();
    }
    if(p1.position.x<=-3.5)
    {
        p1f = 0;
    }
    if(p2f == 0 && p2.position.x<=1.5)
    {
        p2.tickright();
    }
    if(p2.position.x>=1.5)
    {
        p2f = 1;
    }
    if(p2f == 1 && p2.position.x>=0.75)
    {
        p2.tickleft();
    }
    if(p2.position.x<=0.75)
    {
        p2f = 0;
    }
    if(ti%1000>=300)
        collisionPorcupine();
    //Movement of Porcupines done
    if(score<0)
    {
        cout<<"You Died. Better Luck Next Time\n";
        exit(0);
    }
    if(score>lastScore+50)      //for increasing the level
    {
        level++;
        lastScore = score;
    }
    if(level>15)
    {
        cout<<"YOU WON!!!!!\n";
        exit(0);
    }

    //cout<<score;

}
   

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    int flag = 0;
    int fp = 0;
    for(int i = 0;i<15;i++)
    {
        float x = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        float y = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        float r = RLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(RHI-RLO)));
        int randNum = rand()%(3) + 1;
        float s = 0.009 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.015-0.005)));
        if(i%3 == 0)   //for the plank on the ball
        {
            fp = 1;
        }
        else
        {
            fp = 0;
        }
        if(randNum == 1)
        {
            if(fp)
                ball[i] = Ball(x,y,r,s,fp,COLOR_BLUE,M_PI/4);
            else
                ball[i] = Ball(x,y,r,s,fp,COLOR_BLUE,0);
        }
        else if(randNum == 2)
        {
            if(fp)
                ball[i] = Ball(x,y,r,s,fp,COLOR_MAGENTA,M_PI/3);
            else
                ball[i] = Ball(x,y,r,s,fp,COLOR_MAGENTA,0);
        }

        else
        {
            if(fp)
                ball[i] = Ball(x,y,r,s,fp,COLOR_BROWN,M_PI/6);
            else
                ball[i] = Ball(x,y,r,s,fp,COLOR_BROWN,0);
        }


    }
    b = Back(0,0,COLOR_BLACK);
    g = Grass(0,0,COLOR_GREEN);
    t = Trampoline(2.75,-1.55,COLOR_RED);
    r = TrampolineRectangle(0,0,COLOR_RED);
    p = Pond(-0.25,-2,COLOR_AQUA);
    m1 = Magnet(-2.5, 3, COLOR_MAGNET,0.75);   
    m2 = Magnet(-2.5, 3, COLOR_BACKGROUND,0.5);
    m3 = MagnetRectangle(0,0, COLOR_GREY);
    virat = Player(-4, -1.75, 0.25, 0, COLOR_YELLOW );
    //float x = -3.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(-3.5+2.2)));
    //ss("p1 x %f\n",x);
    p1 = Porcupine(-3.1, -2);
    //x = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.9)));
    //printf("p2 x %f\n",x);
    p2 = Porcupine(1, -2);

    //cout<<b.color;
    //ball1       = Ball(2, 1, COLOR_RED);
    //ball2       = Ball(-2, -1, COLOR_RED);
    //ball2.speed = 0;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);


    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            ti++;
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

// bool detect_collision(Ball b, Player p) 
// {
//     float x1 = b->position.x;
//     float y1 = b->position.y;
//     float x2 = p->position.x;
//     float y2 = p->position.y;
//     float r1 = b.rad;
//     float r2 = 0.25;
//     if(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))<=(r1+0.25))
//     {
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }

void reset_screen(float zoom) {
    screen_zoom+=zoom;
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
