#include <stdio.h>
#include <string.h>


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
    char operation_target[20]; // int_max is up to 2,147,483,647
    
    char value_type;
    int element;

    scanf("%d", &operation_num);

    while (operation_num--)
    {
        // Get input from user and execute operations.
        scanf(" %c %s", &operation_type, operation_target);
        
        if (operation_type == 'I') 
        {
            sscanf(operation_target, " %d", &element);
            //insert(element);
            printf("%c %d\n",operation_type, element);
        }

        else 
        {
            sscanf(operation_target, " %c", &value_type);

            if (operation_type == 'D')
            {
                if (value_type == 'M') 
                { 
                    //delete_min; 
                    printf("%c %c\n",operation_type, value_type);
                }
                else if (value_type == 'X') 
                { 
                    //delete_max; 
                    printf("%c %c\n",operation_type, value_type);
                }
                else if (value_type == 'E')
                {
                    //delete_median; 
                    printf("%c %c\n",operation_type, value_type);
                }
            }

            else if (operation_type == 'F')
            {
                if (value_type == 'M') 
                { 
                    //find_min; 
                    printf("%c %c\n",operation_type, value_type);
                }
                else if (value_type == 'X') 
                { 
                    //find_max; 
                    printf("%c %c\n",operation_type, value_type);
                }
                else if (value_type == 'E')
                { 
                    //find_median; 
                    printf("%c %c\n",operation_type, value_type);
                }
            }
        }
    }
    return 0;
}