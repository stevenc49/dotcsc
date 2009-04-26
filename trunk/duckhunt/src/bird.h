#ifndef BIRD_H
#define Bird_H

//The dot that will move around on the screen
class Bird
{
    private:
    //Stores the bird's x and y's offset
    SDL_Rect bird;

    //The status of the bird
    enum Status{ALIVE, SHOT, FALLING};

    Status bird_status;

    //The velocity of the dot
    int xVel, yVel;

    //Frame
    int frame;

    public:
    //Initializes the variables
    Bird();

    //Takes key presses and adjusts the dot's velocity
    void handle_input();

    //Handles the events when the bird is clicked
    void handle_event();

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void show();
};

#endif
