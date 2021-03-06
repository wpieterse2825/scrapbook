typedef struct video_export_s {
    bool (*Create)(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y);
    void (*Destroy)(SDL_Window* window);

    void (*BeginFrame)(void);
    void (*EndFrame)(void);
} video_export_t;

void Video_Start(void);
void Video_Stop(void);

void Video_BeginFrame(void);
void Video_EndFrame(void);
