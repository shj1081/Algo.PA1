#include <stdio.h>
#include <string.h>

#define MAX_SIZE 500000

struct MinMaxHeap {
    int array[(MAX_SIZE/2)+2];
    int size;
};

struct PriorityQueue {
    struct MinMaxHeap lh; // Left half heap
    struct MinMaxHeap rh; // Right half heap
};

struct PriorityQueue priority_queue; // struct priority queue in global var

/*
function for min-max heap
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

int get_smallest_index_of_C_and_GC(struct MinMaxHeap* heap, int index) {
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

int get_largest_index_of_C_and_GC(struct MinMaxHeap* heap, int index) {
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

int is_child(struct MinMaxHeap* heap, int parent, int child) {
    if (2 * parent + 1 <= child && child <= 2 * parent + 2)
        return 1;
    else
        return 0;
}

int is_grand_child(struct MinMaxHeap* heap, int Gparent, int Gchild) {
    if (4 * Gparent + 3 <= Gchild && Gchild <= 4 * Gparent + 6)
        return 1;
    else
        return 0;
}

void trickle_min_down(struct MinMaxHeap* heap, int index) {
    int comparison_target_index = get_smallest_index_of_C_and_GC(heap, index);
    if (comparison_target_index != -1) {
        if (is_grand_child(heap, index, comparison_target_index) && heap->array[index] > heap->array[comparison_target_index]) {
            swap(&heap->array[index], &heap->array[comparison_target_index]);
            if (heap->array[comparison_target_index] > heap->array[(comparison_target_index - 1) / 2])
                swap(&heap->array[comparison_target_index], &heap->array[(comparison_target_index - 1) / 2]);
            trickle_min_down(heap, comparison_target_index);
        } 
        else if (is_child(heap, index, comparison_target_index) && heap->array[index] > heap->array[comparison_target_index]) {
            swap(&heap->array[index], &heap->array[comparison_target_index]);
        }
    }
}

void trickle_max_down(struct MinMaxHeap* heap, int index) {
    int comparison_target_index = get_largest_index_of_C_and_GC(heap, index);
    if (comparison_target_index != -1) {
        if (is_grand_child(heap, index, comparison_target_index) && heap->array[index] < heap->array[comparison_target_index]) {
            swap(&heap->array[index], &heap->array[comparison_target_index]);
            if (heap->array[comparison_target_index] < heap->array[(comparison_target_index - 1) / 2])
                swap(&heap->array[comparison_target_index], &heap->array[(comparison_target_index - 1) / 2]);
            trickle_max_down(heap, comparison_target_index);
        } 
        else if (is_child(heap, index, comparison_target_index) && heap->array[index] < heap->array[comparison_target_index]) {
            swap(&heap->array[index], &heap->array[comparison_target_index]);
        }
    }
}


void trickle_down(struct MinMaxHeap* heap, int index) {
    if (get_level(index)%2 == 0)
        trickle_min_down(heap, index);
    else
        trickle_max_down(heap, index);
}

void bubble_min_up(struct MinMaxHeap* heap, int index) {
    if (index < 3)
        return;
    if (heap->array[index] < heap->array[(index - 3) / 4]) {
        swap(&heap->array[index], &heap->array[(index - 3) / 4]);
        bubble_min_up(heap, (index - 3) / 4);
    }
}

void bubble_max_up(struct MinMaxHeap* heap, int index) {
    if (index < 3)
        return;
    if (heap->array[index] > heap->array[(index - 3) / 4]) {
        swap(&heap->array[index], &heap->array[(index - 3) / 4]);
        bubble_max_up(heap, (index - 3) / 4);
    }
}

void bubble_up(struct MinMaxHeap* heap, int index) {
    if (index < 1)
        return;

    if (get_level(index)%2 == 0) {
        if (heap->array[index] > heap->array[(index - 1) / 2]) {
            swap(&heap->array[index], &heap->array[(index - 1) / 2]);
            bubble_max_up(heap, (index - 1) / 2);
        } else {
            bubble_min_up(heap, index);
        }
    } else {
        if (heap->array[index] < heap->array[(index - 1) / 2]) {
            swap(&heap->array[index], &heap->array[(index - 1) / 2]);
            bubble_min_up(heap, (index - 1) / 2);
        } else {
            bubble_max_up(heap, index);
        }
    }
}

int get_max_index(struct MinMaxHeap* heap) {
    switch (heap->size) {
        case 0:
            return -1;
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

void insert_of_heap(struct MinMaxHeap* heap, int element) {
    heap->array[heap->size] = element;
    bubble_up(heap, heap->size);
    heap->size++;
}

int find_min_of_heap(struct MinMaxHeap* heap) {
    if (heap->size == 0)
        return -1;
    return heap->array[0];
}

int find_max_of_heap(struct MinMaxHeap* heap) {
    int index = get_max_index(heap);
    if (index == -1)
        return -1;
    return heap->array[index];
}

int delete_min_of_heap(struct MinMaxHeap* heap) {
    int min = heap->array[0];
    heap->size--;
    heap->array[0] = heap->array[heap->size];
    trickle_down(heap, 0);
    return min;
}

int delete_max_of_heap(struct MinMaxHeap* heap) {
    int index = get_max_index(heap);
    if (index == -1)
        return -1;
    int max = heap->array[index];
    heap->size--;
    heap->array[index] = heap->array[heap->size];
    trickle_down(heap, index);
    return max;
}

void insert(int element); // Inserts an integer element into the priority queue. 

int delete_min(); // Deletes and returns the minimum element.
int delete_max(); // Deletes and returns the maximum element.
int delete_median(); // Deletes and returns the median element.

int find_min(); // Fetches but does not remove the minimum element. 
int find_max(); // Fetches but does not remove the maximum element. 
int find_median(); // Fetches but does not remove the median element.



int main() {

    int operation_num; 
    char operation_type;
    int element;
    char value_type;

    scanf("%d", &operation_num);

    while (operation_num--)
    {
        scanf(" %c", &operation_type);
        
        if (operation_type == 'I') 
        {
            scanf("%d", &element);
            insert(element);
        }

        else if (operation_type == 'D')
            {
                scanf(" %c", &value_type);

                if (value_type == 'M') 
                { 
                    //delete_min; 
                }
                else if (value_type == 'X') 
                { 
                    //delete_max; 
                }
                else if (value_type == 'E')
                {
                    //delete_median; 
                }
            }

            else if (operation_type == 'F')
            {
                scanf(" %c", &value_type);

                if (value_type == 'M') 
                { 
                    //find_min;
                }
                else if (value_type == 'X') 
                { 
                    //find_max; 
                }
                else if (value_type == 'E')
                { 
                    //find_median; 
                }
            }
        }
        
        return 0;
    }
    