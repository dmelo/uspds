#include"mmath.h"

float mmath::area_triangulo(float ax, float ay, float bx, float by, float cx, float cy) {
	return fabs((ax * by) + (ay * cx) + (bx * cy) - (ax * cy) - (ay * bx) - (by * cx)) / 2;
}

float mmath::distancia(float ax, float ay, float bx, float by) {
	return sqrtf(powf(ax - bx, 2) + powf(ay - by, 2));
}

float mmath::padronizar_angulo_2_pi(float angulo) {
	while(angulo < 0)
		angulo += 2 * M_PI;
	while(angulo >= 2 * M_PI)
		angulo -= 2 * M_PI;
	
	return angulo;
}

float mmath::padronizar_angulo_pi(float angulo) {
	while(angulo < 0)
		angulo += M_PI;
	while(angulo >= M_PI)
		angulo -= M_PI;
	
	return angulo;
}

float mmath::padronizar_angulo_pi_sobre_2(float angulo) {
	while(angulo < 0)
		angulo += M_PI_2;
	while(angulo >= M_PI_2)
		angulo -= M_PI_2;
	
	return angulo;
}
float mmath::padronizar_angulo_pi_sobre_4(float angulo) {
	while(angulo < 0)
		angulo += M_PI_4;
	while(angulo >= M_PI_4)
		angulo -= M_PI_4;
	
	return angulo;
}

int mmath::angcmp(float um, float dois) {
	if(fabs(um - dois) <= 0.0001)
		return 0;
	if(um < dois)
		return -1;
	
	return 1;
}

bool mmath::point_inside_convex_polygon(float px, float py, float *x, float *y, int n_points) {
    float middle_x = 0.0, middle_y = 0.0;
    float total_area = 0.0;
    float virtual_area = 0.0;

    for(int i = 0; i < n_points; i++) {
	middle_x += x[i];
	middle_y += y[i];
    }
    middle_x /= n_points;
    middle_y /= n_points;

    for(int i = 0; i < n_points; i++) total_area += mmath::area_triangulo(middle_x, middle_y, x[i], y[i], x[(i+1)%n_points], y[(i+1)%n_points]);
    for(int i = 0; i < n_points; i++) virtual_area += mmath::area_triangulo(px, py, x[i], y[i], x[(i+1)%n_points], y[(i+1)%n_points]);

    if(fabs(virtual_area - total_area) < 0.0001)
	return false;
    return true;
}
	
bool mmath::histogram(vector<float> *data, int n_bars, char *filename) {
    float biggest, smallest, size, area = 0.0;
    int *histogram = new int[n_bars];
    FILE *fd;

    if(data->size() == 0)
	return false;

    if((fd = fopen(filename, "w")) == NULL)
	return false;

    biggest = smallest = data->at(0);
    for(int i = 1; i < data->size(); i++) {
	if(data->at(i) > biggest) biggest = data->at(i);
	if(data->at(i) < smallest) smallest = data->at(i);
    }
    size = (biggest - smallest) / n_bars;
    for(int i = 0; i < n_bars; i++) histogram[i] = 0;
    for(int i = 0; i < data->size(); i++) {
	(histogram[(int) ((data->at(i) - smallest) / size)])++;
	area += size;
    }
    for(int i = 0; i < n_bars; i++) fprintf(fd, "%f %f\n", smallest + (i * size), ((float) histogram[i]) / area);

    fclose(fd);

    return true;
}

float mmath::mean(vector<float> *data) {
    float aux = 0.0;
    for(int i = 0; i < data->size(); i++) aux += data->at(i);
    return aux / data->size();
}

float mmath::variance(vector<float> *data) {
    float aux = 0.0;
    float mean = mmath::mean(data);
    for(int i = 0; i < data->size(); i++) aux += powf(data->at(i) - mean, 2.0);
    return aux / data->size();
}
