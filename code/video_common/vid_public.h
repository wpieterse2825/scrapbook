typedef struct video_export_s {
    void (*Create)(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y);
    void (*Destroy)(SDL_Window* window);

    void (*BeginFrame)();
    void (*EndFrame)();
} video_export_t;

void Video_Start();
void Video_Stop();

void Video_BeginFrame();
void Video_EndFrame();
