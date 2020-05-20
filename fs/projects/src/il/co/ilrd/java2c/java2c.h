#ifndef FS69_JAVA2C_H
#define FS69_JAVA2C_H

#define CAST_TO_VFUNC_T(func) ((void (*)(void *)) & func)
#define virtual /* marker of late-binded method */

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

enum vtable_position
{
    /* class Object */
    CLONE,
    EQUALS,
    GET_CLASS,
    FINALIZE,
    HASH_CODE,
    NOTIFY,
    NOTIFY_ALL,
    TO_STRING,
    WAIT1,
    WAIT2,
    WAIT3,

    /* class Animal extends Object */
    GET_NUM_MASTERS,
    SAY_HELLO
};

typedef char *String;

typedef void (*vfunc_t)(void *);

typedef struct metadata
{
    char *name;
    size_t size;
    const struct metadata *superclass;
    const vfunc_t (*vtable)[];
} metadata_t;

typedef struct object
{
    const metadata_t *metadata;
} Object;

typedef struct animal
{
    Object super;
    int num_legs;
    int num_masters;
    int id;
} Animal;

typedef struct dog
{
    Animal super;
    int num_legs;
} Dog;

typedef struct cat
{
    Animal super;
    String colors;
    int num_masters;
} Cat;

typedef struct legendary_animal
{
    Cat super;
} LegendaryAnimal;

Object *Alloc(const metadata_t *metadata);
vfunc_t GetVirtualMethod(Object *this, int position);

void Object_ctor(Object *this);
virtual Object *Object_clone(const Object *this);
virtual Boolean Object_equals(const Object *this, const Object *other);
virtual void Object_finalize(Object *this);
virtual const metadata_t *Object_getClass(Object *this);
virtual int Object_hashCode(const Object *this);
virtual void Object_notify(Object *this);
virtual void Object_notifyAll(Object *this);
virtual String Object_toString(Object *this);
virtual void Object_wait1(Object *this);
virtual void Object_wait2(Object *this, long timeout);
virtual void Object_wait3(Object *this, long timeout, int nanos);

void showCounter();
void Animal_ctor(Animal *this);
void Animal_ctor2(Animal *this, int num_masters);
virtual void Animal_finalize(Object *this);
virtual String Animal_toString(Object *this);
virtual int Animal_getNumMasters(Animal *this);
virtual void Animal_sayHello(Animal *this);

void Dog_ctor(Dog *this);
virtual void Dog_finalize(Object *this);
virtual String Dog_toString(Object *this);
virtual void Dog_sayHello(Animal *this);

void Cat_ctor1(Cat *this);
void Cat_ctor2(Cat *this, String colors);
virtual void Cat_finalize(Object *this);
virtual String Cat_toString(Object *this);

void LegendaryAnimal_ctor(LegendaryAnimal *this);
virtual void LegendaryAnimal_finalize(Object *this);
virtual String LegendaryAnimal_toString(Object *this);
virtual void LegendaryAnimal_sayHello(Animal *this);

#endif /* FS69_JAVA2C_H */