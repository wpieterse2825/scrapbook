typedef struct plane_s {
    double normal_x;
    double normal_y;
    double normal_z;
    double distance;
} plane_t;

typedef struct texture_matrix_s {
    double u_offset_x;
    double u_offset_y;
    double u_offset_z;

    double v_offset_x;
    double v_offset_y;
    double v_offset_z;
} texture_matrix_t;

typedef struct primitive_brush_side_s {
    const char*      material;
    plane_t          plane;
    texture_matrix_t texture_matrix;
} primitive_brush_side_t;

typedef struct primitive_brush_s {
    size_t sides_count;

    primitive_brush_side_t* sides;
} primitive_brush_t;

typedef struct primitive_patch_s {
    const char* material;
    bool        explicitly_subdivided;
    int32_t     subdivision_horizontal;
    int32_t     subdivision_vertical;
} primitive_patch_t;

typedef struct entity_key_value_s {
    const char* key;
    const char* value;
} entity_key_value_t;

typedef struct entity_s {
    size_t configuration_count;
    size_t primitive_brushes_count;
    size_t primitive_patches_count;

    entity_key_value_t* configuration;
    primitive_brush_t*  primitive_brushes;
    primitive_patch_t*  primitive_patches;
} entity_t;

typedef struct map_s {
    const char* name;

    size_t    entity_count;
    entity_t* entities;
} map_t;

#if defined(__cplusplus)
extern "C" {
#endif

void ProcessMap(map_t* map_object);

#if defined(__cplusplus)
}
#endif
