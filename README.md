<div align="center">
    <p>
        <h1>
            <img src="https://user-images.githubusercontent.com/38016689/106351546-13de3400-62ee-11eb-8dc0-76ed1daee4b9.png"
                 alt="Figure">
        </br>
        Harmonograph
        </h1>
    </p>
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
