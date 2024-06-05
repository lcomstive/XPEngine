#include <Engine/API.hpp>
#include <stdio.h>

#define SOKOL_IMPL

#if defined(ENGINE_PLATFORM_WEB)
#define SOKOL_GLES3
#endif

#include <sokol_gfx.h>
#include <sokol_app.h>
#include <sokol_log.h>
#include <sokol_glue.h>

static sg_pass_action pass_action;

static void init()
{
	sg_desc desc =
	{
		.logger = { .func = slog_func },
		.environment = sglue_environment()
	};
	sg_setup(&desc);

	pass_action.colors[0] = {
		.load_action = SG_LOADACTION_CLEAR,
		.clear_value = { 1.0f, 0.0f, 0.0f, 1.0f }
	};
}

static void frame()
{
	float g = pass_action.colors[0].clear_value.g + 0.01f;
	pass_action.colors[0].clear_value.g = (g > 1.0f) ? 0.0f : g;

	sg_pass pass = { .action = pass_action, .swapchain = sglue_swapchain() };
	sg_begin_pass(&pass);
	sg_end_pass();
	sg_commit();
}

static void cleanup()
{
	sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[])
{
	return (sapp_desc)
	{
		.init_cb = init,
		.frame_cb = frame,
		.cleanup_cb = cleanup,
		.window_title = "XP App",
		.icon = { .sokol_default = true },
		.logger = { .func = slog_func }
	};
}