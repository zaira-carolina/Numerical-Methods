double funcion(double x){
    double y;
    double pi = M_PI;
	/* 
	 * a) y = pow(x,3)-21*(x,2)+120*x-100;
	 * a.1) y = 0.99*pow(x,3)-21*(x,2)+120*x-100;
	 * a.2) y = 1.01*pow(x,3)-21*(x,2)+120*x-100;
	 * b) y = 2-log(x)*(1/x); 
	 * c) y = log(pow(x,2)+1)-exp(0.4*x)*cos(M_PI*x); 
	*/
     y = 1.01*pow(x,3)-21*(x,2)+120*x-100;
	//y = pow(x,3)-21*(x,2)+120*x-100;
	//y = log(pow(x,2)+1)-exp(0.4*x)*cos(M_PI*x);
	//y = 0.99*pow(x,3)-21*(x,2)+120*x-100; 
    return y;
	}
