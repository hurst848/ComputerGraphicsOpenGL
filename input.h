#include "glm/ext.hpp"


struct input
{
public:
	// update input //
	bool pollInput(glm::ivec2 windSize);

	// retrive key states //
	bool getKey_a() { return key_a; } bool getKey_b() { return key_b; }
	bool getKey_c() { return key_c; } bool getKey_d() { return key_d; }
	bool getKey_e() { return key_e; } bool getKey_f() { return key_f; }
	bool getKey_g() { return key_g; } bool getKey_h() { return key_h; }
	bool getKey_i() { return key_i; } bool getKey_j() { return key_j; }
	bool getKey_k() { return key_k; } bool getKey_l() { return key_l; }
	bool getKey_m() { return key_m; } bool getKey_n() { return key_n; }
	bool getKey_o() { return key_o; } bool getKey_p() { return key_p; }
	bool getKey_q() { return key_q; } bool getKey_r() { return key_r; }
	bool getKey_s() { return key_s; } bool getKey_t() { return key_t; }
	bool getKey_u() { return key_u; } bool getKey_v() { return key_v; }
	bool getKey_w() { return key_w; } bool getKey_x() { return key_x; }
	bool getKey_y() { return key_y; } bool getKey_z() { return key_z; }

	bool getKey_0() { return key_0; } bool getKey_1() { return key_1; }
	bool getKey_2() { return key_2; } bool getKey_3() { return key_3; }
	bool getKey_4() { return key_4; } bool getKey_5() { return key_5; }
	bool getKey_6() { return key_6; } bool getKey_7() { return key_7; }
	bool getKey_8() { return key_8; } bool getKey_9() { return key_9; }

	bool getKey_up() { return key_up; }				bool getKey_down() { return key_down; }
	bool getKey_left() { return key_left; }			bool getKey_right() { return key_right; }
	bool getKey_space() { return key_space; }		bool getKey_lControl() { return key_lControl; }
	bool getKey_lShift() { return key_lShift; }		bool getKey_esc() { return key_esc; }

	bool getKey_ins()  { return key_ins;  }	bool getKey_home() { return key_home; }
	bool getKey_pgup() { return key_pgup; } bool getKey_del()  { return key_del;  }
	bool getKey_end()  { return key_end;  } bool getKey_pgdn() { return key_pgdn; }

	glm::vec2 getMouseDelta() { return mouse_posDelta; }
private:

	bool key_a = false; bool key_b = false;
	bool key_c = false;	bool key_d = false;
	bool key_e = false;	bool key_f = false;
	bool key_g = false;	bool key_h = false;
	bool key_i = false;	bool key_j = false;
	bool key_k = false;	bool key_l = false;
	bool key_m = false;	bool key_n = false;
	bool key_o = false;	bool key_p = false;
	bool key_q = false;	bool key_r = false;
	bool key_s = false;	bool key_t = false;
	bool key_u = false;	bool key_v = false;
	bool key_w = false;	bool key_x = false;
	bool key_y = false;	bool key_z = false;

	bool key_0 = false;	bool key_1 = false;
	bool key_2 = false;	bool key_3 = false; 
	bool key_4 = false;	bool key_5 = false;
	bool key_6 = false;	bool key_7 = false;
	bool key_8 = false;	bool key_9 = false;
	
	bool key_up = false;		bool key_down = false;
	bool key_left = false;		bool key_right = false;
	bool key_space = false;		bool key_lShift = false;
	bool key_lControl = false;	bool key_esc = false;

	bool key_ins  = false;	bool key_home = false;	
	bool key_pgup = false;	bool key_del  = false;
	bool key_end = false;	bool key_pgdn = false;


	glm::vec2 mouse_posDelta;
	glm::vec2 mouse_posPrev;
	bool mouse_buttonLeft;
	bool mouse_buttonRight;
	bool mouse_buttonMiddle;


};
