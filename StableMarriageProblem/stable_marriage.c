#include "stable_marriage.h"
// reads in the two preference files and populates the preference matrices.
// INPUT: 
// menPrefs: men preference file name
// womenPrefs: women preference file name
// size: The number of men or women
// men: empty men preference array
// women: empty women preference array
// SIDE EFFECTS:
// men: populated men preference array where men[i][j] is the jth preference of the ith man
// women: populated women preference array where women[i][j] is the jth preference of the jth woman

void readPrefFiles(char *menPrefs, char *womenPrefs, int size, int **men, int **women)
{
    int i,j;
    
    FILE *fp1;
    fp1=fopen(menPrefs,"r");
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            fscanf(fp1,"%d",&men[i][j]);
        }
    }
    fclose(fp1);
    fp1=fopen(womenPrefs,"r");
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            fscanf(fp1,"%d",&women[i][j]);
        }
    }
}

//This function recursively solves the stable marriage problem
//INPUTS:
//men- populated preference array for men
//women- populated preference array for women
//solution- the 1-dimensional solution array where solution[i] is the wife of man i
//size- Number of men or women
//start- Start of the subarray
//end- End of subarray
void maleOptimalSolution(int **men, int **women, int *solution, int start, int end, int size)
{
    if(start==end) // base case. One man subarray
        solution[start]=men[start][0];
    else
    {
    int mid=(start+end)/2;
    maleOptimalSolution(men, women, solution,0,mid,size); // break problem into two sub problems
    maleOptimalSolution(men,women,solution,mid+1,end,size);
    maleOptimalMerge(men,women,solution,start,end, size); // merge two sub solutions.
    }
}

// This function handles the merging of the solutions to two sub problems
// The parameters passed to this function have the same meaning as the maleOptimalSolution function
void maleOptimalMerge(int **men,int **women,int *solution, int start, int end, int size)
{
    int i,j,k;
    int conflict=1;// flag to keep track of conflicts. Assume that there is a conflict.
    while(conflict)
    {
    for(i=start;i<=end;i++) // the merge of solution subsets S1 and S2 will be the set from start to end
    {
        for(j=i+1;j<=end;j++) // pairwise checking of all couples for conflicts
        {
            if(solution[i]==solution[j]) // two men married to the same woman
            {
                int indexi,indexj; // variables to store the ranks of the men i and j in the prefernce list of the woman. 
                for(k=0; k<size; k++)
                {
                    if(women[solution[i]][k]==i)
                        indexi=k;
                    if(women[solution[j]][k]==j)
                        indexj=k;
                    
                }
                if(indexi<indexj)   // if rank of man i is less than rank of man j
                {
                   for(k=0;k<size;k++)
                   {
                       if(men[j][k]==solution[j])
                       {
                           solution[j]=men[j][k+1]; // give man j his next preference
                           break;
                       }
                   }
                }
                
                if(indexi>indexj)
                {
                   for(k=0;k<size;k++)
                   {
                       if(men[i][k]==solution[i])
                       {
                           solution[i]=men[i][k+1];
                           break;
                       }
                   }

                }
            }
        }
    }
     conflict=0;
     for(i=start;i<=end;i++) // checking for new conflicts created.
    {
        for(j=i+1;j<=end;j++)
        {
            if(solution[i]==solution[j])
                conflict=1;
                break;
        }
    }
    }
}


