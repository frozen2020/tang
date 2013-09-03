/*************************************************

Name	: AT25320.h
Function: The head-file of AT25320.C,including 
		  function prototypes.
Author	: Pan.L.F
Date	: 2006-02-19
***************************************************/

void Init_AT25320(unsigned char);


void AT25_WritePage(unsigned int address, 		//from this address;
					unsigned char num_of_byte,	//the number(<32) of bytes to write;
					unsigned char* source		//data to write.
					);



void AT25_ReadArray(unsigned int address, 		//from this address;
					unsigned int num_of_byte,	//the number of bytes to read;
					unsigned char* destination	//store the result.
					);


