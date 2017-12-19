#include <iostream>
#include <string>
#include <time.h>

using namespace std; 

#define M_PI      3.14159265358979323846
#define N					1000


class dot {
	int x;
	int y;

public:
	dot();
	dot(int x, int y);
	
	void set_x();
	void set_y();
	
	int get_x();
	int get_y();
	
	virtual void init();
	virtual void get_results();
};

class circle: public dot{
	double radius;

public:
	circle();
	circle(double radius);
	
	void set_radius();
	double get_radius();

	virtual void init();
	virtual void get_results();
};

class rhomb: public dot{
	double side_of;

public:
	rhomb();
	rhomb(double side_of);

	void set_side_of();
	double get_side_of();

	virtual void init();
	virtual void get_results();
};

class circle_in_rhomb: public circle, public rhomb{
	double area_without_circle; // Area_rhomb = 2ar, a - side, r - radius_circle  
														// Area_circle = pr^2, p - PI, r - radius 
public: 
	circle_in_rhomb();

	void set_area_without_circle();
	double get_area_without_circle();
	
	virtual void init();
	virtual void get_results();
};

class list_of_rhomb{
	circle_in_rhomb *many_circle_in;

public:
	list_of_rhomb();

	circle_in_rhomb *get_many_circle_in();
	circle_in_rhomb *operator [](int i);
	
	virtual void get_results();
};


dot::dot(){
	x = rand();
	y = rand();
};

dot::dot(int x, int y){
	this->x = x;
	this->y = y;
}

void dot::set_x(){
	cin>>x;
}

void dot::set_y(){
	cin>>y;
}

int dot::get_x(){
	return x;
}

int dot::get_y(){
	return y;
}

void dot::init(){
	cout<<"Input x: ";
	set_x();
	
	cout<<"Input y: ";
	set_y();
}

void dot::get_results(){
	
}


circle::circle(){
	radius = rand() % 5 + 1;
}

circle::circle(double radius){
	this->radius = radius; 
}

void circle::set_radius(){
	cin>>radius; 
}

double circle::get_radius(){
	return radius;
}

void circle::init(){
	dot::init();
	cout<<"Input radius: ";
	set_radius();
}

void circle::get_results(){
	
}


rhomb::rhomb(){
	side_of = rand() % 5 + 10;
}

rhomb::rhomb(double side_of){
	this->side_of = side_of;
}

void rhomb::set_side_of(){
	cin>>side_of;
} 

double rhomb::get_side_of(){
	return side_of;
}

void rhomb::init(){
	cout<<"Input side of rhomb: ";
	set_side_of();
}

void rhomb::get_results(){
	
}


circle_in_rhomb::circle_in_rhomb(){
	area_without_circle = 2 * get_radius() * get_side_of() - (M_PI * pow(get_radius(),2));
}

void circle_in_rhomb::set_area_without_circle(){
	double	radius = get_radius();

	area_without_circle = 2 * radius * get_side_of() - (M_PI * pow(radius,2));
}

double circle_in_rhomb::get_area_without_circle(){
	return area_without_circle;
}

void circle_in_rhomb::init(){
	circle::init();
	rhomb::init();

	set_area_without_circle();
}

void circle_in_rhomb::get_results(){
	cout<<"Area without circle: "<<circle_in_rhomb::get_area_without_circle();	
}


list_of_rhomb::list_of_rhomb(){
	many_circle_in = new circle_in_rhomb[N];
}

circle_in_rhomb *list_of_rhomb::get_many_circle_in(){
	return many_circle_in;
}

circle_in_rhomb	*list_of_rhomb::operator[](int i){
	if(i < 0){
		exit(0);	
	}

	return (many_circle_in + i);
}

void list_of_rhomb::get_results(){

}


template <class T> double  ser_har(T list_rhomb){
	long double sum = 0; 

	for(int i = 0; i < N; i++){
		sum += 1./list_rhomb[i]->get_area_without_circle();
		cout<<list_rhomb[i]->get_area_without_circle()<<" ";
	}

	cout<<"\n"<<sum;
	return (double) N/sum; 
}


int main(){
	int i;

	list_of_rhomb a;

/*	cout<<"Input some index: ";
	cin>>i;
	
	a[i]->init();
	a[i]->set_area_without_circle();

	*/
	
	cout<<"Input some index: ";
	cin>>i;

	cout<<"Area_of_element "<<i<<":  "<<a[i]->get_area_without_circle()<<endl;
	cout<<"\nSerednie Harmon: "<<ser_har(a)<<endl;
	
	/*
	dot *b = new dot[10];
	for(int i = 0; i < 10; i++){
		cout<<(b+i)->get_x()<<" ";
	}
	cout<<endl;

	for(int i = 0; i < 10; i++){
		cout<<(b+i)->get_y()<<" ";
	}
	cout<<endl;
	*/
}