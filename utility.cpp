#include <iostream> 
using namespace std;
#include "utility.h"

const char *error_messages[] = { "success", "fail", "utility_range_error", "underflow", "overflow", "fatal", "not_present", 
"duplicate_error", "entry_inserted", "entry_found", "internal_error" };

bool user_says_yes() { 
	int c; 
	bool initial_response = true; 
	
	do { // Loop until an appropriate input is received. 
		if (initial_response) 
			cout << " (y,n)? " << flush; 
		else 
			cout << "Respond with either y or n: " << flush; 
		
		do { // Ignore white space. 
			c = cin.get(); 
		} while (c == '\n' || c ==' ' || c == '\t'); 
		
		initial_response = false; 
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N'); 
	
	return (c == 'y' || c == 'Y'); 
}

const char *return_error_message( Error_code code )
{
	return error_messages[ (int)code ];
}
