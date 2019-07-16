

#include "hi_adp.h"
#include "hi_adp_hdmi.h"


HI_S32 main(HI_VOID)
{
	HI_S32                      Ret;
    HI_CHAR aszInputCmd[16];

    Ret = HIADP_Disp_Init(HI_UNF_ENC_FMT_720P_50);
    if (HI_SUCCESS != Ret)
    {
        printf("HIADP_Disp_Init failed 0x%x\n", Ret);
        return Ret;
    }

    while (1)
    {
        SAMPLE_GET_INPUTCMD(aszInputCmd);
        if ('q' == aszInputCmd[0])
        {
            break;
        }

        sleep(1);
    }

    HIADP_Disp_DeInit();

    return 0;
}

