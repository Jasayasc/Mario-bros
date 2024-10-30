class obj
{
	public:
		int wx, wy, x,y,w,h;
		bool visible, flip;
		obj(int _wx, int _wy, int _x, int _y,int _w, int _h, bool _visible){
			x = _x;
			y = _y;
			w = _w;
			h = _h;
			wx = _wx;
			wy = _wy;
			flip = false;
			visible = _visible;
		}
		void show(BITMAP *buffer, BITMAP *sourceImg){
			if(visible)
					if(flip){
						BITMAP *flipImg = create_bitmap(w,h);
						clear_to_color(flipImg, 0xff00ff);
						masked_blit(sourceImg, flipImg, wx, wy, 0, 0, w, h);
						draw_sprite_h_flip(buffer, flipImg, x, y);
						destroy_bitmap(flipImg);
					}else{
						masked_blit(sourceImg, buffer, wx, wy, x, y, w, h);
					}
		}
};

