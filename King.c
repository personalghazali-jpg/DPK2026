#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    char * nama1 = "Popol";
    char * nama2 = "Kupa";

    if (argc < 2) {
        printf("Argumen kurang\n");
        printf("tambahkan argumen %s %s %s " , argv[0], nama1, nama2);
        return -1;
}

printf("Halo %s", argv[1]);
printf("Halo Juga %s", argv[2]);

return 0;
}