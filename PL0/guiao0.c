#include "guiao0.h"

int fill (int *v, int size, int value) {
	int i;
	for (i = 0; i < size; i++)
		v[i] = value;

	return 1;
}

int find (int *v, int size, int value) {
	int i, r = 0;
	for (i = 0; i < size && r == 0; i++)
		if(v[i] == value) r = 1;

	return r;
}

