#include <stdio.h>

#define SIZE 100000

FILE *ifp, *ofp;
const char str_head[]="{\"objects\":[";
const char str_bline[]="b-line";
const char str_item[]="{\"ongoing\":\"";

void Search_Save(char *str) {
    int first=1;
    while(str) {
        str = strstr(str, "Ongoing");
        if (str) {
            str += 46;
            SaveIt(str,first);
            if (first) first=0;
        }
    }
}

void SaveIt(char *str, int first) {
    int i;
    if (!first) fputc(',',ofp);
    for (i=0;i<12;i++) {
        fputc(str_item[i],ofp);
    }
    i = 0;
    while(str[i] != '<') {
        fputc(str[i],ofp);
        i++;
    }
    fputc('\"',ofp);
    fputc('}',ofp);
}

int main(int argc, char* argv[]) {
    int i;
    char str[SIZE];
    if (argc != 2) {
        printf("usage: %s <filename>\n",argv[0]);
        return(1);
    }
    ifp = fopen(argv[1],"r");
	ofp = fopen(str_bline,"w");
    for (i=0;i<12;i++)
        fputc(str_head[i],ofp);
    //fwrite(str_head,sizeof(char),sizeof(str_head),ofp);
    fclose(ofp);
    
    for (i=0; i<SIZE; i++) {
        str[i] = fgetc(ifp);
        if(str[i] == -1) {
            str[i] = '\0';
            break;
        }
    }
    
	ofp = fopen(str_bline,"a");
    Search_Save(str);
    fputc(']',ofp);
    fputc('}',ofp);
    fclose(ifp);
    fclose(ofp);
}
