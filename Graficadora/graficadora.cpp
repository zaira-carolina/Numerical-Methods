#include <iostream>
#include "fparser4.5.2/fparser.hh"
#include <vector>
#include <cairo/cairo.h>
#include <cairo-svg.h>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>


using namespace std; 
double pi = M_PI;
// Tamaño de la superficie de Cairo
double WIDTH {616}; 
double HEIGHT {516}; 
// Bordes para la superficie
double xmin_pix{40}, xmax_pix{WIDTH-50};
double ymin_pix{30}, ymax_pix{HEIGHT-30};
int divisiones {1000}; //definición de la gráfica, más puntos, más suave
double cant_valores_ejes {10};


//Ecuación de la recta para transformar puntos x, f(x) a pixeles. 
double Ecuacion_recta(double xmax_pix, double xmin_pix, double espaciox, double x, double a){
	double y, m;
	m = (xmax_pix-xmin_pix)/(espaciox);
	y = m*(x-a)+xmin_pix;
	return y;
	}

int main(){
	double a, b; 
	double espaciox, espacioy;
	
	//Llamar a la función desde consola con Fparser
	string function; 
	FunctionParser fparser; 
	fparser.AddConstant("pi", 3.1415926535897932); 
	while (true){
		cout << "f(x) = " ; 
		getline(cin, function); 
		if (cin.fail()) return 0; 
		int res = fparser.Parse(function, "x");
		if (res < 0) break; 
		cout << string(res+7, ' ') << "^\n" << fparser.ErrorMsg() << "\n\n"; 
		}
	//Valores del dominio de x
	cout << "Inserte valor de a: " << endl; 
	cin >> a; 
	cout << "Inserte valor de b: " << endl; 
	cin >> b; 
	
	//Hacer la superficie con Cairo
	cairo_surface_t*surface; 
	cairo_t*cr; 
	surface = cairo_svg_surface_create("grafica.svg", WIDTH, HEIGHT);
	cr = cairo_create(surface); 
	//Hacer un rectángulo del tamaño de la superficie para colorear el fondo
	cairo_set_source_rgb(cr, 255, 255, 255);
	cairo_rectangle(cr, 0, 0, WIDTH, HEIGHT);
	cairo_fill(cr);
	//Hacer los bordes de la imagen
	// - bordes verticales -
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_move_to(cr, xmin_pix, ymin_pix);
	cairo_line_to(cr, xmin_pix, ymax_pix);
	
	cairo_move_to(cr, xmax_pix, ymin_pix);
	cairo_line_to(cr, xmax_pix, ymax_pix);
	// - bordes horizontales - 
	cairo_move_to(cr, xmin_pix, ymin_pix);
	cairo_line_to(cr, xmax_pix, ymin_pix);
	
	cairo_move_to(cr, xmin_pix, ymax_pix);
	cairo_line_to(cr, xmax_pix, ymax_pix);
	
	cairo_stroke(cr);
	
	// dibujar la función f(x)
	double minx[] = {0}, maxx[] = {0};
	double vals[] = {0}, valsend[] = {0}; // vals: para evaluar la función, valsend: para evaluar el punto siguiente
	double divisiones_x = abs(b-a)/divisiones;
	double divisiones_y = (ymax_pix)/cant_valores_ejes; 
	//vectores para guardar las evaluaciones de la función
	vector<double> valy (divisiones), valyend (divisiones);
	vector<double> valxpix (divisiones), valxpixend (divisiones); 
	vector<double> valypix (divisiones), valypixend (divisiones);
	
	
	minx[0] = a, maxx[0] = b; 
	espaciox = (b-a); 
	
	for (int i = {0}; i<= divisiones; ++i){
		vals[0] = a + i*divisiones_x;
		valy[i] = fparser.Eval(vals); 
		}
	
	espacioy = *min_element(valy.begin(), valy.end())-*max_element(valy.begin(), valy.end());
	double max_valy = *max_element(valy.begin(), valy.end()); 
	
	for (int i={0}; i<= divisiones; ++i){
		// obtener los puntos x , f(x), y x+i y f(x+1)
		vals[0] = a + i*divisiones_x; 
		valy[i] = fparser.Eval(vals);
		
		valsend[0] = a+(i+1)*divisiones_x; 
		valyend[i] = fparser.Eval(valsend);
		
		valxpix[i] = Ecuacion_recta(xmax_pix, xmin_pix, espaciox, vals[0], a);
		valypix[i] = Ecuacion_recta(ymax_pix, ymin_pix, espacioy, valy[i], max_valy);
		
		valxpixend[i] = Ecuacion_recta(xmax_pix, xmin_pix, espaciox, valsend[0], a);
		valypixend[i] = Ecuacion_recta(ymax_pix, ymin_pix, espacioy, valyend[i], max_valy);
		
		//dibujar la gráfica
		cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
		cairo_set_line_width(cr, 0.5);
		
		cairo_move_to(cr, valxpix[i], valypix[i]);
		cairo_line_to(cr, valxpixend[i], valypixend[i]);
		
		cairo_stroke(cr);
		}
	//Valores al eje x
	
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.1);
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 7.0);
	
	for (int i{0}; i<= divisiones; i+=(divisiones/10)){
	 
		vals[0] = a + i*divisiones_x; 
		valxpix[i] = Ecuacion_recta(xmax_pix, xmin_pix, espaciox, vals[0], a); 		
		
		stringstream streamx; 
		streamx << fixed << setprecision(2) << vals[0];
		string s = streamx.str();
			
		cairo_move_to(cr, valxpix[i], ymax_pix+7);
		cairo_save(cr);
		cairo_rotate(cr, 0.0);
		cairo_show_text(cr, s.c_str());
		cairo_restore(cr);
	}
	//Valores al eje y
	vector<double> pix_to_y (11);	
	for (int i{1}; i<= 10; ++i){
		pix_to_y[i] = (espacioy/(ymax_pix-ymin_pix))*(i*divisiones_y-ymin_pix)+ max_valy; 
		stringstream stream; 
		stream << fixed << setprecision(2) << pix_to_y[i];
		string sy = stream.str();

		cairo_move_to(cr, xmin_pix-25, i*divisiones_y);
		cairo_save(cr);
		cairo_rotate(cr, 0.0);
		cairo_show_text(cr, sy.c_str());
		cairo_restore(cr);
		}
	//Nombre a la gráfica y a los ejes
	cairo_set_font_size(cr, 20.0);
	cairo_move_to(cr, xmin_pix+170, 20.0);
	string titulo = "f(x) = " + function;
	cairo_show_text(cr, titulo.c_str());
	
	cairo_set_font_size(cr, 10.0);
	cairo_move_to(cr, xmin_pix+235.0, ymax_pix+20.0);
	cairo_show_text(cr, " eje x ");
	
	cairo_move_to(cr, xmin_pix-30.0, ymin_pix+250.0);
	cairo_rotate(cr, -90*(M_PI/180));
	cairo_show_text(cr, "eje y");
		

	cairo_destroy(cr);
	cairo_surface_destroy(surface);
	
	}

