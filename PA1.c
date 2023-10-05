#include <stdio.h>
#include <string.h>

#define MAX_SIZE 500000

/*
structure for priority queue
*/
typedef struct MinMaxHeap {
    int array[(MAX_SIZE/2)+2];
    int size;
}MinMaxHeap;

typedef struct PriorityQueue {
    MinMaxHeap smaller_heap; // smaller half element (actually almost half)
    MinMaxHeap larger_heap; // larger half heap (actually almost half)
}PriorityQueue;

PriorityQueue priority_queue; // as a global variable

/*
helper functions for heap property
*/
int get_level(int index) {
    if (index == 0)
        return 0;
    else { 
        int level = 0;
        int node_num = index+1;
        while (node_num > 1) {
        node_num /= 2;
        level++;
        }
        return level;
    }
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int get_smallest_index_of_C_and_GC(MinMaxHeap* heap, int index) {
    if (heap->size - 1 < 2 * index + 1)
        return -1;
    
    int min_index = 2 * index + 1;
    int min_value = heap->array[min_index];

    if (2 * index + 2 <= heap->size - 1 && min_value > heap->array[2 * index + 2]) {
        min_index = 2 * index + 2;
        min_value = heap->array[min_index];
    }
    if (4 * index + 3 <= heap->size - 1 && min_value > heap->array[4 * index + 3]) {
        min_index = 4 * index + 3;
        min_value = heap->array[min_index];
    }
    if (4 * index + 4 <= heap->size - 1 && min_value > heap->array[4 * index + 4]) {
        min_index = 4 * index + 4;
        min_value = heap->array[min_index];
    }
    if (4 * index + 5 <= heap->size - 1 && min_value > heap->array[4 * index + 5]) {
        min_index = 4 * index + 5;
        min_value = heap->array[min_index];
    }
    if (4 * index + 6 <= heap->size - 1 && min_value > heap->array[4 * index + 6]) {
        min_index = 4 * index + 6;
    }

    return min_index;
}

int get_largest_index_of_C_and_GC(MinMaxHeap* heap, int index) {
    if (heap->size - 1 < 2 * index + 1)
        return -1;

    int max_index = 2 * index + 1;
    int max_value = heap->array[max_index];

    if (2 * index + 2 <= heap->size - 1 && max_value < heap->array[2 * index + 2]) {
        max_index = 2 * index + 2;
        max_value = heap->array[max_index];
    }

    if (4 * index + 3 <= heap->size - 1 && max_value < heap->array[4 * index + 3]) {
        max_index = 4 * index + 3;
        max_value = heap->array[max_index];
    }

    if (4 * index + 4 <= heap->size - 1 && max_value < heap->array[4 * index + 4]) {
        max_index = 4 * index + 4;
        max_value = heap->array[max_index];
    }

    if (4 * index + 5 <= heap->size - 1 && max_value < heap->array[4 * index + 5]) {
        max_index = 4 * index + 5;
        max_value = heap->array[max_index];
    }

    if (4 * index + 6 <= heap->size - 1 && max_value < heap->array[4 * index + 6]) {
        max_index = 4 * index + 6;
    }

    return max_index;
}

int is_grand_child(MinMaxHeap* heap, int Gparent, int Gchild) {
    if (4 * Gparent + 3 <= Gchild && Gchild <= 4 * Gparent + 6)
        return 1;
    else
        return 0;
}

/*
functions for heap property
these are based on the pseudo code from wikipedia document about min max heap (https://en.wikipedia.org/wiki/Min-max_heap)
*/
void push_down_min(MinMaxHeap* heap, int index) {
    int comparison_index = get_smallest_index_of_C_and_GC(heap, index);
    if (comparison_index != -1) {
        if (is_grand_child(heap, index, comparison_index) && heap->array[index] > heap->array[comparison_index]) {
            swap(&heap->array[index], &heap->array[comparison_index]);
            if (heap->array[comparison_index] > heap->array[(comparison_index - 1) / 2])
                swap(&heap->array[comparison_index], &heap->array[(comparison_index - 1) / 2]);
            push_down_min(heap, comparison_index);
        } 
        else if (heap->array[index] > heap->array[comparison_index]) {
            swap(&heap->array[index], &heap->array[comparison_index]);
        }
    }
}

void push_down_max(MinMaxHeap* heap, int index) {
    int comparison_index = get_largest_index_of_C_and_GC(heap, index);
    if (comparison_index != -1) {
        if (is_grand_child(heap, index, comparison_index) && heap->array[index] < heap->array[comparison_index]) {
            swap(&heap->array[index], &heap->array[comparison_index]);
            if (heap->array[comparison_index] < heap->array[(comparison_index - 1) / 2])
                swap(&heap->array[comparison_index], &heap->array[(comparison_index - 1) / 2]);
            push_down_max(heap, comparison_index);
        } 
        else if (heap->array[index] < heap->array[comparison_index]) {
            swap(&heap->array[index], &heap->array[comparison_index]);
        }
    }
}

void push_down(MinMaxHeap* heap, int index) {
    if (get_level(index)%2 == 0)
        push_down_min(heap, index);
    else
        push_down_max(heap, index);
}

void push_up_min(MinMaxHeap* heap, int index) {
    if (index >= 3 && heap->array[index] < heap->array[(index - 3) / 4]) {
        swap(&heap->array[index], &heap->array[(index - 3) / 4]);
        push_up_min(heap, (index - 3) / 4);
    }
}

void push_up_max(MinMaxHeap* heap, int index) {
    if (index >= 3 && heap->array[index] > heap->array[(index - 3) / 4]) {
        swap(&heap->array[index], &heap->array[(index - 3) / 4]);
        push_up_max(heap, (index - 3) / 4);
    }
}

void push_up(MinMaxHeap* heap, int index) {
    if (index >= 1) {
        if (get_level(index)%2 == 0) {
            if (heap->array[index] > heap->array[(index - 1) / 2]) {
                swap(&heap->array[index], &heap->array[(index - 1) / 2]);
                push_up_max(heap, (index - 1) / 2);
            } 
            else {
                push_up_min(heap, index);
            }
        } 
        else {
            if (heap->array[index] < heap->array[(index - 1) / 2]) {
                swap(&heap->array[index], &heap->array[(index - 1) / 2]);
                push_up_min(heap, (index - 1) / 2);
            } 
            else {
                push_up_max(heap, index);
            }
        }
    }
}

/*
functions for heap operation
in the find, delete functions for heap, do not consider when heap size are zero 
it will be considered in find, delete functions of priority queue
*/
int get_max_index(MinMaxHeap* heap) {
    switch (heap->size) {
        case 1:
            return 0;
        case 2:
            return 1;
        default:
            if (heap->array[1] > heap->array[2])
                return 1;
            return 2;
    }
}

void insert_of_heap(MinMaxHeap* heap, int element) {
    heap->array[heap->size] = element;
    push_up(heap, heap->size);
    heap->size++;
}

int find_min_of_heap(MinMaxHeap* heap) {
    return heap->array[0];
}

int find_max_of_heap(MinMaxHeap* heap) {
    int index = get_max_index(heap);
    return heap->array[index];
}

int delete_min_of_heap(MinMaxHeap* heap) {
    int min = heap->array[0];
    heap->size--;
    heap->array[0] = heap->array[heap->size];
    push_down(heap, 0);
    return min;
}

int delete_max_of_heap(MinMaxHeap* heap) {
    int index = get_max_index(heap);
    int max = heap->array[index];
    heap->size--;
    heap->array[index] = heap->array[heap->size];
    push_down(heap, index);
    return max;
}

/*
functions for priority queue
in here we should consider when the size of heap is zero (when heap is empty)

we will maintain this condition to get median always from larger_heap 's min element
condition : 2 >= (# of larger_heap 's element) - (# of smaller_heap 's element) >= 1 (except the case of priority queue is empty)
*/
void insert(int element) { 
    if (priority_queue.smaller_heap.size == 0 && priority_queue.larger_heap.size == 0) {
        insert_of_heap(&priority_queue.larger_heap, element);
    }
    else if (element > find_min_of_heap(&priority_queue.larger_heap)) {
        insert_of_heap(&priority_queue.larger_heap, element);
        if (priority_queue.larger_heap.size > priority_queue.smaller_heap.size + 2) {
            insert_of_heap(&priority_queue.smaller_heap, delete_min_of_heap(&priority_queue.larger_heap));
        }
    }
    else if (element < find_min_of_heap(&priority_queue.larger_heap)) {
        insert_of_heap(&priority_queue.smaller_heap, element);
        if (priority_queue.smaller_heap.size == priority_queue.larger_heap.size)
            insert_of_heap(&priority_queue.larger_heap, delete_max_of_heap(&priority_queue.smaller_heap));
    }
}

int delete_min() { 
    int result;
    if (priority_queue.smaller_heap.size == 0 && priority_queue.larger_heap.size == 0)
        return 0;
    else if (priority_queue.smaller_heap.size == 0 && (priority_queue.larger_heap.size == 1 || priority_queue.larger_heap.size == 2))
        result = delete_min_of_heap(&priority_queue.larger_heap);
    else {
        result = delete_min_of_heap(&priority_queue.smaller_heap);
        if (priority_queue.larger_heap.size > priority_queue.smaller_heap.size + 2)
            insert_of_heap(&priority_queue.smaller_heap, delete_min_of_heap(&priority_queue.larger_heap));
    }
    printf("%d\n", result);
    return 0;
}

int delete_max() { 
    int result;
    if (priority_queue.smaller_heap.size == 0 && priority_queue.larger_heap.size == 0)
        return 0;
    result = delete_max_of_heap(&priority_queue.larger_heap);
    if (priority_queue.smaller_heap.size == priority_queue.larger_heap.size && priority_queue.smaller_heap.size != 0) 
        insert_of_heap(&priority_queue.larger_heap, delete_max_of_heap(&priority_queue.smaller_heap));
    printf("%d\n", result);
    return 0;
}

int delete_median() { 
    int result;
    if (priority_queue.smaller_heap.size == 0 && priority_queue.larger_heap.size == 0)
        return 0;
    else {
        result = delete_min_of_heap(&priority_queue.larger_heap);
        if (priority_queue.smaller_heap.size == priority_queue.larger_heap.size && priority_queue.smaller_heap.size != 0) 
            insert_of_heap(&priority_queue.larger_heap, delete_max_of_heap(&priority_queue.smaller_heap));
    }
    printf("%d\n", result);
    return 0;
}

int find_min() {  
    if (priority_queue.smaller_heap.size == 0 && priority_queue.larger_heap.size == 0)
        printf("NULL\n");
    else if (priority_queue.smaller_heap.size == 0 && (priority_queue.larger_heap.size == 1 || priority_queue.larger_heap.size == 2))
        printf("%d\n", find_min_of_heap(&priority_queue.larger_heap));
    else
        printf("%d\n", find_min_of_heap(&priority_queue.smaller_heap));
    return 0;
}

int find_max() {  
    if (priority_queue.smaller_heap.size == 0 && priority_queue.larger_heap.size == 0)
        printf("NULL\n");
    else
        printf("%d\n", find_max_of_heap(&priority_queue.larger_heap));
    return 0;
}

int find_median() { 
    if (priority_queue.smaller_heap.size == 0 && priority_queue.larger_heap.size == 0)
        printf("NULL\n");
    else
        printf("%d\n", find_min_of_heap(&priority_queue.larger_heap));
    return 0;
}

/*
main function
*/
int main() {

    // initialize priority queue's heap
    priority_queue.smaller_heap.size = 0;
    priority_queue.larger_heap.size = 0;

    // variable store input from user
    int operation_num; 
    char operation_type;
    int element;
    char value_type;

    scanf("%d", &operation_num);
    while (operation_num--) {
        scanf(" %c", &operation_type);
        if (operation_type == 'I') {
            scanf("%d", &element);
            insert(element);
        }
        else if (operation_type == 'D') {
                scanf(" %c", &value_type);
                if (value_type == 'M') 
                    delete_min(); 
                else if (value_type == 'X') 
                    delete_max(); 
                else if (value_type == 'E')
                    delete_median(); 
        }
        else if (operation_type == 'F') {
                scanf(" %c", &value_type);
                if (value_type == 'M') 
                    find_min();
                else if (value_type == 'X') 
                    find_max(); 
                else if (value_type == 'E')
                    find_median();
        }
    }
    return 0;
}
    