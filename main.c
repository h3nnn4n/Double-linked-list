#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(){
    int i;
    _list_header *list;
    _list_data data;
    list=list_create();
    
    for(i=0;i<100;i++){
        data.n=rand()%41-20;
        list_add_sorted(list,&data);
    }

    list_print(list);
    puts("");
    
    return EXIT_SUCCESS;
}
