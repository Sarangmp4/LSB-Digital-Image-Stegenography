#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include <string.h>

Status E_Validate(int argc,char *argv[]);
OperationType Checkoperation(char *argv[]);
Status D_Validate(int argc,char *argv[]);

int main(int argc,char *argv[])
{
    if(Checkoperation(argv)==e_encode)
    {
	if(E_Validate(argc,argv)==e_success)
	{
	    printf("[*] Validation Successfull...\n");

	    printf("[*] Encoding started...\n");

	    EncodeInfo encinfo; //structure initialisation

	    //collecting the input file names
	    encinfo.src_image_fname=argv[2];  //input.bmp
	    encinfo.secret_fname=argv[3];     //secret.txt

	    //checking 5th CLA is passed 
	    if(argv[4] != NULL)   
	    {
		encinfo.stego_image_fname=argv[4]; //storing name of 5th CLA
	    }
	    else
		encinfo.stego_image_fname= "output.bmp";  //else stroing name as "output.bmp"


	    //callinf do_encoding function
	    if(do_encoding(&encinfo)==e_success)
	    {
		printf("[*] Encoding completely successfull\n");
	    }
	    else
		printf("Encoding fail\n");
	}
    }
    else if(Checkoperation(argv)==e_decode)
    {
	if(D_Validate(argc,argv)==e_success)
	{
	    printf("[*] Decoding Started...\n");

	    DecodeInfo decinfo;   //structor initialisation

	    decinfo.output_img_name=argv[2];

	    if(argv[3] != NULL)
	    {
		decinfo.output_text_name=argv[3];
	    }
	    else
		decinfo.output_text_name= "outsecret.txt";

	    if(do_decoding(&decinfo)==e_success)
	    {
		printf("[*] Decoding completely successfull\n");
	    }
	    else
		printf("Decoding Failed");
	}
    }
    else
    {
	printf("Validation Unsuccessfull\nFor Encoding: Please give 4 or 5 arguments"
		"\neg: ./a.out -e beatuful.bmp text.txt\n"
		"\nFor Encoding Give 3 or 4 arguments"
		"\neg: ./a.out -d output.bmp\n" );
    }
    return 0;
}

//function for validation of CLA and Checking input file is .bmp or not
Status E_Validate(int argc,char *argv[])
{
    //checking 3rd CLA is other than .bmp file 
    if(strstr(argv[2],".bmp")==NULL) 
	return e_failure;

    //checking 4 or 5 CLA and 3rd CLA is .bmp file
    else if((argc==4 || argc==5) && (!strcmp(strstr(argv[2],".bmp"),".bmp")))
	return e_success;

    //fail condition
    else
	return e_failure;
}
//validation for decoding
Status D_Validate(int argc,char *argv[])
{
    if(strstr(argv[2],".bmp")==NULL)
	return e_failure;

    else if( (argc==3 || argc==4) &&  (!strcmp(strstr(argv[2],".bmp"),".bmp") ))
	return e_success;
    else
	return e_failure;
} 

//function for checking decdoing or encoding -e or -d
OperationType Checkoperation(char *argv[])
{
    //checking encoding mode
    if(strcmp(argv[1],"-e")==0)
	return e_encode;

    //checking decoding mode
    else if(strcmp(argv[1],"-d")==0)
	return e_decode;
    //fail condition
    else
	return e_unsupported;  //other than -e or -d
}



