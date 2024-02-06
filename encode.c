#include <stdio.h>
#include "encode.h"
#include "common.h"
#include "types.h"
#include <string.h>


Status do_encoding(EncodeInfo *encInfo)
{
    //calling function open files
    if(open_files(encInfo)==e_success)
    {
	printf("[*] File open Successfull...\n");

	//calling copying bmp header function
	if(copy_bmp_header(encInfo)==e_success)
	{
	    printf("[*] Copying header successfull...\n");

	    //callinf magic stirng function
	    if(encode_magic_string(MAGIC_STRING,encInfo)==e_success)
	    {
		printf("[*] Encoding magic string is successfull...\n");

		//calling fileformat function
		if(encode_secret_file_extn(encInfo) ==e_success)
		{
		    printf("[*] Encoding secrete file extension is successfull...\n");

		    //calling secret data to image function
		    if(encode_secret_file_data(encInfo)==e_success)
		    {
			printf("[*] Encoding secrete data is successfull...\n");

			//calling remining data copy function
			if(copy_remaining_img_data(encInfo)==e_success)
			{
			    printf("[*] Remining data copying is successful...\n");
			    return e_success;
			}
			else
			{
			    printf("Remining data copying is failed...\n");
			}
		    }
		    else
		    {
			printf("Encoding secrete data is failed...\n");
		    }

		}
		else
		{
		    printf("secrete file extension failed...\n");
		}
	    }
	    else
	    {
		printf("Encoding magic string is failed...\n");
	    }
	}
	else
	{
	    printf("Copying header is failed...\n");
	}

    }
    if(open_files(encInfo)==e_failure) //fail condition for file opening
    {
	printf("File open failed...\n");
    }
}
//open files function definition
Status open_files(EncodeInfo *encInfo)
{
    encInfo->fptr_src_image=fopen(encInfo->src_image_fname,"r"); //opening source image file using file pointer and structure
    if(encInfo->fptr_src_image==NULL)       //checking file is exist or not
    {
	return e_failure;
    }
    else
    {
	encInfo->fptr_secret=fopen(encInfo->secret_fname,"r");  //opening secret message file
	if(encInfo->fptr_secret==NULL)      //checking exist or not 
	{
	    return e_failure;
	}
	else
	{
	    encInfo->fptr_stego_image=fopen(encInfo->stego_image_fname,"w");  //opening output image file(in write mode)
	    if(encInfo->fptr_stego_image==NULL)        //check file exist or not
	    {
		return e_failure;
	    }
	    else
		return e_success;
	}
    }
}
//bmp header copy function
Status copy_bmp_header(EncodeInfo *encInfo)  
{
    char buffer[54];  //creating 54 bytes space for operation
    fread(buffer,1,sizeof(buffer),encInfo->fptr_src_image);   //reading from input image
    fwrite(buffer,1,sizeof(buffer),encInfo->fptr_stego_image);  //writing to otput image
    return e_success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    //encoding magic string length
    int magic_length=strlen(magic_string);

    encode_byte_to_lsb(magic_length,encInfo);  //calling encoding function

    //encoding magic string data
    for(int i=0; i<magic_length; i++)
    {
	encode_data_to_image(magic_string[i],encInfo);    //calling encoding function
    }
    return e_success;
}
Status encode_secret_file_extn(EncodeInfo *encInfo)
{
    char *extension;
    extension=strstr(encInfo->secret_fname,".txt");

    int secret_length=strlen(extension);
    encode_byte_to_lsb(secret_length,encInfo);

    //encoding file extension data
    for(int i=0;i<secret_length; i++)
    {
	encode_data_to_image(extension[i],encInfo);
    }
    return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    //encoding secrete file length
    fseek(encInfo->fptr_secret,0,SEEK_END); //moving cursor to last posiion
    int length=(ftell(encInfo->fptr_secret))-1; //finding length

    encode_byte_to_lsb(length,encInfo);  //function calling

    //encoding secrete file data
    rewind(encInfo->fptr_secret);
    for(int i=0; i<length; i++)
    {
	char data;
	data=fgetc(encInfo->fptr_secret);
	//printf("data is %c ",data);
	encode_data_to_image(data,encInfo);
    }
    return e_success;
}
Status copy_remaining_img_data(EncodeInfo *encInfo)
{

    char ch;
    while( fread(&ch,1,1,encInfo->fptr_src_image) >0 ) //reading
    {
	fwrite(&ch,1,1,encInfo->fptr_stego_image);  //writing
    }
    return e_success;
}
Status encode_byte_to_lsb(int data,EncodeInfo *encInfo)
{
    char buffer[32];   //buffer with 32 bytes sice int is 32 bytes
    fread(buffer,1,sizeof(buffer),encInfo->fptr_src_image);
    for(int i=31; i>=0; i--)
    {
	buffer[31-i]=(((unsigned)(data & (1<<i))) >> i ) | ( buffer[31-i] & (~1) );
    }
    fwrite(buffer,1,sizeof(buffer),encInfo->fptr_stego_image);
    return e_success;

}
Status encode_data_to_image(char data, EncodeInfo *encInfo)
{
    char buffer[8]; //buffer with 8 bytes since char is 8 bytes
    fread(buffer,1,sizeof(buffer),encInfo->fptr_src_image);
    for(int i=7; i>=0; i--)
    {
	buffer[7-i]=(((unsigned)(data & (1<<i))) >> i ) | ( buffer[7-i] & (~1) );
    }
    fwrite(buffer,1,sizeof(buffer),encInfo->fptr_stego_image);
    return e_success;
}

