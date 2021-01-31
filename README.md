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

Harmonograph is a C++ application made using Qt Framework that simulates a [real Harmonograph Machine](https://youtu.be/S92mZcNIS8w).

A Harmonograph is a mechanical apparatus that employs pendulums to create a geometric image. It usually consists of about 2 or 3 pendulums.
Real pendulums are affected by external forces that slow their movement over time, so mathematical equation for each pendulum looks like this:

<img src="https://user-images.githubusercontent.com/44650342/83406272-f41d0600-a416-11ea-88cc-4a3e1633c278.png"
     width="300"
     alt="eq1"/>
     
where _A_ is amplitude, _t_ is the moment in time, _f_ is frequency, _φ_ is phase, and _d_ is damping.

This equation gives us point with coordinates  _X_ and _Y_ at the moment _t_, so if _Δt_ will be small, we can get several points and connect
them with a straight line, which will give us pendulum movement over time (for 1 pendulums it will be just damped sine wave).

However, Harmonograph consists of several pendulums, so using superposition principle we can get coordinates  _X_ and _Y_ at the moment _t_ for a combination
of any number of pendulums in Harmonograph, which will give us something awesome:
![Gui](https://user-images.githubusercontent.com/38016689/106395405-2dc56700-6413-11eb-9be9-a1113919ee43.png)

We can randomly set parameters in equation, and get different pictures each time.

### Check out some of our figures in [Gallery](https://github.com/Afomin01/Harmonograph/wiki/Gallery)

## General Features
<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380327-a18b5380-63c2-11eb-86a4-5bcd9db823dd.png"
       alt="Update"
       width="30">
    Update
</h3>

Generates a new figure by randomizing pendulums parameters.

<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380441-47d75900-63c3-11eb-9b9c-75ac76605bcf.png"
       alt="AutoRotate"
       width="30">
    Auto rotate
</h3>

Toggle automatic figure rotation along Y axis.

<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380495-c502ce00-63c3-11eb-8f99-059482bd0793.png"
       alt="Undo"
       width="30">
    Undo
</h3>

Undo the last Harmonograph randomization (up to 10 times).

<h3>
    <img src="https://user-images.githubusercontent.com/38016689/106380298-5b35f480-63c2-11eb-84d6-88a1d11283b2.png"
       alt="Flex"
       width="30">
    Flex mode
</h3>

Can you imagine these figures dance and morfing over time? You can create smooth dynamic images that can fascinate no less than fractals 
by pressing this button! We call this "Flex mode".

The principle of flexing is pretty simple: every frame we just change all phases(for "Phase flex") or frequencies(for "Frequency flex) for
all pendulums by a fixed, but really small value.

Just click the Flex mode button on the toolbar, select one of the modes and you are good to go! A small instruction is included in flex settings dialog window.

### Other
* ✋ Click on the figure and drag for manually rotation along X or Y axis
* 💾 From file menu you can save figure as PNG image or you can save JSON with parameters of Harmonograph and load them later 

## Draw features
* Pen width
* Mode
  * Lines
  * Points
* Time step (Δt between 2 points)
* Colors for Harmonograph and background
* Color templates. Templates are stored in Preferences folder near executable. You can place any number of valid template JSON files in this folder.

## Harmonograph options
* ⭐ The frequency ratios between 1st and 2-3 pendulums make it possible to create Stars
* #️⃣ Set number of pendulums. The more pendulums, the more complex figures
* Frequency point. Basically, defines how dense are lines in figure. We recommend to increase this value when changing frequency ratio.
* Circle mode. Allows to create plane circles. We recommend to use this mode with different frequency ratios.

## Build
Qt5 (>= 5.10), freeglut (glut), required.

Harmonograph is developed in Visual Studio 2019 on Windows with Qt tools plug-in, so you can open it in this IDE and build.

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
