#include <stdio.h>
#include "decode.h"
#include "common.h"
#include "types.h"
#include <string.h>

Status do_decoding(DecodeInfo *decInfo)
{
    if(open_files_decode(decInfo) == e_success)
    {
	printf("[*] File open successfull\n");
	fseek(decInfo->fptr_output_img,54,SEEK_SET);
	printf("\n");
	//calling magic string decoding function
	if( decoding_magic_string(MAGIC_STRING,decInfo) == e_success )
	{
	    printf("\n");
	    printf("[*] Dcoding magic string is completed\n");
	    printf("\n");

	    //calling file extension decoding function
	    if(decoding_secret_file_extension(decInfo)== e_success)
	    {
		printf("\n");
		printf("[*] Decoding secret file extension is successfull\n");
		printf("\n");
		//sectret file decoding

		if(secret_file_decoding(decInfo) == e_success)
		{
		    printf("\n");
		    //sectret file decoding
		    printf("[*] Decoding secret file is completed\n");
		    return e_success;
		}
		else
		{
		    printf("[*] Decoding secret file is completed\n");
		    return e_failure;
		}
	    }
	    else
	    {
		printf("Decoding secret file extension is failed\n");
		return e_failure;
	    }

	}
	else
	{
	    printf("Decoding magic string is failed\n");
	    return e_failure;
	}
    }
    else
    {
	printf("file pen failed\n");
	return e_failure;
    }


}
//file opening function
Status open_files_decode(DecodeInfo *decInfo)
{
    decInfo->fptr_output_img=fopen(decInfo->output_img_name,"r");
    if(decInfo->fptr_output_img != NULL)
    {
	    return e_success;
    }
    else
    {
	return e_failure;
    }
}

//magic string decoding function
Status decoding_magic_string(const char *magic_string,DecodeInfo *decInfo)
{
    //magic length decoding
    int length=0;
    length_decoding(decInfo,&length);  //function calling
    printf("MAGIC STRING LENGTH IS DECODED AND VALUE IS : %d\n",length);

    //magic data decoding
    char data;
    char magic_string_data[length+1];
    for(int i=0;i<length;i++)
    {
	data=0x00;
	character_decoding(decInfo,&data); //function calling
	magic_string_data[i]=data;
    }
    magic_string_data[length]='\0';
    printf("MAGIC STRING IS DECODED AND IT IS %s\n",magic_string_data);
	if(strcmp(magic_string,magic_string_data)==0)
	{
		return e_success;
	}
	else
	{
                printf("MAGIC STRING AUTHENTICATION IS FAILED\n");
		return e_failure;
	}

    return e_success;
}

//secret file extension decoding function
Status decoding_secret_file_extension(DecodeInfo *decInfo)
{
    //secret file extension length decoding
    int length=0;
    length_decoding(decInfo,&length);  //function calling
    printf("SECRET FILE EXTENSION LENGTH IS %d\n",length);

    //secret file extension data decoding
    char data;
    char exten_string[length+1];
    for(int i=0;i<length;i++)
    {
	data=0x00;
	character_decoding(decInfo,&data);
	exten_string[i]=data;
    }
    exten_string[length]='\0';
    printf("SECRET FILE EXTENSION IS %s",exten_string);
    strcat(decInfo->output_text_name,exten_string);
    decInfo->fptr_output_text=fopen(decInfo->output_text_name,"w");
     if(decInfo->fptr_output_text == NULL)
      {
        return e_failure;
      }
    printf("\n");
    return e_success;
}
Status secret_file_decoding(DecodeInfo *decInfo)
{
    int length=0;
    length_decoding(decInfo,&length);
    printf("SECRET FILE LENGTH IS COMPLETED AND VALUE IS %d\n",length);

    printf("SECRET FILE DECODING IS COMPLETED AND DATA IS :");
    for(int i=0; i<length; i++)
    {
	char data=0x00;
	character_decoding(decInfo,&data);
	fputc(data,decInfo->fptr_output_text);
	printf("%c",data);
    }
    fputc(EOF,decInfo->fptr_output_text);

    printf("\n");
    return e_success;
}

Status length_decoding(DecodeInfo *decInfo,int *length)
{
    char buffer[32];
    fread(buffer,1,32,decInfo->fptr_output_img);
    
    //legnth decoding
    for(int i=0; i<32; i++)
    {
	*length= *length | ( buffer[i] & 1 ) << (31-i);
    }
    return e_success;
}
Status character_decoding(DecodeInfo *decInfo,char *data)
{
    char buffer[8];
    fread(buffer,1,8,decInfo->fptr_output_img);
    
    //character decoding
    for(int i=0; i<8; i++)
    {
	*data= *data | ( buffer[i] & 1) << (7-i);
    }
    return e_success;
}





