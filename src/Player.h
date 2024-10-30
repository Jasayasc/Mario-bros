class player: public obj{
	private:
		int aWx,step, speed, zKey, saltoInit;
		bool nwSalto;
	public:
		bool dir, cayendo, saltando;
		int LSpeed, Rspeed, velUp;
	player(int _wx, int _wy, int _x, int _y, int _w, int _h, bool _visible): obj( _wx, _wy,_x, _y, _w, _h, _visible){
		aWx = _wx;
		zKey = 0;
		step = 0;
		velUp = 0;
		speed = 0;
		LSpeed = 0;
		Rspeed = 0;
		dir =  true;
		nwSalto = false;
		cayendo = true;
		saltando = false;
		saltoInit = 0;
	}
	int control(){ //Controles del jugador
		int mov = 0;
		wx = aWx + (step/(2 - zKey))*w;
		if(key[KEY_Z]){
			zKey = 1;
		}else	zKey = 0; //Aceleracion
		if(key[KEY_LEFT]){
			if(speed < 10);	speed++;
			flip= true;
			step++;
			if(LSpeed < 2+zKey+ (speed==10)*2)	LSpeed++;
			if(Rspeed){
				wx = 98;
				flip = false;
				Rspeed--;
				LSpeed--;
			}
		}
		else if(key[KEY_RIGHT]){
			if(speed < 10);	speed++;
			flip= false;
			step++;
			if(Rspeed <2+zKey+(speed==10)*2)	Rspeed++;
			if(LSpeed){
				wx = 98;
				flip = true;
				LSpeed--;
				Rspeed--;
			}
		}
		else{
			if(LSpeed)	LSpeed--;
			if(Rspeed)	Rspeed--;
			if(speed)	speed--;
			wx = 0;
		}
		//Movimientos y velocidades
		if(step >5-(zKey*3))	step = 0; 
		x -= LSpeed;
		x += Rspeed;
		mov += Rspeed;
		if(x<0){
			x = 0;
			LSpeed--;
		}	
		
		saltar();
		
		return mov;
	}
	
	void saltar(){
		if(key[KEY_X] and !saltando and !cayendo and nwSalto){
			saltando = true;
			velUp = 0;
			nwSalto = true;
		}
		if(saltando and key[KEY_X] and velUp > -12 and nwSalto){
			velUp -=3;
			y+=velUp;
		}else{
			nwSalto = false;
			saltando = false;
		}
		if(!key[KEY_X]){
			nwSalto = false;
			if(!velUp)	nwSalto = true;
		}
		if(cayendo and !saltando){
			if(velUp < 12)	velUp +=2;
			y += velUp;
		}
		if(!cayendo and !saltando){
			velUp = 0;
		}else{
			wx  = 119;
		}
	}
};

