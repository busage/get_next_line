#include <unistd.h>
#include <stdio.h>
int main()
{
    char data[100];

    if(read(0, data, 100) < 0)
     write(2, "An error occurred in the read.\n", 31);
	else
	printf("%s\n",data);
    return(0);
}
