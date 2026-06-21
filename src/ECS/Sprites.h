#pragma once
#include <vector>

std::vector<std::string> playerSprites = {
    "./assets/Char_Sprites/char_idle_down_anim_strip_6.png", //Idle down 0 (Initial animation)
    "./assets/Char_Sprites/char_idle_left_anim_strip_6.png", //Idle left 1
    "./assets/Char_Sprites/char_idle_right_anim_strip_6.png",//Idle right 2
    "./assets/Char_Sprites/char_idle_up_anim_strip_6.png",   //Idle up 3
    "./assets/Char_Sprites/char_run_down_anim_strip_6.png",  //Run down 4
    "./assets/Char_Sprites/char_run_left_anim_strip_6.png",  //Run left 5
    "./assets/Char_Sprites/char_run_right_anim_strip_6.png", //Run right 6
    "./assets/Char_Sprites/char_run_up_anim_strip_6.png",     //Run up 7
    "idle diagonal up right", "idle diagonal up left", "idle diagonal down right", "idle diagonal down left", // Future diagonal animations 8-11
    "run diagonal up right", "run diagonal up left", "run diagonal down right", "run diagonal down left" // Future diagonal animations 12-15
};
