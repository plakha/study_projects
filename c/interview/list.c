#include <stdlib.h> /* size_t */
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct node
{
    int data;
    struct node *next;
} node_t;

size_t ListSize(const node_t *list)
{
    size_t size = 0;

    while (NULL != list)
    {
        ++size;
        list = list->next;
    }

    return size;
}

static void UtilOpenIntersection(node_t *list1, node_t *list2)
{
    assert(ListSize(list1) == ListSize(list2));

    while (NULL != list1 && list1->next != list2->next)
    {
        assert(NULL != list2);

        list1 = list1->next;
        list2 = list2->next;
    }

    if (NULL != list1 && list1 != list2) /* to make sure one is not a sublist of another (same list) */
    {
        list1->next = NULL;
    }
}

void OpenIntersection(node_t *list1, node_t *list2)
{
    size_t size1 = ListSize(list1);
    size_t size2 = ListSize(list2);

    node_t *long_list = NULL;
    node_t *short_list = NULL;

    if (size1 > size2)
    {
        long_list = list1;
        short_list = list2;
    }
    else
    {    
        long_list = list2;
        short_list = list1;
    }

    const size_t delta = MAX(size1, size2) - MIN(size1, size2);
    for (size_t i = 0; delta > i; ++i)
    {
        long_list = long_list->next;
    }

    UtilOpenIntersection(long_list, short_list);
}

static node_t *CreateNode(int data)
{
    node_t *new_node = malloc(sizeof(*new_node));

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void DestroyList(node_t *list)
{
    while (NULL != list)
    {
        node_t *to_destroy = list;
        list = list->next;
        to_destroy->next = NULL;
        free(to_destroy);
        to_destroy = NULL;
    }
}

node_t *CreateList(int arr[], const size_t size)
{
    assert(NULL != arr);

    node_t *new_list = CreateNode(arr[0]);
    if (NULL == new_list)
    {
        return NULL;
    }

    node_t *runner = new_list;
    for (size_t i = 1; size > i; ++i)
    {
        runner->next = CreateNode(arr[i]);
        runner = runner->next;

        if (NULL == runner)
        {
            DestroyList(new_list);
            break;
        }
    }

    return new_list;
}

void PrintList(const node_t *list)
{
    while (NULL != list)
    {
        printf("%d ", list->data);
        list = list->next;
    }

    puts("");
}

node_t *ReverseList(node_t *list)
{
    if (NULL == list->next)
    {
        return list;
    }

    node_t *ret = ReverseList(list->next);
    list->next->next = list;
    list->next = NULL;

    return ret;
}

int main()
{
    size_t arr_size = 8;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    node_t *list = CreateList(arr, arr_size);

    PrintList(list = ReverseList(list));
    DestroyList(list);

    /*
    int arr2[] = {0};
    node_t *intersected_list = CreateList(arr2, 1);
    intersected_list->next = list->next;

    node_t *intersected_list = list->next;

    OpenIntersection(list, intersected_list);

    PrintList(list);
    PrintList(intersected_list);

    DestroyList(list);
    //DestroyList(intersected_list);
*/
    return 0;
}

