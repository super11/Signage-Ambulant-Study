/*
 * This file is part of Ambulant Player, www.ambulantplayer.org.
 *
 * Copyright (C) 2003-2015 Stichting CWI, 
 * Science Park 123, 1098 XG Amsterdam, The Netherlands.
 *
 * Ambulant Player is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * Ambulant Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Ambulant Player; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * $Id$
 */

#ifndef AMBULANT_GUI_SDL_SDL_RENDERER_H
#define AMBULANT_GUI_SDL_SDL_RENDERER_H

#ifdef  WITH_SDL_IMAGE

#include "ambulant/common/factory.h"
#include "ambulant/common/renderer_impl.h"
#include "ambulant/smil2/transition.h"
#include "ambulant/lib/mtsync.h"

#include "SDL.h"

namespace ambulant {

using namespace lib;
using namespace common;

namespace gui {

namespace sdl {
class sdl_window {

 protected:
  SDL_Renderer* get_sdl_renderer(); 
  SDL_Surface* get_sdl_surface(); 
  SDL_Texture* get_sdl_texture();
  SDL_Window* get_sdl_window(); 

 sdl_window() {}

 private:
  static SDL_Renderer* s_sdl_renderer; 
  static SDL_Surface* s_sdl_surface; 
  static SDL_Texture* s_sdl_texture;
  static SDL_Window* s_sdl_window; 
};

// When blending is needed, one rarely used color is taken as
// transparent color for chromakeying. However should this
// color be needed anyway, an alternative undistinguishable
// color is taken to be drawn instead, to avoid the ugly bug
// of seeing absolutely nothing. This could happen e.g. during
// color animations resulting in occasional unreproduceable
// flicker.
//#define SDL_TRANSPARENT_COLOR to_color(0x0,0x1,0x0) // almost black
#define SDL_TRANSPARENT_COLOR to_color(0x0,0x0,0xFF) // almost black
#define SDL_ALTERNATIVE_COLOR to_color(0x0,0x0,0x1) // almost black too

class sdl_transition_renderer : public ref_counted_obj {
  public:
	sdl_transition_renderer(event_processor *evp)
	:	m_event_processor(evp),
		m_transition_dest(NULL),
		m_view(NULL),
		m_intransition(NULL),
		m_outtransition(NULL),
		m_fullscreen(false),
		m_trans_engine(NULL) {};
	~sdl_transition_renderer();

	void set_surface(common::surface *dest);
	void start(double where);
	void stop();
	void redraw_pre(gui_window *window);
	void redraw_post(gui_window *window);
	void set_intransition(const lib::transition_info *info);
	void start_outtransition(const lib::transition_info *info);

  protected:
  private:
	void transition_step();

	event_processor* m_event_processor;
	surface* m_transition_dest;
	void* m_view; //ambulant_sdl_window*
	const lib::transition_info* m_intransition;
	const lib::transition_info* m_outtransition;
	bool m_fullscreen;
	smil2::transition_engine* m_trans_engine;
	critical_section m_lock;
};

template <class RP_Base>
class sdl_renderer : public RP_Base {
  public:
	sdl_renderer(
		playable_notification *context,
		playable_notification::cookie_type cookie,
		const lib::node *node,
		event_processor *evp,
		common::factories *factory,
		common::playable_factory_machdep *mdp)
	:	RP_Base(context, cookie, node, evp, factory, mdp),
		m_transition_renderer(new sdl_transition_renderer(evp)) {};
	sdl_renderer(
		playable_notification *context,
		playable_notification::cookie_type cookie,
		const lib::node *node,
		event_processor *evp)
	:	RP_Base(context, cookie, node, evp),
		m_transition_renderer(new sdl_transition_renderer(evp)) {};
	~sdl_renderer() {
		m_transition_renderer->release();
	}

	void set_surface(common::surface *dest) {
		RP_Base::set_surface(dest);
		m_transition_renderer->set_surface(dest);
	}

	virtual void start(double where) {
		start_transition(where);
		RP_Base::start(where);
	}

	virtual bool stop() {
		stop_transition();
		return RP_Base::stop();
	}

	void redraw(const rect &dirty, gui_window *window) {
		m_transition_renderer->redraw_pre(window);
		redraw_body(dirty, window);
		m_transition_renderer->redraw_post(window);
		if (RP_Base::m_erase_never) RP_Base::m_dest->keep_as_background();
	}

	void set_intransition(const lib::transition_info *info) {
		m_transition_renderer->set_intransition(info);
	}

	void start_outtransition(const lib::transition_info *info) {
		m_transition_renderer->start_outtransition(info);
	}
  protected:
	void start_transition(double where) {
		m_transition_renderer->start(where);
	}
	void stop_transition() {
		m_transition_renderer->stop();
	}
	virtual void redraw_body(const rect &dirty, gui_window *window) = 0;

  private:
	sdl_transition_renderer *m_transition_renderer;
};

} // namespace sdl

} // namespace gui

} // namespace ambulant

#endif // WITH_SDL_IMAGE

#endif  /*AMBULANT_GUI_SDL_SDL_RENDERER_H*/
