#include <stdio.h>
#include <stdlib.h>
#include "list.h"

node_t *flag_node_insert(node_t *head, flag_t *value, node_t *pos){
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;
    if(head == NULL){
	    new_node->prev = NULL;
	    new_node->next = NULL;
	    return new_node;
    }
    if(pos == NULL){
	    new_node->next = head;
	    new_node->prev = NULL;
	    head->prev = new_node;
	    return new_node;
    } else if (pos->next == NULL){
	    new_node->next = NULL;
	    new_node->prev = pos;
	    pos->next = new_node;
    } else {
	    new_node->prev = pos;
	    new_node->next = pos->next;
	    pos->next->prev = new_node;
	    pos->next = new_node;
    }
    return head;
}

node_t *flag_node_find(node_t *head, flag_t* value){
    node_t *end = head;
    while(end != NULL){
	    if (end->value == value){
	        return end;
	    }
	    end = end->next;
    }
    return NULL;
    
}

node_t *flag_node_erase(node_t *head, node_t *node){
    if(head != NULL && node != NULL){
    	if(node->next == NULL && node->prev == NULL){
	        head = NULL;
    	} else if (node->prev == NULL){
	        head = head->next;
	        head->prev = NULL;
	    } else if (node->next == NULL){
	        node->prev->next = NULL;
	    } else {
	        node->prev->next = node->next;
	        node->next->prev = node->prev;
	    }
	    free(node);
	    return head;
    }
    return NULL;
}

void flag_node_destroy(node_t *node){
    while(node != NULL){
	    node_t * next = node->next;
	    node->next = NULL;
	    node->prev = NULL;
	    free(node);
	    node = next;
    }
}


/*
int main(){
    node_t *head = insert(NULL, 1, NULL);
    node_t *node = head;
    node_print(head);
    head = insert(head, 12, node);
    node = head->next;
    node_print(head);
    head = insert(head, 54, node);
    node = node->next;
    node_print(head);
    head = insert(head, 49, node);
    node = node->next;
    node_print(head);
    head = insert(head, 1, node);
    node = node->next;
    node_print(head);
    head = insert(head, 7, node);
    printf("%p VALUE!\n", find(head, 100));
    node = node->next;
    head = erase(head, head);
    head = erase(head, head);
    head = erase(head, head);
    node_print(head);
    head = erase(head, node);
    destroy(head);
    head = NULL;
    node_print(head);
    return 0;
}*/
