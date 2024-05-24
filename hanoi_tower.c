#include <stdio.h>
#include <stdlib.h>
void hanoi_solve_ans(int disks, int start, int end, int free)
{
if(disks == 1)
{
printf("%d - %d\n",start,end);
return;
}
hanoi_solve_ans(disks-1, start, free, end);
printf("%d - %d\n",start,end);
hanoi_solve_ans(disks-1, free, end, start);
}

void hanoi_solve(int disks, int start, int end, int free)
{
    if(disks == 1){
        printf("%d-%d\n", start,end);
        return;
    }
    hanoi_solve(disks-1,start,free,end);
    hanoi_solve(1,start,end,free);
    hanoi_solve(disks-1,free,end,start);
}
int main (void){
    hanoi_solve(4,1,3,2);
    printf("ans\n");
    hanoi_solve_ans(4,1,3,2);
}