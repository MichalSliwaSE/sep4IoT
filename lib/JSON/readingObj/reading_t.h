#ifndef READING_H
#define READING_H

typedef struct Reading_t {
    char *name;
    double reading;
} Reading_t;

typedef struct Reading_t *reading;

reading *create_instances_in_json(char *name, double result);

#endif
