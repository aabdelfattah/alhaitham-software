/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

/********************************* COPYRIGHT NOTICE *******************************\
  The function for RGB to Lab conversion is based on the MATLAB script
  RGB2Lab.m translated by Mark Ruzon from C code by Yossi Rubner, 23 September 1997.
  See the page [http://vision.stanford.edu/~ruzon/software/rgblab.html]
\**********************************************************************************/

/********************************* COPYRIGHT NOTICE *******************************\
  Original code for Bayer->BGR/RGB conversion is provided by Dirk Schaefer
  from MD-Mathematische Dienste GmbH. Below is the copyright notice:

    IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
    By downloading, copying, installing or using the software you agree
    to this license. If you do not agree to this license, do not download,
    install, copy or use the software.

    Contributors License Agreement:

      Copyright (c) 2002,
      MD-Mathematische Dienste GmbH
      Im Defdahl 5-10
      44141 Dortmund
      Germany
      www.md-it.de
  
    Redistribution and use in source and binary forms,
    with or without modification, are permitted provided
    that the following conditions are met: 

    Redistributions of source code must retain
    the above copyright notice, this list of conditions and the following disclaimer. 
    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution. 
    The name of Contributor may not be used to endorse or promote products
    derived from this software without specific prior written permission. 

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
    THE POSSIBILITY OF SUCH DAMAGE.
\**********************************************************************************/

#include "_cv.h"
#include"cxmisc.h"

typedef CvStatus (CV_STDCALL * CvColorCvtFunc0)(
    const void* src, int srcstep, void* dst, int dststep, CvSize size );

typedef CvStatus (CV_STDCALL * CvColorCvtFunc1)(
    const void* src, int srcstep, void* dst, int dststep,
    CvSize size, int param0 );

typedef CvStatus (CV_STDCALL * CvColorCvtFunc2)(
    const void* src, int srcstep, void* dst, int dststep,
    CvSize size, int param0, int param1 );

typedef CvStatus (CV_STDCALL * CvColorCvtFunc3)(
    const void* src, int srcstep, void* dst, int dststep,
    CvSize size, int param0, int param1, int param2 );

/****************************************************************************************\
*                                      RGB <-> HSV                                       *
\****************************************************************************************/

static const uchar icvHue255To180[] =
{
      0,   1,   1,   2,   3,   4,   4,   5,   6,   6,   7,   8,   8,   9,  10,  11,
     11,  12,  13,  13,  14,  15,  16,  16,  17,  18,  18,  19,  20,  20,  21,  22,
     23,  23,  24,  25,  25,  26,  27,  28,  28,  29,  30,  30,  31,  32,  32,  33,
     34,  35,  35,  36,  37,  37,  38,  39,  40,  40,  41,  42,  42,  43,  44,  44,
     45,  46,  47,  47,  48,  49,  49,  50,  51,  52,  52,  53,  54,  54,  55,  56,
     56,  57,  58,  59,  59,  60,  61,  61,  62,  63,  64,  64,  65,  66,  66,  67,
     68,  68,  69,  70,  71,  71,  72,  73,  73,  74,  75,  76,  76,  77,  78,  78,
     79,  80,  80,  81,  82,  83,  83,  84,  85,  85,  86,  87,  88,  88,  89,  90,
     90,  91,  92,  92,  93,  94,  95,  95,  96,  97,  97,  98,  99, 100, 100, 101,
    102, 102, 103, 104, 104, 105, 106, 107, 107, 108, 109, 109, 110, 111, 112, 112,
    113, 114, 114, 115, 116, 116, 117, 118, 119, 119, 120, 121, 121, 122, 123, 124,
    124, 125, 126, 126, 127, 128, 128, 129, 130, 131, 131, 132, 133, 133, 134, 135,
    136, 136, 137, 138, 138, 139, 140, 140, 141, 142, 143, 143, 144, 145, 145, 146,
    147, 148, 148, 149, 150, 150, 151, 152, 152, 153, 154, 155, 155, 156, 157, 157,
    158, 159, 160, 160, 161, 162, 162, 163, 164, 164, 165, 166, 167, 167, 168, 169,
    169, 170, 171, 172, 172, 173, 174, 174, 175, 176, 176, 177, 178, 179, 179, 180
};


static const uchar icvHue180To255[] =
{
      0,   1,   3,   4,   6,   7,   9,  10,  11,  13,  14,  16,  17,  18,  20,  21,
     23,  24,  26,  27,  28,  30,  31,  33,  34,  35,  37,  38,  40,  41,  43,  44,
     45,  47,  48,  50,  51,  52,  54,  55,  57,  58,  60,  61,  62,  64,  65,  67,
     68,  69,  71,  72,  74,  75,  77,  78,  79,  81,  82,  84,  85,  86,  88,  89,
     91,  92,  94,  95,  96,  98,  99, 101, 102, 103, 105, 106, 108, 109, 111, 112,
    113, 115, 116, 118, 119, 120, 122, 123, 125, 126, 128, 129, 130, 132, 133, 135,
    136, 137, 139, 140, 142, 143, 145, 146, 147, 149, 150, 152, 153, 154, 156, 157,
    159, 160, 162, 163, 164, 166, 167, 169, 170, 171, 173, 174, 176, 177, 179, 180,
    181, 183, 184, 186, 187, 188, 190, 191, 193, 194, 196, 197, 198, 200, 201, 203,
    204, 205, 207, 208, 210, 211, 213, 214, 215, 217, 218, 220, 221, 222, 224, 225,
    227, 228, 230, 231, 232, 234, 235, 237, 238, 239, 241, 242, 244, 245, 247, 248,
    249, 251, 252, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};


static CvStatus CV_STDCALL
icvBGRx2HSV_8u_CnC3R( const uchar* src, int srcstep, uchar* dst, int dststep,
                      CvSize size, int src_cn, int blue_idx )
{
    int i;

#ifdef HAVE_IPP
    CvStatus status = icvBGRx2ABC_IPP_8u_CnC3R( src, srcstep, dst, dststep, size,
                                            src_cn, blue_idx, (CvColorCvtFunc0)ippiRGBToHSV_8u_C3R );
    if( status >= 0 )
    {
        size.width *= 3;
        for( ; size.height--; dst += dststep )
        {
            for( i = 0; i <= size.width - 12; i += 12 )
            {
                uchar t0 = icvHue255To180[dst[i]], t1 = icvHue255To180[dst[i+3]];
                dst[i] = t0; dst[i+3] = t1;
                t0 = icvHue255To180[dst[i+6]]; t1 = icvHue255To180[dst[i+9]];
                dst[i+6] = t0; dst[i+9] = t1;
            }
            for( ; i < size.width; i += 3 )
                dst[i] = icvHue255To180[dst[i]];
        }
    }
    return status;
#else
    
    const int hsv_shift = 12;

    static const int div_table[] = {
        0, 1044480, 522240, 348160, 261120, 208896, 174080, 149211,
        130560, 116053, 104448, 94953, 87040, 80345, 74606, 69632,
        65280, 61440, 58027, 54973, 52224, 49737, 47476, 45412,
        43520, 41779, 40172, 38684, 37303, 36017, 34816, 33693,
        32640, 31651, 30720, 29842, 29013, 28229, 27486, 26782,
        26112, 25475, 24869, 24290, 23738, 23211, 22706, 22223,
        21760, 21316, 20890, 20480, 20086, 19707, 19342, 18991,
        18651, 18324, 18008, 17703, 17408, 17123, 16846, 16579,
        16320, 16069, 15825, 15589, 15360, 15137, 14921, 14711,
        14507, 14308, 14115, 13926, 13743, 13565, 13391, 13221,
        13056, 12895, 12738, 12584, 12434, 12288, 12145, 12006,
        11869, 11736, 11605, 11478, 11353, 11231, 11111, 10995,
        10880, 10768, 10658, 10550, 10445, 10341, 10240, 10141,
        10043, 9947, 9854, 9761, 9671, 9582, 9495, 9410,
        9326, 9243, 9162, 9082, 9004, 8927, 8852, 8777,
        8704, 8632, 8561, 8492, 8423, 8356, 8290, 8224,
        8160, 8097, 8034, 7973, 7913, 7853, 7795, 7737,
        7680, 7624, 7569, 7514, 7461, 7408, 7355, 7304,
        7253, 7203, 7154, 7105, 7057, 7010, 6963, 6917,
        6872, 6827, 6782, 6739, 6695, 6653, 6611, 6569,
        6528, 6487, 6447, 6408, 6369, 6330, 6292, 6254,
        6217, 6180, 6144, 6108, 6073, 6037, 6003, 5968,
        5935, 5901, 5868, 5835, 5803, 5771, 5739, 5708,
        5677, 5646, 5615, 5585, 5556, 5526, 5497, 5468,
        5440, 5412, 5384, 5356, 5329, 5302, 5275, 5249,
        5222, 5196, 5171, 5145, 5120, 5095, 5070, 5046,
        5022, 4998, 4974, 4950, 4927, 4904, 4881, 4858,
        4836, 4813, 4791, 4769, 4748, 4726, 4705, 4684,
        4663, 4642, 4622, 4601, 4581, 4561, 4541, 4522,
        4502, 4483, 4464, 4445, 4426, 4407, 4389, 4370,
        4352, 4334, 4316, 4298, 4281, 4263, 4246, 4229,
        4212, 4195, 4178, 4161, 4145, 4128, 4112, 4096
    };

    srcstep -= size.width*src_cn;
    size.width *= 3;

    for( ; size.height--; src += srcstep, dst += dststep )
    {
        for( i = 0; i < size.width; i += 3, src += src_cn )
        {
            int b = (src)[blue_idx], g = (src)[1], r = (src)[2^blue_idx];
            int h, s, v = b;
            int vmin = b, diff;
            int vr, vg;

            CV_CALC_MAX_8U( v, g );
            CV_CALC_MAX_8U( v, r );
            CV_CALC_MIN_8U( vmin, g );
            CV_CALC_MIN_8U( vmin, r );

            diff = v - vmin;
            vr = v == r ? -1 : 0;
            vg = v == g ? -1 : 0;

            s = diff * div_table[v] >> hsv_shift;
            h = (vr & (g - b)) +
                (~vr & ((vg & (b - r + 2 * diff)) + ((~vg) & (r - g + 4 * diff))));
            h = ((h * div_table[diff] * 15 + (1 << (hsv_shift + 6))) >> (7 + hsv_shift))\
                + (h < 0 ? 30*6 : 0);

            dst[i] = (uchar)h;
            dst[i+1] = (uchar)s;
            dst[i+2] = (uchar)v;
        }
    }

    return CV_OK;
#endif
}



/****************************************************************************************\
*                                   The main function                                    *
\****************************************************************************************/
// di el function ally ana 3ayzha hena

CV_IMPL void
cvCvtColor( const CvArr* srcarr, CvArr* dstarr, int code )
{
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    CvSize size;
    int src_step, dst_step;
    int src_cn, dst_cn, depth;
    CvColorCvtFunc0 func0 = 0;
    CvColorCvtFunc1 func1 = 0;
    CvColorCvtFunc2 func2 = 0;
    CvColorCvtFunc3 func3 = 0;
    int param[] = { 0, 0, 0, 0 };
    
    src = cvGetMat( srcarr, &srcstub );
    dst = cvGetMat( dstarr, &dststub );
    
    if( !CV_ARE_SIZES_EQ( src, dst ))
        CV_Error( CV_StsUnmatchedSizes, "" );

    if( !CV_ARE_DEPTHS_EQ( src, dst ))
        CV_Error( CV_StsUnmatchedFormats, "" );

    depth = CV_MAT_DEPTH(src->type);
    if( depth != CV_8U && depth != CV_16U && depth != CV_32F )
        CV_Error( CV_StsUnsupportedFormat, "" );

    src_cn = CV_MAT_CN( src->type );
    dst_cn = CV_MAT_CN( dst->type );
    size = cvGetMatSize( src );
    src_step = src->step;
    dst_step = dst->step;

    if( CV_IS_MAT_CONT(src->type & dst->type) &&
        code != CV_BayerBG2BGR && code != CV_BayerGB2BGR &&
        code != CV_BayerRG2BGR && code != CV_BayerGR2BGR ) 
    {
        size.width *= size.height;
        size.height = 1;
        src_step = dst_step = CV_STUB_STEP;
    }

    switch( code )
    {
    case CV_BGR2BGRA:
    case CV_RGB2BGRA:
        if( src_cn != 3 || dst_cn != 4 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

       /* func1 = depth == CV_8U ? (CvColorCvtFunc1)icvBGR2BGRx_8u_C3C4R :
                depth == CV_16U ? (CvColorCvtFunc1)icvBGR2BGRx_16u_C3C4R :
                depth == CV_32F ? (CvColorCvtFunc1)icvBGR2BGRx_32f_C3C4R : 0;*/
        param[0] = code == CV_BGR2BGRA ? 0 : 2; // blue_idx
        break;

    case CV_BGRA2BGR:
    case CV_RGBA2BGR:
    case CV_RGB2BGR:
        if( (src_cn != 3 && src_cn != 4) || dst_cn != 3 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        //func2 = depth == CV_8U ? (CvColorCvtFunc2)icvBGRx2BGR_8u_CnC3R :
        //        depth == CV_16U ? (CvColorCvtFunc2)icvBGRx2BGR_16u_CnC3R :
        //        depth == CV_32F ? (CvColorCvtFunc2)icvBGRx2BGR_32f_CnC3R : 0;
        param[0] = src_cn;
        param[1] = code == CV_BGRA2BGR ? 0 : 2; // blue_idx
        break;

    case CV_BGRA2RGBA:
        if( src_cn != 4 || dst_cn != 4 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

       /* func0 = depth == CV_8U ? (CvColorCvtFunc0)icvBGRA2RGBA_8u_C4R :
                depth == CV_16U ? (CvColorCvtFunc0)icvBGRA2RGBA_16u_C4R :
                depth == CV_32F ? (CvColorCvtFunc0)icvBGRA2RGBA_32f_C4R : 0;
  */      break;

    case CV_BGR2BGR565:
    case CV_BGR2BGR555:
    case CV_RGB2BGR565:
    case CV_RGB2BGR555:
    case CV_BGRA2BGR565:
    case CV_BGRA2BGR555:
    case CV_RGBA2BGR565:
    case CV_RGBA2BGR555:
        if( (src_cn != 3 && src_cn != 4) || dst_cn != 2 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        if( depth != CV_8U )
            CV_Error( CV_BadDepth,
            "Conversion to/from 16-bit packed RGB format "
            "is only possible for 8-bit images (8-bit grayscale, 888 BGR/RGB or 8888 BGRA/RGBA)" );

    //    func3 = (CvColorCvtFunc3)icvBGRx2BGR5x5_8u_CnC2R;
        param[0] = src_cn;
        param[1] = code == CV_BGR2BGR565 || code == CV_BGR2BGR555 ||
                   code == CV_BGRA2BGR565 || code == CV_BGRA2BGR555 ? 0 : 2; // blue_idx
        param[2] = code == CV_BGR2BGR565 || code == CV_RGB2BGR565 ||
                   code == CV_BGRA2BGR565 || code == CV_RGBA2BGR565 ? 6 : 5; // green_bits
        break;

    case CV_BGR5652BGR:
    case CV_BGR5552BGR:
    case CV_BGR5652RGB:
    case CV_BGR5552RGB:
    case CV_BGR5652BGRA:
    case CV_BGR5552BGRA:
    case CV_BGR5652RGBA:
    case CV_BGR5552RGBA:
        if( src_cn != 2 || (dst_cn != 3 && dst_cn != 4))
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        if( depth != CV_8U )
            CV_Error( CV_BadDepth,
            "Conversion to/from 16-bit packed BGR format "
            "is only possible for 8-bit images (8-bit grayscale, 888 BGR/BGR or 8888 BGRA/BGRA)" );

       // func3 = (CvColorCvtFunc3)icvBGR5x52BGRx_8u_C2CnR;
        param[0] = dst_cn;
        param[1] = code == CV_BGR5652BGR || code == CV_BGR5552BGR ||
                   code == CV_BGR5652BGRA || code == CV_BGR5552BGRA ? 0 : 2; // blue_idx
        param[2] = code == CV_BGR5652BGR || code == CV_BGR5652RGB ||
                   code == CV_BGR5652BGRA || code == CV_BGR5652RGBA ? 6 : 5; // green_bits
        break;

    case CV_BGR2GRAY:
    case CV_BGRA2GRAY:
    case CV_RGB2GRAY:
    case CV_RGBA2GRAY:
        if( (src_cn != 3 && src_cn != 4) || dst_cn != 1 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

      /*  func2 = depth == CV_8U ? (CvColorCvtFunc2)icvBGRx2Gray_8u_CnC1R :
                depth == CV_16U ? (CvColorCvtFunc2)icvBGRx2Gray_16u_CnC1R :
                depth == CV_32F ? (CvColorCvtFunc2)icvBGRx2Gray_32f_CnC1R : 0;*/
        
        param[0] = src_cn;
        param[1] = code == CV_BGR2GRAY || code == CV_BGRA2GRAY ? 0 : 2;
        break;

    case CV_BGR5652GRAY:
    case CV_BGR5552GRAY:
        if( src_cn != 2 || dst_cn != 1 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        if( depth != CV_8U )
            CV_Error( CV_BadDepth,
            "Conversion to/from 16-bit packed BGR format "
            "is only possible for 8-bit images (888 BGR/BGR or 8888 BGRA/BGRA)" );

      //  func2 = (CvColorCvtFunc2)icvBGR5x52Gray_8u_C2C1R;
        
        param[0] = code == CV_BGR5652GRAY ? 6 : 5; // green_bits
        break;

    case CV_GRAY2BGR:
    case CV_GRAY2BGRA:
        if( src_cn != 1 || (dst_cn != 3 && dst_cn != 4))
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        //func1 = depth == CV_8U ? (CvColorCvtFunc1)icvGray2BGRx_8u_C1CnR :
        //        depth == CV_16U ? (CvColorCvtFunc1)icvGray2BGRx_16u_C1CnR :
        //        depth == CV_32F ? (CvColorCvtFunc1)icvGray2BGRx_32f_C1CnR : 0;
        
        param[0] = dst_cn;
        break;

    case CV_GRAY2BGR565:
    case CV_GRAY2BGR555:
        if( src_cn != 1 || dst_cn != 2 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        if( depth != CV_8U )
            CV_Error( CV_BadDepth,
            "Conversion to/from 16-bit packed BGR format "
            "is only possible for 8-bit images (888 BGR/BGR or 8888 BGRA/BGRA)" );

       // func2 = (CvColorCvtFunc2)icvGray2BGR5x5_8u_C1C2R;
        param[0] = code == CV_GRAY2BGR565 ? 6 : 5; // green_bits
        break;

    case CV_BGR2YCrCb:
    case CV_RGB2YCrCb:
    case CV_BGR2XYZ:
    case CV_RGB2XYZ:
    case CV_BGR2HSV:
    case CV_RGB2HSV:
    case CV_BGR2Lab:
    case CV_RGB2Lab:
    case CV_BGR2Luv:
    case CV_RGB2Luv:
    case CV_BGR2HLS:
    case CV_RGB2HLS:
        if( (src_cn != 3 && src_cn != 4) || dst_cn != 3 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        if( depth == CV_8U )
            func2 = //code == CV_BGR2YCrCb || code == CV_RGB2YCrCb ? (CvColorCvtFunc2)icvBGRx2YCrCb_8u_CnC3R :
                    //code == CV_BGR2XYZ || code == CV_RGB2XYZ ? (CvColorCvtFunc2)icvBGRx2XYZ_8u_CnC3R :
                    code == CV_BGR2HSV || code == CV_RGB2HSV ? (CvColorCvtFunc2)icvBGRx2HSV_8u_CnC3R :
                   // code == CV_BGR2Lab || code == CV_RGB2Lab ? (CvColorCvtFunc2)icvBGRx2Lab_8u_CnC3R :
                   // code == CV_BGR2Luv || code == CV_RGB2Luv ? (CvColorCvtFunc2)icvBGRx2Luv_8u_CnC3R :
                    //code == CV_BGR2HLS || code == CV_RGB2HLS ? (CvColorCvtFunc2)icvBGRx2HLS_8u_CnC3R : 
					0;
		/*
        else if( depth == CV_16U )
            func2 = code == CV_BGR2YCrCb || code == CV_RGB2YCrCb ? (CvColorCvtFunc2)icvBGRx2YCrCb_16u_CnC3R :
                    code == CV_BGR2XYZ || code == CV_RGB2XYZ ? (CvColorCvtFunc2)icvBGRx2XYZ_16u_CnC3R : 0;*/
   /*     else if( depth == CV_32F )
            func2 = code == CV_BGR2YCrCb || code == CV_RGB2YCrCb ? (CvColorCvtFunc2)icvBGRx2YCrCb_32f_CnC3R :
                    code == CV_BGR2XYZ || code == CV_RGB2XYZ ? (CvColorCvtFunc2)icvBGRx2XYZ_32f_CnC3R :
                    code == CV_BGR2HSV || code == CV_RGB2HSV ? (CvColorCvtFunc2)icvBGRx2HSV_32f_CnC3R :
                    code == CV_BGR2Lab || code == CV_RGB2Lab ? (CvColorCvtFunc2)icvBGRx2Lab_32f_CnC3R :
                    code == CV_BGR2Luv || code == CV_RGB2Luv ? (CvColorCvtFunc2)icvBGRx2Luv_32f_CnC3R :
                    code == CV_BGR2HLS || code == CV_RGB2HLS ? (CvColorCvtFunc2)icvBGRx2HLS_32f_CnC3R : 0;*/
        
        param[0] = src_cn;
        param[1] = code == CV_BGR2XYZ || code == CV_BGR2YCrCb || code == CV_BGR2HSV ||
                   code == CV_BGR2Lab || code == CV_BGR2Luv || code == CV_BGR2HLS ? 0 : 2;
        break;

    case CV_YCrCb2BGR:
    case CV_YCrCb2RGB:
    case CV_XYZ2BGR:
    case CV_XYZ2RGB:
    case CV_HSV2BGR:
    case CV_HSV2RGB:
    case CV_Lab2BGR:
    case CV_Lab2RGB:
    case CV_Luv2BGR:
    case CV_Luv2RGB:
    case CV_HLS2BGR:
    case CV_HLS2RGB:
        if( src_cn != 3 || (dst_cn != 3 && dst_cn != 4) )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );

        //if( depth == CV_8U )
        //    func2 = code == CV_YCrCb2BGR || code == CV_YCrCb2RGB ? (CvColorCvtFunc2)icvYCrCb2BGRx_8u_C3CnR :
        //            code == CV_XYZ2BGR || code == CV_XYZ2RGB ? (CvColorCvtFunc2)icvXYZ2BGRx_8u_C3CnR :
        //            code == CV_HSV2BGR || code == CV_HSV2RGB ? (CvColorCvtFunc2)icvHSV2BGRx_8u_C3CnR :
        //            code == CV_HLS2BGR || code == CV_HLS2RGB ? (CvColorCvtFunc2)icvHLS2BGRx_8u_C3CnR :
        //            code == CV_Lab2BGR || code == CV_Lab2RGB ? (CvColorCvtFunc2)icvLab2BGRx_8u_C3CnR :
        //            code == CV_Luv2BGR || code == CV_Luv2RGB ? (CvColorCvtFunc2)icvLuv2BGRx_8u_C3CnR : 0;
       /* else if( depth == CV_16U )
            func2 = code == CV_YCrCb2BGR || code == CV_YCrCb2RGB ? (CvColorCvtFunc2)icvYCrCb2BGRx_16u_C3CnR :
                    code == CV_XYZ2BGR || code == CV_XYZ2RGB ? (CvColorCvtFunc2)icvXYZ2BGRx_16u_C3CnR : 0;
        else if( depth == CV_32F )
           func2 = code == CV_YCrCb2BGR || code == CV_YCrCb2RGB ? (CvColorCvtFunc2)icvYCrCb2BGRx_32f_C3CnR :
                    code == CV_XYZ2BGR || code == CV_XYZ2RGB ? (CvColorCvtFunc2)icvXYZ2BGRx_32f_C3CnR :
                    code == CV_HSV2BGR || code == CV_HSV2RGB ? (CvColorCvtFunc2)icvHSV2BGRx_32f_C3CnR :
                    code == CV_HLS2BGR || code == CV_HLS2RGB ? (CvColorCvtFunc2)icvHLS2BGRx_32f_C3CnR :
                    code == CV_Lab2BGR || code == CV_Lab2RGB ? (CvColorCvtFunc2)icvLab2BGRx_32f_C3CnR :
                    code == CV_Luv2BGR || code == CV_Luv2RGB ? (CvColorCvtFunc2)icvLuv2BGRx_32f_C3CnR : 0;*/
        
        param[0] = dst_cn;
        param[1] = code == CV_XYZ2BGR || code == CV_YCrCb2BGR || code == CV_HSV2BGR ||
                   code == CV_Lab2BGR || code == CV_Luv2BGR || code == CV_HLS2BGR ? 0 : 2;
        break;

    case CV_BayerBG2BGR:
    case CV_BayerGB2BGR:
    case CV_BayerRG2BGR:
    case CV_BayerGR2BGR:
        if( src_cn != 1 || dst_cn != 3 )
            CV_Error( CV_BadNumChannels,
            "Incorrect number of channels for this conversion code" );
        
        if( depth != CV_8U )
            CV_Error( CV_BadDepth,
            "Bayer pattern can be converted only to 8-bit 3-channel BGR/RGB image" );

       // func1 = (CvColorCvtFunc1)icvBayer2BGR_8u_C1C3R;
        param[0] = code; // conversion code
        break;
    default:
        CV_Error( CV_StsBadFlag, "Unknown/unsupported color conversion code" );
    }

    if( func0 )
    {
        IPPI_CALL( func0( src->data.ptr, src_step, dst->data.ptr, dst_step, size ));
    }
    else if( func1 )
    {
        IPPI_CALL( func1( src->data.ptr, src_step,
            dst->data.ptr, dst_step, size, param[0] ));
    }
    else if( func2 )
    {
        IPPI_CALL( func2( src->data.ptr, src_step,
            dst->data.ptr, dst_step, size, param[0], param[1] ));
    }
    else if( func3 )
    {
        IPPI_CALL( func3( src->data.ptr, src_step,
            dst->data.ptr, dst_step, size, param[0], param[1], param[2] ));
    }
    else
        CV_Error( CV_StsUnsupportedFormat, "The image format is not supported" );
}


void cv::cvtColor( const Mat& src, Mat& dst, int code, int dst_cn )
{
    switch( code )
    {
    case CV_BGR2BGRA:
    case CV_RGB2BGRA:
    case CV_BGRA2RGBA:
    case CV_BGR5652BGRA:
    case CV_BGR5552BGRA:
    case CV_BGR5652RGBA:
    case CV_BGR5552RGBA:
    case CV_GRAY2BGRA:
        dst_cn = 4;
        break;

    case CV_BGR2YCrCb:
    case CV_RGB2YCrCb:
    case CV_BGR2XYZ:
    case CV_RGB2XYZ:
    case CV_BGR2HSV:
    case CV_RGB2HSV:
    case CV_BGR2Lab:
    case CV_RGB2Lab:
    case CV_BGR2Luv:
    case CV_RGB2Luv:
    case CV_BGR2HLS:
    case CV_RGB2HLS:
        dst_cn = 3;
        break;

    case CV_BayerBG2BGR:
    case CV_BayerGB2BGR:
    case CV_BayerRG2BGR:
    case CV_BayerGR2BGR:

    case CV_BGRA2BGR:
    case CV_RGBA2BGR:
    case CV_RGB2BGR:
    case CV_BGR5652BGR:
    case CV_BGR5552BGR:
    case CV_BGR5652RGB:
    case CV_BGR5552RGB:
    case CV_GRAY2BGR:
        
    case CV_YCrCb2BGR:
    case CV_YCrCb2RGB:
    case CV_XYZ2BGR:
    case CV_XYZ2RGB:
    case CV_HSV2BGR:
    case CV_HSV2RGB:
    case CV_Lab2BGR:
    case CV_Lab2RGB:
    case CV_Luv2BGR:
    case CV_Luv2RGB:
    case CV_HLS2BGR:
    case CV_HLS2RGB:
        if( dst_cn != 4 )
            dst_cn = 3;
        break;

    case CV_BGR2BGR565:
    case CV_BGR2BGR555:
    case CV_RGB2BGR565:
    case CV_RGB2BGR555:
    case CV_BGRA2BGR565:
    case CV_BGRA2BGR555:
    case CV_RGBA2BGR565:
    case CV_RGBA2BGR555:
    case CV_GRAY2BGR565:
    case CV_GRAY2BGR555:
        dst_cn = 2;
        break;

    case CV_BGR2GRAY:
    case CV_BGRA2GRAY:
    case CV_RGB2GRAY:
    case CV_RGBA2GRAY:
    case CV_BGR5652GRAY:
    case CV_BGR5552GRAY:
        dst_cn = 1;
        break;
    default:
        CV_Error( CV_StsBadFlag, "Unknown/unsupported color conversion code" );
    }
    
    dst.create(src.size(), CV_MAKETYPE(src.depth(), dst_cn));
    CvMat _src = src, _dst = dst;
    cvCvtColor( &_src, &_dst, code );
}

/* End of file. */


