

#include "hi_adp.h"
#include "hi_adp_hdmi.h"


HI_S32 main(HI_VOID)
{
	HI_S32                      Ret;
    HI_CHAR aszInputCmd[16];

    Ret = HIADP_HDMI_Init(HI_UNF_HDMI_ID_0);
    if (HI_SUCCESS != Ret)
    {
        printf("HIADP_HDMI_Init failed 0x%x\n", Ret);
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


    return 0;
}

