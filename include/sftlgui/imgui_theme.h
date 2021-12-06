
//
//  Created by Egor Chekhov O'Leo on 24/12/2015.
//  Copyright © 2015 Control Systems Interfaces. All rights reserved.
//

#ifndef __IMGUI_THEME__
#define __IMGUI_THEME__

//----------------------------------------------------------------

#include <stdlib.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

//----------------------------------------------------------------

//----------------------------------------------------------------

inline void imgui_theme_set (void)
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	
	ImVec4 col_main = ImColor::HSV(0.583f, 1.000f, 1.000f, 1.000);
	
	colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg]               = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
	colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_FrameBgHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.40f);
	colors[ImGuiCol_FrameBgActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 0.67f);
	colors[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	colors[ImGuiCol_TitleBgActive]          = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg]              = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	colors[ImGuiCol_CheckMark]              = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	colors[ImGuiCol_SliderGrab]             = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
	colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
	colors[ImGuiCol_Button]                 = ImVec4(col_main.x, col_main.y, col_main.z, 0.40f);
	colors[ImGuiCol_ButtonHovered]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header]                 = ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
	colors[ImGuiCol_HeaderHovered]          = ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
	colors[ImGuiCol_HeaderActive]           = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
	colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip]             = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
	colors[ImGuiCol_ResizeGripHovered]      = ImVec4(col_main.x, col_main.y, col_main.z, 0.67f);
	colors[ImGuiCol_ResizeGripActive]       = ImVec4(col_main.x, col_main.y, col_main.z, 0.95f);
	colors[ImGuiCol_Tab]                    = ImLerp(colors[ImGuiCol_Header],       colors[ImGuiCol_TitleBgActive], 0.90f);
	colors[ImGuiCol_TabHovered]             = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive]              = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabUnfocused]           = ImLerp(colors[ImGuiCol_Tab],          colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive]     = ImLerp(colors[ImGuiCol_TabActive],    colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
	colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);   // Prefer using Alpha=1.0 here
	colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);   // Prefer using Alpha=1.0 here
	colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
	colors[ImGuiCol_TextSelectedBg]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
	colors[ImGuiCol_DragDropTarget]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.95f);
	colors[ImGuiCol_NavHighlight]           = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	
//	#if 1
//	// FIXME: those should become parameters to the function
//	static int hue = 140;
//	static float col_main_sat = 180.f / 255.f;
//	static float col_main_val = 161.f / 255.f;
//	static float col_area_sat = 124.f / 255.f;
//	static float col_area_val = 100.f / 255.f;
//	static float col_back_sat =  59.f / 255.f;
//	static float col_back_val =  40.f / 255.f;
//
//	ImGui::Begin("Hue Style");
//	ImGui::SliderInt("master hue", &hue, 0, 255);
//
//	float dummy;
//	ImVec4 rgb;
//	ImGui::SetColorEditOptions(ImGuiColorEditFlags_HSV);
//
//	ImGui::ColorConvertHSVtoRGB(hue/255.f, col_main_sat, col_main_val, rgb.x, rgb.y, rgb.z);
//	ImGui::ColorEdit3("main", &rgb.x);
//	ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_main_sat, col_main_val);
//
//	ImGui::ColorConvertHSVtoRGB(hue/255.f, col_area_sat, col_area_val, rgb.x, rgb.y, rgb.z);
//	ImGui::ColorEdit3("area", &rgb.x);
//	ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_area_sat, col_area_val);
//
//	ImGui::ColorConvertHSVtoRGB(hue/255.f, col_back_sat, col_back_val, rgb.x, rgb.y, rgb.z);
//	ImGui::ColorEdit3("back", &rgb.x);
//	ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_back_sat, col_back_val);
//
//	ImGui::End();
//	#endif
//
//	ImGuiStyle& style = ImGui::GetStyle();
//
//	ImVec4 col_text = ImColor::HSV(hue/255.f,  20.f/255.f, 235.f/255.f);
//	ImVec4 col_main = ImColor::HSV(hue/255.f, col_main_sat, col_main_val);
//	ImVec4 col_back = ImColor::HSV(hue/255.f, col_back_sat, col_back_val);
//	ImVec4 col_area = ImColor::HSV(hue/255.f, col_area_sat, col_area_val);
//
//	style.Colors[ImGuiCol_Text]                  = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
//	style.Colors[ImGuiCol_TextDisabled]          = ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
//	style.Colors[ImGuiCol_WindowBg]              = ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
//	style.Colors[ImGuiCol_ChildBg]         		 = ImVec4(col_area.x, col_area.y, col_area.z, 0.00f);
//	style.Colors[ImGuiCol_Border]                = ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
//	style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	style.Colors[ImGuiCol_FrameBg]               = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
//	style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
//	style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
//	style.Colors[ImGuiCol_TitleBg]               = ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
//	style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
//	style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
//	style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
//	style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
//	style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
//	style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
//	style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
//	style.Colors[ImGuiCol_CheckMark]             = ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
//	style.Colors[ImGuiCol_SliderGrab]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
//	style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
//	style.Colors[ImGuiCol_Button]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
//	style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
//	style.Colors[ImGuiCol_ButtonActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
//	style.Colors[ImGuiCol_Header]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
//	style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
//	style.Colors[ImGuiCol_HeaderActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
//	style.Colors[ImGuiCol_TableRowBg]                = ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
////	style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
////	style.Colors[ImGuiCol_ColumnActive]          = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
//	style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
//	style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
//	style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
////	style.Colors[ImGuiCol_Close]           = ImVec4(col_text.x, col_text.y, col_text.z, 0.16f);
////	style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(col_text.x, col_text.y, col_text.z, 0.39f);
////	style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
//	style.Colors[ImGuiCol_PlotLines]             = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
//	style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
//	style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
//	style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
//	style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
//	style.Colors[ImGuiCol_PopupBg]             = ImVec4(col_main.x, col_main.y, col_main.z, 0.92f);
////	style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	return;
}

//----------------------------------------------------------------

#endif /* __IMGUI_THEME__ */




























