#include <iostream>
#include <stdio.h>
#include <string>

using namespace std; 

class Data{
public:
	int year;
	int month;
	int day;

public:
	Data() : 	year (1), month (1), day (1)
	{}
	Data(int, int, int);

	void set_year(int year){
		this->year = year;
	}
	void set_month(int month){
		this->month = month;
	}
	void set_day(int day){
		this->day = day;
	}
	int get_year(){
		return year;
	}
	int get_month(){
		return month;
	}
	int get_day(){
		return day;
	}
	void operator =(Data some_data){
	this->day = some_data.day;
	this->month = some_data.month;
	this->year = some_data.year;
}
	virtual	void show(){
		cout<<"Day: "<<day<<endl<<"Month:  "<<month<<endl<<"Year:  "<<year<<endl;
	}
};

class Person : public Data{
	string surname;
	string name;
public:
	Person() : 	name("Tomy"), surname ("Cash")
	{}
	Person(string, string);

	void set_surname(string surname){
		this->surname = surname;
	}
	void set_name(string name ){
		this->name = name;
	}
	void operator =(Person some_persone){
		this->day = some_persone.day;
		this->month = some_persone.month;
		this->year = some_persone.year;
		this->name = some_persone.name;
		this->surname = some_persone.surname;
	}
	virtual	void show(){
		cout<<"Name: "<<name<<endl<<"Surname: "<<surname<<endl;
		Data::show();
	}
};

class Position{
	enum position_in{student, masters, postgraduate, assistant, s_lecturer, docent, professor};
public:
	int get_position_student(){
		return student;
	}
	int get_position_masters(){
		return student;
	}
	int get_position_postgraduate(){
		return student;
	}
	int get_position_assistant(){
		return student;
	}
	int get_position_s_lecturer(){
		return student;
	}
	int get_position_docent(){
		return student;
	}
	int get_position_professor(){
		return student;
	}
};

class Author : public Position, public Person{
	Data come_on_place;
public: 

	void set_come_day(int day){
		come_on_place.set_day(day);
	}
	void set_come_month(int month){
		come_on_place.set_month(month);
	}
	void set_come_year(int year){
		come_on_place.set_year(year);
	}
	void operator =(Author some_data){
	this->day = some_data.day;
	this->month = some_data.month;
	this->year = some_data.year;
	}

	virtual void show(){
		cout<<"Day on coming: "<<come_on_place.get_day()<<endl<<"Month on coming: "<<come_on_place.get_month()<<endl<<"Year on coming: "<<come_on_place.get_year()<<endl;
		Person::show();
	} 
	
};

class Thesis : public virtual Data{
	Author student;
	Author boss;
	string title;
	int count_paint;
	int count_let;
	float size;
};

class Arr_thesis : public virtual Data{
	Thesis *many_thesis;
	int count_list;
	int count_d_list;
};

Data::Data(int day, int month, int year){
	this->set_day(day);
	this->set_month(month);
	this->set_year(year);
}

Person::Person(string name, string surname){
	this->name = name;
	this->surname = surname;
}

void init_Data(Data *);
void init_Person(Person *);
int init_Position(Position *);
void init_Author(Author *);

int main(){
	Author *a = new Author;
	init_Author(a);
	a->show();
}

void init_Data(Data *someDay){
	int some_day;
	int some_month;
	int some_year;

	cout<<"Input day "<<endl;
	cin>>some_day;

	cout<<"Input month "<<endl;
	cin>>some_month;

	cout<<"Input year "<<endl;
	cin>>some_year;

	Data b(some_day, some_month, some_year);
	*someDay = b;
}

void init_Person(Person *somePersone){
	string some_name;
	string some_surname;

	cout<<"Input name "<<endl;
	cin>>some_name;

	cout<<"Input surname "<<endl;
	cin>>some_surname;

	Person b(some_name, some_surname);
	*somePersone = b;
	init_Data(somePersone);
}

int init_Position(Position *some_Position){
	int posit = some_Position->get_position_assistant();
	return posit;
} 

void init_Author(Author *some_Author){
	Person a, b;
	a = b;
	a.show();
}
