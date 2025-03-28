#include "../includes/miniRT.h"

t_vector reflect(t_vector incident, t_vector normal)
{
    double		dot;
	t_vector	reflected;
	
	dot = dot_vector(normal, incident);
    reflected = sub_vector(incident, mul_vector(normal, 2.0 * dot));
    return (reflected);
}

int phong_lighting(t_hit hit, t_light light, t_program *prog)
{
    t_vector light_dir = sub_vector(light.position, hit.point);
    normalize_vector(&light_dir);
    t_vector view_dir = sub_vector(prog->view->origin, hit.point);
    normalize_vector(&view_dir);
    
    // Composante ambiante
    double ambient = prog->file->ambient_light.ratio;
    
    // Composante diffuse (Lambert)
    double diffuse = fmax(dot_vector(hit.normal, light_dir), 0.0);
    
    // Composante spéculaire (Phong)
    t_vector reflect_dir = reflect(mul_vector(light_dir, -1.0), hit.normal);
    double specular_coef = pow(fmax(dot_vector(reflect_dir, view_dir), 0.0), 32);
    
    // Intensité totale (avec coefficients)
    double intensity = ambient 
                     + (light.ratio * diffuse) 
                     + (0.5 * specular_coef);
    intensity = fmin(intensity, 1.0);
    
    // Calcul des couleurs
    int r = ((hit.color >> 16) & 0xFF) * intensity * ((light.color >> 16) & 0xFF) / 255;
    int g = ((hit.color >> 8) & 0xFF) * intensity * ((light.color >> 8) & 0xFF) / 255;
    int b = (hit.color & 0xFF) * intensity * (light.color & 0xFF) / 255;
    
    return (r << 16) | (g << 8) | b;
}





































// int	phong_lighting(t_hit hit, t_light light, t_program *prog)
// {
// 	t_vector	light_dir;
// 	t_vector	reflect_dir;
// 	t_vector	view_dir;
// 	double		diffuse;
// 	double		specular;
// 	double		intensity;
// 	double		shininess;
// 	int			r, g, b;

// 	shininess = 32; //brillance specular
// 	//vecteur lumere normalise
// 	light_dir = sub_vector(light.position, hit.point);
// 	normalize_vector(&light_dir);
// 	//diffuse Lambert
// 	diffuse = dot_vector(hit.normal, light_dir);
// 	if (diffuse < 0)
// 		diffuse = 0;
// 	//specular Phong
// 	reflect_dir = sub_vector(mul_vector(hit.normal, 2 * dot_vector(hit.normal, light_dir)), light_dir);
//     normalize_vector(&reflect_dir);

//     // view_dir = sub_vector(prog->file->camera.origin, hit.point);
//     view_dir = sub_vector(prog->view->origin, hit.point);


//     normalize_vector(&view_dir);
//     specular = pow(fmax(dot_vector(reflect_dir, view_dir), 0.0), shininess);
// 	//intensite finale
// 	intensity = (light.ratio * diffuse) + (0.5 * specular);
//     if (intensity > 1)
// 	{
//         intensity = 1;
// 	}
// 	//application couleur
// 	r = ((hit.color >> 16) & 0xFF) * ((light.color >> 16) & 0xFF) / 255 * intensity;
//     g = ((hit.color >> 8) & 0xFF) * ((light.color >> 8) & 0xFF) / 255 * intensity;
//     b = (hit.color & 0xFF) * (light.color & 0xFF) / 255 * intensity;
//     return ((r << 16) | (g << 8) | b);
// }

// int	lambert_color(t_hit hit, t_light light)
// {
// 	t_vector	light_dir;
// 	double		intensity;
// 	int			r, g, b;

// 	// Vecteur lumière normalisé
// 	light_dir = sub_vector(light.position, hit.point);
// 	normalize_vector(&light_dir);

// 	// Intensité diffus : cos(theta) = dot(normal, light_dir)
// 	intensity = dot_vector(hit.normal, light_dir);
// 	if (intensity < 0)
// 		intensity = 0;
// 	if (intensity > 1)
// 		intensity = 1;

// 	// On combine la couleur de la lumière et celle de l'objet
// 	r = ((hit.color >> 16) & 0xFF) * ((light.color >> 16) & 0xFF) / 255;
// 	g = ((hit.color >> 8) & 0xFF) * ((light.color >> 8) & 0xFF) / 255;
// 	b = (hit.color & 0xFF) * (light.color & 0xFF) / 255;

// 	// On applique l'intensité de lumière (et le ratio de la lumière)
// 	r = r * intensity * light.ratio;
// 	g = g * intensity * light.ratio;
// 	b = b * intensity * light.ratio;

// 	// Clamp
// 	if (r > 255) r = 255;
// 	if (g > 255) g = 255;
// 	if (b > 255) b = 255;

// 	return ((r << 16) | (g << 8) | b);
// }
