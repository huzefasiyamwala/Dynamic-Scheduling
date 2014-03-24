//
//  main.c
//  CMPE220
//
//  Created by Huzefa on 3/13/14.
//  Copyright (c) 2014 Huzefa. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#define MAX_TIME 6
#define INPUT_PATH "/Users/admin/Desktop/220/CMPE220/test.txt"

int counter =0;
struct cases{
    int time;
    float prob;
    int cost;
    struct cases *next;
} ;

struct value{
    float prob;
    int cost;
    struct value *next;
};
struct time_unit{
    int time;
    struct value *values;
    struct time_unit *next;
};
struct processor{
    struct cases *cases;
    struct processor *next;
    
};
struct Node{
    int nodeNum;
    struct processor *process;
    struct time_unit *timeNode;
    struct time_unit *dTableValues;
    struct Node *next;
};
void appendCostProb(struct time_unit **time,struct cases *cas);


struct time_unit * getTimeNode(struct time_unit **time,struct cases *pCase){
    struct time_unit *ret,*prev;
    int flag=0;
    struct value *v;
    struct cases y;
    int prevValue=0;
    struct value *Val;
    if(*time==NULL){
        *time = malloc(sizeof(struct time_unit));
        (*time)->time = pCase->time;
        return *time;
    }else{
        
        ret=*time;
        while(ret!=NULL){
            if(ret->time==pCase->time){
                flag=1;
                return ret;
            }
            prev=ret;
            ret=ret->next;
        }
    
        
        prevValue = prev->time+1;
        while(prevValue<pCase->time){
            v=prev->values;
            while(v!=NULL){
                y.cost = v->cost;
                y.prob = v->prob;
                y.time = prevValue;
                appendCostProb(time,&y);
                v=v->next;
            }
            prevValue++;
        }
//        while(ret!=NULL){
//            if(ret->time==pCase->time){
//                flag=1;
//                cu=ret;
//                //return ret;
//            }else if (ret->time<pCase->time){
//                
//            }
//            prev=ret;
//            ret=ret->next;
//        }
        
//        for(i=prev->time+1;i<pCase->time;i++){
//            v=prev->values;
//            while(v!=NULL){
//                y.cost = v->cost;
//                y.prob = v->prob;
//                y.time = i;
//                appendCostProb(time,&y);
//                v=v->next;
//            }
//        }
//        if(flag==1)
//            return cu;
        ret=*time;
        while(ret->next!=NULL)
            ret=ret->next;
//        
//        v=ret->values;
//        while(v!=NULL){
//            y.cost = v->cost;
//            y.prob = v->prob;
//            y.time = pCase->time;
//            appendCostProb(time,&y);
//            v=v->next;
//        }
        
        
        ret->next = malloc(sizeof(struct time_unit));
        ret->next->time = pCase->time;
        v=ret->values;
        while(v!=NULL){
            if(ret->next->values==NULL){
                ret->next->values=malloc(sizeof(struct value));
                Val = ret->next->values;
            }else{
                Val = ret->next->values;
                while(Val->next!=NULL)
                    Val = Val->next;
                Val->next = malloc(sizeof(struct value));
                Val = Val->next;
            }
            Val->cost=v->cost;
            Val->prob=v->prob;
            v=v->next;
        }
    }
    return ret->next;
}
void appendCostProb(struct time_unit **time,struct cases *cas){
    struct value *Val;
    struct time_unit *ActualTimeStructure = NULL;
    ActualTimeStructure = getTimeNode(time,cas);
    if(ActualTimeStructure->values==NULL){
        ActualTimeStructure->values=malloc(sizeof(struct value));
        Val = ActualTimeStructure->values;
    }else{
        Val = ActualTimeStructure->values;
        while(Val->next!=NULL)
            Val = Val->next;
        Val->next = malloc(sizeof(struct value));
        Val = Val->next;
    }
    Val->cost=cas->cost;
    Val->prob=cas->prob;
   
    ActualTimeStructure=ActualTimeStructure->next;
    while(ActualTimeStructure!=NULL){
        Val = ActualTimeStructure->values;
        while(Val->next!=NULL){
            Val = Val->next;
        }
        Val->next = malloc(sizeof(struct value));
        Val = Val->next;
        Val->next=NULL;
        Val->cost=cas->cost;
        Val->prob=cas->prob;
        ActualTimeStructure=ActualTimeStructure->next;
    };
}
void sortList(struct value **pValues){
    struct value *first;
    struct value temp;
    struct value *last;
    first = *pValues;
    if(first==NULL){
        return;
    }
    last = first->next;
    while(first!=NULL){
        last=first->next;
        while(last!=NULL){
            if(first->prob>last->prob){
                temp.prob=last->prob;
                temp.cost=last->cost;
                last->cost = first->cost;
                last->prob=first->prob;
                first->prob =temp.prob;
                first->cost=temp.cost;
            }
            last=last->next;
        }
        first=first->next;
    }
    
}
void removeValues(struct value **pValues){
    struct value *first;
    struct value *last;
    struct value *prev;
    struct value *prevFirst;
    first = *pValues;
   // int flag=0;
    prevFirst = first;
    while(first!=NULL){
        last=first->next;
        prev=first;
        while(last!=NULL){
            if(first->prob==last->prob){
                if(first->cost<=last->cost){
                   ///Remove last
                    prev->next=last->next;
                    free(last);
                    last=last->next;
                    continue;
                }else{
                    if(first==*pValues){
                        *pValues=first->next;
                        free(first);
                        first=first->next;
                        last=first->next;
                        prev=first;
                        //prevFirst=first;
                        continue;
                    }else{
                        prevFirst->next=first->next;
                        free(first);
                        first=first->next;
                        last=first->next;
                        prev=first;
                        //prevFirst=first;
                        continue;
                    }
                    /// remove first
                }
            }else if(first->cost==last->cost){
                if(first->prob>=last->prob){
                    ///Remove last
                    prev->next=last->next;
                    free(last);
                    last=last->next;
                    continue;
                }else{
                    /// remove first
                    if(first==*pValues){
                        *pValues=first->next;
                        free(first);
                        first=first->next;
                        last=first->next;
                        prev=first;
                        //prevFirst=first;
                        continue;
                    }else{
                        
                        prevFirst->next=first->next;
                        free(first);
                        first=first->next;
                        last=first->next;
                        prev=first;
                        //prevFirst=first;
                        continue;
                    }
                }
            }else if(first->prob>last->prob && first->cost<last->cost){
                //remove last
                prev->next=last->next;
                free(last);
                last=last->next;
                continue;

            }else if(first->prob<last->prob && first->cost>last->cost){
                //remove first
                if(first==*pValues){
                    *pValues=first->next;
                    free(first);
                    first=first->next;
                    last=first->next;
                    prev=first;
                    //prevFirst=first;
                    continue;
                }else{
                    prevFirst->next=first->next;
                    free(first);
                    first=first->next;
                    last=first->next;
                    prev=first;
                    //prevFirst=first;
                    continue;
                }

            }
            prev=last;
            if(last!=NULL)
                last=last->next;
        }
        prevFirst = first;
        first=first->next;
    }
    
}
void removeRedudant(struct Node *headNode){
    struct Node *node = headNode;
    struct time_unit *timeNode;
    while(node!=NULL){
        timeNode = node->timeNode;
        while(timeNode!=NULL){
          sortList(&(timeNode->values));
          removeValues(&(timeNode->values));
            timeNode=timeNode->next;
        }
        node= node->next;
    }

}

void removeRedudantdValues(struct Node *headNode){
    struct Node *node = headNode;
    struct time_unit *timeNode;
    while(node!=NULL){
        timeNode = node->dTableValues;
        while(timeNode!=NULL){
            sortList(&(timeNode->values));
            removeValues(&(timeNode->values));
            timeNode=timeNode->next;
        }
        node= node->next;
    }
    
}

void generateBTable(struct Node *headNode){
    struct Node *node = headNode;
    struct processor *pProcessor;
   // int lastTime=0;
    struct cases *pCases;
    while(node!=NULL){
        pProcessor = node->process;
        while(pProcessor!=NULL){
            pCases = pProcessor->cases;
            while(pCases!=NULL){
                appendCostProb(&(node->timeNode),pCases);
                pCases=pCases->next;
            }
            pProcessor =  pProcessor->next;
        }
        node= node->next;
    }
    removeRedudant(headNode);
}

int can_be_stopped(struct Node *node){
//    struct time_unit *current;
//    current = node->dTableValues;
//    if(current==NULL){
//        return 1;
//    }
//    while(current->next!=NULL){
//        current=current->next;
//    }
//    if(current->time==13){
//        return 0;
//    }else{
//        return 1;
//    }

    counter++;
    if(counter==14){
        counter=0;
        return (0);
    }else{
        return 1;
    }
}

void generateDTable(struct Node *headNode){
    struct Node *node = headNode;
    struct Node *prevNode =NULL;
    int lastTime=1;
    struct time_unit *timeNode=NULL;
    struct time_unit *prevdTable;
    struct time_unit *traversing;
    struct value *Val;
    struct value *first;
    struct value *second;
    struct value *newVal;
    while(node!=NULL){
       // timeNode = node->timeNode;
        
        while(can_be_stopped(node)){
          
            timeNode = node->timeNode;
            if(node->dTableValues==NULL){
                node->dTableValues = malloc(sizeof(struct time_unit));
                traversing = node->dTableValues;
                 traversing->values=NULL;
            }else{
                traversing = node->dTableValues;
                while(traversing->next!=NULL){
                    traversing=traversing->next;
                }
                traversing->next =malloc(sizeof(struct time_unit));
                traversing=traversing->next;
                traversing->values=NULL;
            }
            traversing->time=lastTime++;
            traversing->next=NULL;
//            if(prevNode!=NULL){
//                prevdTable = prevNode->dTableValues;
//            }else{
//                prevdTable=NULL;
//            }
            while(timeNode!=NULL){
                
                if(prevNode!=NULL){
                    prevdTable = prevNode->dTableValues;
                }else{
                    prevdTable=NULL;
                }
                if(prevdTable){
                    while(prevdTable!=NULL){
                        if(((timeNode->time)+(prevdTable->time))==traversing->time){
                            first = timeNode->values;
                            second = prevdTable->values;
                            while(first!=NULL){
                               
                                while(second!=NULL){
                                    
                                    if(traversing->values==NULL){
                                        traversing->values=malloc(sizeof(struct value));
                                        newVal = traversing->values;
                                        newVal->next=NULL;
                                    }else{
                                        newVal = traversing->values;
                                        while(newVal->next!=NULL)
                                            newVal = newVal->next;
                                        newVal->next = malloc(sizeof(struct value));
                                        newVal = newVal->next;
                                        newVal->next=NULL;
                                    }
                                    newVal->cost=first->cost+second->cost;
                                    newVal->prob=first->prob*second->prob;
                                    second=second->next;
                                }
                                first=first->next;
                            }
                        }
                        prevdTable = prevdTable->next;
                    }
                }else{
                    if(timeNode->time==traversing->time){
                        Val=timeNode->values;
                        while(Val!=NULL){
                
                            if(traversing->values==NULL){
                               traversing->values=malloc(sizeof(struct value));
                                newVal = traversing->values;
                                if(newVal==NULL){
                                    printf("Error!!!");
                                }
                               // newVal->next=NULL;
                            }else{
                                newVal = traversing->values;
                                while(newVal->next!=NULL)
                                    newVal = newVal->next;
                                newVal->next = malloc(sizeof(struct value));
                                if(newVal->next==NULL){
                                    printf("Error!!!");
                                }
                                newVal = newVal->next;
                              //  newVal->next=NULL;
                            }
                            newVal->next=NULL;
                            newVal->cost=Val->cost;
                            newVal->prob=Val->prob;
                            Val=Val->next;
                        }
                    }
                }
                timeNode = timeNode->next;
            }
        }
        prevNode=node;
        node = node->next;
        lastTime=1;
    }
    removeRedudantdValues(headNode);
}

void init( struct Node **headNode){
    FILE *fp;
    struct processor *pProcessor;
    struct cases *pCases;
    int noOfNodes,noOfModes,noOfCases;
    struct Node *pNode;
    //fp = fopen("/Users/admin/Desktop/220/CMPE220/test.txt","r");
    fp = fopen(INPUT_PATH,"r");
    if(fp==NULL) {
        printf("files not found\n\n");
    }
    //printf("Enter the no. of nodes:");
    fscanf(fp,"%d,",&noOfNodes);
    printf("Nodes are %d\n",noOfNodes);
    for(int i=0;i<noOfNodes;i++){
        if(*headNode==NULL){
            *headNode =  malloc(sizeof(struct Node));
            pNode = *headNode;
        }else{
            pNode = *headNode;
            while(pNode->next!=NULL)
                pNode = pNode->next;
            pNode->next = malloc(sizeof(struct Node));
            pNode = pNode->next;
        }
        pNode->next=NULL;
        pNode->nodeNum = i;
        pNode->process=NULL;
        //printf("Enter the details for Node :%d\n",i);
        //printf("Enter no of energy mode:");
        fscanf(fp,"%d",&noOfModes);
        do{
            if(pNode->process==NULL){
                pNode->process = malloc(sizeof(struct processor));
                pProcessor = pNode->process;
            }else{
                pProcessor = pNode->process;
                while(pProcessor->next!=NULL)
                    pProcessor = pProcessor->next;
                pProcessor->next = malloc(sizeof (struct processor));
                pProcessor = pProcessor->next;
            }
            pProcessor->next=NULL;
            pProcessor->cases=NULL;
            //printf("Enter no of cases:");
            fscanf(fp,"%d",&noOfCases);
            do{
                if(pProcessor->cases==NULL){
                    pProcessor->cases = malloc(sizeof(struct cases));
                    pCases = pProcessor->cases;
                }else{
                    pCases = pProcessor->cases;
                    while(pCases->next!=NULL)
                        pCases = pCases->next;
                    pCases->next = malloc(sizeof (struct cases));
                    pCases= pCases->next;
                }
                pCases->next=NULL;
                //printf("Enter time:");
                fscanf(fp,"%d",&pCases->time);
               // printf("Enter cost:");
                fscanf(fp,"%d",&pCases->cost);
               // printf("Enter prob:");
                fscanf(fp,"%f",&pCases->prob);
            }while(--noOfCases);
        }while(--noOfModes);
    }
    return;
}

void printDTable(struct Node *headNode){
    struct Node *node = headNode;
    struct time_unit *t;
    struct value *v;
    printf("\n\n\nPrinting D Table");
    while(node!=NULL){
        printf("\n\nPrinting Details of Node : %d\n",node->nodeNum);
        t=node->dTableValues;
        while(t!=NULL){
            
            v=t->values;
            if(v!=NULL)
                printf("\nTime: %d\n",t->time);
            while(v!=NULL){
                printf("(%d , %f)\t",v->cost,v->prob);
                v=v->next;
            }
            t=t->next;
             if(v!=NULL)
                 printf("\n");
        }
        node = node->next;
    }
    
    
}
void printBTable(struct Node *headNode){
    struct Node *node = headNode;
    struct time_unit *t;
    struct value *v;
    printf("\nPrinting B Table\n\n");
    while(node!=NULL){
        printf("\n\nPrinting Details of Node : %d\n",node->nodeNum);
        t=node->timeNode;
        while(t!=NULL){
            
            v=t->values;
            if(v!=NULL)
                printf("\nTime: %d\n",t->time);
            while(v!=NULL){
                printf("(%d , %f)\t",v->cost,v->prob);
                v=v->next;
            }
            t=t->next;
             if(v!=NULL)
                 printf("\n");
        }
        node = node->next;
    }
    
    
}
int main(int argc, const char * argv[])
{
    struct Node *headNode;
    printf("The code starts here...\n");
    init(&headNode);
    generateBTable(headNode);
    printBTable(headNode);
    generateDTable(headNode);
    printDTable(headNode);
    return 0;
}


