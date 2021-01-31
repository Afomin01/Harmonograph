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
         height="45">    
    <img src="https://user-images.githubusercontent.com/38016689/106370062-d8804b80-6367-11eb-8755-8ff3fe379093.png"
         alt="cpp"
         height="45">
    <img src="https://user-images.githubusercontent.com/38016689/106370456-395d5300-636b-11eb-902b-c0d4c4419d19.png"
         alt="cpp"
         height="45">
</div>

&nbsp;

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

## General Features
<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380327-a18b5380-63c2-11eb-86a4-5bcd9db823dd.png"
       alt="Update"
       width="30">
    Update
</h3>

Randomly generate a new figure.

<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380441-47d75900-63c3-11eb-9b9c-75ac76605bcf.png"
       alt="AutoRotate"
       width="30">
    Auto rotate
</h3>

Toggle figure auto rotating

<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380495-c502ce00-63c3-11eb-8f99-059482bd0793.png"
       alt="Undo"
       width="30">
    Undo
</h3>

Undo the last update.

<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380298-5b35f480-63c2-11eb-84d6-88a1d11283b2.png"
       alt="Flex"
       width="30">
    Flex mode
</h3>

Imagine how to make those figures dance? Create smooth dynamic images that can fascinate no less than fractals.
We need to change one or more parameters about 60 times per minute. That's it!

Just press the Flex mode button on the toolbar, choose one of the modes, and let's go.

### Other
* ✋ Click on the figure and drag for manually rotation
* 💾 From file menu you can save figure as PNG image or JSON with parameters

## Draw features
* Pen width
* Mode
  * Lines
  * Points
* Time step
* Colors

## Harmonograph options
* ⭐ The frequency ratios between 1st and 2-3 pendulums make it possible to create Stars
* #️⃣ Set number of pendulums. The more pendulums, the more intricate pictures
* Frequency point
* Circle mode

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
