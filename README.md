This is for me to learn C++, OpenGl and Cmake (so basically everthing about c++ development lol)

## Goal 
dude let's remake my cg project


## Todos 
    -   use glfw as submodule

    #version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
   gl_Position = vec4(aPos, 1.0);
   ourColor = aColor;
   TexCoord = aTexCoord;
}



## Development Diary

17/10/2025
  Using static linking won't work on any machine so it's no use to include that into this repository, I will fix that later with dynamic linking ( which I have not learned yet ).
  currently learning Cmake overall (
    GOAL: to be able to simply using cmake to properly link all dependencies,
  )

21/10/2025
  gosh i need to learn more about cpp. now i have template, fstream, sstream and import management to learn

23/10/2025
  currently learning cpp with cherno's video about class and template

28/10/2025
  seems like i can't quite understand how to read file in c++. So I;m currently using direct path to shader files