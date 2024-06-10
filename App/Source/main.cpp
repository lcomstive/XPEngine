#include <Engine/API.hpp>
#include <stdio.h>

#if !defined(ENGINE_PLATFORM_APPLE)
#define SOKOL_IMPL
#endif

#include <sokol_gfx.h>
#include <sokol_app.h>
#include <sokol_log.h>
#include <sokol_glue.h>
#include <sokol_fetch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma region Shaders
#include <Shaders/texturedCube.h>
#pragma endregion

static struct
{
	float rx, ry;

	sg_pipeline pipeline;
	sg_bindings bindings;
	sg_pass_action pass_action;

	uint8_t file_buffer[256 * 1024 * 1024];
} state;

typedef struct
{
	float x, y, z;
	uint16_t u, v;
} vertex_t;

static void fetch_callback(const sfetch_response_t*);

const vertex_t vertices[] = {
	// pos                  uvs
	{ -1.0f, -1.0f, -1.0f,      0,     0 },
	{  1.0f, -1.0f, -1.0f,  65534,     0 },
	{  1.0f,  1.0f, -1.0f,  65534, 65534 },
	{ -1.0f,  1.0f, -1.0f,      0, 65534 },

	{ -1.0f, -1.0f,  1.0f,      0,     0 },
	{  1.0f, -1.0f,  1.0f,  65534,     0 },
	{  1.0f,  1.0f,  1.0f,  65534, 65534 },
	{ -1.0f,  1.0f,  1.0f,      0, 65534 },

	{ -1.0f, -1.0f, -1.0f,      0,     0 },
	{ -1.0f,  1.0f, -1.0f,  65534,     0 },
	{ -1.0f,  1.0f,  1.0f,  65534, 65534 },
	{ -1.0f, -1.0f,  1.0f,      0, 65534 },

	{  1.0f, -1.0f, -1.0f,      0,     0 },
	{  1.0f,  1.0f, -1.0f,  65534,     0 },
	{  1.0f,  1.0f,  1.0f,  65534, 65534 },
	{  1.0f, -1.0f,  1.0f,      0, 65534 },

	{ -1.0f, -1.0f, -1.0f,      0,     0 },
	{ -1.0f, -1.0f,  1.0f,  65534,     0 },
	{  1.0f, -1.0f,  1.0f,  65534, 65534 },
	{  1.0f, -1.0f, -1.0f,      0, 65534 },

	{ -1.0f,  1.0f, -1.0f,      0,     0 },
	{ -1.0f,  1.0f,  1.0f,  65534,     0 },
	{  1.0f,  1.0f,  1.0f,  65534, 65534 },
	{  1.0f,  1.0f, -1.0f,      0, 65534 },
};

const uint16_t indices[] = {
	0, 1, 2,		0, 2, 3,
	6, 5, 4,		7, 6, 4,
	8, 9, 10,		8, 10, 11,
	14, 13, 12,		15, 14, 12,
	16, 17, 18,		16, 18, 19,
	22, 21, 20,		23, 22, 20
};

static void init()
{
	sg_desc desc =
	{
		.logger = { .func = slog_func },
		.environment = sglue_environment()
	};
	sg_setup(&desc);

	sfetch_desc_t sfetchDesc =
	{
		.max_requests = 1,
		.num_channels = 1,
		.num_lanes = 1,
		.logger = { .func = slog_func }
	};
	sfetch_setup(sfetchDesc);

	// Allocate image handle, but don't initialise yet.
	// File loading through sfetch is asynchronous,
	// image will be assigned when sfetch request completes
	state.bindings.fs.images[SLOT_TexturedCube_tex] = sg_alloc_image();

	sg_sampler_desc samplerDesc = { .min_filter = SG_FILTER_LINEAR, .mag_filter = SG_FILTER_LINEAR };
	state.bindings.fs.samplers[SLOT_TexturedCube_smp] = sg_make_sampler(samplerDesc);

	// Vertex buffer
	sg_buffer_desc vertDesc =
	{
		.data = SG_RANGE(vertices),
		.label = "cube-vertices"
	};
	state.bindings.vertex_buffers[0] = sg_make_buffer(&vertDesc);

	// Index buffer
	sg_buffer_desc indexDesc =
	{
		.type = SG_BUFFERTYPE_INDEXBUFFER,
		.data = SG_RANGE(indices),
		.label = "cube-indices"
	};
	state.bindings.index_buffer = sg_make_buffer(&indexDesc);

	sg_pipeline_desc pipelineDesc = {
		.shader = sg_make_shader(TexturedCube_program_shader_desc(sg_query_backend())),
		.depth = { .compare = SG_COMPAREFUNC_LESS_EQUAL, .write_enabled = true },
		.index_type = SG_INDEXTYPE_UINT16,
		.cull_mode = SG_CULLMODE_BACK,
		.label = "textured-cube-pipeline"
	};
	pipelineDesc.layout.attrs[ATTR_TexturedCube_vs_inPosition].format = SG_VERTEXFORMAT_FLOAT3;
	pipelineDesc.layout.attrs[ATTR_TexturedCube_vs_inTexCoords].format = SG_VERTEXFORMAT_USHORT2N;
	state.pipeline = sg_make_pipeline(&pipelineDesc);

	state.pass_action.colors[0] = {
		.load_action = SG_LOADACTION_CLEAR,
		.clear_value = { 0.0f, 0.0f, 0.0f, 1.0f }
	};

	// Request texture
	sfetch_request_t fetchRequest =
	{
		.path = "Assets/Textures/jano.jpg",
		.callback = fetch_callback,
		.buffer = SFETCH_RANGE(state.file_buffer)
	};
	sfetch_send(fetchRequest);
}

static void frame()
{
	sfetch_dowork();

	// Calculate MVP
	const float t = sapp_frame_duration();
	glm::mat4 proj = glm::perspective(45.0f, sapp_widthf() / sapp_heightf(), 0.01f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 1.75f, 5.f), glm::vec3(), glm::vec3(0, 1, 0));

	TexturedCube_vs_params_t params;
	state.rx += 1 * t; state.ry += 2 * t;
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), state.rx, glm::vec3(0, 1, 0));
	model = glm::rotate(model, state.ry, glm::vec3(1, 0, 0));
	params.mvp = proj * view * model;

	// Render
	sg_pass pass = { .action = state.pass_action, .swapchain = sglue_swapchain() };
	sg_begin_pass(&pass);
	sg_apply_pipeline(state.pipeline);
	sg_apply_bindings(&state.bindings);

	sg_range paramsRange = SG_RANGE(params);
	sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_TexturedCube_vs_params, &paramsRange);

	sg_draw(0, 36, 1);

	sg_end_pass();
	sg_commit();
}

static void cleanup()
{
	sfetch_shutdown();
	sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[])
{
	return sapp_desc
	{
		.init_cb = init,
		.frame_cb = frame,
		.cleanup_cb = cleanup,
		.width = 1600,
		.height = 900,
		.window_title = "XP App",
		.icon = { .sokol_default = true },
		.logger = { .func = slog_func }
	};
}

static void fetch_callback(const sfetch_response_t* response)
{
	if (response->failed)
	{
		// Failed to load, set clear colour to red
		state.pass_action.colors[0].clear_value = { 1, 0, 0, 1 };
		return;
	}

	int width, height, channels;
	const int desiredChannels = 4;

	stbi_uc* pixels = stbi_load_from_memory(
		(const stbi_uc*)response->data.ptr,
		(int)response->data.size,
		&width, &height, &channels,
		desiredChannels
	);

	if (!pixels)
		return;

	// Initialise texture
	sg_image_desc desc =
	{
		.width = width,
		.height = height,
		.pixel_format = SG_PIXELFORMAT_RGBA8,
	};
	desc.data.subimage[0][0] = { .ptr = pixels, .size = (size_t)(width * height * 4) };
	sg_init_image(state.bindings.fs.images[SLOT_TexturedCube_tex], desc);

	stbi_image_free(pixels);
}