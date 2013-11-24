/*     Compiler Environment : Microsoft Visual C++ 2008 Express Version    Language : C Language    */
#include<stdio.h>
#include<stdlib.h>
/********************************************************************************************************
    The part of "Jobs nodes definition" define the struct of the nodes of Maximum heap name jobs and jobptr.
    
    "id" is the id of the job, "priority" is the priority of the job,
    
    "rtime" is the request time of the job, "ptime" is the printing time of the job
    
    and "nodeid" is the position of job in the Maximum heap.
    
********************************************************************************************************/
/*----------------------Jobs nodes definition--------------------------*/
typedef struct jobs *jobptr;
typedef struct jobs
{
	int id, priority, rtime, ptime, nodeid;
	jobptr leftchild, rightchild;
} job;
/***************************************************************************************************************
    The part of "Maxheap functions" are the functions of Maximum heap operation : 
    
    void clear(jobptr target)  -> to clear the data of the node expect nodeid.
    
    void copynode_p2p(jobptr target,jobptr source) 
                               -> to copy the data from nodepointer source to nodepointer target expect nodeid.

    void copynode_n2p(jobptr target,job source) 
                               -> to copy the data from node source to nodepointer target expect nodeid.
                               
    job copynode_n(int id,int priority,int rtime,int ptime,int nodeid) 
                               -> to insert the value to a node and return the node.
                               
    jobptr findparent(jobptr start ,int num) 
                               -> to find the parentnode of the nodeid = num and return the nodepointer.
                               
    void create_maxheap(jobptr sptr) 
                               -> to initialize the heap.
                               
    void insert_maxheap(jobptr *sptr,int id,int priority,int rtime,int ptime,int nodeid)
                               -> to insert a data to the heap at nodeid = nodeid.

    void delete_maxheap(jobptr *sptr,int treeid) 
                               -> to delete a data from heap (delete root).
                               
    int output_maxheap(jobptr *sptr,FILE *outptr,int printtime) 
                               -> to print the data to the file and return the printing time.
                               
***************************************************************************************************************/
/*----------------------Maxheap functions---------------------------*/
void preorder(jobptr ptr)
{
	if(ptr)
	{
		printf("%d ",ptr->priority);
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void clear(jobptr target)
{
	target->id = 0;
	target->priority = 0;
	target->ptime = 0;
	target->rtime = 0;
}
void copynode_p2p(jobptr target,jobptr source)
{
	target->id = source->id;
	target->priority = source->priority;
	target->ptime = source->ptime;
	target->rtime = source->rtime;
}
void copynode_n2p(jobptr target,job source)
{
	target->id = source.id;
	target->priority = source.priority;
	target->ptime = source.ptime;
	target->rtime = source.rtime;
}
job copynode_n(int id,int priority,int rtime,int ptime,int nodeid)
{
	job target;
	target.id = id;
	target.nodeid = nodeid;
	target.priority = priority;
	target.ptime = ptime;
	target.rtime = rtime;
	return target;
}
jobptr findparent(jobptr start ,int num)
{
	num/=2; // parent id
	if(num != 1) // 2 up nodes
	{
		int i,counter = 0,*road,temp = num;
		while(temp) // calculus the level of the parent node
		{
			temp/=2;
			counter++; 
		}
		// create a road array, size depend on the level of the parent node
		road = (int*) malloc(counter*sizeof(int)); 

		for(i=counter;i>=1;i--) // calculus the path  from top to the parent node
		{
			road[i-1] = num % 2;
			num/=2;			
		}
		for(i=1;i<counter;i++) // move to the parent node
		{
			if(road[i] == 1) // if = 1, move right
			{
				start = start->rightchild;
			}
			else // if = 0, move left
			{
				start = start->leftchild;
			}
		}

	}
	return start; //return this node
}
void create_maxheap(jobptr sptr)
{
	 sptr = NULL; // initialize
}
void insert_maxheap(jobptr *sptr,int id,int priority,int rtime,int ptime,int nodeid)
{
	jobptr newptr,parentptr;
	job n = copynode_n(id,priority,rtime,ptime,nodeid); // insert the data in node n
	newptr = (job*) malloc( sizeof( job ) ); // allocate a memory space, size is the size of job

	if ( newptr != NULL ) // have memory space
	{ 
		newptr->leftchild = NULL;
		newptr->rightchild = NULL;
		newptr->nodeid = n.nodeid; // give nodeid

		if(n.nodeid != 1) // 2 up node
		{
			parentptr = findparent((*sptr),newptr->nodeid); // find the parent of current node
			if(newptr->nodeid % 2 != 1)
			{
				parentptr->leftchild = newptr;
			}
			else
			{
				parentptr->rightchild = newptr;
			}
		}
		else // only 1 node
		{
			copynode_n2p(newptr,n);
			(*sptr) = newptr;
		}

		while(n.nodeid != 1 && n.priority > parentptr->priority || 
        (n.nodeid != 1 && n.priority == parentptr->priority && n.rtime < parentptr->rtime)) // if node > parent
		{
			copynode_p2p(newptr,parentptr);
			parentptr = findparent((*sptr),parentptr->nodeid);
			newptr = findparent((*sptr),newptr->nodeid);
			n.nodeid /= 2; // move up
		}
		
		 copynode_n2p(newptr,n); // insert
	}
	else
	{
		printf("node not inserted. No memory available. \n");
	}
}
void delete_maxheap(jobptr *sptr,int treeid)
{
	jobptr tempptr,parentptr,start;

	if(!treeid) // null
	{
		printf("The Maxheap is empty. \n");
	}
	else // not null
	{
		if(treeid != 1) // 2 up node
		{
			clear((*sptr)); // clear
			start = (*sptr);

			while(start->leftchild || start->rightchild) // complete the heap
			{
				if(start->leftchild && start->rightchild) // 2 children
				{
					if(start->leftchild->priority >= start->rightchild->priority)
					{
						copynode_p2p(start,start->leftchild);
						start = start->leftchild;
					}
					else
					{
						copynode_p2p(start,start->rightchild);
						start = start->rightchild;
					}
				} 
				else // 1 left child
				{
					copynode_p2p(start,start->leftchild);
					start = start->leftchild;
				}
			}

			parentptr = findparent((*sptr),treeid); // find the parent of current node 

			if(treeid % 2 != 1) // left child
			{
				tempptr = parentptr->leftchild;
				parentptr->leftchild = NULL;
			}
			else // right child
			{
				tempptr = parentptr->rightchild;
				parentptr->rightchild = NULL;
			}
			copynode_p2p(start,tempptr);
		}
		else // only 1 node
		{
			tempptr = (*sptr);
		}

		free(tempptr); // delete the node
	}

}
int output_maxheap(jobptr *sptr,FILE *outptr,int printtime)
{
	if(printtime < (*sptr)->rtime) // if printing idle
	{
		fprintf(outptr, "%d %d %d\n", (*sptr)->id, (*sptr)->priority,(*sptr)->rtime); // print data to file
		return ((*sptr)->rtime + (*sptr)->ptime);// retrun printing time
	}
	else
	{
		fprintf(outptr, "%d %d %d\n", (*sptr)->id, (*sptr)->priority,printtime); // print data to file
		return (printtime + (*sptr)->ptime); // retrun printing time
	}
}
/********************************************************************************************************
    The part of "Priority Queue definition" define the struct of the Priority Queue.
    
    "heap" is the queue of the Priority Queue.
        
********************************************************************************************************/
/*----------------------Priority Queue definition--------------------------*/
typedef struct pq
{
	jobptr heap;
} priority_queue;
/***************************************************************************************************************
    The part of "Priority Queue functions" are the functions of Priority Queue operation : 
          
    void create_pq(priority_queue *queue)
                               -> to initialize the priority queue.
                               
    void insert_pq(priority_queue *queue,int id,int priority,int rtime,int ptime,int nodeid)
                               -> to insert a data to the priority queue.

    void delete_pq(priority_queue *queue,int treeid) 
                               -> to delete a data from priority queue.
                               
    int output_pq(priority_queue *queue,FILE *outptr,int printtime) 
                               -> to print the data to the file and return the printing time.
                               
***************************************************************************************************************/
/*----------------------Priority Queue functions---------------------------*/

void create_pq(priority_queue *queue)
{
	create_maxheap(queue->heap); 
}
void insert_pq(priority_queue *queue,int id,int priority,int rtime,int ptime,int nodeid)
{
	insert_maxheap(&(queue->heap), id, priority, rtime, ptime, nodeid);
}
void delete_pq(priority_queue *queue,int treeid)
{
	delete_maxheap(&(queue->heap),treeid);
}
int output_pq(priority_queue *queue,FILE *outptr,int printtime)
{
	return output_maxheap(&(queue->heap),outptr,printtime);
}
/*--------------------main program-----------------------------*/
int main()
{
	int id, priority, rtime, ptime,treeid = 0,printtime = 0; // job's data
	priority_queue q;
	FILE *inptr; // input file pointer
	FILE *outptr = fopen("pq_out.txt","w"); // output file pointer

	create_pq(&q); // initialize

	if((inptr = fopen("pq.txt", "r")) == NULL) // file not exist 
	{	
		printf("File Not Found.\n");
	}
	else
	{
		while(fscanf(inptr, "%d %d %d %d", &id, &priority, &rtime, &ptime) != EOF) // no data
		{
			if(printtime == rtime && printtime == 0) // at first
			{                                        // insert current job and print out
				insert_pq(&q,id,priority,rtime,ptime,++treeid); 
				printtime = output_pq(&q,outptr,printtime);
				delete_pq(&q,treeid);
				treeid--;
			}
			else if(printtime <= rtime) // if it's not printing
			{	                         
				if(!treeid) // if queue is empty
				{           // insert the current job to queue
					insert_pq(&q,id,priority,rtime,ptime,++treeid);
					printtime = output_pq(&q,outptr,printtime);
					delete_pq(&q,treeid);
					treeid--;
				}
				else // if queue is not empty
				{    
					while(treeid && printtime <= rtime) 
					{// clear and print out whole queue
						printtime = output_pq(&q,outptr,printtime);
						delete_pq(&q,treeid);
						treeid--;
					}// and insert the current job to queue
					insert_pq(&q,id,priority,rtime,ptime,++treeid);
				}

			}	
			else // if it's printing
			{    // insert the current job to queue
				insert_pq(&q,id,priority,rtime,ptime,++treeid);
			}
		}
		
		while(treeid) // if no data and queue is not empty
		{             // clear and print out whole queue
			printtime = output_pq(&q,outptr,printtime);
			delete_pq(&q,treeid);
			treeid--;
		}
	}

	fclose (inptr); // close flie
	fclose (outptr); // close flie

	return 0; // termination successful
}
