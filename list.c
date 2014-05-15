#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

_list_header *list_create(){
    _list_header *list=(_list_header*)malloc(sizeof(_list_header));
    if(list!=NULL){
        list->size=0;
        list->first=NULL;
        return list;
    }else{
        return NULL;
    }
}

int list_add_begining(_list_header *list, _list_data *data){
    _list_member *new=(_list_member*)malloc(sizeof(_list_member));
    _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
    if(new!=NULL && datanew!=NULL){
        memcpy(datanew,data,sizeof(_list_data));
        new->data=datanew;
        new->next=list->first;
        new->prev=NULL;
        if(new->next!=NULL)
            new->next->prev=new;
        list->first=new;
        list->size++;
        return list->size;
    }
    return 0;
}

int list_add_end(_list_header *list, _list_data *data){
    if(list_empty(list)==1){
        return list_add_begining(list,data);
    }else{
        _list_member *aux=list->first;
        while(aux->next!=NULL)
            aux=aux->next;
        
        _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
        _list_member *new=(_list_member*)malloc(sizeof(_list_member));
        if(new!=NULL){
            new->next=NULL;
            new->data=datanew;
            memcpy(new->data,data,sizeof(_list_data));
            aux->next=new;
            new->prev=aux;
            list->size++;
            return list->size;
        }
    }
}

int list_add_sorted(_list_header *list,_list_data *data){
    if(list_empty(list)==1 || data->n<=list->first->data->n){
        return list_add_begining(list,data);
    }else{
        int i;
        _list_member *aux=list->first;
        while(aux->next!=NULL && aux->next->data->n<data->n){
            aux=aux->next;
        }

        _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
        _list_member *new=(_list_member*)malloc(sizeof(_list_member));
        if(new!=NULL){
            new->next=aux->next;
            new->data=datanew;
            memcpy(datanew,data,sizeof(_list_data));
            aux->next=new;
            new->prev=aux;
            list->size++;
            return list->size;
        }
    }
}

_list_data *list_del_begining(_list_header *list){
    if(list_empty(list)==1){
        return NULL;
    }else{
        _list_member *t=list->first;
        _list_data *data=t->data;
        list->first=t->next;
        if(t->next!=NULL)
            t->next->prev=NULL;
        list->size--;
        free(t);
        return data;
    }
}

_list_data *list_del_end(_list_header *list){
   if(list_empty(list)==1){
        return 0;
   }else{
        _list_member *aux=list->first;
        while(aux->next->next!=NULL)
            aux=aux->next;
        _list_member *t=aux->next;
        _list_data *data=aux->data;
        aux->next=NULL;
        list->size--;
        free(t);
        return data;
   }
}

_list_data *list_del(_list_header *list,int pos){
   if(list_empty(list)==1 || pos>list_size(list)){
        return 0;
   }else if(pos==0){
        list_del_begining(list);
   }else if(pos==list_size(list)){
        list_del_end(list);
   }else{
        int i;
        _list_member *aux=list->first;
        for(i=0;i<pos-1;i++)
            aux=aux->next;
       
        _list_member *t=aux->next;
        _list_data *data=aux->data;
        aux->next=aux->next->next;
        list->size--;
        free(t);
        return data;
   }
}

int list_empty(_list_header *list){
    if(list->size==0)
        return 1;
    else
        return 0;
}

int list_size(_list_header* list){
    return list->size;
}

void list_print(_list_header *list){
    _list_member *aux=list->first;
    int i=0;
    printf("%d ",aux->data->n);
    while(aux->next!=NULL){
        //printf("%d @ %p\n",aux->data->n,aux->data);
        i++;
        aux=aux->next;
        printf("%d ",aux->data->n);
    }
}
