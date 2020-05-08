
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"


unsigned char charset[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

unsigned char revchar(char ch)
{
   if (ch >= 'A' && ch <= 'Z')
      ch -= 'A';
   else if (ch >= 'a' && ch <='z')
      ch = ch - 'a' + 26;
   else if (ch >= '0' && ch <='9')
      ch = ch - '0' + 52;
   else if (ch == '+')
      ch = 62;
   else if (ch == '/')
      ch = 63;
   return(ch);
}

int base64_encode(unsigned char in[], unsigned char out[], int len, int newline_flag, int separator)
{
   int index,index2,blks,left_over;

   blks = (len / 3) * 3;
   for (index=0,index2=0; index < blks; index += 3,index2 += 4) {
      out[index2] = charset[in[index] >> 2];
      out[index2+1] = charset[((in[index] & 0x03) << 4) + (in[index+1] >> 4)];
      out[index2+2] = charset[((in[index+1] & 0x0f) << 2) + (in[index+2] >> 6)];
      out[index2+3] = charset[in[index+2] & 0x3F];
      
      if (!(index2 % (separator+1)) && newline_flag) {
         out[index2+4] = '\n';
         index2++;
      }
   }
   left_over = len % 3;
   if (left_over == 1) {
      out[index2] = charset[in[index] >> 2];
      out[index2+1] = charset[(in[index] & 0x03) << 4];
      out[index2+2] = '=';
      out[index2+3] = '=';
      index2 += 4;
   }
   else if (left_over == 2) {
      out[index2] = charset[in[index] >> 2];
      out[index2+1] = charset[((in[index] & 0x03) << 4) + (in[index+1] >> 4)];
      out[index2+2] = charset[(in[index+1] & 0x0F) << 2];
      out[index2+3] = '=';
      index2 += 4;
   }
   out[index2] = '\0';
   return(index2);
}

int main(int argc, char *argv[]){
   //USAGE:
   //base64 file -> for eecode data
   //base64 -d file -> for decode data 
   //base64 -e file -> for encode data
   //base64 -w n file -> for encode and add newline every n characters
   //base64 -we n file -> for encode and add newline every n characters
   //base64 -wd n file -> for dencode and add newline every n characters
   if(argc==2){
      int inputfile;
      if((inputfile = open(argv[1],O_RDONLY)) < 0){
         close(inputfile);
         exit();
      }
      int buff_len;
      unsigned char output[1024],data[1024];
      while ((buff_len = read(inputfile,data,sizeof(data))) > 0);
      base64_encode(data, output, strlen((char*)data),0,76);
      printf(1,"%s\n",output);
      close(inputfile);
      exit();
   }
}