#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std; 

#define M_PI      3.14159265358979323846
#define N					10000000

class IntThrow {
	int *a;
public:
	IntThrow(){a = new int;}
	virtual void TakeThrow(){throw a;};
};

class DoubleThrow :public IntThrow {
	double *b;
public:
	DoubleThrow(){b = new double;}
	virtual void TakeThrow(){throw b;};
};

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
	list_of_rhomb(int &);

	circle_in_rhomb *get_many_circle_in();
	circle_in_rhomb *operator [](int i);
	
	virtual void get_results();
	
	void mysort(int);

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


dot::dot(){
	x = rand() % 1024;
	y = rand() % 1024;
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

list_of_rhomb::list_of_rhomb(int& size){
	many_circle_in = new circle_in_rhomb[size];
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

void list_of_rhomb::mysort(int size){
	unsigned int start_time; // початковий час
  unsigned int end_time; // кінцевий час
  unsigned int search_time; // шуканий час

	int *arrInt = new int [size];
	int tempI;
	double *arrDouble = new double [size];
	double tempD;

	for(register int i = 0; i < size; i++){
		arrInt[i] = many_circle_in[i].circle::get_x();
		arrDouble[i] = many_circle_in[i].get_area_without_circle();
	}
/*
	for(int i = 0; i < size; i++){
		cout<<setw(10)<<arrInt[i]<<"   "<<setw(10)<<arrDouble[i]<<endl;
	}
*/
	start_time = clock();
	register int i = size - 1;

	for(register int count = 0; count < size - 1; count++){
		for(; i > 0 + count; i--){
			if(arrInt[i] < arrInt[i - 1]){
				tempI = arrInt[i];
				arrInt[i] = arrInt[i - 1];
				arrInt[i - 1] = tempI;
			}	
			if(arrDouble[i] < arrDouble[i - 1]){
				tempD = arrDouble[i];
				arrDouble[i] = arrDouble[i - 1];
				arrDouble[i - 1] = tempD;
			}
		}
	}
	end_time = clock();
	search_time = end_time - start_time;
	cout<<"Time my sort(int and double):"<<search_time<<endl;
/*	cout<<endl;
	for(int i = 0; i < N; i++){
		cout<<setw(10)<<arrInt[i]<<"   "<<setw(10)<<arrDouble[i]<<endl;
	}
*/
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


template <class T> double ser_har(T list_rhomb){
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

/*
template <class T> void saving<T>::outBinary(){
	char* FName = "outresult1.txt";
	
	ofstream out(FName, ofstream::binary | ofstream::out);

	for(int i = 0; i < N; i++) {
		out<<setw(9)<<example[i]->circle::get_x()<<setw(9)<<example[i]->circle::get_y()
			<<setw(9)<<example[i]->get_side_of()<<setw(9)<<example[i]->get_radius()<<setw(9)<<example[i]->get_area_without_circle()<<endl;
	}
	out.close();                                 
}

template <class T> void saving<T>::outText(){
	char* FName = "outresult.txt";

	ofstream out(FName, ofstream::out | ofstream::out);
	for(int i = 0; i < N; i++){
		out<<setw(9)<<example[i]->circle::get_x()<<setw(9)
			<<example[i]->circle::get_y()<<setw(9)
			<<example[i]->get_side_of()<<setw(9)<<example[i]->get_radius()<<setw(9)<<example[i]->get_area_without_circle()<<endl;
	}
	out.close();    
}
*/
bool MySortInt(int a, int b){
	return a < b ;
}

bool MySortDouble(double a, double b){
	return a < b ;
}

void Librarysort(int &size){
	unsigned int start_time; // початковий час
  unsigned int end_time; // кінцевий час
  unsigned int search_time; // шуканий час

	list_of_rhomb l_o_r(size);
		
	vector <int> v_i(size);
	for(int i = 0; i < size; i++){
		v_i[i] = l_o_r.get_many_circle_in()[i].circle::get_x();
		//cout<<v_i[i]<<endl;
	}

	vector <double> v_d(size);
	for(int i = 0; i < size; i++){
		v_d[i] = l_o_r.get_many_circle_in()[i].get_area_without_circle();
		//cout<<v_d[i]<<endl;
	}

	start_time = clock();
	sort(v_d.begin(), v_d.end(), MySortDouble);
	sort(v_i.begin(), v_i.end(), MySortInt);
	end_time = clock();
	search_time = end_time - start_time;
	cout<<"Time library sort(int and double): "<<search_time<<endl;
		
	/*
	cout<<endl;
	for(int i = 0; i < N; i++){
		cout <<v_i[i]<<endl;
	}
		
	cout<<endl;
	for(int i = 0; i < N; i++){
		cout <<v_d[i]<<endl;
	}
	*/

}

void MakeSortWithDiffSize(){
		for(register int size = 10; size < N; size*= 10){
			list_of_rhomb l_o_r(size);

			Librarysort(size);
			cout<<endl<<endl;
			l_o_r.mysort(size);
			cout<<"-----------------------------------------------------------------------";
			cout<<endl<<endl;
		}
}

int main(){
	dot *point = new dot;
	cout<<"Base class: "<<typeid(*point).name()<<endl;
	
	point = new circle;
	cout<<"Child class: "<<typeid(*point).name()<<endl;
	cout<<endl<<endl;
		
	IntThrow *somethrow;
	circle somecircle;

	try{
		somecircle.init();
		if(somecircle.get_radius() <= 0){
			somethrow = new DoubleThrow;
			somethrow->TakeThrow();
		}
		
		else if(somecircle.get_x() == 0 || somecircle.get_y() == 0){
			somethrow = new IntThrow;
			somethrow->TakeThrow();
		}
		cout<<endl<<endl;
		MakeSortWithDiffSize();
	}
	catch(int*){
		cout<<"Erro int type"<<endl;
	}
	catch(double*){
		cout<<"Erro double type"<<endl;
	}
}