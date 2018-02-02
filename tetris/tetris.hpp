#pragma once
#include "stdafx.h"
#include "tetris_component.hpp"

using component_vector_t = std::vector<std::tuple<vector_t, bool, component>>;

namespace tetris
{
	void run();

	// PRIVATE
	namespace details
	{
		void draw_boundary();
		void clear_game_frame();
		void draw_component(const int16_t x, const int16_t y, component comp);

		// GAME BORDER
		const extern int32_t border_width;
		const extern int32_t border_height;

		// ENTITIES
		extern component_vector_t components;
		extern std::vector<vector_t> solid_parts; // FOR COLLISION DETECTION
	}
}