
#include "hi_egl.h"

EGLDisplay g_EglDisplay;

NativeDisplayType g_NativeDisplay;
NativeWindowType g_NativeWindow;


HI_S32 main(HI_S32 argc, HI_CHAR ** argv)
{
    g_NativeDisplay = EGL_DEFAULT_DISPLAY; //(NativeDisplayType)nativeCreateDisplay();
    if (g_NativeDisplay < 0)
    {
        printf("nativeCreateDisplay failed!\n");
        return -1;
    }

#if 0
    g_NativeWindow = nativeCreateWindow("egl window", 1280, 720, 0);
#else
    fbdev_window *fbwin = malloc( sizeof(fbdev_window));
    if (NULL == fbwin)
    {
        return 0;
    }
    fbwin->width  = 1280;
    fbwin->height = 720;
    g_NativeWindow = fbwin;
#endif

	eglBindAPI(EGL_OPENGL_ES_API);

	g_EglDisplay = eglGetDisplay(g_NativeDisplay);

    if (g_EglDisplay == EGL_NO_DISPLAY)
    {
        printf("g_EglDisplay == EGL_NO_DISPLAY\n");
        return HI_FAILURE;
    }

    if (!eglInitialize(g_EglDisplay, NULL, NULL))
    {
        printf("eglInitialize failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
