#include <iostream>
#include <windows.h>

using namespace std;

#define Zero_id "0000000000"
#define SIZE_MASS 50

class loan_document{
	char *name;
	char *surname;
	int id_code ;
	double loan_sum;
	double loan_interest;

public:
	loan_document();
	loan_document(char *name_i, char *surname_i, int id_code_i, double loan_sum_i, double loan_interest_i);
	loan_document(const loan_document &some_document);
	~loan_document();

	char *set_name(char *somechar);
	char *set_surname(char *somechar);
	char *set_id_code(char *somechar);
	char* set_loan_sum(char *somechar);
	char* set_loan_interest(char *somechar);
	char* check_string(char *some_char);
	int	check_id(char *some_char_id);
	double check_double(char *loan_money);

	void get_rezult();
}some;

loan_document::loan_document(){
	char *somechar = new char [SIZE_MASS];

	while(! check_string( set_name(somechar)));
	name = new char [strlen(somechar) + 1];
	strcpy(name, somechar);

	while(! check_string( set_surname(somechar)));
	surname = new char [strlen(somechar) + 1];
	strcpy(surname, somechar);

	while(! (id_code = check_id( set_id_code(somechar)) ));
	while(! (loan_sum = check_double( set_loan_sum(somechar)) ));
	while(! (loan_interest = check_double( set_loan_interest(somechar)) ));
	
	printf("\n");
	delete [] somechar;
}

loan_document::loan_document(char *name_i, char *surname_i, int id_code_i, double loan_sum_i, double loan_interest_i){
	name = new char [strlen(name_i) + 1];
	strcpy(name, name_i);

	surname = new char [strlen(surname_i) + 1];
	strcpy(surname, surname_i);

	id_code = id_code_i;
	loan_sum = loan_sum_i;
	loan_interest = loan_interest_i;
} 

loan_document::loan_document(const loan_document &some_document){
	name = new char [strlen(some_document.name) + 1];
	strcpy(name, some_document.name);

	surname = new char [strlen(some_document.surname) + 1];
	strcpy(surname, some_document.surname);

	id_code = some_document.id_code;
	loan_sum = some_document.loan_sum;
	loan_interest = some_document.loan_interest;
}

loan_document::~loan_document(){
	delete [] name;
	delete [] surname;
}

char *loan_document::set_name(char *somechar){
	printf("Enter name (First letter big) = ");
	gets(somechar);
	
	return somechar;
}

char *loan_document::set_surname(char *somechar){
	printf("Enter surname (First letter big) = ");
	gets(somechar);

	return somechar; 
}

char *loan_document::set_id_code(char *somechar){
	printf("Enter id_code (10 sumbol) = " );
	gets(somechar);
	
	return somechar;
}

char *loan_document::set_loan_sum(char *somechar){
	printf("Enter sum of loan (ALL money of credit) = ");
	gets(somechar);
	
	return somechar; 
}

char *loan_document::set_loan_interest(char *somechar){
	printf("Enter interest of loan = ");
	gets(somechar);

	return somechar;
}

char *loan_document::check_string(char *some_char){
	if((*some_char >= -65 && *some_char <= -33) || (*some_char >= 65 && *some_char <= 90)){
		for(int i = 1; i < strlen(some_char); i++){
			if((*(some_char + i) >= -32 && *(some_char + i) <= -1) || (*(some_char + i) >= 97 && *(some_char + i) <= 122)){
			}

			else 
				return 0;
		}
	}

	else
		return 0;

	return some_char;
}

int loan_document::check_id(char *some_char_id){
	int count = 0;

	while( *(some_char_id + count) != '\0'){
		count++;
	}

	if(count == 10){
		for(int i = 0; i < sizeof(some_char_id); i++){
			if(*(some_char_id + i) >= 48 && *(some_char_id + i) <= 57 ){
			} 

			else
				return 0; 
		}
	}

	else
		return 0;
	
	return atoi(some_char_id);
} 

double loan_document::check_double(char *loan_money){
	unsigned int	checker = 0,
								dot_index = 0;
	

	for(int i = 0; i < strlen(loan_money); i++){
		if(*(loan_money + i) == 46){
			checker++;
			dot_index = i;
		}

		else if(*(loan_money + i) < 48 || *(loan_money + i) > 57 || checker > 1);
	}

	if(checker){
		*(loan_money + dot_index) = 44;
	}

	return atof(loan_money);
}

void loan_document::get_rezult(){
	printf("Name = %s\nSurname = %s\nId_code = %010d\nLoan_sum = %lf\nLoan_interest = %lf\n", name, surname, id_code, loan_sum, loan_interest);
}

int main(){
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(0, "");

	loan_document a("Вася", "Пупкин", 1000000001, 1000.1000, 100.100);
	a.get_rezult();
	printf("\n");

	some.get_rezult();
	printf("\n");
	
	loan_document b;
	b.get_rezult();
	printf("\n");

	loan_document c(b);
	c.get_rezult();
	printf("\n");
}

