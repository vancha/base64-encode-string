#include <stdio.h>
#include <string.h>
#include <search.h>
#include <assert.h>
#include <stdlib.h>

//takes an int, returns 8 chars
char* int_to_binary_representation(const int value){
	char* binary_representation = malloc(8 * sizeof(char));
	for(int bit = 7; bit >= 0;bit--){
		binary_representation[7-bit] = ((value >> bit) & 0x01 ) ? '1' : '0';
        }
	return binary_representation;
}

int binary_string_to_int(const char* binary_string) {
        char *used_for_strtol;
        return  strtol(binary_string, &used_for_strtol, 2);
}

int* octet_to_sextet(int v1, int v2, int v3) {
        //first get the binary strings
        char* v1_binary = int_to_binary_representation(v1);
        char* v2_binary = int_to_binary_representation(v2); 
        char* v3_binary = int_to_binary_representation(v3);

	//then append them together
	int size = (sizeof(char)*24)+1;
	char* concat_string = malloc(size);
	strcat(concat_string, v1_binary);
	strcat(concat_string, v2_binary);
	strcat(concat_string, v3_binary);
	concat_string[size] = '\0';
	//seperate the large binary string in to fourths
	char s1[7],s2[7],s3[7],s4[7];
	s1[7] = '\0';
	s2[7] = '\0';
	s3[7] = '\0';
	s4[7] = '\0';
	
	int idx = 0;
	for(int concat_index = 0; concat_index < 4;concat_index++){
		
		for(int fourth_index = 0; fourth_index < 6;fourth_index++){

			int inner_index = (6 * idx)+fourth_index;
			if(inner_index / 6 == 0){
				s1[fourth_index] = concat_string[inner_index];
			} else if(inner_index / 6 == 1){
				s2[fourth_index] = concat_string[inner_index];
			} else if(inner_index / 6 == 2){
				s3[fourth_index] = concat_string[inner_index];
			} else if(inner_index / 6 == 3){
				s4[fourth_index] = concat_string[inner_index];
			}
		}
		idx += 1;
	}
	int* sextet = malloc(sizeof(int)*4);
	sextet[0] = binary_string_to_int(s1);
	sextet[1] = binary_string_to_int(s2);
	sextet[2] = binary_string_to_int(s3);
	sextet[3] = binary_string_to_int(s4);
	return sextet;

}


int main() {
	//the "map" that we can use to convert indices to characters
	char value_string[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','f','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};


	char input[] = "Many hands make light work.";

	int length = strlen(input);

	while(length % 3 != 0){
		length = length + 1;
		printf("%i",length);
	}

	char* new_str[length];
	strcpy(new_str, input);
	new_str[length] = '\0';
	
	char* test = &new_str;
	
	for(int chunk = 0; chunk < length;chunk+=3){
		char first = *test;
		test++;
		char second = *test;
		test++;
		char third = *test;
		test++;
		int* sextet = octet_to_sextet(first,second,third);
		
		for(int new_char = 0; new_char < 4;new_char++){
			printf("%c",value_string[sextet[new_char]]);
		}
		free(sextet);
	}
	return 0;
}
