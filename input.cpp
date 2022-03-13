#include "input.h"
#include "SDL2/SDL.h"
bool input::pollInput(glm::ivec2 windSize)
{
	bool _stopped = false;
	
	mouse_posDelta = glm::vec2(0);
	SDL_Event event = { 0 };
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			_stopped = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				// arrow keys
			case SDLK_UP:
				key_up = true;
				break;
			case SDLK_DOWN:
				key_down = true;
				break;
			case SDLK_RIGHT:
				key_right = true;
				break;
			case SDLK_LEFT:
				key_left = true;
				break;
			case SDLK_SPACE:
				key_space = true;
				break;
			case SDLK_LCTRL:
				key_lControl = true;
				break;
			case SDLK_LSHIFT:
				key_lShift = true;
				break;
			case SDLK_ESCAPE:
				key_esc = true;
				break;
			// --home function cluster-- //
			case SDLK_INSERT:			 //
				key_ins = true;			 //
				break;					 //
			case SDLK_HOME:				 //
				key_home = true;		 //
				break;					 //
			case SDLK_PAGEDOWN:			 //
				key_pgdn = true;		 //
				break;					 //
			case SDLK_DELETE:			 //
				key_del = true;			 //
				break;					 //
			case SDLK_END:				 //
				key_end = true;			 //
				break;					 //
			case SDLK_PAGEUP:			 //
				key_pgup = true;		 //
				break;					 //
			// ------------------------- //

				// --- alphabet keys --- //
			case SDLK_a:				 //
				key_a = true;			 //
				break;					 //
			case SDLK_b:				 //
				key_b = true;			 //
				break;					 //
			case SDLK_c:				 //
				key_c = true;			 //
				break;					 //
			case SDLK_d:				 //
				key_d = true;			 //
				break;					 //
			case SDLK_e:				 //
				key_e = true;			 //
				break;					 //
			case SDLK_f:				 //
				key_f = true;			 //
				break;					 //
			case SDLK_g:				 //
				key_g = true;			 //
				break;					 //
			case SDLK_h:				 //
				key_h = true;			 //
				break;					 //
			case SDLK_i:				 //
				key_i = true;			 //
				break;					 //
			case SDLK_j:				 //
				key_j = true;			 //
				break;					 //
			case SDLK_k:				 //
				key_k = true;			 //
				break;					 //
			case SDLK_l:				 //
				key_l = true;			 //
				break;					 //
			case SDLK_m:				 //
				key_m = true;			 //
				break;					 //
			case SDLK_n:				 //
				key_n = true;			 //
				break;					 //
			case SDLK_o:				 //
				key_o = true;			 //
				break;					 //
			case SDLK_p:				 //
				key_p = true;			 //
				break;					 //
			case SDLK_q:				 //
				key_q = true;			 //
				break;					 //
			case SDLK_r:				 //
				key_r = true;			 //
				break;					 //
			case SDLK_s:				 //
				key_s = true;			 //
				break;					 //
			case SDLK_t:				 //
				key_t = true;			 //
				break;					 //
			case SDLK_u:				 //
				key_u = true;			 //
				break;					 //
			case SDLK_v:				 //
				key_v = true;			 //
				break;					 //
			case SDLK_w:				 //
				key_w = true;			 //
				break;					 //
			case SDLK_x:				 //
				key_x = true;			 //
				break;					 //
			case SDLK_y:				 //
				key_y = true;			 //
				break;					 //
			case SDLK_z:				 //
				key_z = true;			 //
				break;					 //
				// --------------------- //
			default:
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
				// arrow keys
			case SDLK_UP:
				key_up = false;
				break;
			case SDLK_DOWN:
				key_down = false;
				break;
			case SDLK_RIGHT:
				key_right = false;
				break;
			case SDLK_LEFT:
				key_left = false;
				break;
			case SDLK_SPACE:
				key_space = false;
				break;
			case SDLK_LCTRL:
				key_lControl = false;
				break;
			case SDLK_LSHIFT:
				key_lShift = false;
				break;
			case SDLK_ESCAPE:
				key_esc = false;
				break;
			
			// --home function cluster-- //
			case SDLK_INSERT:			 //
				key_ins = false;		 //
				break;					 //
			case SDLK_HOME:				 //
				key_home = false;		 //
				break;					 //
			case SDLK_PAGEDOWN:			 //
				key_pgdn = false;		 //
				break;					 //
			case SDLK_DELETE:			 //
				key_del = false;		 //
				break;					 //
			case SDLK_END:				 //
				key_end = false;		 //
				break;					 //
			case SDLK_PAGEUP:			 //
				key_pgup = false;		 //
				break;					 //
			// ------------------------- //


				// --- alphabet keys --- //
			case SDLK_a:				 //
				key_a = false;			 //
				break;					 //
			case SDLK_b:				 //
				key_b = false;			 //
				break;					 //
			case SDLK_c:				 //
				key_c = false;			 //
				break;					 //
			case SDLK_d:				 //
				key_d = false;			 //
				break;					 //
			case SDLK_e:				 //
				key_e = false;			 //
				break;					 //
			case SDLK_f:				 //
				key_f = false;			 //
				break;					 //
			case SDLK_g:				 //
				key_g = false;			 //
				break;					 //
			case SDLK_h:				 //
				key_h = false;			 //
				break;					 //
			case SDLK_i:				 //
				key_i = false;			 //
				break;					 //
			case SDLK_j:				 //
				key_j = false;			 //
				break;					 //
			case SDLK_k:				 //
				key_k = false;			 //
				break;					 //
			case SDLK_l:				 //
				key_l = false;			 //
				break;					 //
			case SDLK_m:				 //
				key_m = false;			 //
				break;					 //
			case SDLK_n:				 //
				key_n = false;			 //
				break;					 //
			case SDLK_o:				 //
				key_o = false;			 //
				break;					 //
			case SDLK_p:				 //
				key_p = false;			 //
				break;					 //
			case SDLK_q:				 //
				key_q = false;			 //
				break;					 //
			case SDLK_r:				 //
				key_r = false;			 //
				break;					 //
			case SDLK_s:				 //
				key_s = false;			 //
				break;					 //
			case SDLK_t:				 //
				key_t = false;			 //
				break;					 //
			case SDLK_u:				 //
				key_u = false;			 //
				break;					 //
			case SDLK_v:				 //
				key_v = false;			 //
				break;					 //
			case SDLK_w:				 //
				key_w = false;			 //
				break;					 //
			case SDLK_x:				 //
				key_x = false;			 //
				break;					 //
			case SDLK_y:				 //
				key_y = false;			 //
				break;					 //
			case SDLK_z:				 //
				key_z = false;			 //
				break;					 //
				// --------------------- //
			default:
				break;
			}
				
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			mouse_posDelta.x += event.motion.xrel;//- (windSize.x / 2);
			mouse_posDelta.y += event.motion.yrel;// -(windSize.y / 2);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse_buttonLeft = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse_buttonRight = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse_buttonMiddle = true;
			default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse_buttonLeft = false;
				break;
			case SDL_BUTTON_RIGHT:
				mouse_buttonRight = false;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse_buttonMiddle = false;
			default:
				break;
			}
		}
	}
	mouse_posPrev += mouse_posDelta;
	//SDL_WarpMouseInWindow(NULL, windSize.x / 2, windSize.y / 2);
	return _stopped;
}
