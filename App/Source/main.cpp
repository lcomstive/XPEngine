#include <Engine/API.hpp>
#include <stdio.h>

#if !defined(ENGINE_PLATFORM_APPLE)
#define SOKOL_IMPL
#endif

#include <sokol_gfx.h>
#include <sokol_app.h>
#include <sokol_log.h>
#include <sokol_glue.h>

#pragma region Shaders
#include <Shaders/triangle.h>
#pragma endregion

static struct
{
	sg_pipeline pipeline;
	sg_bindings bindings;
	sg_pass_action pass_action;
} state;

static void init()
{
	sg_desc desc =
	{
		.logger = { .func = slog_func },
		.environment = sglue_environment()
	};
	sg_setup(&desc);

	float vertices[] =
	{
		// positions            // colors
		 0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
	};
	sg_buffer_desc vertDesc =
	{
		.data = SG_RANGE(vertices),
		.label = "triangle-vertices"
	};
	state.bindings.vertex_buffers[0] = sg_make_buffer(vertDesc);

	sg_shader shader = sg_make_shader(triangle_shader_desc(sg_query_backend()));
	sg_pipeline_desc pipelineDesc = { .shader = shader };
	pipelineDesc.layout.attrs[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3;
	pipelineDesc.layout.attrs[ATTR_vs_colour0].format = SG_VERTEXFORMAT_FLOAT4;
	pipelineDesc.label = "triangle-pipeline";
	state.pipeline = sg_make_pipeline(pipelineDesc);

	state.pass_action.colors[0] = {
		.load_action = SG_LOADACTION_CLEAR,
		.clear_value = { 0.0f, 0.0f, 0.0f, 1.0f }
	};
}

static void frame()
{
	sg_pass pass = { .action = state.pass_action, .swapchain = sglue_swapchain() };
	sg_begin_pass(&pass);
	sg_apply_pipeline(state.pipeline);
	sg_apply_bindings(state.bindings);
	sg_draw(0, 3, 1);
	sg_end_pass();
	sg_commit();
}

static void cleanup()
{
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
