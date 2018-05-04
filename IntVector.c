#include <stdio.h>
#include <stdlib.h>
#include "IntVector.h"

IntVector *int_vector_new(size_t initial_capacity) //Создает массив нулевого размера.
{
	IntVector *a = malloc (sizeof(IntVector));
	
	if (a == NULL) {
		printf ("\nStruct (a) was not created\n ");
		return NULL;
	}
	a->capacity = initial_capacity;
	
	a->mas = calloc(a->capacity , sizeof(int));
	
	if (a->mas == NULL) {
		printf ("\nArray was not created\n");
		return NULL;
	}
	a -> size = 0;
	printf ("\nVector was created, capacity = %ld\n", initial_capacity);
	return a;
}

IntVector *int_vector_copy(const IntVector *v)
{
	IntVector *a = malloc(sizeof(IntVector));
	if ( a == NULL ) {
		printf ("\nError\n");
		return NULL;
	}
	a -> capacity = v -> capacity;
	
	a -> mas = malloc ( v -> capacity * sizeof ( int ) );
	
	if ( a -> mas == NULL ) {
	printf ("\nError\n");
	return NULL;
	}
	
	for ( size_t i = 0; i < (v -> size); i++ ) {
	a -> mas [i] = v -> mas [i];
	}
	
	a -> size = v -> size;
	
	return a;	
}

void int_vector_free(IntVector **v)
{
	free ((*v)->mas);
	free (*v);
	*v = NULL;
	printf ("\nVector is free\n");
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    if(index-1 > v->size){
		printf(" index > size\n");
		return 0;
	}
    return v->mas[index-1];
}

void int_vector_set_item(const IntVector *v, size_t index, int item)
{
	if(index - 1 > v->size){
		printf("Index > Vector size\n");
		return;
	}
	v->mas[index-1] = item;
}

size_t int_vector_get_size(const IntVector *v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
	if ( v->size + 1 <= v->capacity ) {
		v->mas[v->size] = item;
		v->size++;
		return 0;
	} else {
		v->mas = realloc ( v->mas, v->capacity * 2 * sizeof ( int ) );
		if ( v == NULL ) {
			printf ("Error\n");
			return -1;
		}
		v->capacity = v->capacity * 2;
		v->mas[v->size] = item;
		v->size ++;
		return 0;
	}
	return -1;
}

void int_vector_pop_back(IntVector *v)
{
    if(v->size == 0){
        printf("Size array 0\n");
        return; 
    }
    v->mas[v->size - 1] = 0;
    v->size--;
}

int int_vector_shrink_to_fit(IntVector *v)
{
	if(v->capacity == v->size){
		printf("capacity = size\n");
        return -1;
	}
	v->capacity = v->size;
	printf("successful\n");
	return 0;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
	if(v->capacity < new_size){
		printf("capacity < new_size\n");
		return -1;
	}
	if(v->size < new_size){
		for(int i = v->size; i < new_size; i++)
			v->mas[i] = 0;
		v->size = new_size;
		printf("successful\n");
		return 0;
	}
	else{
		if(int_vector_shrink_to_fit(v) == 0){
			printf("successful\n");
			return 0;
		}
		else{
			printf("size no change\n");
			return -1;
		}
	}
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
	if(v->capacity < new_capacity){
		v->mas = realloc(v->mas, new_capacity * sizeof ( int ) );
		if ( v == NULL ) {
		printf ("Error of reallocation\n");
		return -1;
		}
		v->capacity = new_capacity;
		return 0;
	}
	else{
	printf ("new_capacity <= capacity\n");
	return -1;
	}
}

void int_vector_print (IntVector *v)
{

	if ( v == NULL) {
		printf ("Error, empty pointer\n");
		return;
	}
	for (int i = 0; i < v->size; i++ ) {
		printf (" %d", v->mas[i] );
	}
	printf ("\n");
	printf("-------------------------------------------------------------\n");
}
