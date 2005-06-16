#include <stdio.h>

main() {
    int i;
    
    for (i=32;i<256;i++) {
	if ((i%8)==0) printf("\n");
	printf("%3.u %2.x %c   ",i,i,i);
    }
    printf("\n\n");
}
