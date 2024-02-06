
#include "types.h" // Contains user defined types

typedef struct _Decodeinfo
{
    //output image
    FILE *fptr_output_img;
    char *output_img_name;

    //output text file
    FILE *fptr_output_text;
    char *output_text_name;
} DecodeInfo;

/* encoding function */
Status do_decoding(DecodeInfo *decInfo);

/* open files function */
Status open_files_decode(DecodeInfo *decInfo);

/*magic string decoding */
Status decoding_magic_string(DecodeInfo *decInfo);

/* length decoding function */
Status length_decoding(DecodeInfo *decInfo,int *length);

/* data decoding function */
Status character_decoding(DecodeInfo *decInfo,char *data);

/* secret file extension decoding function */
Status decoding_secret_file_extension(DecodeInfo *decInfo);

/* secret file decoding function */
Status secret_file_decoding(DecodeInfo *decInfo);
