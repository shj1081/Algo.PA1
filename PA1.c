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
    int element;
    char value_type;

    scanf("%d", &operation_num);

    while (operation_num--)
    {
        scanf(" %c", &operation_type);
        
        if (operation_type == 'I') 
        {
            scanf("%d", &element);
            //insert(element);
            printf("%c %d\n",operation_type, element);
        }

        else if (operation_type == 'D')
            {
                scanf(" %c", &value_type);

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
                scanf(" %c", &value_type);

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
        
        return 0;
    }
    