#include"mstring.h"

int mstring::split_string_to_float(char *msn, char *regex, float *array) {
    char *msn_a = msn;
    char *aux;
    int index = -1;

    while(strcmp(msn_a, "")) {
	if(sscanf(msn_a, "%f", &(array[index + 1])) == 1) index++;
	if((msn_a = strstr(msn_a, regex)) == NULL) break;
	else msn_a += strlen(regex);
    }

    return index + 1;
}
