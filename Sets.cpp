#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

int cmpfunc(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
	int *search;
	
	search = (int*) bsearch (&x, self->elements, self->len, sizeof(int), cmpfunc);

	if (search != NULL) {
		return true;
	}
	else {
		return false;
	}

	free(search);
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
	if (isMemberSet(self, x)) {
		return;
	}
	else if (self->len == 0) {						//if there is nothing in the set 
		free(self->elements);
		self->elements = (int *)malloc(sizeof(int));
		self->elements[0] = x;
		self->len += 1;
	}
	else {	//if the integer x is the largest value add it to the end
		int j = 0, k = 0;
		int *tempArr = (int *)malloc(sizeof(int) * (self->len + 1));
		
		for (int i = 0; i < self->len; i++) {

			if (x < self->elements[0]) {
				k = 1;
				tempArr[0] = x;
			}

			j = i + k;
			tempArr[j] = self->elements[i];
			
			if (i != self->len - 1 && x > self->elements[i] && x < self->elements[i + 1]) {
				tempArr[i + 1] = x;
				k = 1;
			}
			
		}
		if (x > self->elements[self->len - 1]) {
				tempArr[self->len] = x;
		}

		free(self->elements);
		self->elements = tempArr;
		self->len += 1;
	} 
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
	if (isMemberSet(self, x) == false || self->len == 0 || self->elements == NULL) {

	}
	else {
		int j, k = 0;
		for (int i = 0; i < self->len; i++) {
			j = i + k;
			if (i != self->len - 1) {
			self->elements[i] = self->elements[j];
			}
			if (self->elements[i] == x && i != self->len - 1) {
				self->elements[i] = self->elements[i + 1];
				k = 1;
			}
		}
		self->len -= 1;
	}
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
	if (self->len != other->len) {
		return false;
	}
	else {
		for (int i = 0; i < self->len; i++) {
			if (self->elements[i] != other->elements[i])
				return false;
		}
		return true;
	}
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
	if (self->len > other->len) {
		return false;
	}
	if (self->len == 0) {
		return true;
	}
	else {
		int i = 0, j = 0, k = 0;
		while (i < self->len && j < other->len) {
			if (self->elements[i] < other->elements[j]) {
				return false;
			}
			else if (self->elements[i] > other->elements[j]) {
				j++;
			}
			else {
				i++;
				j++;
			}
	}		return true;
	}
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
	int i = 0, j = 0, k = 0;
	int *temp1 = (int *)malloc(sizeof(int) * self->len);
	while (i < self->len && j < other->len) {
		if (self->elements[i] < other->elements[j]) {
			i++;
		}
		else if (self->elements[i] > other->elements[j]) {
			j++;
		}
		else {
			temp1[k] = self->elements[i];
			k++;
			i++;
		}
	}
	self->len = k;
	free(self->elements);
	self->elements = temp1;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
	int i = 0, j = 0, k = 0;
	int *temp2 = (int *)malloc(sizeof(int) * self->len);
	while (i < self->len && j < other->len) {
		if (self->elements[i] < other->elements[j]) {
			temp2[k] = self->elements[i];
			k++;
			i++;
		}
		else if (self->elements[i] > other->elements[j]) {
			j++;
		}
		else {
			i++;
			j++;
		}
	}
	while (i < self->len) {
		temp2[k] = self->elements[i];
		k++;
		i++;
	}

	self->len = k;
	free(self->elements);
	self->elements = temp2;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */

void unionInSet(Set* self, const Set* other) {
	if (other->elements == NULL) {
		return;
	}

	int i = 0, j = 0, k = 0;
	int *temp3 = (int *)malloc(sizeof(int) * (self->len + other->len));
	while (i < self->len && j < other->len) {
		if (self->elements[i] < other->elements[j]) {
			temp3[k] = self->elements[i];
			k++;
			i++;
		}
		else if (self->elements[i] > other->elements[j]) {
			temp3[k] = other->elements[j];
			k++;
			j++;
		}
		else {
			temp3[k] = self->elements[i];
			k++;
			i++;
			j++;
		}
	}
	
	while (j < other->len) {
		temp3[k] = other->elements[j];
		k++;
		j++;
	}
	while (i < self->len) {
		temp3[k] = self->elements[i];
		k++;
		i++;
	}

	self->len = k;
	free(self->elements);
	self->elements = temp3;
}
