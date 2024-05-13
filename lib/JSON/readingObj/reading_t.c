#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading_t.h"

typedef struct Reading_t *reading;

reading *create_instances_in_json(char *name, double result)
{
  // Allocate memory for the object
  Reading_t *obj = malloc(sizeof(Reading_t));
  if (obj == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  // Initialize the fields of the object
  obj->name = strdup(name); // Duplicate the string to prevent modifying the original
  obj->reading = result;

  return obj;
}