
#ifndef __IMGUI_W__
#define __IMGUI_W__

//----------------------------------------------------------------

extern "C" {
    #include <sftlstd/vld3.h>
};

#include <sftlstd/vl3d_imgui.h>

#include <imgui/imgui_internal.h>
#include <imgui/imgui.h>

//----------------------------------------------------------------

void imgui_mat_get (void *ptr, t_f64 *mat, t_f64 *def)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	
	s_vl3hpr def_hpr = vl3hpr_mat(def);
	
	s_vl3hpr hpr = {
//			.heading = window->StateStorage.GetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x00)), vld_rad(45)),
//			.pitch 	 = window->StateStorage.GetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x01)), vld_rad(45)),
//			.roll    = window->StateStorage.GetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x02)), vld_rad( 0)),
			.heading = window->StateStorage.GetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x00)), def_hpr.heading),
			.pitch 	 = window->StateStorage.GetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x01)), def_hpr.pitch),
			.roll    = window->StateStorage.GetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x02)), def_hpr.roll),
	};
	
	vld3m_rot(mat, hpr);
}

//----------------------------------------------------------------

void imgui_mat_set (void *ptr, t_f64 *mat)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	
	s_vl3hpr hpr = vl3hpr_mat(mat);
	
	window->StateStorage.SetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x00)), (float) hpr.heading);
	window->StateStorage.SetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x01)), (float) hpr.pitch);
	window->StateStorage.SetFloat(ImGui::GetID((void*) ((uintptr_t) ptr + 0x02)), (float) hpr.roll);
}

//----------------------------------------------------------------

void imgui_vec3 (char *label, t_f64 *vec,
                float v_speed, t_f64 min, t_f64 max, char *format)
{
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    ImGui::DragScalarN(label, ImGuiDataType_Double, vec, 3, v_speed, &min, &max, format);
}

//----------------------------------------------------------------

void imgui_vec (t_s32 dim, char *label, t_f64 *vec,
                float v_speed, t_f64 min, t_f64 max, char *format)
{
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);

    ImGui::DragScalarN(label, ImGuiDataType_Double,
                       vec, dim, v_speed, &min, &max, format);
}

//----------------------------------------------------------------

void imgui_hpr (char *label, s_vl3hpr *hpr, float v_speed, char *format)
{
	static t_f64 heading_min = 0.0;
	static t_f64 heading_max = 360.0;
	
	static t_f64 pitch_min = -90.0;
	static t_f64 pitch_max = +90.0;
	
	static t_f64 roll_min = -180.0;
	static t_f64 roll_max = +180.0;
	
	s_vl3hpr hpr_deg;
	
	hpr_deg.heading = vld_deg(hpr->heading);
	hpr_deg.pitch   = vld_deg(hpr->pitch);
	hpr_deg.roll    = vld_deg(hpr->roll);

//	t_f64 hpr_deg[3] = {
//			(float) vld_deg(hpr->heading),
//			(float) vld_deg(hpr->pitch),
//			(float) vld_deg(hpr->roll)
//	};
//
	float item_width = ImGui::GetContentRegionAvail().x / 3 - 2.0/3.0 * ImGui::GetStyle().ItemInnerSpacing.x;
	
	ImGui::PushID(label);

//	vl_gui_vec("##hpr", hpr_deg, 1.0, NULL, NULL, "%.0f");
	
	ImGui::SetNextItemWidth(item_width);
	ImGui::DragScalar("##heading", ImGuiDataType_Double, &hpr_deg.heading, v_speed, &heading_min, &heading_max, format);
	if (ImGui::IsItemHovered()) { ImGui::SetTooltip("heading [deg]"); }
	ImGui::SameLine(1*item_width+ImGui::GetStyle().ItemInnerSpacing.x, 0.0);
	ImGui::SetNextItemWidth(item_width);
	ImGui::DragScalar("##pitch", ImGuiDataType_Double, &hpr_deg.pitch  , v_speed, &pitch_min, &pitch_max, format);
	if (ImGui::IsItemHovered()) { ImGui::SetTooltip("pitch [deg]"); }
	ImGui::SameLine(2*(item_width+ImGui::GetStyle().ItemInnerSpacing.x), 0.0);
	ImGui::SetNextItemWidth(item_width);
	ImGui::DragScalar("##roll", ImGuiDataType_Double, &hpr_deg.roll   , v_speed, &pitch_min, &pitch_max, format);
	if (ImGui::IsItemHovered()) { ImGui::SetTooltip("roll [deg]"); }
	
	ImGui::PopID();
	
	hpr->heading = vld_rad(hpr_deg.heading);
	hpr->pitch   = vld_rad(hpr_deg.pitch);
	hpr->roll    = vld_rad(hpr_deg.roll);

//	hpr->heading = vld_rad(hpr_deg[0]);
//	hpr->pitch   = vld_rad(hpr_deg[1]);
//	hpr->roll    = vld_rad(hpr_deg[2]);
}

//----------------------------------------------------------------

void imgui_mat (char *label, t_f64 *mat, float v_speed, t_f64 *min, t_f64 *max, char *format)
{
	ImGui::PushID(label);
	
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	
	ImGui::BeginGroup();
	
	for (int i = 0; i < 3; ++i)
	{
		ImGui::PushID(i);
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::DragScalarN("##mat_view", ImGuiDataType_Double, &mat[3 * i], 3, v_speed, min, max, format);
		ImGui::PopID();
	}
	
	ImGui::EndGroup();
	
	ImGui::PopID();
}

//----------------------------------------------------------------

void imgui_rot (char *label, t_f64 *mat)
{
	enum st
	{
		st_mode = 100,
		st_heading,
		st_pitch,
		st_roll,
		st_scale
	};
	
	ImGui::PushID(label);
	
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	
	int mode = window->StateStorage.GetInt(ImGui::GetID(mat + 0xFFFF), 0x00);
	
	ImGui::BeginGroup();
	
	switch (mode)
	{
		default:
		{
			s_vl3d 		vl3d;
			s_vl3d_obj 	vl3d_obj_list[32];
			s_vl3d_view vl3d_view;
			
			vl3d_view_load(mat, &vl3d_view, (s_vl3d_view) {});
			vl3d_view.scale = 0.75;
			vld3v_set(vl3d_view.pos, 0.0);
			
			vl3d_init(&vl3d, (s_vl3d_attr) {
				.obj_sz = sizeof(vl3d_obj_list) / sizeof(s_vl3d_obj),
				.obj_ls = vl3d_obj_list
			});
			
			vl3d_draw_arrow(&vl3d, vl3d_col_d, vld3v(-1.0, +0.0, +0.0), vld3v(+1.0, +0.0, +0.0) );
			vl3d_draw_arrow(&vl3d, vl3d_col_d, vld3v(+0.0, -1.0, +0.0), vld3v(+0.0, +1.0, +0.0) );
			vl3d_draw_arrow(&vl3d, vl3d_col_d, vld3v(+0.0, +0.0, -1.0), vld3v(+0.0, +0.0, +1.0) );
			
			vl3d_draw_arrow(&vl3d, vl3d_col_legacy,
								vld3v(-mat[0*3+0], -mat[1*3+0], -mat[2*3+0]),
								vld3v(+mat[0*3+0], +mat[1*3+0], +mat[2*3+0])
			);
			
			vl3d_draw_arrow(&vl3d, vl3d_col_legacy,
								vld3v(-mat[0*3+1], -mat[1*3+1], -mat[2*3+1]),
								vld3v(+mat[0*3+1], +mat[1*3+1], +mat[2*3+1])
			);
			
			vl3d_draw_arrow(&vl3d, vl3d_col_legacy,
								vld3v(-mat[0*3+2], -mat[1*3+2], -mat[2*3+2]),
								vld3v(+mat[0*3+2], +mat[1*3+2], +mat[2*3+2])
			);

			vl3d_add_line(&vl3d, (s_vl3d_line) { .color = vl3d_col_d, .p0 = { +1.0, +0.0, +0.0 }, .p1 = { mat[0*3+0], mat[1*3+0], mat[2*3+0] } } );
			vl3d_add_line(&vl3d, (s_vl3d_line) { .color = vl3d_col_d, .p0 = { +0.0, +1.0, +0.0 }, .p1 = { mat[0*3+1], mat[1*3+1], mat[2*3+1] } } );
			vl3d_add_line(&vl3d, (s_vl3d_line) { .color = vl3d_col_d, .p0 = { +0.0, +0.0, +1.0 }, .p1 = { mat[0*3+2], mat[1*3+2], mat[2*3+2] } } );
			
			vl3d_add_text(&vl3d, (s_vl3d_text) { .color = vl3d_col_d, .p0 = { +1.0, +0.0, +0.0 }, .data = "X0" } );
			vl3d_add_text(&vl3d, (s_vl3d_text) { .color = vl3d_col_d, .p0 = { +0.0, +1.0, +0.0 }, .data = "Y0" } );
			vl3d_add_text(&vl3d, (s_vl3d_text) { .color = vl3d_col_d, .p0 = { +0.0, +0.0, +1.0 }, .data = "Z0" } );
			
			vl3d_add_text(&vl3d, (s_vl3d_text) { .color = vl3d_col_legacy, .p0 = { mat[0*3+0], mat[1*3+0], mat[2*3+0] }, .data = "X" } );
			vl3d_add_text(&vl3d, (s_vl3d_text) { .color = vl3d_col_legacy, .p0 = { mat[0*3+1], mat[1*3+1], mat[2*3+1] }, .data = "Y" } );
			vl3d_add_text(&vl3d, (s_vl3d_text) { .color = vl3d_col_legacy, .p0 = { mat[0*3+2], mat[1*3+2], mat[2*3+2] }, .data = "Z" } );
			
			vl3d_begin(&vl3d, ImVec2(
					ImGui::GetContentRegionAvail().x,
					ImGui::GetContentRegionAvail().x)
					);
			
			vl3d_view_ctrl3d(&vl3d, &vl3d_view);
			vl3d_view_draw(&vl3d, &vl3d_view);
			vl3d_end();
			
			vl3d_view_save(mat, &vl3d_view);
			
			{
				s_vl3hpr rot_hpr = vl3hpr_mat(mat);
				imgui_hpr("##hpr", &rot_hpr, 1.0, "%.0f");
				vld3m_rot(mat, rot_hpr);
			}
			
			break;
		}
		
		case 0x01:
		{
			static t_f64 min = -1;
			static t_f64 max = +1;
			
			imgui_mat(label, mat, 0.001, &min, &max, "%.001f");
			
			break;
		}
	}
	
	ImGui::EndGroup();
	
	if (ImGui::BeginPopupContextItem("item context menu"))
	{
		if (ImGui::Selectable("3d")) mode = 0x00;
		if (ImGui::Selectable("mat")) mode = 0x01;
		
		ImGui::EndPopup();
	}
	
	window->StateStorage.SetInt(ImGui::GetID(mat + 0xFFFF), mode);
	
	ImGui::PopID();
}

//----------------------------------------------------------------

bool imgui_hash (char *label, t_u32 hash)
{
	ImGui::PushID(label);
	
	ImGuiStyle style = ImGui::GetStyle();
	bool res = false;

	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	
	float dy = ImGui::GetTextLineHeightWithSpacing() * 0.5;
	float dx = ImGui::GetContentRegionAvail().x / 16.0;
	
	float height = 2 * dy;
	float width  = 16 * dx;
	
	if (ImGui::InvisibleButton(label, ImVec2(width, height)))
	{ res = true; }
	
	t_u32 col_table[2] = {
			ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_FrameBg]), vl3d_col_l
	};
	
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 16; ++x)
		{
			draw_list->AddRectFilled(
					ImVec2(p.x+x*dx, p.y+y*dy),
					ImVec2(p.x+(x+1)*dx, p.y+(y+1)*dy),
					col_table[(hash & (1 << (y*16+x))) > 0x00]
					);
		}
	}
	
	ImGui::PopID();
	
	return res;
}

//----------------------------------------------------------------

void imgui_bool (char *label, ImVec2 size, t_u8 *data)
{
//	ImGuiStyle& style = ImGui::GetStyle();
//	ImU32 col_text_u32 = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]);
//	ImU32 col_textdis_u32 = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_TextDisabled]);
//	ImU32 col_button_u32 = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Button]);
//
//	ImVec2 p = ImGui::GetCursorScreenPos();
//	ImDrawList* draw_list = ImGui::GetWindowDrawList();
//
//	float height = ImGui::GetFrameHeight();
//	float width = height * 2.0f;
//
//	if (ImGui::InvisibleButton(label, ImVec2(width, height)))
//	{
//		*data = (!*data) & 0x01;
//	}
//
//	switch (*data)
//	{
//		case 0x00:
//		{
//			draw_list->AddRect(ImVec2(p.x, p.y), ImVec2(p.x+width, p.y+height), col_text_u32);
//			draw_list->AddText(ImVec2(p.x, p.y), col_text_u32, "OFF");
//
//			break;
//		}
//
//		default:
//		{
//			draw_list->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x+width, p.y+height), col_button_u32);
//			draw_list->AddText(ImVec2(p.x, p.y), col_text_u32, "ON");
//
//			break;
//		}
//	}
//
	ImGui::PushID(label);
	
	if (ImGui::Button((*data == 0x00) ? "OFF" : "ON", size))
	{ *data = (!*data) & 0x01; }
	
	ImGui::PopID();

//	ImU32 col_bg;
//
//	if (ImGui::IsItemHovered())
//		col_bg = *data ? IM_COL32(145+20, 211, 68+20, 255) : IM_COL32(218-20, 218-20, 218-20, 255);
//	else
//		col_bg = *data ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);
//
//	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg);
//	draw_list->AddRectFilled(ImVec2(*data ? (p.x + width) : (p.x), p.y), ImVec2(*data ? (p.x + width) : (p.x), p.y), IM_COL32(255, 255, 255, 255));
}

//----------------------------------------------------------------

void imgui_switch (char *label, char **labels, ImVec2 size, t_u8 *data, int flags = ImGuiButtonFlags_None)
{
	ImGui::PushID(label);
	
	if (*data != 0x00) { *data = 0x01; }
	
	if (ImGui::ButtonEx(labels[*data], size, flags))
	{ *data = (*data != 0x00) ? 0x00 : 0x01; }
	
	if (*data != 0x00) { *data = 0x01; }
	
	ImGui::PopID();
}

//----------------------------------------------------------------

void imgui_switchbox (char *label, char **labels, ImVec2 size, t_u8 *data)
{
	ImGui::PushID(label);

	ImGuiStyle& style = ImGui::GetStyle();
	ImU32 col_text_u32 = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]);
	ImU32 col_textdis_u32 = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_TextDisabled]);
	ImU32 col_button_u32 = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Button]);

	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = size.x;

//	if (ImGui::InvisibleButton(label, ImVec2(width, height)))
//	{
//		*data = (!*data) & 0x01;
//	}

	switch (*data)
	{
		case 0x00:
		{
			draw_list->AddRect(ImVec2(p.x, p.y), ImVec2(p.x+width, p.y+height), col_button_u32);

			float font_size = ImGui::GetFontSize() * strlen(labels[0x00]) / 2;
			ImGui::SameLine(width / 2 - font_size + (font_size / 2));
			ImGui::Text(labels[0x00]);

//			draw_list->AddText(ImVec2(p.x, p.y), col_text_u32, "OFF");
			
			break;
		}

		default:
		{
			draw_list->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x+width, p.y+height), col_button_u32);
			
			float font_size = ImGui::GetFontSize() * strlen(labels[0x00]) / 2;
			ImGui::SameLine(width / 2 - font_size + (font_size / 2));
			ImGui::Text(labels[0x01]);
			
//			draw_list->AddText(ImVec2(p.x, p.y), col_text_u32, "ON");

			break;
		}
	}
	
	ImGui::SetCursorScreenPos(p + ImVec2(width, 0));
	
	ImGui::PopID();
}

//----------------------------------------------------------------

void __imgui_lla_elem__ (char *label, char **nswe, t_f64 *range, t_f64 *value, float width)
{
    ImGuiWindow *window = ImGui::GetCurrentWindow();

    char mode_str[64];
    sprintf(mode_str, "##%s_%s", label, "mode");
    ImGuiID mode_id = ImGui::GetID(mode_str);

    t_u8 mode = window->StateStorage.GetInt(mode_id, 0x00);

    // remove sign life is easier that way
    // we MUST AND WILL resore it in the end
    t_u8 nswe_sign = (*value < 0.0) ? 0x00 : 0x01;
    *value = fabs(*value);

    t_f64 value_deg = vld_deg(*value);
    int dms_d = (int) value_deg;
    int dms_m = (int) ((value_deg - dms_d) * 60);
    t_f64 dms_s = (value_deg - dms_d - dms_m / (t_f64) 60.0) * 3600;

    ImGui::PushID(label);
    ImGui::BeginGroup();

//    vl_gui_switch("##d/dms", "Г", "ГМС", ImVec2(50, 0), &mode);
//    ImGui::SameLine();

    ImGui::SetNextItemWidth(width-40);

    switch (mode)
    {
        case 0x01:
        {
            char dms_str[32];
            sprintf(dms_str, "% 3d°%02d'%06.3f\"", dms_d, dms_m, dms_s);
            ImGui::InputText("##dms", dms_str, sizeof(dms_str));
            sscanf(dms_str, "%d°%d'%lf\"", &dms_d, &dms_m, &dms_s);

            dms_s = (dms_s <   0.0) ?  0.0 : dms_s;
            dms_s = (dms_s >= 60.0) ? 60.0 : dms_s;

            dms_m = (dms_m <   0.0) ?  0.0 : dms_m;
            dms_m = (dms_m >= 60.0) ? 60.0 : dms_m;

            t_f64 value_new = vld_rad(
                    (t_f64) dms_d + (t_f64) dms_m / 60.0 + (t_f64) dms_s / 3600.0);

            *value = value_new;

            break;
        }

        default:
        {
            t_f64 value_new;

            char deg_str[32];
            sprintf(deg_str, "% 10.6f°", value_deg);
            ImGui::InputText("##deg", deg_str, sizeof(deg_str));
            sscanf(deg_str, "%lf°", &value_new);

            value_new = vld_rad(value_new);

            *value = value_new;

            break;
        }
    }

    ImGui::SameLine(0,0);
	imgui_switch("##nswe", nswe, ImVec2(40, 0), &nswe_sign);

    *value = (*value < range[0]) ? range[0] : *value;
    *value = (*value > range[1]) ? range[1] : *value;

    *value *= (nswe_sign == 0x00) ? -1.0 : +1.0;

    ImGui::EndGroup();

    if (ImGui::BeginPopupContextItem("##mode"))
    {
		if (ImGui::Selectable("DEG°")) { mode = 0x00; }
        if (ImGui::Selectable("DEG°MIN'SEC\"")) { mode = 0x01; }

        ImGui::EndPopup();
    }

    ImGui::PopID();

    window->StateStorage.SetInt(mode_id, mode);
}

//----------------------------------------------------------------

extern inline
void imgui_lat (char *label, t_f64 *lat, float width = 160)
{
    __imgui_lla_elem__(label, (char*[2]){ "S", "N" },
                     (t_f64[2]) { vld_rad(-90), vld_rad(+90) }, lat, width);
}

//----------------------------------------------------------------

extern inline
void imgui_lon (char *label, t_f64 *lon, float width = 160)
{
    __imgui_lla_elem__(label, (char*[2]){ "W", "E" },
                     (t_f64[2]) { vld_rad(-180), vld_rad(+180) }, lon, width);
}

//----------------------------------------------------------------

typedef struct
{
	int day;
	int month;
	int year;
	
	int hour;
	int min;
	int sec;
	
}	s_imgui_datetime;

void imgui_datetime (char *label,
		int *day, int *month, int *year,
		int *hour, int *min, int *sec)
{
	ImGui::PushID(label);
	
	char datetime_str[64];
	
	sprintf(datetime_str, "%02d/%02d/%04d %02d:%02d:%02d",
			*day, *month, *year, *hour, *min, *sec);
	
	ImGui::InputText("##datetime", datetime_str, sizeof(datetime_str));
	
	sscanf(datetime_str, "%02d/%02d/%04d %02d:%02d:%02d",
		   day , month, year, hour, min  , sec);
	
	*day   = (*day   <    1) ?    1 : *day;
	*day   = (*day   >   30) ?   30 : *day;
	
	*month = (*month <    1) ?    1 : *month;
	*month = (*month >   12) ?   12 : *month;
	
	*year  = (*year  < 1990) ? 1990 : *year;
	*year  = (*year  > 3000) ? 3000 : *year;
	
	*hour  = (*hour  <    0) ?    0 : *hour;
	*hour  = (*hour  >   23) ?   23 : *hour;
	
	*min   = (*min   <    0) ?    0 : *min;
	*min   = (*min   >   59) ?   59 : *min;
	
	*sec   = (*sec   <    0) ?    0 : *sec;
	*sec   = (*sec   >   59) ?   59 : *sec;
	
	ImGui::PopID();
}

//----------------------------------------------------------------

extern inline void 	 imgui_save_uint8   (char *label, t_u8  data) { ImGui::GetCurrentWindow()->StateStorage.SetInt    (ImGui::GetID(label), (int) data); return; }
extern inline void 	 imgui_save_uint16  (char *label, t_u16 data) { ImGui::GetCurrentWindow()->StateStorage.SetInt    (ImGui::GetID(label), (int) data); return; }
extern inline void 	 imgui_save_uint32  (char *label, t_u32 data) { ImGui::GetCurrentWindow()->StateStorage.SetInt    (ImGui::GetID(label), (int) data); return; }
extern inline void 	 imgui_save_int8    (char *label, t_s8  data) { ImGui::GetCurrentWindow()->StateStorage.SetInt    (ImGui::GetID(label), (int) data); return; }
extern inline void 	 imgui_save_int16   (char *label, t_s16 data) { ImGui::GetCurrentWindow()->StateStorage.SetInt    (ImGui::GetID(label), (int) data); return; }
extern inline void 	 imgui_save_int32   (char *label, t_s32 data) { ImGui::GetCurrentWindow()->StateStorage.SetInt    (ImGui::GetID(label), (int) data); return; }
extern inline void 	 imgui_save_float32 (char *label, t_f32 data) { ImGui::GetCurrentWindow()->StateStorage.SetFloat  (ImGui::GetID(label),       data); return; }
extern inline void 	 imgui_save_void    (char *label, void *data) { ImGui::GetCurrentWindow()->StateStorage.SetVoidPtr(ImGui::GetID(label),       data); return; }

extern inline t_u8   imgui_load_uint8   (char *label, t_u8  def ) { return (t_u8  ) ImGui::GetCurrentWindow()->StateStorage.GetInt    (ImGui::GetID(label), (int) def); }
extern inline t_u16  imgui_load_uint16  (char *label, t_u16 def ) { return (t_u16 ) ImGui::GetCurrentWindow()->StateStorage.GetInt    (ImGui::GetID(label), (int) def); }
extern inline t_u32  imgui_load_uint32  (char *label, t_u32 def ) { return (t_u32 ) ImGui::GetCurrentWindow()->StateStorage.GetInt    (ImGui::GetID(label), (int) def); }
extern inline t_s8   imgui_load_int8    (char *label, t_s8  def ) { return (t_s8  ) ImGui::GetCurrentWindow()->StateStorage.GetInt    (ImGui::GetID(label), (int) def); }
extern inline t_s16  imgui_load_int16   (char *label, t_s16 def ) { return (t_s16 ) ImGui::GetCurrentWindow()->StateStorage.GetInt    (ImGui::GetID(label), (int) def); }
extern inline t_s32  imgui_load_int32   (char *label, t_s32 def ) { return (t_s32 ) ImGui::GetCurrentWindow()->StateStorage.GetInt    (ImGui::GetID(label), (int) def); }
extern inline t_f32  imgui_load_float32 (char *label, t_f32 def ) { return (t_f32 ) ImGui::GetCurrentWindow()->StateStorage.GetFloat  (ImGui::GetID(label),       def); }
extern inline void*  imgui_load_void    (char *label            ) { return          ImGui::GetCurrentWindow()->StateStorage.GetVoidPtr(ImGui::GetID(label)           ); }

//----------------------------------------------------------------

extern inline
void gui_autowidth (void)
{
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
}

//inline void gui_hint(const char* fmt, ...)
//{
//	va_list args;
//	va_start (args, fmt);
//
//	if (ImGui::IsItemHovered()) { ImGui::SetTooltip(fmt, args); }
//
//	va_end (args);
//
//	return;
//}

#define gui_hint(fmt, ...) if (ImGui::IsItemHovered()) { ImGui::SetTooltip(fmt, ##__VA_ARGS__); }

//----------------------------------------------------------------

bool imgui_loadbar (const char* label, float value,
                                  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;
	
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	
	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = size_arg;
	
	if (size.x < 0) size.x = ImGui::GetContentRegionAvail().x;
	
	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;
	
	// Render
	window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + size.x, bb.Max.y), bg_col);
	window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + size.x*value, bb.Max.y), fg_col);
	
	return true;
}

//----------------------------------------------------------------

bool imgui_loadspin (const char* label,
                                   float radius, int thickness, const ImU32& color)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;
	
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	
	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size((radius )*2, (radius + style.FramePadding.y)*2);
	
	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;
	
	// Render
	window->DrawList->PathClear();
	
	int num_segments = 30;
	int start = ImAbs(ImSin(g.Time*1.8f)*(num_segments-5));
	
	const float a_min = IM_PI*2.0f * ((float)start) / (float)num_segments;
	const float a_max = IM_PI*2.0f * ((float)num_segments-3) / (float)num_segments;
	
	const ImVec2 centre = ImVec2(pos.x+radius, pos.y+radius+style.FramePadding.y);
	
	for (int i = 0; i < num_segments; i++) {
		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
		window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a+g.Time*8) * radius,
											centre.y + ImSin(a+g.Time*8) * radius));
	}
	
	window->DrawList->PathStroke(color, false, thickness);
	
	return true;
}

//----------------------------------------------------------------

#endif /* __IMGUI_W__ */


