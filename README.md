# PROJECT MINIRT FOR 42
By chdonnat (Christophe Donnat) and olthorel (Olivier Thorel) from 42 Perpignan, France

## AIM OF THE PROJECT:

### BONUS PART:

## SOME COMMANDS YOU CAN USE:

compile the program and suppress the .o files:

	make && make clean

execute the program with a file.rt (representing a scene) as argument

	./minirt <scene_file.rt>

 execute the program with valgrind excluding readline() leaks:

	make val

## ARCHITECTURE:

## ABOUT OUR PROJECT:

# DOCUMENTATION:

## VECTOR BASICS

### WHAT IS A VECTOR?

A **vector** is a mathematical entity represented by **three components** in 3D space:

> x, y, z

It can describe either a **direction in space** or a **position in a coordinate system**.

✅ In the context of miniRT, a vector can be used in two different ways:
- **As a 3D point** → to store positions (e.g. the position of an object, a light source, or an intersection point)
- **As a direction** → to represent orientations (e.g. camera direction, ray direction, or a surface normal)
For example:
- `(1, 0, 0)` could represent a point on the X axis **or** a direction pointing right.
- `(3, 2, -5)` could be a position in space, or the vector from one point to another.

### MAGNITUDE (OR NORM) OF A VECTOR

The **magnitude** (also called the **norm**) of a vector measures its **length** in space.  
It is calculated using the formula:

> ||v|| = sqrt(x² + y² + z²)

- If the vector represents **movement or displacement**, the norm gives the **distance traveled**.  
- If it represents a **direction**, the norm allows you to **normalize** it — i.e. convert it into a unit vector.

### UNIT VECTOR

A **unit vector** is a vector with a length of exactly `1`.  
It is obtained by dividing a vector by its own magnitude:
👉 When we say that a vector is **normalized**, it means that it has been converted into a **unit vector** — keeping the direction, but adjusting the length to 1.

> unit_v = v / ||v||

**Why use unit vectors?**
- To keep only the **direction**, regardless of distance
- To ensure **correct lighting and angle calculations** (many formulas assume normalized inputs)
- To **avoid proportion errors** in vector math

✅ In miniRT, unit vectors are used extensively for:
- Ray directions
- Surface normals
- Light directions

### SURFACE NORMAL

A **normal** is a **vector perpendicular** to a surface at a given point.  
It describes the **local orientation** of that surface.

Examples:
- On a sphere, the normal at a point is the vector pointing from the center of the sphere to that point.
- For a plane, the normal is the same everywhere because the surface is flat.

✅ In miniRT, surface normals are critical for:
- Calculating the **amount of light received** (using the dot product between the normal and the light direction)
- Computing **reflections** (a ray bounces based on the surface normal)
- Handling **refraction** (according to Snell’s Law)

![Vector Concepts](vecteurs explanied.png)

---


