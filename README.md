# MiniRT
A minimal raytracing engine wrote in C and MiniLibX
Ready configuration files are in the scenes directory!
Switch between camera using the TAB key.

<img width="994" alt="Screen Shot 2021-07-08 at 9 56 21 AM" src="https://user-images.githubusercontent.com/42047633/124878518-dd12f500-dfd4-11eb-94c7-c7e3c10ecb72.png">
<img width="904" alt="Screen Shot 2021-07-08 at 10 07 27 AM" src="https://user-images.githubusercontent.com/42047633/124878533-e00de580-dfd4-11eb-9290-631e831cb37f.png">

Accepts a config of the form:
R 1000 1000 | Resolution. More values for your monitor can be set. In this case, the resolution will be adjusted to the maximum resolution of your monitor.

A 0.1   255,255,255 | Ambient light. 0.1 - light intensity (Сan be set up to 1.0). 255.255.255 - The palette allowed in the RGB scene (each color can be up to 255)

c 0,0,100 0,0,-1 120 | Camera set up. 0,0,100 - camera position. 0,0,-1 - camera normal (1/-1 max). 120 - FOV (180 max)

c 0,0,100 1,0,-1 120 | Camera can be several of them in a scene. If there are several of them, then you can switch between them using the TAB key.

c 0,0,100 -1,0,-1 120

c 0,0,100 0,-1,-1 120

c 0,0,100 0,1,-1 120

l 300,0,500 1 255,255,255 | light. 300,0,500 - position of light. 1 - light intensity (1 max). 255.255.255 - RGB color of light

sp 0.0,0.0,0 40 50,255,0 | Sphere object. 0.0,0.0,0 - Sphere center position. 40 - sphere diameter. 50,255,0 - RGB color of light

sq 0,0,-50 0,0,1 3000 255,255,255 | Square object. 0.0,0.0,-50 - Square center position. 0,0,1 - normal square. 3000 - 
side length. 255,255,255 - RGB color of light

cy 0,0,0 0,1,0 30 50 0,0,255 | Cylinder object. 0.0,0.0,0 - Cylinder center position. 0,0,1 - normal cylinder. 30 - cylinder height. 50 - cylinder diameter. 0,0,255 - RGB color of light
