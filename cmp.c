#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[1000000];

int isSameFiles(char file1[], char file2[], int length1, int length2){
    int i = 0;
    if(length1 == length2){
        for(i = 0; i < length1; i++){
            if(file1[i] != file2[i]) return 0; 
        }
        return 1;
    }
    else return 0;
}

void isDifferentFile(int lengthTemp, int lengthTemp2, char temp[], char temp2[], char namaFile1[], char namaFile2[]){
    int i = 0, lines = 0;
    if(lengthTemp > lengthTemp2){
        for(i = 0; i < lengthTemp; i++) {
            if(temp[i] != temp2[i]) {
            printf(1, "%s %s differ: byte %d, line %d\n", namaFile1, namaFile2, i, lines+1);
            exit();
            }
            if(temp[i] == '\n') lines++;
        }
    }
    else if(lengthTemp < lengthTemp2){
        for(i = 0; i < lengthTemp2; i++) {
            if(temp[i] != temp2[i]) {
            printf(1, "%s %s differ: byte %d, line %d\n", namaFile1, namaFile2, i, lines+1);
            exit();
            }
            if(temp[i] == '\n') lines++;
        }
    }

}

int main (int argc, char *argv[]) {
    int fPtr, fPtr2, i, p, q;
    // int lines = 0;
    char *temp = (char*) malloc(1000000 * sizeof(char));
    int lengthTemp = 0;
    char *temp2 = (char*) malloc(1000000 * sizeof(char));
    int lengthTemp2 = 0;
    if(argc < 3) {
        printf(1, "butuh 2 argumen\n");
        exit();
    }
    
    if((fPtr = open(argv[1], O_RDWR)) < 0) {
        printf(1, "cmp: cannot open %s for reading\n", argv[1]);
        exit();
    }
    while((p = read(fPtr, buf, sizeof(buf))) > 0){
        for(i = 0; i < p; i++){
            temp[lengthTemp] = (char)buf[i];
            lengthTemp++;
        }
    }
    if(p < 0) {
        printf(1, "file kosong | error\n");
        exit();
    }
    
    if((fPtr2 = open(argv[2], O_RDWR)) < 0) {
        printf(1, "cmp: cannot open %s for reading\n", argv[2]);
        exit();
    }
    while((q = read(fPtr2, buf, sizeof(buf))) > 0)
    {
        for(i = 0; i < q; i++){
            temp2[lengthTemp2] = (char)buf[i];
            lengthTemp2++;
        }
    }
    if(q < 0) {
        printf(1, "file kosong | error\n");
        exit();
    }
    if(isSameFiles(temp, temp2, lengthTemp, lengthTemp2)){
            printf(1, "same files\n");
        }
    else {
        isDifferentFile(lengthTemp, lengthTemp2, temp, temp2, argv[1], argv[2]);
        // if(lengthTemp > lengthTemp2){
        //     for(i = 0; i < lengthTemp; i++) {
        //         if(temp[i] != temp2[i]) {
        //         printf(1, "%s %s differ: byte %d, line %d\n", argv[1], argv[2], i, lines+1);
        //         exit();
        //         }
        //         if(temp[i] == '\n') lines++;
        //     }
        // }
        // else if(lengthTemp < lengthTemp2){
        //     for(i = 0; i < lengthTemp2; i++) {
        //         if(temp[i] != temp2[i]) {
        //         printf(1, "%s %s differ: byte %d, line %d\n", argv[1], argv[2], i, lines+1);
        //         exit();
        //         }
        //         if(temp[i] == '\n') lines++;
        //     }
        // }
    }
    exit();
}

/**
 * Function to compare two files.
 * Returns 0 if both files are equivalent, otherwise returns
 * -1 and sets line and col where both file differ.
 */
// int compareFile(FILE * fPtr1, FILE * fPtr2, int * line, int * col)
// {
//     char ch1, ch2;

//     *line = 1;
//     *col  = 0;

//     do
//     {
//         // Input character from both files
//         ch1 = fgetc(fPtr1);
//         ch2 = fgetc(fPtr2);
        
//         // Increment line 
//         if (ch1 == '\n')
//         {
//             *line += 1;
//             // *col = 0;
//         }

//         // If characters are not same then return -1
//         if (ch1 != ch2)
//             return -1;

//         *col  += 1;

//     } while (ch1 != EOF && ch2 != EOF);


//     /* If both files have reached end */
//     if (ch1 == EOF && ch2 == EOF)
//         return 0;
//     else
//         return -1;
// }