#include <stdio.h>

int main() {
    int x;
    int y;

    scanf("%d", &x);
    scanf("%d", &y);

    printf("  xxxxxxx  \n");
   printf(" xx     xx \n");
   printf(" x  0 0  x \n");
   printf(" \\   >   / \n");
   printf("  \\  ~  /  \n");
   printf("   \\___/   \n");

   printf("  xxxxxxx  \n");
   printf(" xx     xx \n");
   printf(" x  %d %d  x \n", x, x);
   printf(" \\   %d   / \n", y);
   printf("  \\  ~  /  \n");
   printf("   \\___/   \n");

   return 0;
}
