#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include "list.h"
/******************check the input string if valid***************************/
long checkInputs(int argc, char*argv[])
{
	int base;
    char *endptr;
	char *str;
    long val;

	str = argv[1];
    base = (argc > 2) ? atoi(argv[2]) : 10;
	errno = 0;    /* To distinguish success/failure after call */
    val = strtol(str, &endptr, base);

   /* Check for various possible errors */

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }
	if (endptr == str) {
        fprintf(stderr, "invalid argument\n");
        exit(EXIT_FAILURE);
    }
	if (*endptr != '\0')  {      /* no valid argument found */
        fprintf(stderr, "invalid argument\n");
        exit(EXIT_FAILURE);
	}else{
	     /* If we got here, strtol() successfully parsed a number */
		return val;   
	}
	exit(EXIT_SUCCESS);
	
}


//main program
int main(int argc, char *argv[]) {

	uint32_t hamming[3];
	uint32_t hammingcurr;

	static uint8_t cnt=0;
	Node* selectedNode;
	Node* currNode;
	bool found=false;
	uint32_t givenValue = 0;

	
	//check inputs
	//invalid number of args
	if ((argc!=2)){
		printf("invalid number of arguments\n");
		return 0;
		
	}else{
		
		if (checkInputs(argc,argv) > 0){
			givenValue = checkInputs(argc,argv);
			//handle invalid inputs
			if (givenValue == 0){
				printf("bad argument\n");
				return 0;
			}		
		}else{
			printf("bad argument\n");
			return 0;
			
		}	
		
	}

	//create list
	List *l = create_List();
	//create number 1 as first node
	append(l,1);
	selectedNode= l->first;
	currNode = selectedNode;
	
	//initialize hamming factors
	hamming[0] = currNode->value *2;
	hamming[1] = currNode->value *3;
	hamming[2] = currNode->value *5;
	//hamming main loop
  while ((hamming[0] <= givenValue) || (hamming[1] <=givenValue) || (hamming[2] <=givenValue))
  {
	 
	while (cnt < 3) {
		
		hammingcurr = hamming[cnt];

		
		while (currNode->next != NULL){
			
			currNode = currNode->next;
			found = false;
				
			if (hammingcurr < currNode->value){			
			//create list node and insert before currNode
			
				if (hammingcurr <= givenValue){
					Node* new_Node = create_Node(hammingcurr);
					
					if (new_Node == NULL){
						printf("memory exhausted\n");
					}else{
						new_Node->next = currNode;
						new_Node->prev = currNode->prev;
						currNode->prev->next = new_Node;
						currNode->prev = new_Node;
						l->n++;
					}		
				}				
				cnt++;			
				found = true;
				break;
			}else if (hammingcurr == currNode->value){
				//node is already in list, so do nothing
				cnt++;
			
				break;
				found = true;
			}
		}
		if ((currNode->next == NULL) && (found == false)){
			cnt++;
		//only append if hammingcurr is smaller given and if its not duplicate already
			if ((hammingcurr <= givenValue) && (hammingcurr != l->last->value)){
				append(l,hammingcurr);
			}
				
		}
		//reset found flag
		if (found == true){
			found = false;
		}
		  
	} 
	
	//select next node in already existing list
	if (selectedNode->next != NULL){
		selectedNode = selectedNode->next;
		currNode = selectedNode;
	
		hamming[0] = currNode->value *2;
		hamming[1] = currNode->value *3;
		hamming[2] = currNode->value *5;
		
		cnt = 0;
	}else{
		
		break;
	}


  }
  //print output
  printf("Hamming sequence smaller or equal to %d is: \n",givenValue);
	printList(l);
//destroy list
	destroyList(l);
	
	return 0;

}

