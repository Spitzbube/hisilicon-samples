/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name       : sample_decmp_fb.c
Version         : Initial Draft
Author          :
Created         : 2015/11/07
Description     : 测试解压功能
Function List   :


History         :
Date                Author              Modification
2015/11/07          y00181162           Created file
******************************************************************************/

/****************************  add include here     ***************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <assert.h>
#include "hifb.h"
#include "hi_unf_disp.h"
#include "hi_adp_data.h"
#include "hi_adp_mpi.h"

/***************************** Macro Definition     ***************************/
#ifndef CONFIG_SUPPORT_CA_RELEASE
#define HIFB_TRACE  printf
#else
#define HIFB_TRACE(x...)
#endif

#if 1
#define DECMP_WIDTH     1280
#define DECMP_HEIGHT    720
#define DENCMP_WIDTH    DECMP_WIDTH
#define DENCMP_HEIGHT   DECMP_HEIGHT
#if defined(CHIP_TYPE_hi3798cv200)
#define DECMP_STRIDE    6656
#define DECMP_FILE      "../res/test_720p.cmp"
#define DENCMP_STRIDE   (DECMP_WIDTH * 4)
#define DENCMP_FILE     "../res/test_720p.ncmp"
#else
#define DECMP_STRIDE    2816
#define DECMP_FILE      "../res/test_normal_stride_720p.cmp"
#define DENCMP_STRIDE   (DECMP_WIDTH * 4)
#define DENCMP_FILE     "../res/test_normal_stride_720p.ncmp"
#endif
#else
#define DECMP_WIDTH     1920
#define DECMP_HEIGHT    1080
#define DENCMP_WIDTH    DECMP_WIDTH
#define DENCMP_HEIGHT   DECMP_HEIGHT
#if defined(CHIP_TYPE_hi3798cv200)
#define DECMP_STRIDE    9984
#define DECMP_FILE      "../res/test_1080p.cmp"
#define DENCMP_STRIDE   (DECMP_WIDTH * 4)
#define DENCMP_FILE     "../res/test_1080p.ncmp"
#else
#define DECMP_STRIDE    3840
#define DECMP_FILE      "../res/test_normal_stride_1080p.cmp"
#define DENCMP_STRIDE   (DECMP_WIDTH * 4)
#define DENCMP_FILE     "../res/test_normal_stride_1080p.ncmp"
#endif
#endif

/***************************** Structure Definition ***************************/

/********************** Global Variable declaration **************************/
static struct fb_var_screeninfo ghifb_st_argb8888_def_vinfo =
{
    DECMP_WIDTH,DECMP_HEIGHT,DECMP_WIDTH,DECMP_HEIGHT,0,0,
    32,
    0,
    {16, 8, 0},
    { 8, 8, 0},
    { 0, 8, 0},
    {24, 8, 0},
    0,
    FB_ACTIVATE_FORCE,0,0,0,-1,-1,-1,-1,-1,-1,-1,
};

/********************** API forward declarations    **************************/

/****************************************************************************
* func          : print_vinfo
* description   : CNcomment: 打印可变信息 CNend\n
* param[in]     : NA
* retval        : NA
* others:       : NA
******************************************************************************/
static void print_vinfo(struct fb_var_screeninfo *vinfo)
{
    HIFB_TRACE("\n=======================================================================\n");
    HIFB_TRACE( "Printing var info:\n");
    HIFB_TRACE( "txres           : %d\n", vinfo->xres);
    HIFB_TRACE( "tyres           : %d\n", vinfo->yres);
    HIFB_TRACE( "txres_virtual   : %d\n", vinfo->xres_virtual);
    HIFB_TRACE( "tyres_virtual   : %d\n", vinfo->yres_virtual);
    HIFB_TRACE( "txoffset        : %d\n", vinfo->xoffset);
    HIFB_TRACE( "tyoffset        : %d\n", vinfo->yoffset);
    HIFB_TRACE( "tbits_per_pixel : %d\n", vinfo->bits_per_pixel);
    HIFB_TRACE( "tgrayscale      : %d\n", vinfo->grayscale);
    HIFB_TRACE( "tnonstd         : %d\n", vinfo->nonstd);
    HIFB_TRACE( "tactivate       : %d\n", vinfo->activate);
    HIFB_TRACE( "theight         : %d\n", vinfo->height);
    HIFB_TRACE( "twidth          : %d\n", vinfo->width);
    HIFB_TRACE( "taccel_flags    : %d\n", vinfo->accel_flags);
    HIFB_TRACE( "tpixclock       : %d\n", vinfo->pixclock);
    HIFB_TRACE( "tleft_margin    : %d\n", vinfo->left_margin);
    HIFB_TRACE( "tright_margin   : %d\n", vinfo->right_margin);
    HIFB_TRACE( "tupper_margin   : %d\n", vinfo->upper_margin);
    HIFB_TRACE( "tlower_margin   : %d\n", vinfo->lower_margin);
    HIFB_TRACE( "thsync_len      : %d\n", vinfo->hsync_len);
    HIFB_TRACE( "tvsync_len      : %d\n", vinfo->vsync_len);
    HIFB_TRACE( "tsync           : %d\n", vinfo->sync);
    HIFB_TRACE( "tvmode          : %d\n", vinfo->vmode);
    HIFB_TRACE( "tred            : %d/%d\n", vinfo->red.length, vinfo->red.offset);
    HIFB_TRACE( "tgreen          : %d/%d\n", vinfo->green.length, vinfo->green.offset);
    HIFB_TRACE( "tblue           : %d/%d\n", vinfo->blue.length, vinfo->blue.offset);
    HIFB_TRACE( "talpha          : %d/%d\n", vinfo->transp.length, vinfo->transp.offset);
    HIFB_TRACE("=======================================================================\n");
}

static void print_finfo(struct fb_fix_screeninfo *finfo)
{
    HIFB_TRACE("\n=======================================================================\n");
    HIFB_TRACE( "Printing finfo  :\n");
    HIFB_TRACE( "tsmem_start     : %p\n", (char *)finfo->smem_start);
    HIFB_TRACE( "tsmem_len       : %d\n", finfo->smem_len);
    HIFB_TRACE( "ttype           : %d\n", finfo->type);
    HIFB_TRACE( "ttype_aux       : %d\n", finfo->type_aux);
    HIFB_TRACE( "tvisual         : %d\n", finfo->visual);
    HIFB_TRACE( "txpanstep       : %d\n", finfo->xpanstep);
    HIFB_TRACE( "typanstep       : %d\n", finfo->ypanstep);
    HIFB_TRACE( "tywrapstep      : %d\n", finfo->ywrapstep);
    HIFB_TRACE( "tline_length    : %d\n", finfo->line_length);
    HIFB_TRACE( "tmmio_start     : %p\n", (char *)finfo->mmio_start);
    HIFB_TRACE( "tmmio_len       : %d\n", finfo->mmio_len);
    HIFB_TRACE( "taccel          : %d\n", finfo->accel);
    HIFB_TRACE("=======================================================================\n");
}
/*****************************************************************************
* func          : test_dec_show
* description   : CNcomment: 显示解码数据  CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
*****************************************************************************/
static inline HI_S32 test_data_show(HI_U32 u32Width,HI_U32 u32Height,HI_U32 u32Stride,HI_BOOL bDecmp,HI_U32 u32PhyStreamBuf)
{

        HI_S32 s32Ret = 0;
        struct fb_fix_screeninfo finfo;
        struct fb_var_screeninfo vinfo;
        HIFB_ALPHA_S stAlpha;
        HIFB_LAYER_INFO_S layerinfo;
        HIFB_BUFFER_S CanvasBuf;
        int console_fd;
        const char* file = "/dev/fb0";
        HI_U32 u32SmemStartPhy = 0;
        HIFB_HWC_LAYERINFO_S stHwcLayerInfo;
        
        console_fd = open(file, O_RDWR, 0);
        if(console_fd < 0){
            HIFB_TRACE("Unable to open %s\n", file);
            return (-1);
        }

        if (ioctl(console_fd, FBIOGET_SMEMSTART_PHY, &u32SmemStartPhy) < 0){
            HIFB_TRACE("Unable to set variable screeninfo!\n");
            s32Ret = HI_FAILURE;
            goto CLOSEFD;
        }

        if (ioctl(console_fd, FBIOPUT_VSCREENINFO, &ghifb_st_argb8888_def_vinfo) < 0){
            HIFB_TRACE("Unable to set variable screeninfo!\n");
            s32Ret = HI_FAILURE;
            goto CLOSEFD;
        }

        if(ioctl(console_fd, FBIOGET_FSCREENINFO, &finfo) < 0){
            HIFB_TRACE("Couldn't get console hardware info\n");
            s32Ret = HI_FAILURE;
            goto CLOSEFD;
        }
        HIFB_TRACE("\n=====================================================\n");
        HIFB_TRACE("u32SmemStartPhy  = 0x%x\n",u32SmemStartPhy);
        HIFB_TRACE("finfo.smem_start = 0x%lx\n",finfo.smem_start);
        HIFB_TRACE("=====================================================\n");

        print_finfo(&finfo);

        if (ioctl(console_fd, FBIOGET_VSCREENINFO, &vinfo) < 0){
            HIFB_TRACE("Couldn't get console pixel format\n");
            s32Ret = HI_FAILURE;
            goto CLOSEFD;
        }
        print_vinfo(&vinfo);


        stAlpha.bAlphaEnable  = HI_TRUE;
        stAlpha.bAlphaChannel = HI_FALSE;
        stAlpha.u8Alpha0      = 0xff;
        stAlpha.u8Alpha1      = 0xff;
        if(ioctl(console_fd, FBIOPUT_ALPHA_HIFB, &stAlpha) < 0){
            HIFB_TRACE("Couldn't set alpha\n");
            s32Ret = HI_FAILURE;
            goto CLOSEFD;
        }

        memset(&stHwcLayerInfo,0x0,sizeof(stHwcLayerInfo));
        stHwcLayerInfo.eFmt = HIFB_FMT_ARGB8888;
        ioctl(console_fd,FBIO_HWC_GETLAYERINFO,&stHwcLayerInfo);
        //HIFB_TRACE("\n===================================================\n");
        //HIFB_TRACE("cmpstride = %d nocmpstride = %d\n",stHwcLayerInfo.u32Stride,stHwcLayerInfo.NoCmpStride);
        //HIFB_TRACE("===================================================\n");
        
        ioctl(console_fd,FBIOPUT_DECOMPRESS_HIFB,&bDecmp);

        layerinfo.u32Mask           = 0;
        layerinfo.eAntiflickerLevel = HIFB_LAYER_ANTIFLICKER_HIGH;
        layerinfo.BufMode           = HIFB_LAYER_BUF_NONE;
        layerinfo.u32CanvasWidth    = vinfo.xres;
        layerinfo.u32CanvasHeight   = vinfo.yres;
        layerinfo.u32Mask |= HIFB_LAYERMASK_BUFMODE;
        layerinfo.u32Mask |= HIFB_LAYERMASK_ANTIFLICKER_MODE;
        layerinfo.u32Mask |= HIFB_LAYERMASK_CANVASSIZE;

        if (ioctl(console_fd, FBIOPUT_LAYER_INFO, &layerinfo) < 0){
            HIFB_TRACE("put layer info failed!\n");
            goto CLOSEFD;
        }
        if(ioctl(console_fd, FBIOGET_CANVAS_BUFFER, &CanvasBuf) < 0){
            HIFB_TRACE("get canvas buffer failed\n");
            goto CLOSEFD;
        }

        CanvasBuf.stCanvas.u32PhyAddr =  u32PhyStreamBuf;
        CanvasBuf.stCanvas.u32Width   =  u32Width;
        CanvasBuf.stCanvas.u32Height  =  u32Height;
        CanvasBuf.stCanvas.u32Pitch   =  u32Stride;
        CanvasBuf.stCanvas.enFmt      =  HIFB_FMT_ARGB8888;
        CanvasBuf.UpdateRect.x = 0;
        CanvasBuf.UpdateRect.y = 0;
        CanvasBuf.UpdateRect.w = CanvasBuf.stCanvas.u32Width;
        CanvasBuf.UpdateRect.h = CanvasBuf.stCanvas.u32Height;
        if(ioctl(console_fd, FBIO_REFRESH, &CanvasBuf) < 0){
            HIFB_TRACE("refresh buffer info failed!\n");
            goto CLOSEFD;
        }

        sleep(1);

        getchar();

    CLOSEFD:
        if(console_fd > 0)
        {
            close(console_fd);
        }
        return s32Ret;

}

/*****************************************************************************
* func          : Display_Init
* description   : VO初始化
* param[in]     :
* retval        : NA
* others:       : NA
*****************************************************************************/
static inline HI_S32 Display_Init()
{
    HI_SYS_Init();
    HIADP_Disp_Init(HI_UNF_ENC_FMT_720P_50);
    return HI_SUCCESS;
}
/*****************************************************************************
* func          : Display_DeInit
* description   : VO去初始化
* param[in]     :
* retval        : NA
* others:       : NA
*****************************************************************************/
static inline HI_S32 Display_DeInit()
{
    HIADP_Disp_DeInit();
    HI_SYS_DeInit();
    return  0;
}

int main(int argc, char* argv[])
{
    HI_S32 s32Ret    = HI_SUCCESS;
    HI_U32 u32Width  = DECMP_WIDTH;
    HI_U32 u32Height = DECMP_HEIGHT;
    HI_U32 u32Stride = 0;
    HI_U32 u32Size   = 0;
    HI_U32 u32PhyStreamBuf  = 0;
    HI_CHAR* pVirStreamBuf  = NULL;
    FILE* pInFile           = NULL;
    HI_U64 u64ReadFileSize  = 0;

    Display_Init();
    s32Ret = HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, DECMP_WIDTH, DECMP_HEIGHT);
    if(s32Ret != HI_SUCCESS){
        goto HIFB_RETURN;
    }
    sleep(1);

#ifdef HI_FB_DECOMPRESS_SUPPORT
    /**
     **decompress data
     **/
    u32Stride = DECMP_STRIDE;
  #if defined(CHIP_TYPE_hi3798cv200)
    u32Size = u32Stride * u32Height;
  #else
    u32Size = ((16 * u32Height + 0xff) & 0xffffff00) * 2 + (u32Stride * u32Height) * 2;
  #endif
    pInFile = fopen(DECMP_FILE,"rb");
    if(NULL == pInFile){
       HIFB_TRACE("open jpeg file failure");
       goto HIFB_RETURN;
    }

    u32PhyStreamBuf = (unsigned long)HI_MMZ_New(u32Size,16,NULL,"sample_fb");
    if(0 == u32PhyStreamBuf){
        HIFB_TRACE("HI_MMZ_New stream buffer failure\n");
        goto HIFB_RETURN;
    }
    pVirStreamBuf = (HI_CHAR*)HI_MMZ_Map(u32PhyStreamBuf,HI_FALSE);
    if(NULL == pVirStreamBuf){
        HIFB_TRACE("HI_MMZ_Map stream buffer failure\n");
        goto HIFB_RETURN;
    }

    u64ReadFileSize = fread(pVirStreamBuf,1,u32Size,pInFile);
    if(u64ReadFileSize != u32Size){
        HIFB_TRACE("=== %s : %s :%d fread failure \n",__FILE__,__FUNCTION__,__LINE__);
        goto HIFB_RETURN;
    }

    HIFB_TRACE("\n=================================================================================\n");
    HIFB_TRACE("width = %d height = %d stride = %d size = %d\n",u32Width,u32Height,u32Stride,u32Size);
    HIFB_TRACE("file  = %s u32PhyStreamBuf = 0x%x\n",DECMP_FILE,u32PhyStreamBuf);
    HIFB_TRACE("=================================================================================\n");

    s32Ret = test_data_show(u32Width,u32Height,u32Stride,HI_TRUE,u32PhyStreamBuf);
    if(HI_SUCCESS != s32Ret){
        HIFB_TRACE("show data failure\n");
        goto HIFB_RETURN;
    }

    if(NULL != pInFile){
        fclose(pInFile);
        pInFile = NULL;
    }
    if(NULL != pVirStreamBuf){
        HI_MMZ_Unmap(u32PhyStreamBuf);
        pVirStreamBuf = NULL;
    }
    if(0 != u32PhyStreamBuf){
        HI_MMZ_Delete(u32PhyStreamBuf);
        u32PhyStreamBuf = 0;
    }
#endif
    /**
     **no decompress data
     **/
    u32Stride = DENCMP_STRIDE;
    u32Size = u32Stride * u32Height;

    pInFile = fopen(DENCMP_FILE,"rb");
    if(NULL == pInFile){
       HIFB_TRACE("open jpeg file failure");
       goto HIFB_RETURN;
    }

    u32PhyStreamBuf = (unsigned long)HI_MMZ_New(u32Size,16,NULL,"sample_fb");
    if(0 == u32PhyStreamBuf){
        HIFB_TRACE("HI_MMZ_New stream buffer failure\n");
        goto HIFB_RETURN;
    }
    pVirStreamBuf = (HI_CHAR*)HI_MMZ_Map(u32PhyStreamBuf,HI_FALSE);
    if(NULL == pVirStreamBuf){
        HIFB_TRACE("HI_MMZ_Map stream buffer failure\n");
        goto HIFB_RETURN;
    }

    u64ReadFileSize = fread(pVirStreamBuf,1,u32Size,pInFile);
    if(u64ReadFileSize != u32Size){
        HIFB_TRACE("=== %s : %s :%d fread failure \n",__FILE__,__FUNCTION__,__LINE__);
        goto HIFB_RETURN;
    }

    HIFB_TRACE("\n=================================================================================\n");
    HIFB_TRACE("width = %d height = %d stride = %d size = %d\n",u32Width,u32Height,u32Stride,u32Size);
    HIFB_TRACE("file  = %s u32PhyStreamBuf = 0x%x\n",DENCMP_FILE,u32PhyStreamBuf);
    HIFB_TRACE("=================================================================================\n");

    s32Ret = test_data_show(u32Width,u32Height,u32Stride,HI_FALSE,u32PhyStreamBuf);
    if(HI_SUCCESS != s32Ret){
        HIFB_TRACE("show data failure\n");
        goto HIFB_RETURN;
    }

HIFB_RETURN:
    if(NULL != pInFile){
        fclose(pInFile);
        pInFile = NULL;
    }
    if(NULL != pVirStreamBuf){
        HI_MMZ_Unmap(u32PhyStreamBuf);
        pVirStreamBuf = NULL;
    }
    if(0 != u32PhyStreamBuf){
        HI_MMZ_Delete(u32PhyStreamBuf);
        u32PhyStreamBuf = 0;
    }

    Display_DeInit();

    return 0;
}
