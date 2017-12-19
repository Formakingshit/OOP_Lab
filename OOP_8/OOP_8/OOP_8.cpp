#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <typeinfo>

using namespace std; 

#define M_PI      3.14159265358979323846
#define N					100


class dot {
protected:
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
	friend ostream &operator << (ostream &stream, const dot& dt){
		stream<<setw(9)<<"X"<<setw(9)<<"Y"<<endl;	
		stream<<setw(9)<<dt.x<<setw(9)<<dt.y<<endl;
		return stream;
	};
};

class circle: public dot{
protected:
	double radius;

public:
	circle();
	circle(double radius);
	
	void set_radius();
	double get_radius();

	virtual void init();
	virtual void get_results();
	friend ostream &operator << (ostream &stream, const circle& dt){
		cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Radius"<<endl;	
		cout<<setw(9)<<dt.x<<setw(9)<<dt.y<<setw(9)<<dt.radius<<endl;
		return stream;
	};
};

class rhomb: public dot{
protected:
	double side_of;

public:
	rhomb();
	rhomb(double side_of);

	void set_side_of();
	double get_side_of();

	virtual void init();
	virtual void get_results();

	friend ostream &operator << (ostream &stream, const rhomb& dt){
		cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Side"<<endl;	
		cout<<setw(9)<<dt.x<<setw(9)<<dt.y<<setw(9)<<dt.side_of<<endl;
		return stream;
	};

};

class circle_in_rhomb: public circle, public rhomb{
protected:
	double area_without_circle; // Area_rhomb = 2ar, a - side, r - radius_circle  
														// Area_circle = pr^2, p - PI, r - radius 
public: 
	circle_in_rhomb();

	void set_area_without_circle();
	double get_area_without_circle();
	
	virtual void init();
	virtual void get_results();
	friend ostream &operator << (ostream &stream, const circle_in_rhomb& dt){
		cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Side"<<setw(9)<<"Radius"<<setw(9)<<"A_W_C"<<endl;	
		cout<<setw(9)<<dt.circle::x<<setw(9)<<dt.circle::y<<setw(9)<<dt.side_of<<setw(9)<<dt.radius<<setw(9)<<dt.area_without_circle<<endl;
		return stream;
	};
};

class list_of_rhomb{
protected:
	circle_in_rhomb *many_circle_in;

public:
	list_of_rhomb();

	circle_in_rhomb *get_many_circle_in();
	circle_in_rhomb *operator [](int i);
	
	virtual void get_results();
	
	friend ostream &operator << (ostream &stream, const list_of_rhomb& dt){
		cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Side"<<setw(9)<<"Radius"<<setw(9)<<"A_W_C"<<endl;	
		
		for(int i = 0; i < N; i++){
			cout<<setw(9)<<dt.many_circle_in[i].circle::get_x()
				<<setw(9)<<dt.many_circle_in[i].circle::get_y()
				<<setw(9)<<dt.many_circle_in[i].get_side_of()
				<<setw(9)<<dt.many_circle_in[i].get_radius()
				<<setw(9)<<dt.many_circle_in[i].get_area_without_circle()<<endl;
		}

		return stream;
	};
};

class ForDotThrow{
protected:
	dot* forThrow;

public:
	ForDotThrow(){forThrow = new dot;}
	virtual void TakeThrow(){throw forThrow;};
};

class ForCircleThrow : public ForDotThrow{
public:
	ForCircleThrow(){forThrow = new circle;}
	virtual void TakeThrow(){throw forThrow;};
};

class ForRhombThrow : public ForDotThrow{
public:
	ForRhombThrow(){forThrow = new rhomb;}
	virtual void TakeThrow(){throw forThrow;}
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
	cout<<setw(9)<<"X"<<setw(9)<<"Y"<<endl;	
	cout<<setw(9)<<x<<setw(9)<<y<<endl;
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
	cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Radius"<<endl;	
	cout<<setw(9)<<get_x()<<setw(9)<<get_y()<<setw(9)<<radius<<endl;
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
	cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Side"<<endl;	
	cout<<setw(9)<<get_x()<<setw(9)<<get_y()<<setw(9)<<side_of<<endl;
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
	cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Side"<<setw(9)<<"Radius"<<setw(9)<<"A_W_C"<<endl;	
	cout<<setw(9)<<circle::get_x()<<setw(9)<<circle::get_y()<<setw(9)<<get_side_of()<<setw(9)<<get_radius()<<setw(9)<<area_without_circle<<endl;
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
	cout<<setw(9)<<"X"<<setw(9)<<"Y"<<setw(9)<<"Side"<<setw(9)<<"Radius"<<setw(9)<<"A_W_C"<<endl;	
	for(int i = 0; i < N; i++){
		cout<<setw(9)<<many_circle_in[i].circle::get_x()
			<<setw(9)<<many_circle_in[i].circle::get_y()
			<<setw(9)<<many_circle_in[i].get_side_of()
			<<setw(9)<<many_circle_in[i].get_radius()
			<<setw(9)<<many_circle_in[i].get_area_without_circle()<<endl;
	}
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


template <class T> class saving{
	T example;

	public:
	void inText();
	void inBinary();
};

template <class T> void saving<T>::inBinary(){
	char* FName = "watchresult1.txt";
	
	ofstream out(FName, ofstream::binary | ofstream::out);

	for(int i = 0; i < N; i++) {
		out<<setw(9)<<example[i]->circle::get_x()<<setw(9)<<example[i]->circle::get_y()
			<<setw(9)<<example[i]->get_side_of()<<setw(9)<<example[i]->get_radius()<<setw(9)<<example[i]->get_area_without_circle()<<endl;
	}
	out.close();                                 
}

template <class T> void saving<T>::inText(){
	char* FName = "watchresult.txt";

	ofstream out(FName, ofstream::out | ofstream::out);
	for(int i = 0; i < N; i++){
		out<<setw(9)<<example[i]->circle::get_x()<<setw(9)
			<<example[i]->circle::get_y()<<setw(9)
			<<example[i]->get_side_of()<<setw(9)<<example[i]->get_radius()<<setw(9)<<example[i]->get_area_without_circle()<<endl;
	}
	out.close();    
}

int main(){
	dot *point = new circle;
	string name = typeid(*point).name();
	ForDotThrow *forthrow;
	
	point = 0;
	try{
		if(name == "class dot *" && point == 0){
			forthrow = new ForDotThrow;
		}

		else if(name == "class circle" && point == 0){
			forthrow = new ForCircleThrow;
		}

		else if(name == "class rhomb" && point == 0){
			forthrow = new ForRhombThrow;
		}

		forthrow->TakeThrow();
	}
		catch(circle*){
			cout<<"bad_typeid"<<endl;
			cout<<"pointer in derived class circle equal 0"<<endl;
		}
	
		catch(rhomb*){
			cout<<"bad_typeid"<<endl;
			cout<<"pointer in derived class rhomb equal 0"<<endl;
		}

		catch(dot*){
			cout<<"bad_typeid"<<endl;
			cout<<"pointer in base class dot equal 0"<<endl;
		}

}		