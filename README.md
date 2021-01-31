<div align="center">
    <p>
        <h1>
            <img src="https://user-images.githubusercontent.com/38016689/106351546-13de3400-62ee-11eb-8dc0-76ed1daee4b9.png"
                 alt="Figure">
        </br>
        Harmonograph
        </h1>
    </p>
    <img src="https://user-images.githubusercontent.com/38016689/106370030-92c38300-6367-11eb-901a-0f604af8b833.png"
         alt="Qt"
         height="50">    
    <img src="https://user-images.githubusercontent.com/38016689/106370062-d8804b80-6367-11eb-8755-8ff3fe379093.png"
         alt="cpp"
         height="50">
    <img src="https://user-images.githubusercontent.com/38016689/106370456-395d5300-636b-11eb-902b-c0d4c4419d19.png"
         alt="cpp"
         height="50">
</div>
         
Harmonograph is a C++ application with Qt GUI that simulates a [real Harmonograph Machine](https://youtu.be/S92mZcNIS8w).

A Harmonograph is a mechanical apparatus that employs pendulums to create a geometric image. It usually consists of about 2 or 3 pendulums.
Real pendulums are affected by external forces that slow their movement over time, so mathematical equation for each pendulum looks like this:

<img src="https://user-images.githubusercontent.com/44650342/83406272-f41d0600-a416-11ea-88cc-4a3e1633c278.png"
     width="300"
     alt="eq1"/>
     
where _A_ is amplitude, _t_ is the moment in time, _f_ is frequency, _φ_ is phase, and _d_ is damping.

This equation gives us point with coordinates  _X_ and _Y_ at the moment _t_, so if _Δt_ will be small, we can get several points and connect
them with a straight line, which will give us something awesome:

![Gui](https://user-images.githubusercontent.com/38016689/106353471-cbc60e00-62fb-11eb-85a0-80facf180765.png)

We can randomly set parameters in equation, and get different pictures each time.

## Toolbar options
Toolbar is our most powerful options place.

* <img src="https://user-images.githubusercontent.com/38016689/106370489-880aed00-636b-11eb-9e57-a3d136525a3c.png"
       alt="Update"
       width="16"> - randomly generate a new figure
* <img src="https://user-images.githubusercontent.com/38016689/106370510-b4bf0480-636b-11eb-9ec2-0e8bc002a8f9.png"
       alt="AutoRotate"
       width="16"> - toggle figure auto rotating
* <img src="https://user-images.githubusercontent.com/38016689/106370536-dd46fe80-636b-11eb-829f-8e25d30c1328.png"
       alt="Undo"
       width="16"> - undo the last update
* <img src="https://user-images.githubusercontent.com/38016689/106370545-fea7ea80-636b-11eb-9efd-75b24b2aa0f7.png"
       alt="Flex"
       width="16"> - make the figure dance
* Pen width - figure line width
* Mode - drawing mode
* Time step - figure accuracy
* Primary color - 1st figure gradient color
* Secondary color - 2nd figure gradient color
* Use two colors - toggle gradient mode
* Backgound color - figure baclground color
* Color templates - color palettes

## Build
Qt5 (>= 5.10), freeglut, glew32 required.

Harmonograph is developed in Visual Studio 2019 on Windows, so you can open it in this IDE and build.

Also, qmake .pro file included, the project can be builded using it.

```console
user@linux:~/Harmonograph$ qmake
user@linux:~/Harmonograph$ make
```

Use _mingw32-make_ or Qt's own _jom_ on Windows.

### Install dependencies on Debian-based distros
```console
user@linux:~/Harmonograph$ sudo apt install qt5-default freeglut3 freeglut3-dev
```
