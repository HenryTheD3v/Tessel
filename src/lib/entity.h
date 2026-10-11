#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
    Vector3 position;
    Vector3 velocity;
    Vector2 rotation;

    float width;
    float height;
    float gravity;
    float friction;

    bool grounded;
    bool ismoving;
} Entity;


extern Entity entity;
void InitEntities(void);
void DrawEntities(void);
void UpdateEntities(void);
void UnloadEntities(void);

#endif