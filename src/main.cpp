#include <allegro.h>
#include "obj.h"
#include "Player.h"

//Funciones
void salir();
void tiempo();
int colision(obj *A, obj *B);


//Variables globales
bool sali = false;
int timer = 0;

player *mario = new player(43, 9,27,192,15,16,true);
obj *scena = new obj(0,0,0,0,3584,240, true);
obj *piso = new obj(0,0,0,208,1103,240,false);


int main(){
	//Inicializando
	allegro_init();
	install_timer();
	install_keyboard();
	set_color_depth(32);
	set_close_button_callback(salir);
	install_int_ex(tiempo, MSEC_TO_TIMER(30));
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0);
	
	
	//variables locales
	BITMAP *fase = load_bitmap("../img/1-1.bmp", NULL);
	BITMAP *iplay = load_bitmap("../img/player.bmp", NULL);
	BITMAP *buffer = create_bitmap(256, 240);
	BITMAP *buffer2 = create_bitmap(SCREEN_W, SCREEN_H);
	MIDI *song = load_midi("../songs/1-1.wav");
	play_midi(song, TRUE);
	
	while(!(key[KEY_ESC] || sali)){
		//graficos
		
		scena->show(buffer, fase);
		
		mario->show(buffer,iplay);
		
		// piso
		bool caer = true;
		int hit = colision(mario, piso);
		
		if(hit == 1){
			mario->y = piso->y - mario->h;
			caer = false;
		}
		
		piso->x = scena->x;
		
		mario->cayendo = caer;
		
		//Movimientos Player
		int mov = mario->control();
		
		if(mario->x > 80){
			mario->x = 80;
			scena->x -= mov;
		}
		
		stretch_blit(buffer, buffer2, 0, 0, 720, 240, 0, 0, SCREEN_W,SCREEN_H);
		draw_sprite(screen,buffer,0,0);
		
		timer=0;
		while(!timer);
		clear_to_color(buffer, 0x0099ff);
	}
	
	//liberar
	destroy_bitmap(fase);
	destroy_bitmap(iplay);
	destroy_bitmap(buffer);
	destroy_bitmap(buffer2);
	return 0;
}

END_OF_MAIN()

void salir(){
	sali = true;
}
void tiempo(){
	timer++;
}

int colision(obj *A, obj *B){
	int ax = A->x, ay= A->y, aw = A->w, ah= A->h;
	int bx = B->x, by= B->y, bw = B->w, bh= B->h;
	
	return (ax + aw >= bx && ax <=bx + bw && ay + ah >= by && ay <= by + bh );
	
}

