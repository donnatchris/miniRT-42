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

### **Vector Addition**

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

### **Vector Subtraction**

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

### **Scalar Multiplication**

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

### **Vector Magnitude (Norm)**

Formula:  
> ||v|| = sqrt(v.x² + v.y² + v.z²)  

✅ Use case:  
- Measure how long a vector is  
- Needed to normalize vectors  

Example:  
Used to calculate the distance between two points (after subtracting them).

### **Normalization (Unit Vector)**

Formula:  
> unit_v = v / ||v||  

✅ Use case:  
- Convert a vector to a direction with length = 1  
- Required for correct lighting calculations (e.g. Lambert, Phong)  

Example:  
If v is a ray direction, you typically normalize it to ensure consistent lighting and geometry behavior.

Note: When we say a vector is “normalized,” we mean it has been converted into a unit vector.

### **Dot Product (Scalar Product)**

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

### **Cross Product**

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


