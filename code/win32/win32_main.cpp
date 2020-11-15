#include <windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "platform_options.h"
#include "platform.h"

#include "win32_error.cpp"
#include "win32_input.cpp"
#include "win32_opengl.cpp"
#include "win32_timer.cpp"
#include "win32_file_io.cpp"

#include "app.cpp"

int CALLBACK WinMain(HINSTANCE h_instance,
                     HINSTANCE h_prev_instance,
                     LPSTR     lp_cmd_line,
                     int       n_show_cmd)
{
    /* Win32 Window Initialisation */
    WNDCLASS wc = {};
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Win32WindowProcedure; //handle to event procedure
    wc.hInstance = h_instance; //handle to app instance
    wc.lpszClassName = PROGRAM_TITLE " Class"; //window class name
    wc.hCursor = LoadCursorA(h_instance, IDC_ARROW);
    
    RegisterClass(&wc); //registers window class with OS
    
    RECT window_rect = {0, 0, PROGRAM_WIDTH, PROGRAM_HEIGHT};
    AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, false);
    i32 desired_width = window_rect.right - window_rect.left;
    i32 desired_height = window_rect.bottom - window_rect.top;
    
    HWND hwnd = CreateWindowEx(0,                              // Optional window styles.
                               wc.lpszClassName,               // Window class
                               PROGRAM_TITLE,                  // Window text
                               WS_OVERLAPPEDWINDOW,            // Window style
                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, desired_width, desired_height,
                               NULL,       // Parent window
                               NULL,       // Menu
                               h_instance, // Instance handle
                               NULL);        // Additional application data
    if(hwnd == NULL){
        OutputDebugString("Failed to create window.\n");
        return 0;
    }
    
    ShowWindow(hwnd, n_show_cmd);
    
    MSG msg = {}; //message struct for events
    POINT cursor_pos = {};
    /* ------------------------- */
    
    /* Win32 OpenGL Context Initialisation */
#if RENDERER_OPENGL == 1
    if(!Win32InitOpenGL(&hwnd)){
        OutputDebugString("Failed to initialise OpenGL.\n");
        return 1;
    }
    Win32SetVSync(1);
#endif
    /* ------------------------- */
    
    
    /* Platform Code Initialisation */
    platform.should_quit = 0;
    platform.is_initialised = 0;
    platform.target_fps = 60.0f;
    
    platform.permanent_memory_size = PERMANENT_MEMORY_SIZE;
    platform.permanent_memory = VirtualAlloc(0, platform.permanent_memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    
    platform.frame_memory_size = FRAME_MEMORY_SIZE;
    platform.frame_memory = VirtualAlloc(0, platform.frame_memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    
    platform.PlatformReadEntireFileToString = Win32ReadEntireFileToString;
    platform.PlatformFreeFile = Win32FreeFile;
    platform.PlatformWriteToFile = Win32WriteToFile;
    
    platform.PlatformDisplayError = Win32DisplayError;
    /* ------------------------ */
    
    /* Win32 Timer Initialisation*/
    Win32Timer timer = {};
    Win32TimerInit(&timer);
    /* ------------------------- */
    
    while(!platform.should_quit){
        Win32TimerBegin(&timer);
        /* Process events */
        while(PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Win32UpdateWindowDimension(hwnd, &platform);
        Win32UpdateScreenCursor(hwnd, cursor_pos, &platform);
        //App code runs here
        UpdateApp(&platform);
        Win32OpenGLSwapBuffers();
        Win32TimerEnd(&timer, platform);
        /*platform.current_time += 1.f / platform.target_fps;
        platform.ms_per_frame = timer.ms_per_frame;*/
    }
    
    Win32OpenGLCleanUp();
    
    return 0;
}