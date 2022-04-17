#pragma once 
#include <iostream> 
#include <fstream> 
#include <string> 
#include <cctype>
#include <ctime>
#include <chrono>
#include <ratio>
using namespace std;

enum Error_code { success, fail, utility_range_error, underflow, overflow, fatal, not_present, 
duplicate_error, entry_inserted, entry_found, internal_error }; 

const char *return_error_message( Error_code code );

bool user_says_yes();

