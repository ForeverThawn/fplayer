/*
 * This file is part of mpv.
 *
 * mpv is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * mpv is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with mpv.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MPLAYER_CFG_MPLAYER_H
#define MPLAYER_CFG_MPLAYER_H

/*
 * config for cfgparser
 */

#include <float.h>
#include <stddef.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>

#include "config.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include "options.h"
#include "m_config.h"
#include "m_option.h"
#include "common/common.h"
#include "input/event.h"
#include "stream/stream.h"
#include "video/csputils.h"
#include "video/hwdec.h"
#include "video/image_writer.h"
#include "sub/osd.h"
#include "player/core.h"
#include "player/command.h"
#include "stream/stream.h"
#include "demux/demux.h"

static void print_version(struct mp_log *log)
{
    mp_print_version(log, true);
}

extern const struct m_sub_options tv_params_conf;
extern const struct m_sub_options stream_cdda_conf;
extern const struct m_sub_options stream_dvb_conf;
extern const struct m_sub_options stream_lavf_conf;
extern const struct m_sub_options sws_conf;
extern const struct m_sub_options zimg_conf;
extern const struct m_sub_options drm_conf;
extern const struct m_sub_options demux_rawaudio_conf;
extern const struct m_sub_options demux_rawvideo_conf;
extern const struct m_sub_options demux_playlist_conf;
extern const struct m_sub_options demux_lavf_conf;
extern const struct m_sub_options demux_mkv_conf;
extern const struct m_sub_options demux_cue_conf;
extern const struct m_sub_options vd_lavc_conf;
extern const struct m_sub_options ad_lavc_conf;
extern const struct m_sub_options input_config;
extern const struct m_sub_options encode_config;
extern const struct m_sub_options ra_ctx_conf;
extern const struct m_sub_options gl_video_conf;
extern const struct m_sub_options ao_alsa_conf;

extern const struct m_sub_options demux_conf;
extern const struct m_sub_options demux_cache_conf;

extern const struct m_obj_list vf_obj_list;
extern const struct m_obj_list af_obj_list;
extern const struct m_obj_list vo_obj_list;

extern const struct m_sub_options ao_conf;

extern const struct m_sub_options opengl_conf;
extern const struct m_sub_options vulkan_conf;
extern const struct m_sub_options vulkan_display_conf;
extern const struct m_sub_options spirv_conf;
extern const struct m_sub_options d3d11_conf;
extern const struct m_sub_options d3d11va_conf;
extern const struct m_sub_options angle_conf;
extern const struct m_sub_options cocoa_conf;
extern const struct m_sub_options macos_conf;
extern const struct m_sub_options wayland_conf;
extern const struct m_sub_options vaapi_conf;

static const struct m_sub_options screenshot_conf = {
    .opts = image_writer_opts,
    .size = sizeof(struct image_writer_opts),
    .defaults = &image_writer_opts_defaults,
};

#undef OPT_BASE_STRUCT
#define OPT_BASE_STRUCT struct mp_vo_opts

static const m_option_t mp_vo_opt_list[] = {
    {"vo", OPT_SETTINGSLIST(video_driver_list, &vo_obj_list)},
    {"taskbar-progress", OPT_BOOL(taskbar_progress)},
    {"drag-and-drop", OPT_CHOICE(drag_and_drop, {"no", -2}, {"auto", -1},
        {"replace", DND_REPLACE}, {"append", DND_APPEND})},
    {"snap-window", OPT_BOOL(snap_window)},
    {"ontop", OPT_BOOL(ontop)},
    {"ontop-level", OPT_CHOICE(ontop_level, {"window", -1}, {"system", -2},
        {"desktop", -3}), M_RANGE(0, INT_MAX)},
    {"border", OPT_BOOL(border)},
    {"fit-border", OPT_BOOL(fit_border),
     .deprecation_message = "the option is ignored and no longer needed"},
    {"on-all-workspaces", OPT_BOOL(all_workspaces)},
    {"geometry", OPT_GEOMETRY(geometry)},
    {"autofit", OPT_SIZE_BOX(autofit)},
    {"autofit-larger", OPT_SIZE_BOX(autofit_larger)},
    {"autofit-smaller", OPT_SIZE_BOX(autofit_smaller)},
    {"auto-window-resize", OPT_BOOL(auto_window_resize)},
    {"window-scale", OPT_DOUBLE(window_scale), M_RANGE(0.001, 100)},
    {"window-minimized", OPT_BOOL(window_minimized)},
    {"window-maximized", OPT_BOOL(window_maximized)},
    {"focus-on-open", OPT_BOOL(focus_on_open)},
    {"force-render", OPT_BOOL(force_render)},
    {"force-window-position", OPT_BOOL(force_window_position)},
    {"x11-name", OPT_STRING(winname)},
    {"wayland-app-id", OPT_STRING(appid)},
    {"monitoraspect", OPT_FLOAT(force_monitor_aspect), M_RANGE(0.0, 9.0)},
    {"monitorpixelaspect", OPT_FLOAT(monitor_pixel_aspect),
        M_RANGE(1.0/32.0, 32.0)},
    {"fullscreen", OPT_BOOL(fullscreen)},
    {"fs", OPT_ALIAS("fullscreen")},
    {"input-cursor-passthrough", OPT_BOOL(cursor_passthrough)},
    {"native-keyrepeat", OPT_BOOL(native_keyrepeat)},
    {"panscan", OPT_FLOAT(panscan), M_RANGE(0.0, 1.0)},
    {"video-zoom", OPT_FLOAT(zoom), M_RANGE(-20.0, 20.0)},
    {"video-pan-x", OPT_FLOAT(pan_x), M_RANGE(-3.0, 3.0)},
    {"video-pan-y", OPT_FLOAT(pan_y), M_RANGE(-3.0, 3.0)},
    {"video-align-x", OPT_FLOAT(align_x), M_RANGE(-1.0, 1.0)},
    {"video-align-y", OPT_FLOAT(align_y), M_RANGE(-1.0, 1.0)},
    {"video-scale-x", OPT_FLOAT(scale_x), M_RANGE(0, 10000.0)},
    {"video-scale-y", OPT_FLOAT(scale_y), M_RANGE(0, 10000.0)},
    {"video-margin-ratio-left", OPT_FLOAT(margin_x[0]), M_RANGE(0.0, 1.0)},
    {"video-margin-ratio-right", OPT_FLOAT(margin_x[1]), M_RANGE(0.0, 1.0)},
    {"video-margin-ratio-top", OPT_FLOAT(margin_y[0]), M_RANGE(0.0, 1.0)},
    {"video-margin-ratio-bottom", OPT_FLOAT(margin_y[1]), M_RANGE(0.0, 1.0)},
    {"video-unscaled", OPT_CHOICE(unscaled,
        {"no", 0}, {"yes", 1}, {"downscale-big", 2})},
    {"wid", OPT_INT64(WinID)},
    {"screen", OPT_CHOICE(screen_id, {"default", -1}), M_RANGE(0, 32)},
    {"screen-name", OPT_STRING(screen_name)},
    {"fs-screen", OPT_CHOICE(fsscreen_id, {"all", -2}, {"current", -1}),
        M_RANGE(0, 32)},
    {"fs-screen-name", OPT_STRING(fsscreen_name)},
    {"keepaspect", OPT_BOOL(keepaspect)},
    {"keepaspect-window", OPT_BOOL(keepaspect_window)},
    {"hidpi-window-scale", OPT_BOOL(hidpi_window_scale)},
    {"native-fs", OPT_BOOL(native_fs)},
    {"override-display-fps", OPT_DOUBLE(override_display_fps),
        M_RANGE(0, DBL_MAX)},
    {"video-timing-offset", OPT_DOUBLE(timing_offset), M_RANGE(0.0, 1.0)},
    {"video-sync", OPT_CHOICE(video_sync,
        {"audio", VS_DEFAULT},
        {"display-resample", VS_DISP_RESAMPLE},
        {"display-resample-vdrop", VS_DISP_RESAMPLE_VDROP},
        {"display-resample-desync", VS_DISP_RESAMPLE_NONE},
        {"display-tempo", VS_DISP_TEMPO},
        {"display-adrop", VS_DISP_ADROP},
        {"display-vdrop", VS_DISP_VDROP},
        {"display-desync", VS_DISP_NONE},
        {"desync", VS_NONE})},
#if HAVE_X11
    {"x11-netwm", OPT_CHOICE(x11_netwm, {"auto", 0}, {"no", -1}, {"yes", 1})},
    {"x11-bypass-compositor", OPT_CHOICE(x11_bypass_compositor,
        {"no", 0}, {"yes", 1}, {"fs-only", 2}, {"never", 3})},
    {"x11-present", OPT_CHOICE(x11_present,
        {"no", 0}, {"auto", 1}, {"yes", 2})},
#endif
#if HAVE_WAYLAND
    {"wayland-content-type", OPT_CHOICE(content_type, {"auto", -1}, {"none", 0},
        {"photo", 1}, {"video", 2}, {"game", 3})},
#endif
#if HAVE_WIN32_DESKTOP
    {"vo-mmcss-profile", OPT_STRING(mmcss_profile)},
#endif
#if HAVE_EGL_ANDROID
    {"android-surface-size", OPT_SIZE_BOX(android_surface_size)},
#endif
    {"swapchain-depth", OPT_INT(swapchain_depth), M_RANGE(1, 8)},
    {0}
};

const struct m_sub_options vo_sub_opts = {
    .opts = mp_vo_opt_list,
    .size = sizeof(struct mp_vo_opts),
    .defaults = &(const struct mp_vo_opts){
        .video_driver_list = NULL,
        .drag_and_drop = -1,
        .monitor_pixel_aspect = 1.0,
        .screen_id = -1,
        .fsscreen_id = -1,
        .panscan = 0.0f,
        .scale_x = 1.0f,
        .scale_y = 1.0f,
        .auto_window_resize = true,
        .keepaspect = true,
        .keepaspect_window = true,
        .hidpi_window_scale = false,  // true
        .native_fs = true,
        .taskbar_progress = true,
        .border = false,  // true
        // .fit_border = true,
        .appid = "fplayer",  // mpv
        .content_type = -1,
        .WinID = -1,
        .window_scale = 1.0,
        .x11_bypass_compositor = 2,
        .x11_present = 1,
        .mmcss_profile = "Playback",
        .ontop_level = -1,
        .timing_offset = 0.050,
        .swapchain_depth = 3,
        .focus_on_open = true,

        .video_sync = VS_DISP_RESAMPLE,  //vsync        
        // {"video-sync", OPT_CHOICE(video_sync,
        //     {"audio", VS_DEFAULT},
        //     {"display-resample", VS_DISP_RESAMPLE},
        //     {"display-resample-vdrop", VS_DISP_RESAMPLE_VDROP},
        //     {"display-resample-desync", VS_DISP_RESAMPLE_NONE},
        //     {"display-tempo", VS_DISP_TEMPO},
        //     {"display-adrop", VS_DISP_ADROP},
        //     {"display-vdrop", VS_DISP_VDROP},
        //     {"display-desync", VS_DISP_NONE},
        //     {"desync", VS_NONE})},

    },
};

#undef OPT_BASE_STRUCT
#define OPT_BASE_STRUCT struct mp_sub_filter_opts

const struct m_sub_options mp_sub_filter_opts = {
    .opts = (const struct m_option[]){
        {"sub-filter-sdh", OPT_BOOL(sub_filter_SDH)},
        {"sub-filter-sdh-harder", OPT_BOOL(sub_filter_SDH_harder)},
        {"sub-filter-regex-enable", OPT_BOOL(rf_enable)},
        {"sub-filter-regex-plain", OPT_BOOL(rf_plain)},
        {"sub-filter-regex", OPT_STRINGLIST(rf_items)},
        {"sub-filter-jsre", OPT_STRINGLIST(jsre_items)},
        {"sub-filter-regex-warn", OPT_BOOL(rf_warn)},
        {0}
    },
    .size = sizeof(OPT_BASE_STRUCT),
    .defaults = &(OPT_BASE_STRUCT){
        .rf_enable = true,
    },
    .change_flags = UPDATE_SUB_FILT,
};

#undef OPT_BASE_STRUCT
#define OPT_BASE_STRUCT struct mp_subtitle_opts

const struct m_sub_options mp_subtitle_sub_opts = {
    .opts = (const struct m_option[]){
        {"sub-delay", OPT_FLOAT(sub_delay)},
        {"sub-fps", OPT_FLOAT(sub_fps)},
        {"sub-speed", OPT_FLOAT(sub_speed)},
        {"sub-visibility", OPT_BOOL(sub_visibility)},
        {"secondary-sub-visibility", OPT_BOOL(sec_sub_visibility)},
        {"sub-forced-only", OPT_CHOICE(forced_subs_only,
            {"auto", -1}, {"no", 0}, {"yes", 1})},
        {"stretch-dvd-subs", OPT_BOOL(stretch_dvd_subs)},
        {"stretch-image-subs-to-screen", OPT_BOOL(stretch_image_subs)},
        {"image-subs-video-resolution", OPT_BOOL(image_subs_video_res)},
        {"sub-fix-timing", OPT_BOOL(sub_fix_timing)},
        {"sub-pos", OPT_INT(sub_pos), M_RANGE(0, 150)},
        {"sub-gauss", OPT_FLOAT(sub_gauss), M_RANGE(0.0, 3.0)},
        {"sub-gray", OPT_BOOL(sub_gray)},
        {"sub-ass", OPT_BOOL(ass_enabled), .flags = UPDATE_SUB_HARD},
        {"sub-scale", OPT_FLOAT(sub_scale), M_RANGE(0, 100)},
        {"sub-ass-line-spacing", OPT_FLOAT(ass_line_spacing),
            M_RANGE(-1000, 1000)},
        {"sub-use-margins", OPT_BOOL(sub_use_margins)},
        {"sub-ass-force-margins", OPT_BOOL(ass_use_margins)},
        {"sub-ass-vsfilter-aspect-compat", OPT_BOOL(ass_vsfilter_aspect_compat)},
        {"sub-ass-vsfilter-color-compat", OPT_CHOICE(ass_vsfilter_color_compat,
            {"no", 0}, {"basic", 1}, {"full", 2}, {"force-601", 3})},
        {"sub-ass-vsfilter-blur-compat", OPT_BOOL(ass_vsfilter_blur_compat)},
        {"embeddedfonts", OPT_BOOL(use_embedded_fonts), .flags = UPDATE_SUB_HARD},
        {"sub-ass-force-style", OPT_STRINGLIST(ass_force_style_list),
            .flags = UPDATE_SUB_HARD},
        {"sub-ass-styles", OPT_STRING(ass_styles_file),
            .flags = M_OPT_FILE | UPDATE_SUB_HARD},
        {"sub-ass-hinting", OPT_CHOICE(ass_hinting,
            {"none", 0}, {"light", 1}, {"normal", 2}, {"native", 3})},
        {"sub-ass-shaper", OPT_CHOICE(ass_shaper,
            {"simple", 0}, {"complex", 1})},
        {"sub-ass-justify", OPT_BOOL(ass_justify)},
        {"sub-ass-override", OPT_CHOICE(ass_style_override,
            {"no", 0}, {"yes", 1}, {"force", 3}, {"scale", 4}, {"strip", 5})},
        {"sub-scale-by-window", OPT_BOOL(sub_scale_by_window)},
        {"sub-scale-with-window", OPT_BOOL(sub_scale_with_window)},
        {"sub-ass-scale-with-window", OPT_BOOL(ass_scale_with_window)},
        {"sub", OPT_SUBSTRUCT(sub_style, sub_style_conf)},
        {"sub-clear-on-seek", OPT_BOOL(sub_clear_on_seek)},
        {"teletext-page", OPT_INT(teletext_page), M_RANGE(1, 999)},
        {"sub-past-video-end", OPT_BOOL(sub_past_video_end)},
        {0}
    },
    .size = sizeof(OPT_BASE_STRUCT),
    .defaults = &(OPT_BASE_STRUCT){
        .sub_visibility = true,
        .sec_sub_visibility = true,
        .forced_subs_only = -1,
        .sub_pos = 100,
        .sub_speed = 1.0,
        .ass_enabled = true,
        .sub_scale_by_window = true,
        .sub_use_margins = true,
        .sub_scale_with_window = true,
        .teletext_page = 100,
        .sub_scale = 1,
        .ass_vsfilter_aspect_compat = true,
        .ass_vsfilter_color_compat = 1,
        .ass_vsfilter_blur_compat = true,
        .ass_style_override = 1,
        .ass_shaper = 1,

        .ass_use_margins = true,  // 使ASS字幕尽可能输出在黑边上
        .use_embedded_fonts = true,
    },
    .change_flags = UPDATE_OSD,
};

#undef OPT_BASE_STRUCT
#define OPT_BASE_STRUCT struct mp_osd_render_opts

const struct m_sub_options mp_osd_render_sub_opts = {
    .opts = (const struct m_option[]){
        {"osd-bar-align-x", OPT_FLOAT(osd_bar_align_x), M_RANGE(-1.0, +1.0)},
        {"osd-bar-align-y", OPT_FLOAT(osd_bar_align_y), M_RANGE(-1.0, +1.0)},
        {"osd-bar-w", OPT_FLOAT(osd_bar_w), M_RANGE(1, 100)},
        {"osd-bar-h", OPT_FLOAT(osd_bar_h), M_RANGE(0.1, 50)},
        {"osd", OPT_SUBSTRUCT(osd_style, osd_style_conf)},
        {"osd-scale", OPT_FLOAT(osd_scale), M_RANGE(0, 100)},
        {"osd-scale-by-window", OPT_BOOL(osd_scale_by_window)},
        {"force-rgba-osd-rendering", OPT_BOOL(force_rgba_osd)},
        {0}
    },
    .size = sizeof(OPT_BASE_STRUCT),
    .defaults = &(OPT_BASE_STRUCT){
        .osd_bar_align_y = 0.5,
        .osd_bar_w = 75.0,
        .osd_bar_h = 3.125,
        .osd_scale = 1,
        .osd_scale_by_window = true,
    },
    .change_flags = UPDATE_OSD,
};

#undef OPT_BASE_STRUCT
#define OPT_BASE_STRUCT struct dvd_opts

const struct m_sub_options dvd_conf = {
    .opts = (const struct m_option[]){
        {"dvd-device", OPT_STRING(device), .flags = M_OPT_FILE},
        {"dvd-speed", OPT_INT(speed)},
        {"dvd-angle", OPT_INT(angle), M_RANGE(1, 99)},
        {0}
    },
    .size = sizeof(struct dvd_opts),
    .defaults = &(const struct dvd_opts){
        .angle = 1,
    },
};

#undef OPT_BASE_STRUCT
#define OPT_BASE_STRUCT struct filter_opts

const struct m_sub_options filter_conf = {
    .opts = (const struct m_option[]){
        {"deinterlace", OPT_BOOL(deinterlace)},
        {0}
    },
    .size = sizeof(OPT_BASE_STRUCT),
    .change_flags = UPDATE_IMGPAR,
};

#undef OPT_BASE_STRUCT
#define OPT_BASE_STRUCT struct MPOpts

static const m_option_t mp_opts[] = {
    // handled in command line pre-parser (parse_commandline.c)
    {"v", &m_option_type_dummy_flag, CONF_NOCFG | M_OPT_NOPROP,
     .offset = -1},
    {"playlist", CONF_TYPE_STRING, CONF_NOCFG | M_OPT_FILE, .offset = -1},
    {"{", &m_option_type_dummy_flag, CONF_NOCFG | M_OPT_NOPROP,
     .offset = -1},
    {"}", &m_option_type_dummy_flag, CONF_NOCFG | M_OPT_NOPROP,
     .offset = -1},

    // handled in m_config.c
    { "include", CONF_TYPE_STRING, M_OPT_FILE, .offset = -1},
    { "profile", CONF_TYPE_STRING_LIST, 0, .offset = -1},
    { "show-profile", CONF_TYPE_STRING, CONF_NOCFG | M_OPT_NOPROP |
        M_OPT_OPTIONAL_PARAM,  .offset = -1},
    { "list-options", &m_option_type_dummy_flag, CONF_NOCFG | M_OPT_NOPROP,
        .offset = -1},
    {"list-properties", OPT_BOOL(property_print_help),
     .flags = CONF_NOCFG | M_OPT_NOPROP},
    { "help", CONF_TYPE_STRING, CONF_NOCFG | M_OPT_NOPROP | M_OPT_OPTIONAL_PARAM,
        .offset = -1},
    { "h", CONF_TYPE_STRING, CONF_NOCFG | M_OPT_NOPROP | M_OPT_OPTIONAL_PARAM,
        .offset = -1},

    {"list-protocols", OPT_PRINT(stream_print_proto_list)},
    {"version", OPT_PRINT(print_version)},
    {"V", OPT_PRINT(print_version)},

    {"player-operation-mode", OPT_CHOICE(operation_mode,
        {"cplayer", 0}, {"pseudo-gui", 1}),
        .flags = M_OPT_PRE_PARSE | M_OPT_NOPROP},

    {"shuffle", OPT_BOOL(shuffle)},

// ------------------------- common options --------------------
    {"quiet", OPT_BOOL(quiet)},
    {"really-quiet", OPT_BOOL(msg_really_quiet),
        .flags = CONF_PRE_PARSE | UPDATE_TERM},
    {"terminal", OPT_BOOL(use_terminal), .flags = CONF_PRE_PARSE | UPDATE_TERM},
    {"msg-level", OPT_MSGLEVELS(msg_levels),
        .flags = CONF_PRE_PARSE | UPDATE_TERM},
    {"dump-stats", OPT_STRING(dump_stats),
        .flags = UPDATE_TERM | CONF_PRE_PARSE | M_OPT_FILE},
    {"msg-color", OPT_BOOL(msg_color), .flags = CONF_PRE_PARSE | UPDATE_TERM},
    {"log-file", OPT_STRING(log_file),
        .flags = CONF_PRE_PARSE | M_OPT_FILE | UPDATE_TERM},
    {"msg-module", OPT_BOOL(msg_module), .flags = UPDATE_TERM},
    {"msg-time", OPT_BOOL(msg_time), .flags = UPDATE_TERM},
#if HAVE_WIN32_DESKTOP
    {"priority", OPT_CHOICE(w32_priority,
        {"no",          0},
        {"realtime",    REALTIME_PRIORITY_CLASS},
        {"high",        HIGH_PRIORITY_CLASS},
        {"abovenormal", ABOVE_NORMAL_PRIORITY_CLASS},
        {"normal",      NORMAL_PRIORITY_CLASS},
        {"belownormal", BELOW_NORMAL_PRIORITY_CLASS},
        {"idle",        IDLE_PRIORITY_CLASS}),
        .flags = UPDATE_PRIORITY},
#endif
    {"config", OPT_BOOL(load_config), .flags = CONF_PRE_PARSE},
    {"config-dir", OPT_STRING(force_configdir),
        .flags = CONF_NOCFG | CONF_PRE_PARSE | M_OPT_FILE},
    {"reset-on-next-file", OPT_STRINGLIST(reset_options)},

#if HAVE_LUA || HAVE_JAVASCRIPT || HAVE_CPLUGINS
    {"scripts", OPT_PATHLIST(script_files), .flags = M_OPT_FILE},
    {"script", OPT_CLI_ALIAS("scripts-append")},
    {"script-opts", OPT_KEYVALUELIST(script_opts)},
    {"load-scripts", OPT_BOOL(auto_load_scripts)},
#endif
#if HAVE_LUA
    {"osc", OPT_BOOL(lua_load_osc), .flags = UPDATE_BUILTIN_SCRIPTS},
    {"ytdl", OPT_BOOL(lua_load_ytdl), .flags = UPDATE_BUILTIN_SCRIPTS},
    {"ytdl-format", OPT_STRING(lua_ytdl_format)},
    {"ytdl-raw-options", OPT_KEYVALUELIST(lua_ytdl_raw_options)},
    {"load-stats-overlay", OPT_BOOL(lua_load_stats),
        .flags = UPDATE_BUILTIN_SCRIPTS},
    {"load-osd-console", OPT_BOOL(lua_load_console),
        .flags = UPDATE_BUILTIN_SCRIPTS},
    {"load-auto-profiles",
        OPT_CHOICE(lua_load_auto_profiles, {"no", 0}, {"yes", 1}, {"auto", -1}),
        .flags = UPDATE_BUILTIN_SCRIPTS},
#endif

// ------------------------- stream options --------------------

#if HAVE_DVDNAV
    {"", OPT_SUBSTRUCT(dvd_opts, dvd_conf)},
#endif
    {"edition", OPT_CHOICE(edition_id, {"auto", -1}), M_RANGE(0, 8190)},
#if HAVE_LIBBLURAY
    {"bluray-device", OPT_STRING(bluray_device), .flags = M_OPT_FILE},
#endif /* HAVE_LIBBLURAY */

// ------------------------- demuxer options --------------------

    {"frames", OPT_CHOICE(play_frames, {"all", -1}), M_RANGE(0, INT_MAX)},

    {"start", OPT_REL_TIME(play_start)},
    {"end", OPT_REL_TIME(play_end)},
    {"length", OPT_REL_TIME(play_length)},

    {"play-dir", OPT_CHOICE(play_dir,
        {"forward", 1}, {"+", 1}, {"backward", -1}, {"-", -1})},

    {"rebase-start-time", OPT_BOOL(rebase_start_time)},

    {"ab-loop-a", OPT_TIME(ab_loop[0]), .flags = M_OPT_ALLOW_NO},
    {"ab-loop-b", OPT_TIME(ab_loop[1]), .flags = M_OPT_ALLOW_NO},
    {"ab-loop-count", OPT_CHOICE(ab_loop_count, {"inf", -1}),
        M_RANGE(0, INT_MAX)},

    {"playlist-start", OPT_CHOICE(playlist_pos, {"auto", -1}, {"no", -1}),
        M_RANGE(0, INT_MAX)},

    {"pause", OPT_BOOL(pause)},
    {"keep-open", OPT_CHOICE(keep_open,
        {"no", 0},
        {"yes", 1},
        {"always", 2})},
    {"keep-open-pause", OPT_BOOL(keep_open_pause)},
    {"image-display-duration", OPT_DOUBLE(image_display_duration),
        M_RANGE(0, INFINITY)},

     {"index", OPT_CHOICE(index_mode, {"default", 1}, {"recreate", 0})},

    // select audio/video/subtitle stream
    // keep in sync with num_ptracks[] and MAX_PTRACKS
    {"aid", OPT_TRACKCHOICE(stream_id[0][STREAM_AUDIO])},
    {"vid", OPT_TRACKCHOICE(stream_id[0][STREAM_VIDEO])},
    {"sid", OPT_TRACKCHOICE(stream_id[0][STREAM_SUB])},
    {"secondary-sid", OPT_TRACKCHOICE(stream_id[1][STREAM_SUB])},
    {"sub", OPT_ALIAS("sid")},
    {"video", OPT_ALIAS("vid")},
    {"audio", OPT_ALIAS("aid")},
    {"alang", OPT_STRINGLIST(stream_lang[STREAM_AUDIO])},
    {"slang", OPT_STRINGLIST(stream_lang[STREAM_SUB])},
    {"vlang", OPT_STRINGLIST(stream_lang[STREAM_VIDEO])},
    {"track-auto-selection", OPT_BOOL(stream_auto_sel)},
    {"subs-with-matching-audio", OPT_BOOL(subs_with_matching_audio)},
    {"subs-fallback", OPT_CHOICE(subs_fallback, {"no", 0}, {"default", 1}, {"yes", 2})},
    {"subs-fallback-forced", OPT_BOOL(subs_fallback_forced)},

    {"lavfi-complex", OPT_STRING(lavfi_complex), .flags = UPDATE_LAVFI_COMPLEX},

    {"audio-display", OPT_CHOICE(audio_display, {"no", 0},
        {"embedded-first", 1}, {"external-first", 2})},

    {"hls-bitrate", OPT_CHOICE(hls_bitrate,
        {"no", -1}, {"min", 0}, {"max", INT_MAX}), M_RANGE(0, INT_MAX)},

    {"display-tags", OPT_STRINGLIST(display_tags)},

#if HAVE_CDDA
    {"cdda", OPT_SUBSTRUCT(stream_cdda_opts, stream_cdda_conf)},
    {"cdrom-device", OPT_STRING(cdrom_device), .flags = M_OPT_FILE},
#endif

    // demuxer.c - select audio/sub file/demuxer
    {"demuxer", OPT_STRING(demuxer_name), .help = demuxer_help},
    {"audio-demuxer", OPT_STRING(audio_demuxer_name), .help = demuxer_help},
    {"sub-demuxer", OPT_STRING(sub_demuxer_name), .help = demuxer_help},
    {"demuxer-thread", OPT_BOOL(demuxer_thread)},
    {"demuxer-termination-timeout", OPT_DOUBLE(demux_termination_timeout)},
    {"demuxer-cache-wait", OPT_BOOL(demuxer_cache_wait)},
    {"prefetch-playlist", OPT_BOOL(prefetch_open)},
    {"cache-pause", OPT_BOOL(cache_pause)},
    {"cache-pause-initial", OPT_BOOL(cache_pause_initial)},
    {"cache-pause-wait", OPT_FLOAT(cache_pause_wait), M_RANGE(0, DBL_MAX)},

    {"mf-fps", OPT_DOUBLE(mf_fps)},
    {"mf-type", OPT_STRING(mf_type)},
#if HAVE_DVBIN
    {"dvbin", OPT_SUBSTRUCT(stream_dvb_opts, stream_dvb_conf)},
#endif
    {"", OPT_SUBSTRUCT(stream_lavf_opts, stream_lavf_conf)},

// ------------------------- a-v sync options --------------------

    // set A-V sync correction speed (0=disables it):
    {"mc", OPT_FLOAT(default_max_pts_correction), M_RANGE(0, 100)},

    {"audio-samplerate", OPT_INT(force_srate), .flags = UPDATE_AUDIO,
        M_RANGE(0, 16*48000)},
    {"audio-channels", OPT_CHANNELS(audio_output_channels), .flags = UPDATE_AUDIO},
    {"audio-format", OPT_AUDIOFORMAT(audio_output_format), .flags = UPDATE_AUDIO},
    {"speed", OPT_DOUBLE(playback_speed), M_RANGE(0.01, 100.0)},

    {"audio-pitch-correction", OPT_BOOL(pitch_correction)},

    // set a-v distance
    {"audio-delay", OPT_FLOAT(audio_delay)},

// ------------------------- codec/vfilter options --------------------

    {"af-defaults", OPT_SETTINGSLIST(af_defs, &af_obj_list),
        .deprecation_message = "use --af + enable/disable flags"},
    {"af", OPT_SETTINGSLIST(af_settings, &af_obj_list)},
    {"vf-defaults", OPT_SETTINGSLIST(vf_defs, &vf_obj_list),
        .deprecation_message = "use --vf + enable/disable flags"},
    {"vf", OPT_SETTINGSLIST(vf_settings, &vf_obj_list)},

    {"", OPT_SUBSTRUCT(filter_opts, filter_conf)},

    {"", OPT_SUBSTRUCT(dec_wrapper, dec_wrapper_conf)},
    {"", OPT_SUBSTRUCT(vd_lavc_params, vd_lavc_conf)},
    {"ad-lavc", OPT_SUBSTRUCT(ad_lavc_params, ad_lavc_conf)},

    {"", OPT_SUBSTRUCT(demux_lavf, demux_lavf_conf)},
    {"demuxer-rawaudio", OPT_SUBSTRUCT(demux_rawaudio, demux_rawaudio_conf)},
    {"demuxer-rawvideo", OPT_SUBSTRUCT(demux_rawvideo, demux_rawvideo_conf)},
    {"", OPT_SUBSTRUCT(demux_playlist, demux_playlist_conf)},
    {"demuxer-mkv", OPT_SUBSTRUCT(demux_mkv, demux_mkv_conf)},
    {"demuxer-cue", OPT_SUBSTRUCT(demux_cue, demux_cue_conf)},

// ------------------------- subtitles options --------------------

    {"sub-files", OPT_PATHLIST(sub_name), .flags = M_OPT_FILE},
    {"sub-file", OPT_CLI_ALIAS("sub-files-append")},
    {"audio-files", OPT_PATHLIST(audio_files), .flags = M_OPT_FILE},
    {"audio-file", OPT_CLI_ALIAS("audio-files-append")},
    {"cover-art-files", OPT_PATHLIST(coverart_files), .flags = M_OPT_FILE},
    {"cover-art-file", OPT_CLI_ALIAS("cover-art-files-append")},

    {"sub-file-paths", OPT_PATHLIST(sub_paths), .flags = M_OPT_FILE},
    {"audio-file-paths", OPT_PATHLIST(audiofile_paths), .flags = M_OPT_FILE},

    {"external-files", OPT_PATHLIST(external_files), .flags = M_OPT_FILE},
    {"external-file", OPT_CLI_ALIAS("external-files-append")},
    {"autoload-files", OPT_BOOL(autoload_files)},

    {"sub-auto", OPT_CHOICE(sub_auto,
        {"no", -1}, {"exact", 0}, {"fuzzy", 1}, {"all", 2})},
    {"audio-file-auto", OPT_CHOICE(audiofile_auto,
        {"no", -1}, {"exact", 0}, {"fuzzy", 1}, {"all", 2})},
    {"cover-art-auto", OPT_CHOICE(coverart_auto,
        {"no", -1}, {"exact", 0}, {"fuzzy", 1}, {"all", 2})},
    {"cover-art-whitelist", OPT_BOOL(coverart_whitelist)},

    {"", OPT_SUBSTRUCT(subs_rend, mp_subtitle_sub_opts)},
    {"", OPT_SUBSTRUCT(subs_filt, mp_sub_filter_opts)},
    {"", OPT_SUBSTRUCT(osd_rend, mp_osd_render_sub_opts)},

    {"osd-bar", OPT_BOOL(osd_bar_visible), .flags = UPDATE_OSD},

//---------------------- libao/libvo options ------------------------
    {"", OPT_SUBSTRUCT(ao_opts, ao_conf)},
    {"audio-exclusive", OPT_BOOL(audio_exclusive), .flags = UPDATE_AUDIO},
    {"audio-fallback-to-null", OPT_BOOL(ao_null_fallback)},
    {"audio-stream-silence", OPT_BOOL(audio_stream_silence)},
    {"audio-wait-open", OPT_FLOAT(audio_wait_open), M_RANGE(0, 60)},
    {"force-window", OPT_CHOICE(force_vo,
        {"no", 0}, {"yes", 1}, {"immediate", 2})},

    {"volume-max", OPT_FLOAT(softvol_max), M_RANGE(100, 1000)},
    // values <0 for volume and mute are legacy and ignored
    {"volume", OPT_FLOAT(softvol_volume), .flags = UPDATE_VOL,
        M_RANGE(-1, 1000)},
    {"mute", OPT_CHOICE(softvol_mute,
        {"no", 0},
        {"auto", 0},
        {"yes", 1}),
        .flags = UPDATE_VOL},
    {"replaygain", OPT_CHOICE(rgain_mode,
        {"no", 0},
        {"track", 1},
        {"album", 2}),
        .flags = UPDATE_VOL},
    {"replaygain-preamp", OPT_FLOAT(rgain_preamp), .flags = UPDATE_VOL,
        M_RANGE(-150, 150)},
    {"replaygain-clip", OPT_BOOL(rgain_clip), .flags = UPDATE_VOL},
    {"replaygain-fallback", OPT_FLOAT(rgain_fallback), .flags = UPDATE_VOL,
        M_RANGE(-200, 60)},
    {"gapless-audio", OPT_CHOICE(gapless_audio,
        {"no", 0},
        {"yes", 1},
        {"weak", -1})},

    {"title", OPT_STRING(wintitle)},
    {"force-media-title", OPT_STRING(media_title)},

    {"cursor-autohide", OPT_CHOICE(cursor_autohide_delay,
        {"no", -1}, {"always", -2}), M_RANGE(0, 30000)},
    {"cursor-autohide-fs-only", OPT_BOOL(cursor_autohide_fs)},
    {"stop-screensaver", OPT_CHOICE(stop_screensaver,
        {"no", 0},
        {"yes", 1},
        {"always", 2}),
        .flags = UPDATE_SCREENSAVER},

    {"", OPT_SUBSTRUCT(video_equalizer, mp_csp_equalizer_conf)},

    {"use-filedir-conf", OPT_BOOL(use_filedir_conf)},
    {"osd-level", OPT_CHOICE(osd_level,
        {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3})},
    {"osd-on-seek", OPT_CHOICE(osd_on_seek,
        {"no", 0},
        {"bar", 1},
        {"msg", 2},
        {"msg-bar", 3})},
    {"osd-duration", OPT_INT(osd_duration), M_RANGE(0, 3600000)},
    {"osd-fractions", OPT_BOOL(osd_fractions)},

    {"sstep", OPT_DOUBLE(step_sec), M_RANGE(0, DBL_MAX)},

    {"framedrop", OPT_CHOICE(frame_dropping,
        {"no", 0},
        {"vo", 1},
        {"decoder", 2},
        {"decoder+vo", 3})},
    {"video-latency-hacks", OPT_BOOL(video_latency_hacks)},

    {"untimed", OPT_BOOL(untimed)},

    {"stream-dump", OPT_STRING(stream_dump), .flags = M_OPT_FILE},

    {"stop-playback-on-init-failure", OPT_BOOL(stop_playback_on_init_failure)},

    {"loop-playlist", OPT_CHOICE(loop_times,
        {"no", 1},
        {"inf", -1}, {"yes", -1},
        {"force", -2}),
        M_RANGE(1, 10000)},
    {"loop-file", OPT_CHOICE(loop_file,
        {"no", 0},
        {"inf", -1},
        {"yes", -1}),
        M_RANGE(0, 10000)},
    {"loop", OPT_ALIAS("loop-file")},

    {"resume-playback", OPT_BOOL(position_resume)},
    {"resume-playback-check-mtime", OPT_BOOL(position_check_mtime)},
    {"save-position-on-quit", OPT_BOOL(position_save_on_quit)},
    {"write-filename-in-watch-later-config",
        OPT_BOOL(write_filename_in_watch_later_config)},
    {"ignore-path-in-watch-later-config",
        OPT_BOOL(ignore_path_in_watch_later_config)},
    {"watch-later-directory", OPT_STRING(watch_later_directory),
        .flags = M_OPT_FILE},
    {"watch-later-options", OPT_STRINGLIST(watch_later_options)},

    {"ordered-chapters", OPT_BOOL(ordered_chapters)},
    {"ordered-chapters-files", OPT_STRING(ordered_chapters_files),
        .flags = M_OPT_FILE},
    {"chapter-merge-threshold", OPT_INT(chapter_merge_threshold),
        M_RANGE(0, 10000)},

    {"chapter-seek-threshold", OPT_DOUBLE(chapter_seek_threshold)},

    {"chapters-file", OPT_STRING(chapter_file), .flags = M_OPT_FILE},

    {"merge-files", OPT_BOOL(merge_files)},

    // a-v sync stuff:
    {"initial-audio-sync", OPT_BOOL(initial_audio_sync)},
    {"video-sync-max-video-change", OPT_DOUBLE(sync_max_video_change),
        M_RANGE(0, DBL_MAX)},
    {"video-sync-max-audio-change", OPT_DOUBLE(sync_max_audio_change),
        M_RANGE(0, 1)},
    {"video-sync-max-factor", OPT_INT(sync_max_factor), M_RANGE(1, 10)},
    {"hr-seek", OPT_CHOICE(hr_seek,
        {"no", -1}, {"absolute", 0}, {"yes", 1}, {"always", 1}, {"default", 2})},
    {"hr-seek-demuxer-offset", OPT_FLOAT(hr_seek_demuxer_offset)},
    {"hr-seek-framedrop", OPT_BOOL(hr_seek_framedrop)},
    {"autosync", OPT_CHOICE(autosync, {"no", -1}), M_RANGE(0, 10000)},

    {"term-osd", OPT_CHOICE(term_osd,
        {"force", 1}, {"auto", 2}, {"no", 0}), .flags = UPDATE_OSD},

    {"term-osd-bar", OPT_BOOL(term_osd_bar), .flags = UPDATE_OSD},
    {"term-osd-bar-chars", OPT_STRING(term_osd_bar_chars), .flags = UPDATE_OSD},
    {"term-title", OPT_STRING(term_title), .flags = UPDATE_OSD},

    {"term-playing-msg", OPT_STRING(playing_msg)},
    {"osd-playing-msg", OPT_STRING(osd_playing_msg)},
    {"osd-playing-msg-duration", OPT_INT(osd_playing_msg_duration),
        M_RANGE(0, 3600000)},
    {"term-status-msg", OPT_STRING(status_msg), .flags = UPDATE_OSD},
    {"osd-status-msg", OPT_STRING(osd_status_msg), .flags = UPDATE_OSD},
    {"osd-msg1", OPT_STRING(osd_msg[0]), .flags = UPDATE_OSD},
    {"osd-msg2", OPT_STRING(osd_msg[1]), .flags = UPDATE_OSD},
    {"osd-msg3", OPT_STRING(osd_msg[2]), .flags = UPDATE_OSD},

    {"video-osd", OPT_BOOL(video_osd), .flags = UPDATE_OSD},

    {"idle", OPT_CHOICE(player_idle_mode,
        {"no",   0}, {"once", 1}, {"yes",  2})},

    {"input-terminal", OPT_BOOL(consolecontrols), .flags = UPDATE_TERM},

    {"input-ipc-server", OPT_STRING(ipc_path), .flags = M_OPT_FILE},
#if HAVE_POSIX
    {"input-ipc-client", OPT_STRING(ipc_client)},
#endif

    {"screenshot", OPT_SUBSTRUCT(screenshot_image_opts, screenshot_conf)},
    {"screenshot-template", OPT_STRING(screenshot_template)},
    {"screenshot-directory", OPT_STRING(screenshot_directory),
        .flags = M_OPT_FILE},
    {"screenshot-sw", OPT_BOOL(screenshot_sw)},

    {"record-file", OPT_STRING(record_file), .flags = M_OPT_FILE,
        .deprecation_message = "use --stream-record or the dump-cache command"},

    {"", OPT_SUBSTRUCT(resample_opts, resample_conf)},

    {"", OPT_SUBSTRUCT(input_opts, input_config)},

    {"", OPT_SUBSTRUCT(vo, vo_sub_opts)},
    {"", OPT_SUBSTRUCT(demux_opts, demux_conf)},
    {"", OPT_SUBSTRUCT(demux_cache_opts, demux_cache_conf)},
    {"", OPT_SUBSTRUCT(stream_opts, stream_conf)},

    {"", OPT_SUBSTRUCT(ra_ctx_opts, ra_ctx_conf)},
    {"", OPT_SUBSTRUCT(gl_video_opts, gl_video_conf)},
    {"", OPT_SUBSTRUCT(spirv_opts, spirv_conf)},

#if HAVE_GL
    {"", OPT_SUBSTRUCT(opengl_opts, opengl_conf)},
#endif

#if HAVE_VULKAN
    {"", OPT_SUBSTRUCT(vulkan_opts, vulkan_conf)},
#if HAVE_VK_KHR_DISPLAY
    {"", OPT_SUBSTRUCT(vulkan_display_opts, vulkan_display_conf)},
#endif
#endif

#if HAVE_D3D11
    {"", OPT_SUBSTRUCT(d3d11_opts, d3d11_conf)},
#if HAVE_D3D_HWACCEL
    {"", OPT_SUBSTRUCT(d3d11va_opts, d3d11va_conf)},
#endif
#endif

#if HAVE_EGL_ANGLE_WIN32
    {"", OPT_SUBSTRUCT(angle_opts, angle_conf)},
#endif

#if HAVE_GL_COCOA
    {"", OPT_SUBSTRUCT(cocoa_opts, cocoa_conf)},
#endif

#if HAVE_COCOA
    {"", OPT_SUBSTRUCT(macos_opts, macos_conf)},
#endif

#if HAVE_DRM
    {"", OPT_SUBSTRUCT(drm_opts, drm_conf)},
#endif

#if HAVE_WAYLAND
    {"", OPT_SUBSTRUCT(wayland_opts, wayland_conf)},
#endif

#if HAVE_GL_WIN32
    {"opengl-dwmflush", OPT_CHOICE(wingl_dwm_flush,
        {"no", -1}, {"auto", 0}, {"windowed", 1}, {"yes", 2})},
#endif

#if HAVE_CUDA_HWACCEL
    {"cuda-decode-device", OPT_CHOICE(cuda_device, {"auto", -1}),
        M_RANGE(0, INT_MAX)},
#endif

#if HAVE_VAAPI
    {"vaapi", OPT_SUBSTRUCT(vaapi_opts, vaapi_conf)},
#endif

    {"sws", OPT_SUBSTRUCT(sws_opts, sws_conf)},

#if HAVE_ZIMG
    {"zimg", OPT_SUBSTRUCT(zimg_opts, zimg_conf)},
#endif

    {"", OPT_SUBSTRUCT(encode_opts, encode_config)},

    {"a52drc", OPT_REMOVED("use --ad-lavc-ac3drc=level")},
    {"afm", OPT_REMOVED("use --ad=...")},
    {"aspect", OPT_REPLACED("video-aspect-override")},
    {"ass-bottom-margin", OPT_REMOVED("use --vf=sub=bottom:top")},
    {"ass", OPT_REPLACED("sub-ass")},
    {"audiofile", OPT_REPLACED("audio-file")},
    {"benchmark", OPT_REMOVED("use --untimed (no stats)")},
    {"capture", OPT_REMOVED(NULL)},
    {"stream-capture", OPT_REMOVED(NULL)},
    {"channels", OPT_REMOVED("use --audio-channels (changed semantics)")},
    {"cursor-autohide-delay", OPT_REPLACED("cursor-autohide")},
    {"delay", OPT_REPLACED("audio-delay")},
    {"dumpstream", OPT_REMOVED("use --stream-dump=<filename>")},
    {"dvdangle", OPT_REPLACED("dvd-angle")},
    {"endpos", OPT_REPLACED("length")},
    {"font", OPT_REPLACED("osd-font")},
    {"forcedsubsonly", OPT_REPLACED("sub-forced-only")},
    {"format", OPT_REPLACED("audio-format")},
    {"hardframedrop", OPT_REMOVED(NULL)},
    {"identify", OPT_REMOVED("use TOOLS/mpv_identify.sh")},
    {"lavdopts", OPT_REMOVED("use --vd-lavc-...")},
    {"lavfdopts", OPT_REMOVED("use --demuxer-lavf-...")},
    {"lua", OPT_REPLACED("script")},
    {"lua-opts", OPT_REPLACED("script-opts")},
    {"mixer-channel", OPT_REMOVED("use AO suboptions (alsa, oss)")},
    {"mixer", OPT_REMOVED("use AO suboptions (alsa, oss)")},
    {"mouse-movements", OPT_REPLACED("input-cursor")},
    {"msgcolor", OPT_REPLACED("msg-color")},
    {"msglevel", OPT_REMOVED("use --msg-level (changed semantics)")},
    {"msgmodule", OPT_REPLACED("msg-module")},
    {"name", OPT_REPLACED("x11-name")},
    {"noar", OPT_REPLACED("no-input-appleremote")},
    {"noautosub", OPT_REPLACED("no-sub-auto")},
    {"noconsolecontrols", OPT_REPLACED("no-input-terminal")},
    {"nosound", OPT_REPLACED("no-audio")},
    {"osdlevel", OPT_REPLACED("osd-level")},
    {"panscanrange", OPT_REMOVED("use --video-zoom, --video-pan-x/y")},
    {"playing-msg", OPT_REPLACED("term-playing-msg")},
    {"pp", OPT_REMOVED(NULL)},
    {"pphelp", OPT_REMOVED(NULL)},
    {"rawaudio", OPT_REMOVED("use --demuxer-rawaudio-...")},
    {"rawvideo", OPT_REMOVED("use --demuxer-rawvideo-...")},
    {"spugauss", OPT_REPLACED("sub-gauss")},
    {"srate", OPT_REPLACED("audio-samplerate")},
    {"ss", OPT_REPLACED("start")},
    {"stop-xscreensaver", OPT_REPLACED("stop-screensaver")},
    {"sub-fuzziness", OPT_REPLACED("sub-auto")},
    {"subcp", OPT_REPLACED("sub-codepage")},
    {"subdelay", OPT_REPLACED("sub-delay")},
    {"subfile", OPT_REPLACED("sub-file")},
    {"subfont-text-scale", OPT_REPLACED("sub-scale")},
    {"subfont", OPT_REPLACED("sub-text-font")},
    {"subfps", OPT_REPLACED("sub-fps")},
    {"subpos", OPT_REPLACED("sub-pos")},
    {"tvscan", OPT_REPLACED("tv-scan")},
    {"use-filename-title", OPT_REMOVED("use --title='${filename}'")},
    {"vc", OPT_REMOVED("use --vd=..., --hwdec=...")},
    {"vobsub", OPT_REMOVED("use --sub-file (pass the .idx file)")},
    {"xineramascreen", OPT_REMOVED("use --screen (different values)")},
    {"xy", OPT_REMOVED("use --autofit")},
    {"zoom", OPT_REMOVED("Inverse available as ``--video-unscaled")},
    {"media-keys", OPT_REPLACED("input-media-keys")},
    {"right-alt-gr", OPT_REPLACED("input-right-alt-gr")},
    {"autosub", OPT_REPLACED("sub-auto")},
    {"autosub-match", OPT_REPLACED("sub-auto")},
    {"status-msg", OPT_REPLACED("term-status-msg")},
    {"idx", OPT_REPLACED("index")},
    {"forceidx", OPT_REPLACED("index")},
    {"cache-pause-below", OPT_REMOVED("for 'no', use --no-cache-pause")},
    {"no-cache-pause-below", OPT_REMOVED("use --no-cache-pause")},
    {"volstep", OPT_REMOVED("edit input.conf directly instead")},
    {"fixed-vo", OPT_REMOVED("--fixed-vo=yes is now the default")},
    {"mkv-subtitle-preroll", OPT_REPLACED("demuxer-mkv-subtitle-preroll")},
    {"ass-use-margins", OPT_REPLACED("sub-use-margins")},
    {"media-title", OPT_REPLACED("force-media-title")},
    {"input-unix-socket", OPT_REPLACED("input-ipc-server")},
    {"softvol-max", OPT_REPLACED("volume-max")},
    {"bluray-angle", OPT_REMOVED("this didn't do anything for a few releases")},
    {"sub-text-font", OPT_REPLACED("sub-font")},
    {"sub-text-font-size", OPT_REPLACED("sub-font-size")},
    {"sub-text-color", OPT_REPLACED("sub-color")},
    {"sub-text-border-color", OPT_REPLACED("sub-border-color")},
    {"sub-text-shadow-color", OPT_REPLACED("sub-shadow-color")},
    {"sub-text-back-color", OPT_REPLACED("sub-back-color")},
    {"sub-text-border-size", OPT_REPLACED("sub-border-size")},
    {"sub-text-shadow-offset", OPT_REPLACED("sub-shadow-offset")},
    {"sub-text-spacing", OPT_REPLACED("sub-spacing")},
    {"sub-text-margin-x", OPT_REPLACED("sub-margin-x")},
    {"sub-text-margin-y", OPT_REPLACED("sub-margin-y")},
    {"sub-text-align-x", OPT_REPLACED("sub-align-x")},
    {"sub-text-align-y", OPT_REPLACED("sub-align-y")},
    {"sub-text-blur", OPT_REPLACED("sub-blur")},
    {"sub-text-bold", OPT_REPLACED("sub-bold")},
    {"sub-text-italic", OPT_REPLACED("sub-italic")},
    {"ass-line-spacing", OPT_REPLACED("sub-ass-line-spacing")},
    {"ass-force-margins", OPT_REPLACED("sub-ass-force-margins")},
    {"ass-vsfilter-aspect-compat", OPT_REPLACED("sub-ass-vsfilter-aspect-compat")},
    {"ass-vsfilter-color-compat", OPT_REPLACED("sub-ass-vsfilter-color-compat")},
    {"ass-vsfilter-blur-compat", OPT_REPLACED("sub-ass-vsfilter-blur-compat")},
    {"ass-force-style", OPT_REPLACED("sub-ass-force-style")},
    {"ass-styles", OPT_REPLACED("sub-ass-styles")},
    {"ass-hinting", OPT_REPLACED("sub-ass-hinting")},
    {"ass-shaper", OPT_REPLACED("sub-ass-shaper")},
    {"ass-style-override", OPT_REPLACED("sub-ass-style-override")},
    {"ass-scale-with-window", OPT_REPLACED("sub-ass-scale-with-window")},
    {"sub-ass-style-override", OPT_REPLACED("sub-ass-override")},
    {"fs-black-out-screens", OPT_REMOVED(NULL)},
    {"sub-paths", OPT_REPLACED("sub-file-paths")},
    {"heartbeat-cmd", OPT_REMOVED("use Lua scripting instead")},
    {"no-ometadata", OPT_REMOVED("use --no-ocopy-metadata")},
    {"video-stereo-mode", OPT_REMOVED("removed, try --vf=stereo3d")},
    {"chapter", OPT_REMOVED("use '--start=#123' '--end=#124' (for chapter 123)")},
    {"video-aspect", OPT_REPLACED("video-aspect-override")},
    {"display-fps", OPT_REPLACED("override-display-fps")},

    {0}
};

// Optimized for fplayer 
static const struct MPOpts mp_default_opts = {
    .use_terminal = true,
    .msg_color = true,
    .softvol_max = 200, // 160 // 130
    .softvol_volume = 80,  // 100
    .gapless_audio = -1,
    // .wintitle = "${?media-title:${media-title}}${!media-title:No file} - mpv",
    .wintitle = "${?media-title:${media-title}}${!media-title:No file} - fplayer",

    .status_msg = "\n\nFile:  [${file-format}]   ${filename}\n   ${?current-demuxer: -> ${current-demuxer}}   ${?stream-end:${stream-end}}\nVideo: [${current-tracks/video/id}] ${?video-format:${video-format}}   ${?video-params:${video-params/w}x${video-params/h}}   ${?estimated-vf-fps:${estimated-vf-fps} fps}   ${?video-params/colorlevels:${video-params/colorlevels}} ${?video-params/colormatrix:${video-params/colormatrix}}   ${?video-params/primaries:${video-params/primaries}} ${?video-params/max-luma:${video-params/max-luma}}\n   ${?current-vo: -> ${current-vo}} ${?video-params/pixelformat:${video-params/pixelformat}}   ${!osd-dimensions/w==0:${osd-dimensions/w}x${osd-dimensions/h}}   ${?display-fps:${display-fps} fps}   ${?video-bitrate:${video-bitrate}}\nAudio: [${current-tracks/audio/id}] ${?audio-codec:${audio-codec-name}}   ${?audio-params/samplerate:${audio-params/samplerate}Hz}   ${?audio-params/channels:${audio-params/channels}} ${?audio-params/channel-count:(${audio-params/channel-count}ch)}\n   ${?current-ao: -> ${current-ao}} ${?audio-params/format:${audio-params/format}}   ${?audio-out-params/samplerate:${audio-out-params/samplerate}Hz}   ${?audio-out-params/channels:${audio-out-params/channels}} ${?audio-out-params/channel-count:(${audio-out-params/channel-count}ch)}   ${?audio-bitrate:${audio-bitrate}}\nSub  : [${current-tracks/sub/id}] ${?current-tracks/sub:${current-tracks/sub/lang}}\n\n\n${?mute==yes:Volume: Muted}${?mute==no:Volume: ${volume}%  }${?ao-volume==100:     }${!ao-volume==100:[${ao-volume}%]}                          | ${?estimated-display-fps:FPS: ${estimated-display-fps}}${?current-window-scale:${!current-window-scale==1.000:  Scale: ${current-window-scale} }}\n${?paused-for-cache==yes:[Cachin] }${?paused-for-cache==no:${?core-idle==no:[ x${speed}] }}${?core-idle==yes:${?percent-pos==100:[Ended ] }}${?paused-for-cache==no:${?core-idle==yes:${!percent-pos==100:[Paused] }}} ${playback-time/full} / ${duration/full} (${percent-pos}%) | ${?avsync:A-V:${avsync}   }${?demuxer-cache-duration:Caches:${cache-speed}}   ${?frame-drop-count:${!frame-drop-count==0:Dropped:${frame-drop-count}  }} ${?mistimed-frame-count:${!mistimed-frame-count==0:Mistimed:${mistimed-frame-count}  }}",
    .keep_open = 1,  // no: 0  yes: 1  always: 2
    // .border = false,  // 在 vo_sub_opts 里
    .position_save_on_quit = true,
    .watch_later_directory = "~~/_cache/watch_later",
    

    .pause = true,
    .stop_screensaver = 1,
    .cursor_autohide_delay = 1000,
    .video_osd = false, // true
    .osd_level = 0,  // 1
    .osd_on_seek = 0,  // 1
    .osd_duration = 1000,
#if HAVE_LUA
    .lua_load_osc = false,  // true
    .lua_load_ytdl = true,
    .lua_ytdl_format = NULL,
    .lua_ytdl_raw_options = NULL,
    .lua_load_stats = true,
    .lua_load_console = true,
    .lua_load_auto_profiles = -1,
#endif
    .auto_load_scripts = false,  // true
    .loop_times = 1,
    .ordered_chapters = true,
    .chapter_merge_threshold = 100,
    .chapter_seek_threshold = 5.0,
    .hr_seek = 2,
    .hr_seek_framedrop = false,  // true  // 跳转时丢帧 利于修正音频延迟

    .sync_max_video_change = 5,  // 1
    // {"video-sync-max-video-change", OPT_DOUBLE(sync_max_video_change), M_RANGE(0, DBL_MAX)},

    .sync_max_audio_change = 0.125,
    .sync_max_factor = 5,
    .load_config = false,  // true
    .position_resume = true,
    .autoload_files = true,
    .demuxer_thread = true,
    .demux_termination_timeout = 0.1,
    .hls_bitrate = INT_MAX,
    .cache_pause = true,
    .cache_pause_wait = 1.0,
    .ab_loop = {MP_NOPTS_VALUE, MP_NOPTS_VALUE},
    .ab_loop_count = -1,
    .edition_id = -1,
    .default_max_pts_correction = -1,
    .initial_audio_sync = true,
    .frame_dropping = 1,
    .term_osd = 0,  // 2
    .term_osd_bar_chars = "[-+-]",
    .consolecontrols = true,
    .playlist_pos = -1,
    .play_frames = -1,
    .rebase_start_time = true,
    .keep_open_pause = true,
    .image_display_duration = 1.0,
    .stream_id = { { [STREAM_AUDIO] = -1,
                     [STREAM_VIDEO] = -1,
                     [STREAM_SUB] = -1, },
                   { [STREAM_AUDIO] = -2,
                     [STREAM_VIDEO] = -2,
                     [STREAM_SUB] = -2, }, },
    .stream_lang = {
        [STREAM_SUB] = (char *[]){ "auto", NULL },
    },
    .stream_auto_sel = true,
    .subs_with_matching_audio = false,
    .subs_fallback_forced = true,
    .audio_display = 1,
    .audio_output_format = 0,  // AF_FORMAT_UNKNOWN
    .playback_speed = 1.,
    .pitch_correction = true,

    .sub_auto = 1,
    .audiofile_auto = 1,  // -1
    // {"sub-auto", OPT_CHOICE(sub_auto,
    //     {"no", -1}, {"exact", 0}, {"fuzzy", 1}, {"all", 2})},
    // {"audio-file-auto", OPT_CHOICE(audiofile_auto,
    //     {"no", -1}, {"exact", 0}, {"fuzzy", 1}, {"all", 2})},
    // {"cover-art-auto", OPT_CHOICE(coverart_auto,
    //     {"no", -1}, {"exact", 0}, {"fuzzy", 1}, {"all", 2})},
    // {"cover-art-whitelist", OPT_BOOL(coverart_whitelist)},
    .coverart_whitelist = true,
    .osd_bar_visible = false,  // true

    .screenshot_template = "FPLAYER-Screenshot-%n",
    // {"screenshot", OPT_SUBSTRUCT(screenshot_image_opts, screenshot_conf)},
    // {"screenshot-template", OPT_STRING(screenshot_template)},
    // {"screenshot-directory", OPT_STRING(screenshot_directory),
    //     .flags = M_OPT_FILE},
    // {"screenshot-sw", OPT_BOOL(screenshot_sw)},
    .play_dir = 1,

    .audio_output_channels = {
        .set = 1,
        .auto_safe = 1,
    },

    .index_mode = 1,

    .mf_fps = 1.0,

    .display_tags = (char *[]){
        "Artist", "Album", "Album_Artist", "Comment", "Composer",
        "Date", "Description", "Genre", "Performer", "Rating",
        "Series", "Title", "Track", "icy-title", "service_name",
        "Uploader", "Channel_URL",
        NULL
    },

    .cuda_device = -1,

    .watch_later_options = (char *[]){
        "start",
        "osd-level",
        "speed",
        "edition",
        "pause",
        "volume",
        "mute",
        "audio-delay",
        "fullscreen",
        "ontop",
        "border",
        "gamma",
        "brightness",
        "contrast",
        "saturation",
        "hue",
        "deinterlace",
        "vf",
        "af",
        "panscan",
        "aid",
        "vid",
        "sid",
        "sub-delay",
        "sub-speed",
        "sub-pos",
        "sub-visibility",
        "sub-scale",
        "sub-use-margins",
        "sub-ass-force-margins",
        "sub-ass-vsfilter-aspect-compat",
        "sub-ass-override",
        "ab-loop-a",
        "ab-loop-b",
        "video-aspect-override",
        NULL
    },
};

const struct m_sub_options mp_opt_root = {
    .opts = mp_opts,
    .size = sizeof(struct MPOpts),
    .defaults = &mp_default_opts,
};

#endif /* MPLAYER_CFG_MPLAYER_H */
