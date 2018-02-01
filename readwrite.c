#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "readwrite.h"
#define FSIZE sizeof(float)

FILE *efopen(const char *file, const char *mode)
{
    FILE *stream;

    if (ERROR == (stream = fopen(file, mode)))
        err("%s: efopen: fopen failed", __FILE__);
    
    return stream;
}
/*----------------------------------------------------------------------------------
Read dat 2d
------------------------------------------------------------------------------------
Input:
fp
nz
nx
Output:
data		data[nz][nx]
------------------------------------------------------------------------------------
Ver1.0 : read dat 2d
Notes:
    Read dat 2d 
------------------------------------------------------------------------------------
Author:  Hao Xue
Email :  xhufoxc@gmail.com
Date  :  2018-01-31 09:41 
------------------------------------------------------------------------------------*/
void ReadDat_2d(FILE *fp, float **data,int nz, int nx) 
{
    int iz,ix;

    for (ix=0 ; ix < nx ; ++ix)
    {
        for (iz = 0 ; iz < nz ; ++iz)
        {
            fread(&data[ix][iz],sizeof(float),1,fp);
        }
    }
}

// Author : Xue Hao
// Ver1.0 : 2016-12-10 write bin data, because su data type display error for GPU cluster in CNPC , own GPU machine ok for write_big_endian su data
void WriteDat_1d(FILE *fp, float *data,int nz, int nx)
/* write horizental wavefield */
{
    //ix*nz+iz
    fwrite(&data[0],sizeof(float),nx*nz,fp);

}

// Author : Xue Hao
// Ver1.0 : 2016-12-10 write bin data, because su data type display error for GPU cluster in CNPC , own GPU machine ok for write_big_endian su data
void WriteDat_2d(FILE *fp, float **data,int nz, int nx)
/* write horizental wavefield */
{
    int iz,ix;

    for (ix=0 ; ix < nx ; ++ix)
    {
        for (iz = 0 ; iz < nz ; ++iz)
        {
            fwrite(&data[ix][iz],sizeof(float),1,fp);
        }
    }
}

void swap_short_2(short *tni2)
/**************************************************************************
swap_short_2        swap a short integer
***************************************************************************/
{
 *tni2=(((*tni2>>8)&0xff) | ((*tni2&0xff)<<8));  
}

void swap_u_short_2(unsigned short *tni2)
/**************************************************************************
swap_u_short_2      swap an unsigned short integer
***************************************************************************/
{
 *tni2=(((*tni2>>8)&0xff) | ((*tni2&0xff)<<8));  
}

void swap_int_4(int *tni4)
/**************************************************************************
swap_int_4      swap a 4 byte integer
***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
        ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));  
}

void swap_u_int_4(unsigned int *tni4)
/**************************************************************************
swap_u_int_4        swap an unsigned integer
***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
        ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));  
}

void swap_long_4(long *tni4)
/**************************************************************************
swap_long_4     swap a long integer
***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
        ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));  
}

void swap_u_long_4(unsigned long *tni4)
/**************************************************************************
swap_u_long_4       swap an unsigned long integer
***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
        ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));  
}

void swap_float_4(float *tnf4)
/**************************************************************************
swap_float_4        swap a float
***************************************************************************/
{
 int *tni4=(int *)tnf4;
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
        ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));  
}

void swap_double_8(double *tndd8)
/**************************************************************************
swap_double_8       swap a double
***************************************************************************/
{
  char *tnd8=(char *)tndd8;
  char tnc;

  tnc= *tnd8;
  *tnd8= *(tnd8+7);
  *(tnd8+7)=tnc;

  tnc= *(tnd8+1);
  *(tnd8+1)= *(tnd8+6);
  *(tnd8+6)=tnc;

  tnc= *(tnd8+2);
  *(tnd8+2)= *(tnd8+5);
  *(tnd8+5)=tnc;

  tnc= *(tnd8+3);
  *(tnd8+3)= *(tnd8+4);
  *(tnd8+4)=tnc;
}

/* swap binary header and trace header value */
void swaphval(segy *tr, int index)
{
    register char *tp= (char *) tr;
    
    switch(*(hdr[index].type)) {
    case 'h': swap_short_2((short*)(tp + hdr[index].offs));
        break;
    case 'u': swap_u_short_2((unsigned short*)(tp + hdr[index].offs));
        break;
    case 'i': swap_int_4((int*)(tp + hdr[index].offs));
        break;
    case 'p': swap_u_int_4((unsigned int*)(tp + hdr[index].offs));
        break;
    case 'l': swap_long_4((long*)(tp + hdr[index].offs));
        break;
    case 'v': swap_u_long_4((unsigned long*)(tp + hdr[index].offs));
        break;
    case 'f': swap_float_4((float*)(tp + hdr[index].offs));
        break;
    case 'd': swap_double_8((double*)(tp + hdr[index].offs));
        break;
    default: fprintf(stderr,"%s: %s: unsupported data type", __FILE__, __LINE__);
        break;
    }
    
    return;
}

// static int fputtr_little(FILE *fp, segy *tp)
// {
//     int nread;

//     nread=fwrite(tp,1,(*tp).ns*FSIZE+240,fp);

//     return nread;
// }
static int fputtr_big(FILE *fp, segy *tp)
{
    segy tr;
    int nread;
    int i;
    int ns;
    ns=(*tp).ns;
    memcpy((void *)(&tr),(void *)(tp),ns*FSIZE+240);
    
    //fprintf(stderr,"ns=%d\n",ns);
    for (i = 0; i < SEGY_NKEYS; ++i) 
        swaphval(&tr,i);
    //if (verbose) printf("Assuming IBM floating point format\n");
    for (i = 0; i < ns ; ++i)//void swap_float_4(float *tnf4)
        swap_float_4(&(tr.data[i]));
    //float2ibm((*tp).data[i],(*tp).data[i]);  
    //float_to_ibm((int *)&(tr).data[i],(int *)&(tr).data[i],ns,1);  
    nread=fwrite(&tr,1,ns*FSIZE+240,fp);
    
    return nread;
}

// Author : Xue Hao
// Ver1.0 : 2016-05-04 14:21:38 change to fputtr_big() 
//          rewrite fputt_big() to solve fputtr problem
//          fputtr in su handle FILE pointer in a way that i cannot understand and cause file write problem 
void WriteSu(FILE *fp, float **data,int nz, int nx, float dt,float dx,int it,int tracl,int tracr)
/* write horizental wavefield */
{
    int iz,ix;
    segy tr;
    tr.sx = 0;
    tr.sdepth = 0;
    tr.trid = 1;
    tr.ns = nz ;
    tr.dt = 1000000 * dt ;
    tr.d2 = 1 ;

    /* account for delay in source starting time */
    tr.delrt = 0 ; 

    tracl = 0;
    for (ix=0 ; ix < nx ; ++ix){
        ++tracl;
        ++tracr;

        /* offset from first source location */
        tr.offset = 0;
        tr.fldr=it;
        tr.tracl = tracl;
        tr.tracr = tracr;

        for (iz = 0 ; iz < nz ; ++iz){
            tr.data[iz] = data[ix][iz];
        }
        fputtr_big(fp , &tr);  
    }
}



// Author : Xue Hao
// Ver1.0 : 2016-05-04 14:21:38 change to fputtr_big() 
//          rewrite fputt_big() to solve fputtr problem
//          fputtr in su handle FILE pointer in a way that i cannot understand and cause file write problem 
void WriteSu_2d(FILE *fp, float **data,int nz_beg,int nz_end,int nx_beg, int nx_end)
/* write horizental wavefield */
{
    segy tr;
    int iz,ix;
    int tracl, tracr;
    int it=0;
    float dt=0.001;
    tr.sx = 0;
    tr.sdepth = 0;
    tr.trid = 1;
    tr.ns = nz_end-nz_beg ;
    tr.dt = 1000000 * dt ;
    tr.d2 = 1 ;

    /* account for delay in source starting time */
    tr.delrt = 0 ; 

    tracl = 0;
    tracr = 0;
    for (ix=nx_beg ; ix < nx_end ; ++ix){
        ++tracl;
        ++tracr;

        /* offset from first source location */
        tr.offset = 0;
        tr.fldr=it;
        tr.tracl = tracl;
        tr.tracr = tracr;

        for (iz = nz_beg ; iz < nz_end ; ++iz){
            tr.data[iz-nz_beg] = data[ix][iz];
        }
        fputtr_big(fp , &tr);  
    }
}

// Author : Xue Hao
// Ver1.0 : 2016-05-04 14:21:38 change to fputtr_big() 
//          rewrite fputt_big() to solve fputtr problem
//          fputtr in su handle FILE pointer in a way that i cannot understand and cause file write problem 
// Ver1.1 : 2016-11-06 11:24:59 change to output 1d data, test passed
void WriteSu_1d(FILE *fp, float *data,int nz, int nx, float dt,float dx,int ffid,int tracl,int tracr)
/* write horizental wavefield */
{
    int iz,ix;
    segy tr;
    tr.sx = 0;
    tr.sdepth = 0;
    tr.trid = 1;
    tr.ns = nz ;
    tr.dt = 1000000 * dt ;
    tr.d2 = 1 ;

    /* account for delay in source starting time */
    tr.delrt = 0 ; 

    tracl = 0;
    for (ix=0 ; ix < nx ; ++ix){
        ++tracl;
        ++tracr;

        /* offset from first source location */
        tr.offset = 0;
        tr.fldr=ffid;
        tr.tracl = tracl;
        tr.tracr = tracr;

        for (iz = 0 ; iz < nz ; ++iz){
            tr.data[iz] = data[ix*nz+iz];
        }
        fputtr_big(fp , &tr);  
    }
}
 