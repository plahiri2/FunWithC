#include "graph.h"
int bellmanFord(char *src, float *dist, int *predecessors);
int main()
{
  
   readNodeFile("nodes.txt");
   readEdgeFile("edges.txt");
   int *predecessors=malloc(sizeof(int)*nodeCount);
   float *distance=malloc(sizeof(float)*nodeCount);
   int retval=0,i;
   retval=bellmanFord("Woodford", distance, predecessors);
   if(retval==-1)
       printf("Negative Cycle Detected\n");
   else
   {
       for(i=0;i<nodeCount;i++)
           printf("%s: %d %f\n",(nodes+i)->name,predecessors[i], distance[i]);
   }
      
   
   return 1;
}
int bellmanFord(char *src, float *dist, int *predecessors)
{
    int i,j,k;
    // initializing the distance array
    for(i=0;i<nodeCount;i++)
    {
        *(dist+i)=INFINITY;
    }
    
    for(i=0;i<nodeCount;i++)
    {
        // initializing the predecessor array
        *(predecessors+i)=-1;
    }
    //finding the index of the src node in the node array
    for(i=0;i<nodeCount;i++)
    {
        if(strcmp((nodes+i)->name,src)==0)
            break;
    }
    *(dist+i)=0; // settng source distance to 0
    //main loop running |V(G)| -1 times
    for(i=0;i<nodeCount-1;i++)
    {
        // traversing through the node array to go through each edge
        for(j=0;j<nodeCount;j++)
        {
            //edge will be used to traverse the edge linked-list
            EDGE *edge=(nodes+j)->edges;
            while(edge!=NULL)
            {
                k=edge->node - nodes;
                // the distance of the node u in edge (u,v) is infinity
                if(*(dist+j)==INFINITY)
                {
                    edge=edge->next;
                    continue;
                }
                //if dist[u]+w<dist[v]   
                else if(edge->distance + *(dist+j)< *(dist+k))
                {
                    *(dist+k)=edge->distance + *(dist+j);
                    predecessors[k]=j;
                    edge=edge->next;
                }
                else
                {
                    edge=edge->next;
                    continue;
                }
                
            }   
         }
    }
    //negative cycle detection
    for(j=0;j<nodeCount;j++)
    {
        EDGE *edge=(nodes+j)->edges;
        while(edge)
        {
            k=edge->node - nodes;
            if(edge->distance + *(dist+j)< *(dist+k))
                return -1;
            edge=edge->next;
        }
    }
    return 1;
} 


