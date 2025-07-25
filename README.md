# 🌐 MiniRT - 42 Project

By chdonnat (Christophe Donnat) and olthorel (Olivier Thorel) from 42 Perpignan, France

[🇫🇷 Voir la version française](README.fr.md)

<p align="center">
  <img src="https://github.com/donnatchris/miniRT/blob/main/img/Earth_Mars_Jupiter.png" />
</p>

---

## AIM OF THE PROJECT:

The goal of the miniRT project is to create a small, real-time ray tracer capable of rendering 3D scenes described in a simple text format.
The program should generate a realistic image using basic geometric objects, lighting, and camera setup, and display the result in a graphical window.

From a pedagogical standpoint, miniRT is an introduction to computer graphics.
It allows students to understand the fundamentals of ray tracing, including vector math, camera transformations, light/surface interaction.
It also emphasizes clean code structure, geometric reasoning, and the importance of performance in rendering systems.

### BONUS PART:

- Add a new object type: cones, cubes, etc.
- Implement specular lighting (Phong Lighting)
- Implement multi-light support and colored lights
- Support textures and bump mapping
- Implement checkerboard

## SOME COMMANDS YOU CAN USE:

compile the program and suppress the .o files:

	make && make clean

execute the program with a file.rt (representing a scene) as argument

	./minirt <scene_file.rt>
 
for exemple you can use the mix.rt file in the scenes/mandatory_scenes directory

	./minirt scenes/mandatory_scenes/Uranus_Neptune_Jupiter_Venus.rt

 compile the bonus program and suppress the .o files:

	make bonus && make clean

execute the bonus program with a file.rt (representing a scene) as argument

	./minirt_bonus <scene_file.rt>
 
for exemple you can use the Earth_Mars_Jupiter.rt file in the scenes/bonus_scenes directory

	./minirt scenes/bonus_scenes/Earth_Mars_Jupiter.rt


## ARCHITECTURE:

- dclst/ directory with functions and header for using doubly circular linked list
- include/ directory for headers
- libft/ directory with the libft (+ get_next_line and ft_printf)
- scenes/ directory with scenes to be used as argument for the program
	- invalid_scenes/ directory with invalid scene files
	- mandatory_scenes/ directory with valid scene files for the mandatory executable
	- bonus_scenes/ directory with valid scene files for the bonus executable
- mandatory/ directory containing the mandatory part of the project
- bonus/ directory for bonus part
- Makefile (with rules: make bonus clean fclean re)
- readme.md for explanations and main commands of the project

## PROJECT OVERVIEW (of the mandatory part):

To build a working ray tracer like **miniRT**, the rendering process follows these main steps:

### 1. Scene Parsing

- Read the scene description from a `.rt` file.
- Extract objects (spheres, planes, cylinders...), lights, and camera settings.
- Store all elements in appropriate data structures.

### 2. Viewport Setup

Construct the viewport in 3D space using a local camera coordinate system, based on the following camera parameters:

- Origin and direction  
- Horizontal FOV (given in degrees → must be converted to radians)  
- Distance to the viewport (set to 1 by default)  
- Image resolution (`ResX × ResY`)

The next steps will determine, for each point on the viewport, which color to assign to the corresponding pixel in the output image.

### 3. Ray Casting (Per Pixel)

For each pixel in the output image:

- Compute normalized coordinates `(u, v)` on the viewport  
- Generate a ray from the camera origin through the corresponding point on the viewport  
- Normalize the ray direction

### 4. Ray-Object Intersection

Check whether the ray intersects any object in the scene:

- Keep the **closest** intersection point (if any)  
- For each object type (sphere, plane, cylinder...), implement a specific intersection function

### 5. Lighting & Shading

- If the ray hits nothing, assign the background color to the pixel (black) 
- If the ray hits an object:
  - Compute the **surface normal** at the intersection point  
  - **Check for shadows** by casting a secondary ray from the intersection point toward each light source  
  - If there is **no object** between the intersection point and the light, compute the pixel color using the object’s color and **diffuse + specular lighting** (based on light position and intensity defined in the scene)  
  - If the point is **in shadow**, compute the pixel color using the object’s color and the **ambient light** defined in the scene

### 6. Color Output

Write the computed pixel color to the image buffer.

### 7. Display / Export

Once all pixels are computed and stored in the buffer, display the final image in a window using a graphics library (e.g., MiniLibX).

---

# DOCUMENTATION:

## VECTOR BASICS

### What is a vector

A **vector** is a mathematical entity represented by **three components** in 3D space:

> x, y, z

It can describe either a **direction in space** or a **position in a coordinate system**.

✅ In the context of miniRT, a vector can be used in two different ways:
- **As a 3D point** → to store positions (e.g. the position of an object, a light source, or an intersection point)
- **As a direction** → to represent orientations (e.g. camera direction, ray direction, or a surface normal)
For example:
- `(1, 0, 0)` could represent a point on the X axis **or** a direction pointing right.
- `(3, 2, -5)` could be a position in space, or the vector from one point to another.

### **Magnitude (or Norm) of a vector**

The **magnitude** (also called the **norm**) of a vector measures its **length** in space.  
It is calculated using the formula:

> ||v|| = sqrt(x² + y² + z²)

- If the vector represents **movement or displacement**, the norm gives the **distance traveled**.  
- If it represents a **direction**, the norm allows you to **normalize** it — i.e. convert it into a unit vector.

### **Unit vector**

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

### **Surface normal**

A **normal** is a **vector perpendicular** to a surface at a given point.  
It describes the **local orientation** of that surface.

Examples:
- On a sphere, the normal at a point is the vector pointing from the center of the sphere to that point.
- For a plane, the normal is the same everywhere because the surface is flat.

✅ In miniRT, surface normals are critical for:
- Calculating the **amount of light received** (using the dot product between the normal and the light direction)
- Computing **reflections** (a ray bounces based on the surface normal)
- Handling **refraction** (according to Snell’s Law)

## COMMON VECTOR OPERATIONS

Vectors are not only used to represent points and directions — they also support many operations essential for 3D rendering and ray tracing. Below are the most common vector operations used in miniRT.

### 🔣 **Vector Addition**

Formula:  
> v3 = v1 + v2

Component-wise:  
> v3.x = v1.x + v2.x  
> v3.y = v1.y + v2.y  
> v3.z = v1.z + v2.z  

✅ Use case:  
- Combine multiple directions or movements  
- Translate a point by a direction vector  

Example:  
If v1 = position and v2 = offset, then v1 + v2 gives a new position translated in space.

### 🔣 **Vector Subtraction**

Formula:  
> v3 = v1 - v2

Component-wise:  
> v3.x = v1.x - v2.x  
> v3.y = v1.y - v2.y  
> v3.z = v1.z - v2.z  

✅ Use case:  
- Compute the direction from one point to another  
- Compute relative positions  

Example:  
If v1 = pointB and v2 = pointA, then v1 - v2 gives a vector that points from A to B.

### 🔣 **Scalar Multiplication**

Formula:  
> v2 = s * v1

Component-wise:  
> v2.x = s * v1.x  
> v2.y = s * v1.y  
> v2.z = s * v1.z  

✅ Use case:  
- Scale the magnitude of a vector  
- Resize a direction or stretch a point from origin  

Example:  
If v1 is a direction and s = 5, then s * v1 gives a new vector pointing in the same direction but 5 times longer.

### 🔣 **Vector Magnitude (Norm)**

Formula:  
> ||v|| = sqrt(v.x² + v.y² + v.z²)  

✅ Use case:  
- Measure how long a vector is  
- Needed to normalize vectors  

Example:  
Used to calculate the distance between two points (after subtracting them).

### 🔣 **Normalization (Unit Vector)**

Formula:  
> unit_v = v / ||v||  

✅ Use case:  
- Convert a vector to a direction with length = 1  
- Required for correct lighting calculations (e.g. Lambert, Phong)  

Example:  
If v is a ray direction, you typically normalize it to ensure consistent lighting and geometry behavior.

Note: When we say a vector is “normalized,” we mean it has been converted into a unit vector.

### 🔣 **Dot Product (Scalar Product)**

Formula:  
> dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z  

✅ Use case:  
- Find the angle between two vectors  
- Determine how much two directions are aligned  
- Used in lighting models (diffuse shading, specular highlights)  

Interpretation:  
- dot > 0 → vectors point in roughly the same direction  
- dot = 0 → vectors are perpendicular  
- dot < 0 → vectors point in opposite directions  

Example:  
Used to compute how much light hits a surface depending on its orientation.

### 🔣 **Cross Product**

Formula:  
> cross.x = v1.y * v2.z - v1.z * v2.y  
> cross.y = v1.z * v2.x - v1.x * v2.z  
> cross.z = v1.x * v2.y - v1.y * v2.x  

✅ Use case:  
- Compute a vector perpendicular to both v1 and v2  
- Build local coordinate systems (camera view plane)  
- Calculate surface normals from triangle vertices  

Interpretation:  
The resulting vector is perpendicular to the plane formed by v1 and v2.

Example:  
Used when constructing the camera's orientation or computing the normal of a triangle surface.

---

## VIEWPORT

In ray tracing, the **viewport** is a virtual rectangular screen placed in front of the camera.
It acts as the **projection plane** — rays are cast from the camera origin through this viewport, one per pixel, to simulate how light interacts with the 3D scene.
Each pixel corresponds to a point on the viewport.
The path of the ray from the camera through that point determines what the pixel will display in the final image.

### **Viewport Parameters and Construction**

In miniRT, the viewport is calculated based on:

- **Camera origin** → the position of the camera (a 3D point) - given in the scene
- **Camera direction** → a normalized vector pointing where the camera looks - given in the scene
- **FOV** → the field of view is the angle that defines how wide the camera can "see" — a larger FOV captures more of the scene, while a smaller FOV zooms in on a narrower portion. In miniRT it's horizontaly but it can be verticaly - given in the scene
- **Distance to viewport** → a configurable distance between the camera and the viewport, set to 1 in the project
- **Aspect ratio** → image width divided by height (`ResX / ResY`)

### **1. Building the Camera's Coordinate System**

To position the viewport in 3D space, we first define a local coordinate system for the camera:

- **Forward vector** → normalized camera direction - given in the scene as the camera direction
- **Right vector** → points horizontally, perpendicular to forward  
- **Up vector** → points vertically, perpendicular to both right and forward

```c
forward = normalize(camera.direction);
right = normalize(cross(world_up, forward));
up = cross(forward, right);
```

> 📌 `world_up` is typically `(0, 1, 0)`, unless the camera is oriented vertically.

### **2. Calculating Viewport Dimensions**

Since the FOV is **horizontal**, we compute the **viewport width** directly from it and the distance to the viewport.
Note that since the FOV is given as an angle in degrees in the scene, it must first be converted to radians using the formula:
> fov_radians = fov_degrees × (π / 180).

```c
viewport_width = 2 * distance * tan(fov_radians / 2);
viewport_height = viewport_width / aspect_ratio;
```

Remember:
- `distance` is the configurable distance from the camera to the viewport (set to 1 in the project)
- `fov_radians` is in **radians**
- `aspect_ratio = ResX / ResY`

### **3. Placing the Viewport in Space**

We now determine the actual position and size of the viewport in 3D:

```c
horizontal = right * viewport_width;
vertical = up * viewport_height;
```

The **center** of the viewport is placed in front of the camera:

```c
center = camera_origin + forward * distance;
```

From that, we compute the **lower-left corner** of the viewport:

```c
lower_left_corner = center - (horizontal / 2) - (vertical / 2);
```

### **4. Generating Rays Through the Viewport**

To cast a ray for a pixel located at normalized coordinates (u, v) in [0, 1]:

```c
point_on_viewport = lower_left_corner + u * horizontal + v * vertical;
ray.origin = camera_origin;
ray.direction = normalize(point_on_viewport - camera_origin);
```

This ray will pass through the correct position on the viewport, simulating perspective projection. 

### **Summary**

In **miniRT**, the viewport:

- Is placed at a variable distance in front of the camera
- Has dimensions based on **horizontal FOV**
- Adjusts height using the **aspect ratio**
- Allows rays to simulate **realistic perspective projection**

Accurate viewport computation ensures your rays align with the camera’s view and that your rendered image matches the intended field of vision.

---

## RAY CASTING STEP BY STEP

Once the **viewport** is set up, the next major step is to generate a **ray** for each pixel of the final image. This is the core of the ray tracing process.

Here’s how ray casting works in **miniRT**:

### 1. Loop Through Each Pixel

Iterate over every pixel in the image using two nested loops:

```c
for (y = 0; y < image_height; y++)
    for (x = 0; x < image_width; x++)
```

### 2. Compute Normalized Screen Coordinates (u, v)

Convert pixel coordinates `(x, y)` into normalized viewport coordinates:

```c
u = (float)x / (image_width - 1);
v = (float)y / (image_height - 1);
```

### 3. Get the Point on the Viewport

Using the viewport vectors:

```c
point_on_viewport = lower_left_corner + u * horizontal + v * vertical;
```

### 4. Generate the Primary Ray

```c
ray.origin = camera_origin;
ray.direction = normalize(point_on_viewport - camera_origin);
```

This ray simulates the path of light from the camera through a pixel.

### 5. Find the First Intersection (Primary Hit)

Check if this ray intersects any object in the scene:

- If no hit is found → use the background color.
- If a hit is found → go to the next step.

### 6. Cast Shadow Rays (for Lighting)

For each light source in the scene:

- Create a **shadow ray** from the intersection point **toward the light source**.
- Check if any object **blocks this ray before it reaches the light**.

If **no object blocks the shadow ray**, then:
- The point is **lit** by this light source.
- Compute **diffuse** and **specular** lighting using the light’s direction and intensity.

If an object **blocks the shadow ray**, then:
- The point is **in shadow** for that light.
- Only apply **ambient lighting**.

### 7. Compute the Final Color

Combine:
- Object color
- Lighting contributions (diffuse, specular, ambient)
  	- Diffuse lighting → depends on the angle between the surface normal and the light direction (Lambert's law)
  	- Specular highlights → depend on the viewer’s position and the angle of reflection
  	- Ambient lighting → a constant low light applied even in shadow
- Visibility from each light (shadows)

Clamp or normalize the result into a valid RGB color.

### 8. Store the Color

Write the computed color to the image buffer at the corresponding pixel location.

---

## LIGHTING MODELS: LAMBERT & PHONG

In ray tracing, simulating realistic lighting is essential to make objects visible and expressive. Two fundamental models are used in **miniRT**: Lambert model (mandatory part) and Phong model (bonus part).

### **Lambert Model (Diffuse)**

#### **What is it for?**  
The Lambert model simulates **diffuse lighting**, which is the way light spreads evenly in all directions when it hits a rough or matte surface (like plaster or fabric).  
It gives an idea of **how much light a point receives directly from a light source**, depending on its orientation.

#### **Concept**  
The perceived light intensity depends on **the angle between the light direction and the surface normal**.

Formula:
```c
diffuse = max(0.0, dot(normal, light_dir)) * light_color * object_color;
```

- `normal`: surface normal at the point
- `light_dir`: normalized vector from the point to the light source
- `light_color`: color/intensity of the light
- `object_color`: base color of the object

#### 🛠️ **Implementation**  
1. Compute the normal at the intersection point.  
2. Normalize the direction to the light.  
3. Take the dot product of the two vectors.  
4. Multiply the result by the light color and the object color.

---

### **Phong Model (Specular)**

#### **What is it for?**  
The Phong model adds **specular highlights** (shininess) to the lighting, simulating how light reflects off smooth surfaces (metal, plastic, water, etc.).

It enhances realism by adding visible light reflections where the **reflection angle matches the camera direction**.

#### **Concept**  
We compute the **reflected direction** of the light relative to the surface normal, and check how closely it aligns with the **view direction** (toward the camera).

Formula:
```c
specular = pow(max(0.0, dot(view_dir, reflect_dir)), shininess) * light_color;
```

- `view_dir`: normalized vector from the point to the camera
- `reflect_dir`: reflected light direction based on the surface normal
- `shininess`: shininess factor (higher = tighter, sharper highlights)

#### **Implementation**  
1. Compute the reflection vector:
```c
reflect_dir = reflect(-light_dir, normal);
```
2. Take the dot product of `view_dir` and `reflect_dir`.  
3. Raise it to the power of `shininess` for a concentrated highlight.  
4. Multiply by the light color/intensity.

### 🎯 **Final Result**  
The total lighting at a point is often the **sum of both models**, weighted based on the material:
```c
color = ambient + diffuse + specular;
```

### 📌 Notes  
- `dot(...)` returns a value between -1 and 1, clamped using `max(0, ...)`.  
- It’s important to **normalize all vectors** to maintain consistent results.  
- The Phong model is **empirical**, meaning it's based on realistic observation rather than strict physical simulation.

---
