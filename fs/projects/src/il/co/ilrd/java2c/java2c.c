#include <stdlib.h> /* malloc */
#include <stdio.h>  /* printf */
#include <string.h>
#include <limits.h> /* INT_MIN */

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
    const char *name;
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

/* Function Declarations */
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

void Animal_showCounter();
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
/* End Function Declarations */

#define TO_STRING_SIZE 100

/* Global definitions *********************************************************/
Object *Alloc(const metadata_t *metadata)
{
    Object *new_obj = malloc(metadata->size);
    if (NULL == new_obj)
    {
        return NULL;
    }

    new_obj->metadata = metadata;

    return new_obj;
}

vfunc_t GetVirtualMethod(Object *this, int position)
{
    return (*(this->metadata->vtable))[position];
}

static vfunc_t GetSuperMethod(Object *this, enum vtable_position position)
{
    const vfunc_t *super_vtable = *(this->metadata->superclass->vtable);

    return super_vtable[position];
}
/* End Global Definitions *****************************************************/

/* Class Object ***************************************************************/
void Object_ctor(Object *this)
{
    (void)this;
}

virtual Object *Object_clone(const Object *this)
{
    Object *ret = Alloc(this->metadata);
    if (NULL == ret)
    {
        return NULL;
    }

    puts("Object_clone");

    Object_ctor(ret);

    return ret;
}

virtual Boolean Object_equals(const Object *this, const Object *other)
{
    puts("Object clone");

    return this == other;
}

virtual void Object_finalize(Object *this)
{
    free(this);
    this = NULL;
}

virtual const metadata_t *Object_getClass(Object *this)
{
    puts("Object_getClass");

    return this->metadata;
}

virtual int Object_hashCode(const Object *this)
{
    return (int)(size_t)(this);
}

virtual void Object_notify(Object *this)
{
    (void)this;
    puts("Object_notify");
}

virtual void Object_notifyAll(Object *this)
{
    (void)this;
    puts("Object_notifyAll");
}

virtual String Object_toString(Object *this)
{
    vfunc_t func = GetVirtualMethod(this, HASH_CODE);
    int hashcode = ((int (*)(Object *))func)(this);
    String ret = malloc(TO_STRING_SIZE * sizeof(char));
    if (NULL == ret)
    {
        return NULL;
    }

    sprintf(ret, "il.co.ilrd.java2c.Object@%x", hashcode);

    return ret;
}

virtual void Object_wait1(Object *this)
{
    (void)this;
    puts("Object_wait1");
}

virtual void Object_wait2(Object *this, long timeout)
{
    (void)this;
    (void)timeout;
    puts("Object_wait2");
}

virtual void Object_wait3(Object *this, long timeout, int nanos)
{
    (void)this;
    (void)timeout;
    (void)nanos;
    puts("Object_wait3");
}

const vfunc_t Object_vtable[] = {
    CAST_TO_VFUNC_T(Object_clone),
    CAST_TO_VFUNC_T(Object_equals),
    CAST_TO_VFUNC_T(Object_getClass),
    CAST_TO_VFUNC_T(Object_finalize),
    CAST_TO_VFUNC_T(Object_hashCode),
    CAST_TO_VFUNC_T(Object_notify),
    CAST_TO_VFUNC_T(Object_notifyAll),
    CAST_TO_VFUNC_T(Object_toString),
    CAST_TO_VFUNC_T(Object_wait1),
    CAST_TO_VFUNC_T(Object_wait2),
    CAST_TO_VFUNC_T(Object_wait3)};

const metadata_t Object_metadata = {
    "Object",
    sizeof(Object),
    NULL,
    &Object_vtable};
/* End class Object ***********************************************************/

/* Class Animal extends Objects ***********************************************/
int Animal_counter;

static void Animal_StaticBlock()
{
    static Boolean has_run_animal_static_block = FALSE;
    if (!has_run_animal_static_block)
    {
        puts("Static block Animal 1 ");
        puts("Static block Animal 2");
        Animal_counter = 0;
    }
    has_run_animal_static_block = TRUE;
}

static void Animal_NonStaticBlock(Animal *this)
{
    puts("Instance initialization block Animal");
    this->num_legs = 5;
    this->num_masters = 1;
    this->id = 0;
}

void Animal_showCounter()
{
    Animal_StaticBlock();
    printf("%d\n", Animal_counter);
}

void Animal_ctor1(Animal *this)
{
    vfunc_t vfunc = NULL;
    String str = NULL;

    Animal_StaticBlock();
    Object_ctor((Object *)this);
    Animal_NonStaticBlock(this);

    puts("Animal Ctor");
    this->id = ++Animal_counter;

    vfunc = GetVirtualMethod((Object *)this, SAY_HELLO);
    ((void (*)(Animal *))vfunc)(this);

    Animal_showCounter();

    vfunc = GetVirtualMethod((Object *)this, TO_STRING);
    str = ((String(*)(Object *))vfunc)((Object *)this);
    puts(str);

    vfunc = GetSuperMethod((Object *)this, TO_STRING);
    str = ((String(*)(Object *))vfunc)((Object *)this);
    puts(str);
}

void Animal_ctor2(Animal *this, int num_masters)
{
    Animal_StaticBlock();
    Object_ctor((Object *)this);
    Animal_NonStaticBlock(this);

    puts("Animal Ctor int");

    this->id = ++Animal_counter;
    this->num_masters = num_masters;
}

virtual void Animal_finalize(Object *this)
{
    vfunc_t super_finalize = NULL;

    printf("finalize Animal with ID: %d\n", ((Animal *)this)->id);
    super_finalize = GetSuperMethod(this, FINALIZE);

    ((void (*)(Object *))super_finalize)(this);
}

virtual String Animal_toString(Object *this)
{
    String ret = malloc(TO_STRING_SIZE * sizeof(char));
    if (NULL == ret)
    {
        return NULL;
    }

    sprintf(ret, "Animal with ID: %d",
            ((Animal *)this)->id);

    return ret;
}

virtual int Animal_getNumMasters(Animal *this)
{
    return this->num_masters;
}

virtual void Animal_sayHello(Animal *this)
{
    puts("Animal_sayHello");
    printf("i have %d legs\n", this->num_legs);
}

const vfunc_t Animal_vtable[] = {
    /* methods from class Object */
    CAST_TO_VFUNC_T(Object_clone),
    CAST_TO_VFUNC_T(Object_equals),
    CAST_TO_VFUNC_T(Object_getClass),
    CAST_TO_VFUNC_T(Animal_finalize),
    CAST_TO_VFUNC_T(Object_hashCode),
    CAST_TO_VFUNC_T(Object_notify),
    CAST_TO_VFUNC_T(Object_notifyAll),
    CAST_TO_VFUNC_T(Animal_toString),
    CAST_TO_VFUNC_T(Object_wait1),
    CAST_TO_VFUNC_T(Object_wait2),
    CAST_TO_VFUNC_T(Object_wait3),

    /* methods from class Animal */
    CAST_TO_VFUNC_T(Animal_getNumMasters),
    CAST_TO_VFUNC_T(Animal_sayHello)};

const metadata_t Animal_metadata = {
    "Animal",
    sizeof(Animal),
    &Object_metadata,
    &Animal_vtable};
/* End Class Animal ***********************************************************/

/* Class Dog extends Animal ***************************************************/

static void Dog_StaticBlock()
{
    static Boolean has_run_dog_static_block = FALSE;

    if (!has_run_dog_static_block)
    {
        puts("Static block Dog");
    }
    has_run_dog_static_block = TRUE;
}

static void Dog_NonStaticBlock(Dog *this)
{
    puts("Instance initialization block Dog");
    this->num_legs = 4;
}

void Dog_ctor(Dog *this)
{
    Animal_StaticBlock();
    Dog_StaticBlock();
    Object_ctor((Object *)this);
    Animal_ctor2((Animal *)this, 2);
    Dog_NonStaticBlock(this);

    puts("Dog Ctor");
}

virtual void Dog_finalize(Object *this)
{
    vfunc_t super_finalize = NULL;

    printf("finalize Dog with ID: %d", ((Animal *)this)->id);

    super_finalize = GetSuperMethod(this, FINALIZE);
    ((void (*)(Object *))super_finalize)(this);
}

virtual String Dog_toString(Object *this)
{
    String ret = malloc(TO_STRING_SIZE * sizeof(char));
    if (NULL == ret)
    {
        return NULL;
    }

    sprintf(ret, "Dog with ID: %d", ((Animal *)this)->id);

    return ret;
}

virtual void Dog_sayHello(Animal *this)
{
    puts("Dog Hello");
    printf("I have %d legs", ((Dog *)this)->num_legs);
}

const vfunc_t Dog_vtable[] = {
    /* methods from class Object */
    CAST_TO_VFUNC_T(Object_clone),
    CAST_TO_VFUNC_T(Object_equals),
    CAST_TO_VFUNC_T(Object_getClass),
    CAST_TO_VFUNC_T(Dog_finalize),
    CAST_TO_VFUNC_T(Object_hashCode),
    CAST_TO_VFUNC_T(Object_notify),
    CAST_TO_VFUNC_T(Object_notifyAll),
    CAST_TO_VFUNC_T(Dog_toString),
    CAST_TO_VFUNC_T(Object_wait1),
    CAST_TO_VFUNC_T(Object_wait2),
    CAST_TO_VFUNC_T(Object_wait3),

    /* methods from class Animal */
    CAST_TO_VFUNC_T(Animal_getNumMasters),
    CAST_TO_VFUNC_T(Dog_sayHello)};

const metadata_t Dog_metadata = {
    "Dog",
    sizeof(Dog),
    &Animal_metadata,
    &Dog_vtable};
/* End Class Dog **************************************************************/

/* Class Cat extends Animal ***************************************************/

static void Cat_StaticBlock()
{
    static Boolean has_run_cat_static_block = FALSE;

    if (!has_run_cat_static_block)
    {
        puts("Static block Cat");
    }
    has_run_cat_static_block = TRUE;
}

static void Cat_NonStaticBlock(Cat *this)
{
    this->colors = NULL;
    this->num_masters = 5;
}

void Cat_ctor1(Cat *this)
{
    Animal_StaticBlock();
    Cat_StaticBlock();
    Cat_ctor2(this, "black");

    puts("Cat Ctor");
    this->num_masters = 2;
}

void Cat_ctor2(Cat *this, String colors)
{
    Animal_StaticBlock();
    Cat_StaticBlock();
    Object_ctor((Object *)this);
    Animal_ctor1((Animal *)this);
    Cat_NonStaticBlock(this);

    this->colors = colors;
    printf("Car ctor with color: %s\n", this->colors);
}

virtual void Cat_finalize(Object *this)
{
    vfunc_t super_finalize = NULL;

    printf("finalize Cat with ID: %d", ((Animal *)this)->id);

    super_finalize = GetSuperMethod(this, FINALIZE);
    ((void (*)(Object *))super_finalize)(this);
}

virtual String Cat_toString(Object *this)
{
    String ret = malloc(TO_STRING_SIZE * sizeof(char));
    if (NULL == ret)
    {
        return NULL;
    }

    sprintf(ret, "Cat with ID: %d", ((Animal *)this)->id);

    return ret;
}

const vfunc_t Cat_vtable[] = {
    /* methods from class Object */
    CAST_TO_VFUNC_T(Object_clone),
    CAST_TO_VFUNC_T(Object_equals),
    CAST_TO_VFUNC_T(Object_getClass),
    CAST_TO_VFUNC_T(Cat_finalize),
    CAST_TO_VFUNC_T(Object_hashCode),
    CAST_TO_VFUNC_T(Object_notify),
    CAST_TO_VFUNC_T(Object_notifyAll),
    CAST_TO_VFUNC_T(Cat_toString),
    CAST_TO_VFUNC_T(Object_wait1),
    CAST_TO_VFUNC_T(Object_wait2),
    CAST_TO_VFUNC_T(Object_wait3),

    /* methods from class Animal */
    CAST_TO_VFUNC_T(Animal_getNumMasters),
    CAST_TO_VFUNC_T(Animal_sayHello)};

const metadata_t Cat_metadata = {
    "Cat",
    sizeof(Cat),
    &Animal_metadata,
    &Cat_vtable};
/* End class Cat **************************************************************/

/* Class LegendaryAnimal extends Cat ******************************************/

static void LegendaryAnimal_StaticBlock()
{
    static Boolean has_run_legendary_animal_static_block = FALSE;

    if (!has_run_legendary_animal_static_block)
    {
        puts("Static block Legendary Animal");
    }

    has_run_legendary_animal_static_block = TRUE;
}

static void LegendaryAnimal_NonStaticBlock(LegendaryAnimal *this)
{
    (void)this;
}

void LegendaryAnimal_ctor(LegendaryAnimal *this)
{
    Animal_StaticBlock();
    Cat_StaticBlock();
    LegendaryAnimal_StaticBlock();
    Cat_ctor1((Cat *)this);
    LegendaryAnimal_NonStaticBlock(this);

    puts("Legendary Ctor");
}

virtual void LegendaryAnimal_finalize(Object *this)
{
    vfunc_t super_finalize = NULL;

    printf("finalize Legendary Legend with ID: %d\n", ((Animal *)this)->id);

    super_finalize = GetSuperMethod(this, FINALIZE);
    ((void (*)(Object *))super_finalize)(this);
}

virtual String LegendaryAnimal_toString(Object *this)
{
    String ret = malloc(TO_STRING_SIZE * sizeof(char));
    if (NULL == ret)
    {
        return NULL;
    }

    sprintf(ret, "Legendary Animal with ID: %d", ((Animal *)this)->id);

    return ret;
}

virtual void LegendaryAnimal_sayHello(Animal *this)
{
    puts("Legendary Hello");
    (void)this;
}

const vfunc_t LegendaryAnimal_vtable[] = {
    /* methods from class Object */
    CAST_TO_VFUNC_T(Object_clone),
    CAST_TO_VFUNC_T(Object_equals),
    CAST_TO_VFUNC_T(Object_getClass),
    CAST_TO_VFUNC_T(LegendaryAnimal_finalize),
    CAST_TO_VFUNC_T(Object_hashCode),
    CAST_TO_VFUNC_T(Object_notify),
    CAST_TO_VFUNC_T(Object_notifyAll),
    CAST_TO_VFUNC_T(LegendaryAnimal_toString),
    CAST_TO_VFUNC_T(Object_wait1),
    CAST_TO_VFUNC_T(Object_wait2),
    CAST_TO_VFUNC_T(Object_wait3),

    /* methods from class Animal */
    CAST_TO_VFUNC_T(Animal_getNumMasters),
    CAST_TO_VFUNC_T(LegendaryAnimal_sayHello)};

const metadata_t LegendaryAnimal_metadata = {
    "LegendaryAnimal",
    sizeof(LegendaryAnimal),
    &Cat_metadata,
    &LegendaryAnimal_vtable};
/* End class LegendaryAnimal **************************************************/

/* Class Java2c ***************************************************************/
static void foo(Animal *animal)
{
    vfunc_t toString = GetVirtualMethod((Object *)animal, TO_STRING);
    String str = ((String(*)(Object *))toString)((Object *)animal);

    puts(str);
}

#define N_MEMBERS (5)
int main(int argc, char const *argv[])
{
    int i = 0;
    Object *obj = NULL;
    /*  vfunc_t func = NULL;
    String str = NULL; */
    Animal *animal = NULL;
    Dog *dog = NULL;
    Cat *cat = NULL;
    LegendaryAnimal *la = NULL;
    Animal *array[N_MEMBERS] = {NULL};

    animal = (Animal *)Alloc(&Animal_metadata);
    dog = (Dog *)Alloc(&Dog_metadata);
    cat = (Cat *)Alloc(&Cat_metadata);
    la = (LegendaryAnimal *)Alloc(&LegendaryAnimal_metadata);
    if (NULL == animal || NULL == dog || NULL == cat || NULL == la)
    {
        puts("Not enough memory");

        return 1;
    }

    Animal_ctor1(animal);
    Dog_ctor(dog);
    Cat_ctor1(cat);
    LegendaryAnimal_ctor(la);

    Animal_showCounter();

    printf("%d\n", animal->id);
    printf("%d\n", ((Animal *)dog)->id);
    printf("%d\n", ((Animal *)cat)->id);
    printf("%d\n", ((Animal *)la)->id);

    array[0] = (Animal *)Alloc(&Dog_metadata);
    array[1] = (Animal *)Alloc(&Cat_metadata);
    array[2] = (Animal *)Alloc(&Cat_metadata);
    array[3] = (Animal *)Alloc(&LegendaryAnimal_metadata);
    array[4] = (Animal *)Alloc(&Animal_metadata);

    for (i = 0; N_MEMBERS > i; ++i)
    {
        if (NULL == array[i])
        {
            puts("Not enough memory");

            return 1;
        }
    }

    Dog_ctor((Dog *)array[0]);
    Cat_ctor1((Cat *)array[1]);
    Cat_ctor2((Cat *)array[2], "white");
    LegendaryAnimal_ctor((LegendaryAnimal *)array[3]);
    Animal_ctor1((Animal *)array[4]);

    for (i = 0; N_MEMBERS > i; ++i)
    {
        int num_masters = INT_MIN;
        vfunc_t vfunc = GetVirtualMethod((Object *)array[i], SAY_HELLO);

        ((void (*)(Animal *))vfunc)((Animal *)array[i]);

        vfunc = GetVirtualMethod((Object *)array[i], GET_NUM_MASTERS);
        num_masters = ((int (*)(Animal *))vfunc)((Animal *)array[i]);
        printf("%d\n", num_masters);
    }

    for (i = 0; N_MEMBERS > i; ++i)
    {
        foo((Animal *)array[i]);
    }

    return 0;

    (void)argc;
    (void)argv;
}
#undef N_MEMBERS
/* End class Java2c ***********************************************************/