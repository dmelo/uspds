#ifndef MSTRING_H
#define MSTRING_H

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<string>

class mstring {
    public:
	/**
	 * Split the given string using the regex into float numbers. The numbers will be located on the array.
	 *
	 * \param msn String that contains the message
	 * \param regex The string that determine the separate field
	 * \param array Is used to store the result
	 *
	 * \return Return the number of elements on the array.
	 */
	static int split_string_to_float(char *msn, char *regex, float *array);
};

#endif
