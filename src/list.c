#include <stdio.h>
#include <stdlib.h>
#include "list.h"

flag_list_t *flag_list_insert(flag_list_t *head, argument_t *value, flag_list_t *pos){
    flag_list_t *new_flag_list = (flag_list_t*)malloc(sizeof(flag_list_t));
    new_flag_list->value = value;
    if(head == NULL){
	    new_flag_list->prev = NULL;
	    new_flag_list->next = NULL;
	    return new_flag_list;
    }
    if(pos == NULL){
	    new_flag_list->next = head;
	    new_flag_list->prev = NULL;
	    head->prev = new_flag_list;
	    return new_flag_list;
    } else if (pos->next == NULL){
	    new_flag_list->next = NULL;
	    new_flag_list->prev = pos;
	    pos->next = new_flag_list;
    } else {
	    new_flag_list->prev = pos;
	    new_flag_list->next = pos->next;
	    pos->next->prev = new_flag_list;
	    pos->next = new_flag_list;
    }
    return head;
}

flag_list_t *flag_list_find(flag_list_t *head, argument_t* value){
    flag_list_t *end = head;
    while(end != NULL){
	    if (end->value == value){
	        return end;
	    }
	    end = end->next;
    }
    return NULL;
    
}

flag_list_t *flag_list_erase(flag_list_t *head, flag_list_t *flag_list){
    if(head != NULL && flag_list != NULL){
    	if(flag_list->next == NULL && flag_list->prev == NULL){
	        head = NULL;
    	} else if (flag_list->prev == NULL){
	        head = head->next;
	        head->prev = NULL;
	    } else if (flag_list->next == NULL){
	        flag_list->prev->next = NULL;
	    } else {
	        flag_list->prev->next = flag_list->next;
	        flag_list->next->prev = flag_list->prev;
	    }
	    free(flag_list);
	    return head;
    }
    return NULL;
}

void flag_list_destroy(flag_list_t *flag_list){
    while(flag_list != NULL){
	    flag_list_t * next = flag_list->next;
	    flag_list->next = NULL;
	    flag_list->prev = NULL;
	    free(flag_list);
	    flag_list = next;
    }
}


/*
int main(){
    flag_list_t *head = insert(NULL, 1, NULL);
    flag_list_t *flag_list = head;
    flag_list_print(head);
    head = insert(head, 12, flag_list);
    flag_list = head->next;
    flag_list_print(head);
    head = insert(head, 54, flag_list);
    flag_list = flag_list->next;
    flag_list_print(head);
    head = insert(head, 49, flag_list);
    flag_list = flag_list->next;
    flag_list_print(head);
    head = insert(head, 1, flag_list);
    flag_list = flag_list->next;
    flag_list_print(head);
    head = insert(head, 7, flag_list);
    printf("%p VALUE!\n", find(head, 100));
    flag_list = flag_list->next;
    head = erase(head, head);
    head = erase(head, head);
    head = erase(head, head);
    flag_list_print(head);
    head = erase(head, flag_list);
    destroy(head);
    head = NULL;
    flag_list_print(head);
    return 0;
}*/
