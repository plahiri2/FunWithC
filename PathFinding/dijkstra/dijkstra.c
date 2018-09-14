#include "graph.h"

void dijkstra(char *src, char *destn)
{
    float *dist=(float *)malloc(sizeof(float)*nodeCount);
    int *prev=(int *)malloc(sizeof(int)*nodeCount);
    int *path=(int *)malloc(sizeof(int)*nodeCount);
    int i,j,source,dest;
    for(i=0;i<nodeCount;i++)
    {
        if(strcmp(src,(nodes+i)->name)==0)
            break;
    }
    source=i;
    for(i=0;i<nodeCount;i++)
    {
        if(strcmp(destn,(nodes+i)->name)==0)
            break;
    }
    dest=i;
    // initializing distance matrix to be infinity
	// and prev array to -1
    for(i=0;i<nodeCount;i++)
    {
        *(dist+i)=-1;
		*(prev+i)=-1;
    }
    // setting source distance to zero
    *(dist+source)=0;
    // initializing nodes to be unvisited
    for(i=0;i<nodeCount;i++)
    {
       (nodes+i)->flag=UNVISITED; 
    }
    
    NODE *current=nodes+source;
	current->flag=VISITED;
    while((nodes+dest)->flag==UNVISITED)
    {
        EDGE *head=current->edges;
        while(head!=NULL)
        {
			if(head->node->flag==VISITED)
			{
				head=head->next;
				continue;
			}
            j=(head->node - nodes);
            if(dist[j]>dist[current-nodes]+head->distance || dist[j]==-1)
            {
                dist[j]=dist[current-nodes]+head->distance;
                prev[j]=current-nodes;
				
            }
            head=head->next;
        }
		current->flag=VISITED;
        for(j=0;j<nodeCount;j++)
        {
            if((nodes+j)->flag==UNVISITED && dist[j]!=-1)
                break;
        }

		if(j==nodeCount)
		{
			printf("No path between source and destination\n");
			return;
		}		
        for(i=0;i<nodeCount;i++)
        {
            if(dist[i]!=-1 && dist[i]<dist[j] && (nodes+i)->flag==UNVISITED)
                j=i;
        }

        current=nodes+j;
    }
    int previous=dest;
    path[0]=previous;
    i=1;
    while(previous!=source)
    {
     
        previous=prev[previous];
        path[i]=previous;
        i++;
    }
    path[i]=source;
	i--;
    for(;i>=0;--i)
    {
        printf("%s ",(nodes+path[i])->name);
    }
	printf("\n");
}
