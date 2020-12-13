
#include "stdafx.cpp"

#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <time.h>
#include "Objetos.h"
#include <windows.h>
#include <iostream>



#include <conio.h>
#include <stdlib.h>
#include <string.h>

//Variables globales
const int WIDTH = 1400;
const int HEIGHT = 650;
const int NUM_ARBOLES = 26;
const int NUM_LINEAS = 21;
const int NUM_BULLETS = 5;
const int NUM_COMETS = 5;
const int NUM_MONEY = 4;
const int NUM_GRASS = 21;
const int NUM_SAND = 10;
const int NUM_AGUA = 14;
const int NUM_LAVA = 10;
int pos_x = WIDTH / 2;
int pos_y = HEIGHT / 2;



bool Automatic = false;
bool Pause = false;
int vueltas = 0;
int R = 500;
int Escenario = 0;
int speed = 2;
int frece = 0;
int *x;
int *y;
int lis=0;
Jugador CajaNegra[10];
Explotion Exp;



enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, Z, X, A,P,B };
bool keys[10] = { false, false, false, false, false, false, false, false,false,false};

//Funciones implementadas [Se encuetran en el final del código, se mencionan aquí para poder ser llamadas en el main]

void InitCar(Carro &Car); //Inicializa las variables del auto
void DrawCar(Carro &Car, ALLEGRO_SAMPLE*Choque); //Imprime los bitmaps correspondientes al auto
void MoveCarUp(Carro &Car); //Avanza el carro en el espacio hacia arriba
void MoveCarDown(Carro &Car); //Retrocede en el espacio el carro hacia abajo
void MoveCarLeft(Carro &Car, Comet comets[]); //mueve el auto hacia la izquierda
void MoveCarRight(Carro &Car, Comet comets[]); //mueve el auto hacia la derecha

void SubirVelocidad(Comet comets[], int sizec, Carro &Car); //Funcion que sube la velocidad global del programa[utilizada por todas las entidades en el juego]
void BajarVelocidad(Comet comets[], int sizec, Carro &Car);//Funcion que disminuye la velocidad global del programa[utilizada por todas las entidades en el juego]

void InitBullet(Bullet bullet[], int size);//Inicializa las variables de las balas
void DrawBullet(Bullet bullet[], int size); //Imprime bitmaps de balas
void FireBullet(Bullet bullet[], int size, Carro &Car); //Esta función inicializa las balas lanzadas en la interfaz
void UpdateBullet(Bullet bullet[], int size); //Esta funcion actualiza la bala en el espacio segun su velocidad, moviendose hasta el borde superior de la pantalla
void CollideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize, Carro &Car, ALLEGRO_SAMPLE * Explo); //Si una bala colisiona con un eneigo este desaparece

void InitComet(Comet comets[], int size);
void DrawComet(Comet comets[], int size, Carro car);
void StartComet(Comet comets[], int size);
void UpdateComet(Comet comets[], int size);
void CollideComet(Comet comets[], int cSize, Carro &Car,ALLEGRO_SAMPLE *Explo);

void InitMoney(Money dinero[], int size);
void DrawMoney(Money dinero[], int size);
void StartMoney(Money dinero[], int size);
void UpdateMoney(Money dinero[], int size);
void CollideMoney(Money dinero[], int cSize, Carro &Car, ALLEGRO_SAMPLE *Pick);

void InitRoad(Road &street);
void DrawRoad(Road &street);

void InitBat(Bateria &bat);
void DrawBat(Bateria &bat, Carro &Car);

void InitLinea(Linea lineas[], int size);
void DrawLinea(Linea lineas[], int size);
void StartLinea(Linea lineas[], int size);
void UpdateLinea(Linea lineas[], int size);

void InitGrass(Grass grass[], int size);
void DrawGrass(Grass grass[], int size);
void StartGrass(Grass grass[], int size);
void UpdateGrass(Grass grass[], int size);

void InitAgua(Agua agua[], int size);
void DrawAgua(Agua agua[], int size);
void StartAgua(Agua agua[], int size);
void UpdateAgua(Agua agua[], int size);

void InitLava(Lava lava[], int size);
void DrawLava(Lava lava[], int size);
void StartLava(Lava lava[], int size);
void UpdateLava(Lava lava[], int size);

void InitSand(Sand sand[], int size);
void DrawSand(Sand sand[], int size);
void StartSand(Sand sand[], int size);
void UpdateSand(Sand sand[], int size);

void Boost(Carro &Car, Comet comets[]);

void InitArbol(Arbol aboles[], int size);
void DrawArbol(Arbol arboles[], int size);
void StartArbol(Arbol arboles[], int size);
void UpdateArbol(Arbol arboles[], int size);

void AutomaticE(Carro &Car, Comet comets[], int size, Bullet bullets[], int NUM_BULLETS, Money dinero[], int sized);
void Limites(Carro &Car, Comet comets[]);

void Pausa(ALLEGRO_SAMPLE*pause, ALLEGRO_FONT *Inicio, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_EVENT &ev);

void InitExplosion(Explotion &Exp);

void InitLuz(Luz &luz);
void DrawLuz(Carro &Car, Luz luz, ALLEGRO_SAMPLE*Low);

void DrawStatic(Comet comets[], int &frece);

void Choca(Comet comets[], int size, Carro Car);

int main(void)
{

	bool done = true;
	bool escenarios = true;
	bool redraw = true;
	const int FPS = 60;
	bool isGameOver = false;


	Carro Car;
	Bullet bullets[NUM_BULLETS];
	Comet comets[NUM_COMETS];
	Road street;
	Money dinero[NUM_MONEY];
	Linea lineas[NUM_LINEAS];
	Arbol arboles[NUM_ARBOLES];
	Grass grass[NUM_GRASS];
	Sand sand[NUM_SAND];
	Agua agua[NUM_AGUA];
	Lava lava[NUM_LAVA];
	Bateria bat;
	Luz luz;



	ALLEGRO_DISPLAY *display = NULL;

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_FONT *font22 = NULL;
	ALLEGRO_FONT *DIGI = NULL;
	ALLEGRO_FONT *Inicio = NULL;
	ALLEGRO_FONT *Fonta = NULL;
	ALLEGRO_FONT *Num = NULL;
	ALLEGRO_FONT *DIGI1 = NULL;
	ALLEGRO_FONT *DIGI2 = NULL;
	ALLEGRO_FONT *DIGI3 = NULL;

	ALLEGRO_BITMAP *dash = NULL;
	ALLEGRO_BITMAP *Pantalla = NULL;
	ALLEGRO_BITMAP *Final = NULL;
	ALLEGRO_BITMAP *cursor = NULL;
	ALLEGRO_BITMAP *fondo = NULL;
	ALLEGRO_BITMAP *volcano = NULL;
	ALLEGRO_BITMAP *volcano2 = NULL;
	ALLEGRO_BITMAP *beach = NULL;
	ALLEGRO_BITMAP *beach2 = NULL;
	ALLEGRO_BITMAP *forest = NULL;
	ALLEGRO_BITMAP *forest2 = NULL;
	ALLEGRO_BITMAP *RBoost = NULL;
	ALLEGRO_BITMAP *RTempa = NULL;
	ALLEGRO_BITMAP *RTempo = NULL;
	ALLEGRO_BITMAP *Vidas = NULL;



	ALLEGRO_SAMPLE *pause = NULL;
	ALLEGRO_SAMPLE *MusicInicio = NULL;
	ALLEGRO_SAMPLE *Explo = NULL;
	ALLEGRO_SAMPLE *Music = NULL;
	ALLEGRO_SAMPLE *Pick = NULL;
	ALLEGRO_SAMPLE *Low = NULL;
	ALLEGRO_SAMPLE *Choque = NULL;
	ALLEGRO_SAMPLE *Choose = NULL;
	ALLEGRO_SAMPLE *SFXlava = NULL;
	ALLEGRO_SAMPLE *SFXforest = NULL;
	ALLEGRO_SAMPLE *Carr = NULL;
	ALLEGRO_SAMPLE *GameOver = NULL;

	ALLEGRO_SAMPLE_ID in;
	ALLEGRO_SAMPLE_ID IDforest;
	ALLEGRO_SAMPLE_ID IDlava;
	ALLEGRO_SAMPLE_ID IDbeach;
	ALLEGRO_SAMPLE_ID IDcar;


	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
		return -1;

	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(20);

	al_install_mouse();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_set_window_position(display, 0, 0);
	al_clear_to_color(al_map_rgb(500, 500, 500));

	srand(time(NULL));
	InitCar(Car);
	InitBat(bat);
	InitExplosion(Exp);
	InitAgua(agua, NUM_AGUA);
	InitLava(lava, NUM_LAVA);
	InitLuz(luz);
	InitBullet(bullets, NUM_BULLETS);
	InitMoney(dinero, NUM_MONEY);
	InitLinea(lineas, NUM_LINEAS);
	InitArbol(arboles, NUM_ARBOLES);
	InitGrass(grass, NUM_GRASS);
	InitSand(sand, NUM_SAND);

	dash = al_load_bitmap("dash/15.png");
	Pantalla = al_load_bitmap("PantallaInicio/Carro.png");
	cursor = al_load_bitmap("PantallaInicio/cursor.png");
	fondo = al_load_bitmap("Seleccion/Fondo.png");
	beach = al_load_bitmap("Seleccion/Beach.jpg");
	beach2 = al_load_bitmap("Seleccion/Beach2.png");
	volcano = al_load_bitmap("Seleccion/Volcano.jpg");
	volcano2 = al_load_bitmap("Seleccion/Volcano2.png");
	forest = al_load_bitmap("Seleccion/Forest.jpg");
	forest2 = al_load_bitmap("Seleccion/Forest2.png");
	Final = al_load_bitmap("Final/Final.jpg");
	RBoost = al_load_bitmap("Relojes/Boost.png");
	RTempa = al_load_bitmap("Relojes/Water.png");
	RTempo = al_load_bitmap("Relojes/Oil.png");
	Vidas = al_load_bitmap("Vidas/1.png");
	
	font18 = al_load_font("arial.ttf", 18, 0);
	font22 = al_load_font("arial.ttf", 22, 0);
	Fonta = al_load_font("Fonts/JAi_____.TTF", 20, 0);
	DIGI = al_load_font("Fonts/DS-DIGI.TTF", 70, 0);
	DIGI3 = al_load_font("Fonts/DS-DIGI.TTF", 52, 0);
	DIGI2 = al_load_font("Fonts/DS-DIGI.TTF", 40, 0);
	DIGI1 = al_load_font("Fonts/DS-DIGI.TTF", 35, 0);
	Inicio = al_load_font("Fonts/Bombing.ttf", 40, 0);
	Num = al_load_font("Fonts/UKNumberPlate.ttf", 40, 0);


	Carr = al_load_sample("SFX/Carro.wav");
	GameOver = al_load_sample("SFX/Fin.wav");
	Low = al_load_sample("SFX/Low.ogg");
	SFXforest = al_load_sample("SFX/Forest.ogg");
	SFXlava = al_load_sample("SFX/Lava.ogg");
	pause = al_load_sample("SFX/pause.wav");
	Explo = al_load_sample("SFX/explosion.wav");
	Pick = al_load_sample("SFX/Pickup.wav");
	Choque = al_load_sample("SFX/Choque.wav");
	Music = al_load_sample("SFX/Music.ogg");
	MusicInicio = al_load_sample("SFX/Inicio.ogg");
	Choose = al_load_sample("SFX/introbeep.wav");

	al_play_sample(MusicInicio, 0.3, 0, 0.9, ALLEGRO_PLAYMODE_LOOP, &in);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);


	al_hide_mouse_cursor(display);

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_EVENT events;

	while (escenarios)
	{

		al_flip_display();

		al_draw_bitmap(Pantalla, -260, 0, NULL);
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			pos_x = events.mouse.x;
			pos_y = events.mouse.y;
		}

		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (events.mouse.button & 1)
			{
				if (pos_x > 640 && pos_x < 740 && pos_y>240 && pos_y < 273)
				{
					al_play_sample(Choose, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					escenarios = false;
					done = false;

				}
				/*else if (pos_x > 620 && pos_x < 774 && pos_y>295 && pos_y < 339)
				{
					al_play_sample(Choose, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}*/

			}

		}


		if (pos_x > 640 && pos_x < 740 && pos_y>240 && pos_y < 273)
		{
			al_draw_text(Inicio, al_map_rgb(255, 255, 255), WIDTH / 2, 250, ALLEGRO_ALIGN_CENTRE, "Jugar");
		}
		else
		{
			al_draw_text(Inicio, al_map_rgb(0, 0, 0), WIDTH / 2, 250, ALLEGRO_ALIGN_CENTRE, "Jugar");
		}

		/*if (pos_x > 620 && pos_x < 774 && pos_y>295 && pos_y < 339)
		{
			al_draw_text(Inicio, al_map_rgb(255, 255, 255), WIDTH / 2, 300, ALLEGRO_ALIGN_CENTRE, "Puntuaciones");
		}
		else
		{
			al_draw_text(Inicio, al_map_rgb(0, 0, 0), WIDTH / 2, 300, ALLEGRO_ALIGN_CENTRE, "Puntuaciones");
		}*/



		al_draw_text(Inicio, al_map_rgb(0, 0, 0), WIDTH / 2, 100, ALLEGRO_ALIGN_CENTRE, "AUTO FANTASTICO");

		al_draw_bitmap(cursor, pos_x, pos_y, NULL);


		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_ENTER)){
			escenarios = false;
			done = false;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{
			escenarios = false;
			done = false;
			isGameOver = true;
		}
	}


	while (!escenarios)
	{


		al_flip_display();

		al_draw_bitmap(fondo, 0, 0, NULL);
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			pos_x = events.mouse.x;
			pos_y = events.mouse.y;
		}

		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (events.mouse.button & 1)
			{
				if (pos_x > 439 && pos_x < 960 && pos_y>0 && pos_y < 217)
				{
					al_play_sample(Choose, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					if (Escenario == 1)
						Escenario = 0;
					else
						Escenario = 1;
				}
				else if (pos_x > 439 && pos_x < 960 && pos_y>217 && pos_y < 434)
				{
					al_play_sample(Choose, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					if (Escenario == 2)
						Escenario = 0;
					else
						Escenario = 2;
				}
				else if (pos_x > 439 && pos_x < 960 && pos_y>434)
				{
					al_play_sample(Choose, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					if (Escenario == 3)
						Escenario = 0;
					else
						Escenario = 3;
				}
				else if (pos_x > 1070 && pos_x < 1210 && pos_y>304 && pos_y < 350&&Escenario!=0)
				{
					al_play_sample(Choose, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					escenarios = true;
				}

			}
		}
		if (Escenario == 1 || pos_x > 439 && pos_x < 960 && pos_y>0 && pos_y < 217)
		{
			al_draw_bitmap(volcano, WIDTH / 2 - 260, 0, NULL);
		}
		else
		{
			al_draw_bitmap(volcano2, WIDTH / 2 - 260, 0, NULL);
		}

		if (Escenario == 2 || pos_x > 439 && pos_x < 960 && pos_y>217 && pos_y < 434)
		{
			al_draw_bitmap(beach, WIDTH / 2 - 260, 217, NULL);
		}

		else
		{
			al_draw_bitmap(beach2, WIDTH / 2 - 260, 217, NULL);
		}

		if (Escenario == 3 || pos_x > 439 && pos_x < 960 && pos_y>434 && pos_y < 650)
		{
			al_draw_bitmap(forest, WIDTH / 2 - 260, 434, NULL);
		}
		else
		{
			al_draw_bitmap(forest2, WIDTH / 2 - 260, 434, NULL);
		}

		al_draw_text(Inicio, al_map_rgb(255, 255, 255), 200, HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTRE, "SELECCIONE UN ESCENARIO");

		if (pos_x > 1070 && pos_x < 1210 && pos_y>304 && pos_y < 350)
		{
			al_draw_text(Inicio, al_map_rgb(0, 0, 0), 1150, HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTRE, "CONTINUAR");
		}
		else
		{
			al_draw_text(Inicio, al_map_rgb(255, 255, 255), 1150, HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTRE, "CONTINUAR");
		}


		al_draw_bitmap(cursor, pos_x, pos_y, NULL);


	}

	InitRoad(street);
	InitComet(comets, NUM_COMETS);
	al_stop_sample(&in);

	if (Escenario == 1)
	{
		al_play_sample(SFXlava, 0.4, 0, 0.9, ALLEGRO_PLAYMODE_LOOP, &IDlava);
	}
	else if (Escenario==2)
	{
		al_play_sample(Music, 0.2, 0, 0.9, ALLEGRO_PLAYMODE_LOOP, &IDbeach);
	}
	else if (Escenario==3)
	{
		al_play_sample(SFXforest, 0.4, 0, 0.9, ALLEGRO_PLAYMODE_LOOP, &IDforest);
	}
	

	while (!done)
	{
		vueltas++;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.timer.source == timer)
		{
			redraw = true;
			if (keys[UP])
				if (!isGameOver)
					MoveCarUp(Car);
			if (keys[DOWN])
				if (!isGameOver)
					MoveCarDown(Car);
			if (keys[LEFT])
				MoveCarLeft(Car, comets);
			if (keys[RIGHT])
				MoveCarRight(Car, comets);
			if (keys[B])
				Boost(Car, comets);

			if (!isGameOver)
			{

				UpdateBullet(bullets, NUM_BULLETS);

				StartComet(comets, NUM_COMETS);
				UpdateComet(comets, NUM_COMETS);

				CollideBullet(bullets, NUM_BULLETS, comets, NUM_COMETS, Car, Explo);
				CollideComet(comets, NUM_COMETS, Car, Explo);

				StartMoney(dinero, NUM_MONEY);
				UpdateMoney(dinero, NUM_MONEY);
				CollideMoney(dinero, NUM_MONEY, Car, Pick);

				StartLinea(lineas, NUM_LINEAS);
				UpdateLinea(lineas, NUM_LINEAS);

				StartGrass(grass, NUM_GRASS);
				UpdateGrass(grass, NUM_GRASS);

				StartAgua(agua, NUM_AGUA);
				UpdateAgua(agua, NUM_AGUA);

				StartLava(lava, NUM_LAVA);
				UpdateLava(lava, NUM_LAVA);

				StartSand(sand, NUM_SAND);
				UpdateSand(sand, NUM_SAND);

				StartArbol(arboles, NUM_ARBOLES);
				UpdateArbol(arboles, NUM_ARBOLES);

				if (Car.lives <= 0)
				{
					al_play_sample(GameOver, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					isGameOver = true;
				}

				if (Car.Energia <= 0)
				{
					al_play_sample(GameOver, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					isGameOver = true;
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				FireBullet(bullets, NUM_BULLETS, Car);
				break;
			case ALLEGRO_KEY_B:
				keys[B] = true;
				break;
			case ALLEGRO_KEY_X:
				keys[X] = true;
				SubirVelocidad(comets, NUM_COMETS, Car);
				break;
			case ALLEGRO_KEY_Z:
				keys[Z] = true;
				BajarVelocidad(comets, NUM_COMETS, Car);
				break;
			case ALLEGRO_KEY_A:
				if (!Automatic)
				{
					Automatic = true;
					break;
				}
				else
				{
					Automatic = false;
					break;
				}
			case ALLEGRO_KEY_P:
				keys[P] = true;
				Pause = true;
			
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_X:
				keys[X] = true;
				break;
			case ALLEGRO_KEY_Z:
				keys[Z] = true;
				break;
			case ALLEGRO_KEY_P:
				keys[P] = false;
				break;

			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if (!isGameOver&&!done)
			{

			
				if (Escenario == 3)
				{
					DrawGrass(grass, NUM_GRASS);
					DrawRoad(street);
					DrawLinea(lineas, NUM_LINEAS);
					DrawMoney(dinero, NUM_MONEY);
					DrawComet(comets, NUM_COMETS, Car);
					DrawCar(Car, Choque);
					DrawArbol(arboles, NUM_ARBOLES);
				}
				else if (Escenario == 2)
				{
					DrawAgua(agua, NUM_AGUA);
					DrawSand(sand, NUM_SAND);
					DrawRoad(street);
					DrawLinea(lineas, NUM_LINEAS);
					DrawMoney(dinero, NUM_MONEY);
					DrawComet(comets, NUM_COMETS, Car);
					DrawCar(Car, Choque);
				}
				else if (Escenario == 1)
				{
					DrawLava(lava, NUM_LAVA);
					DrawRoad(street);
					DrawLinea(lineas, NUM_LINEAS);
					DrawMoney(dinero, NUM_MONEY);
					DrawComet(comets, NUM_COMETS, Car);
					DrawCar(Car, Choque);
				}

				
				DrawBullet(bullets, NUM_BULLETS);
				al_draw_bitmap(dash, 0, -10, NULL);
				DrawBat(bat, Car);
				DrawStatic(comets, frece);

				Choca(comets, NUM_COMETS, Car);

				bool alerta = false;
				for (int i = 0; i < 5;  i++)
				{
					if (comets[i].choca&&comets[i].live)
					{
						alerta = true;
					}
				}

				if (alerta)
				{
					al_draw_bitmap(luz.luz, 1050, 245, NULL);
				}

				

				al_draw_bitmap(RTempa, 290, 0, NULL);
				al_draw_bitmap(RTempo, 140, 60, NULL);
				al_draw_bitmap(RBoost, -10, 160, NULL);

				al_draw_bitmap(bullets[0].imagenbala, 245, 225, NULL);
				
				if (Car.lives >=6)
				{
					al_draw_bitmap(Vidas, 150, 510, NULL);
					al_draw_bitmap(Vidas, 200, 510, NULL);
					al_draw_bitmap(Vidas, 250, 510, NULL);
					al_draw_bitmap(Vidas, 300, 510, NULL);
					al_draw_bitmap(Vidas, 350, 510, NULL);
					al_draw_bitmap(Vidas, 400, 510, NULL);
				}


				else if (Car.lives == 5)
				{
					al_draw_bitmap(Vidas, 150, 510, NULL);
					al_draw_bitmap(Vidas, 200, 510, NULL);
					al_draw_bitmap(Vidas, 250, 510, NULL);
					al_draw_bitmap(Vidas, 300, 510, NULL);
					al_draw_bitmap(Vidas, 350, 510, NULL);
				}

				else if (Car.lives == 4)
				{
					al_draw_bitmap(Vidas, 150, 510, NULL);
					al_draw_bitmap(Vidas, 200, 510, NULL);
					al_draw_bitmap(Vidas, 250, 510, NULL);
					al_draw_bitmap(Vidas, 300, 510, NULL);
				}
				else if (Car.lives == 3)
				{
					al_draw_bitmap(Vidas, 150, 510, NULL);
					al_draw_bitmap(Vidas, 200, 510, NULL);
					al_draw_bitmap(Vidas, 250, 510, NULL);

				}
				else if (Car.lives == 2)
				{
					al_draw_bitmap(Vidas, 150, 510, NULL);
					al_draw_bitmap(Vidas, 200, 510, NULL);
				}
				else if (Car.lives == 1)
				{
					al_draw_bitmap(Vidas, 150, 510, NULL);

				}

				if (keys[P])
				{
					al_play_sample(pause, 0.8, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					while (keys[P])
					{
						al_flip_display();
						al_draw_text(Inicio, al_map_rgb(255, 255, 255), WIDTH / 2, 150, ALLEGRO_ALIGN_CENTRE, "PAUSA");
						al_wait_for_event(event_queue, &ev);
						if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
						{
							switch (ev.keyboard.keycode)
							{
							case ALLEGRO_KEY_P:
								al_play_sample(pause, 0.8, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								keys[P] = false;
								break;
							case ALLEGRO_KEY_ESCAPE:
								keys[P] = false;
								done = true;
								break;
							}
						}
					}
				}
				

				if (Automatic)
				{
					AutomaticE(Car, comets, NUM_COMETS, bullets, NUM_BULLETS, dinero, NUM_MONEY);
				}


				Car.Energia -= 0.4;
				Car.distancia += speed*0.025;

				
				if (Car.boost <= 1000)
				{
					Car.boost++;
				}
				if (Car.boost==1000)
				{
					Car.Boost = true;
				}

				if (Car.Boost)
				{
					al_draw_textf(Num, al_map_rgb(255, 255, 255), 147, 100, ALLEGRO_ALIGN_RIGHT, "B Turbo");
				}


				if (Car.distancia >= 950 * Car.C + (50 + 50 * (Car.C - 1))*Car.C)
				{
					Car.lives++;
					Car.C += 1;
				}

				if (Car.distancia >= (100*Car.V))
				{	
					if (Car.minima<= 20)
						Car.minima += 1;
					Car.V++;
				}



				if (Car.Energia <= 400)
				{
					DrawLuz(Car, luz, Low);

				}


				int g;
				float ta;
				float to;
				if (vueltas <100)
				{
					g = int(speed*5.4);
					ta = Car.Temp + float(speed)/ 6 + 25;
					to = Car.Temp + float(speed)/ 2 + 27;
				}
				
				if (rand() % 10 == 0)
				{
					g = int(speed*5.4) + rand() % 5;
					ta = Car.Temp + float(speed)/ 6 + 25 + rand() % 2;
					to = Car.Temp + float(speed)/ 2 + 27 + rand() % 2;
					al_draw_textf(DIGI, al_map_rgb(255, 255, 255), 1200, 425, ALLEGRO_ALIGN_RIGHT, "%i ", g);
					al_draw_textf(DIGI1, al_map_rgb(255, 255, 255), 402, 58, ALLEGRO_ALIGN_RIGHT, "%.1f ", ta);
					al_draw_textf(DIGI2, al_map_rgb(255, 255, 255), 279, 123, ALLEGRO_ALIGN_RIGHT, "%.1f ", to);
				}
				else
				{
					al_draw_textf(DIGI, al_map_rgb(255, 255, 255), 1200, 425, ALLEGRO_ALIGN_RIGHT, "%i ", g);
					al_draw_textf(DIGI1, al_map_rgb(255, 255, 255), 402, 58, ALLEGRO_ALIGN_RIGHT, "%.1f ", ta);
					al_draw_textf(DIGI2, al_map_rgb(255, 255, 255), 279, 123, ALLEGRO_ALIGN_RIGHT, "%.1f ", to);
					al_draw_textf(DIGI3, al_map_rgb(255, 255, 255), 139, 231, ALLEGRO_ALIGN_RIGHT, "%i ", Car.boost/100);
				}


				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 1100, 100, 0, "Puntuacion: %i", Car.score * 10 + int(Car.distancia));
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 1100, 120, 0, "Coste de balas 3%%");
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 1135, 500, 0, "km/h");
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 1090, 250, 0, "Posible Choque");
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 1210, 600, 0, "%0.f%%", Car.Energia/10);
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 1100, 540, 0, "%.2f km", Car.distancia/1000);
				al_draw_textf(Num, al_map_rgb(255, 255, 255), 275, 325, 0, ":  %i", Car.kills);
				al_draw_textf(Num, al_map_rgb(255, 255, 255), 275, 250, 0, ":  %0.f", Car.Energia/30);
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 5, 5, 0, "Aumentar velocidad X");
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 5, 25, 0, "Disminuir velocidad Z");
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 5, 45, 0, "Pausa P");
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 5, 65, 0, "Automatico A");
				al_draw_textf(Fonta, al_map_rgb(255, 255, 255), 100, 600, 0, "++ %i", int(950 * Car.C + (50 + 50 * (Car.C - 1))*Car.C - Car.distancia));
			}
			else
			{

				if (Escenario == 1)
				{
					al_stop_sample(&IDlava);
					al_play_sample(MusicInicio, 0.3, 0, 0.9, ALLEGRO_PLAYMODE_LOOP, &in);
					Escenario = 0;
				}
				else if (Escenario == 2)
				{
					al_stop_sample(&IDbeach);
					al_play_sample(MusicInicio, 0.3, 0, 0.9, ALLEGRO_PLAYMODE_LOOP, &in);
					Escenario = 0;
				}
				else if (Escenario == 3)
				{
					al_stop_sample(&IDforest);
					al_play_sample(MusicInicio, 0.3, 0, 0.9, ALLEGRO_PLAYMODE_LOOP, &in);
					Escenario = 0;
				}
				

				al_draw_bitmap(Final, -100, -150, NULL);
				al_draw_textf(Inicio, al_map_rgb(0, 0, 0), WIDTH / 2, 100, ALLEGRO_ALIGN_CENTRE, "Juego terminado");
				al_draw_textf(Inicio, al_map_rgb(0, 0, 0), WIDTH / 2, 160, ALLEGRO_ALIGN_CENTRE, "Puntuacion: %i", Car.score * 10 + int(Car.distancia));
				al_draw_textf(Inicio, al_map_rgb(0, 0, 0), WIDTH / 2, 220, ALLEGRO_ALIGN_CENTRE, "Distancia recorrida: %.2f km", Car.distancia / 1000);

			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	al_destroy_font(font18);
	al_destroy_font(font22);
	al_destroy_font(DIGI);
	al_destroy_font(DIGI1);
	al_destroy_font(DIGI2);
	al_destroy_font(DIGI3);
	al_destroy_font(Inicio);
	al_destroy_font(Fonta);
	al_destroy_font(Num);

	al_destroy_sample(Explo);
	al_destroy_sample(Music);
	al_destroy_sample(Pick);
	al_destroy_sample(Low);
	al_destroy_sample(Choque);
	al_destroy_sample(Choose);
	al_destroy_sample(MusicInicio);
	al_destroy_sample(pause);
	al_destroy_sample(SFXlava);
	al_destroy_sample(SFXforest);
	al_destroy_sample(Carr);
	al_destroy_sample(GameOver);
	
	
	al_destroy_bitmap(dash);

	al_destroy_bitmap(Car.imagencarro);
	al_destroy_bitmap(Car.izq);
	al_destroy_bitmap(Car.der);

	al_destroy_bitmap(luz.luz);

	al_destroy_bitmap(street.imagencamino);

	al_destroy_bitmap(Vidas);

	al_destroy_bitmap(fondo);
	al_destroy_bitmap(volcano);
	al_destroy_bitmap(volcano2);
	al_destroy_bitmap(beach);
	al_destroy_bitmap(beach2);
	al_destroy_bitmap(forest);
	al_destroy_bitmap(forest2);
	al_destroy_bitmap(Pantalla);
	al_destroy_bitmap(Final);
	al_destroy_bitmap(cursor);

	al_destroy_bitmap(Exp.expl2);
	al_destroy_bitmap(Exp.expl3);
	al_destroy_bitmap(Exp.expl4);
	al_destroy_bitmap(Exp.expl5);
	al_destroy_bitmap(Exp.expl6);
	al_destroy_bitmap(Exp.expl7);
	al_destroy_bitmap(Exp.expl8);
	al_destroy_bitmap(Exp.expl9);
	al_destroy_bitmap(Exp.expl10);

	al_destroy_bitmap(bat.bateria1);
	al_destroy_bitmap(bat.bateria2);
	al_destroy_bitmap(bat.bateria3);
	al_destroy_bitmap(bat.bateria4);
	al_destroy_bitmap(bat.bateria5);

	al_destroy_bitmap(RBoost);
	al_destroy_bitmap(RTempa);
	al_destroy_bitmap(RTempo);

	if (Escenario == 1)
	{
		for (int i = 0; i < NUM_COMETS; i++)
		{
			al_destroy_bitmap(comets[i].imagen000);
			al_destroy_bitmap(comets[i].imagen001);
			al_destroy_bitmap(comets[i].imagen002);
			al_destroy_bitmap(comets[i].imagen003);
			al_destroy_bitmap(comets[i].imagen004);
			al_destroy_bitmap(comets[i].imagen005);
			al_destroy_bitmap(comets[i].imagen006);
			al_destroy_bitmap(comets[i].imagen007);
			al_destroy_bitmap(comets[i].imagen008);
			al_destroy_bitmap(comets[i].imagen009);
		}
	}

	else if (Escenario == 2 || Escenario == 3)
	{
		for (int i = 0; i < NUM_COMETS; i++)
		{
			al_destroy_bitmap(comets[i].imagen000);
			al_destroy_bitmap(comets[i].imagen001);
			al_destroy_bitmap(comets[i].imagen002);
			al_destroy_bitmap(comets[i].imagen003);
			al_destroy_bitmap(comets[i].imagen004);
			al_destroy_bitmap(comets[i].imagen005);
			al_destroy_bitmap(comets[i].imagen006);
			al_destroy_bitmap(comets[i].imagen007);
			al_destroy_bitmap(comets[i].imagen008);
			al_destroy_bitmap(comets[i].imagen009);
			al_destroy_bitmap(comets[i].imagen010);
			al_destroy_bitmap(comets[i].imagen011);
			al_destroy_bitmap(comets[i].imagen012);
			al_destroy_bitmap(comets[i].imagen013);
			al_destroy_bitmap(comets[i].imagen014);
			al_destroy_bitmap(comets[i].imagen015);
		}
	}
	
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		al_destroy_bitmap(bullets[i].imagenbala);
	}
	for (int i = 0; i < NUM_LINEAS; i++)
	{
		al_destroy_bitmap(lineas[i].gato);
	}
	for (int i = 0; i < NUM_ARBOLES; i++)
	{
		al_destroy_bitmap(arboles[i].imagenarbol);
	}
	for (int i = 0; i < NUM_MONEY; i++)
	{
		al_destroy_bitmap(dinero[i].imagendinero);
	}
	for (int i = 0; i < NUM_GRASS; i++)
	{
		al_destroy_bitmap(grass[i].grass);
	}
	for (int i = 0; i < NUM_SAND; i++)
	{
		al_destroy_bitmap(sand[i].sandi);
		al_destroy_bitmap(sand[i].sandd);
	}
	for (int i = 0; i < NUM_AGUA; i++)
	{
		al_destroy_bitmap(agua[i].a1);
		al_destroy_bitmap(agua[i].a2);
		al_destroy_bitmap(agua[i].a3);
		al_destroy_bitmap(agua[i].a4);
		al_destroy_bitmap(agua[i].a5);
		al_destroy_bitmap(agua[i].a6);
		al_destroy_bitmap(agua[i].a7);
		al_destroy_bitmap(agua[i].a8);
	}

	for (int i = 0; i < NUM_LAVA; i++)
	{
		al_destroy_bitmap(lava[i].lava);
	}

	return 0;
}


void InitCar(Carro &Car)
{
	
	Car.x = WIDTH / 2 - 35;
	Car.y = HEIGHT - 75;
	Car.ID = PLAYER;
	Car.lives = 3;
	Car.minima = -1;
	Car.Energia = 1000;
	Car.speed = 7;
	Car.low = 0;
	Car.boundx = 35;
	Car.boundy = 85;
	Car.boost = 0;
	Car.Bos = 0;
	Car.Boost = false;
	Car.score = 0;
	Car.distancia = 0;
	Car.luz = 0;
	Car.C = 0;
	Car.V = 0;
	Car.kills = 0;
	Car.choque = false;
	Car.frec = 0;
	Car.imagencarro = al_load_bitmap("autos/1.png");
	Car.izq = al_load_bitmap("autos/izq.png");
	Car.der = al_load_bitmap("autos/der.png");
}
void DrawCar(Carro &Car, ALLEGRO_SAMPLE*Choque)
{

	if (vueltas < 100)
	{
		if (Escenario == 1)
		{
			Car.Temp = 15;
		}
		else if (Escenario == 2)
		{
			Car.Temp = 10;
		}
		else if (Escenario == 3)
		{
			Car.Temp = 6;
		}
	}
	
	if (Car.minima >= speed)
	{
		speed = float(Car.minima);
	}


	if (Car.choque)
		Car.frec +=2;
	if (Car.frec >= 50)
	{
		Car.frec = 0;
		Car.choque = false;
	}
	
	if (keys[RIGHT])
	{
		if (Car.choque)
		{
			if (Car.frec%10==0)
			{
				al_draw_bitmap(Car.der, Car.x, Car.y - 80, NULL);
				al_play_sample(Choque, 0.5, 0, 1.2, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
		else
			al_draw_bitmap(Car.der, Car.x, Car.y - 80, NULL);
	}
	else if (keys[LEFT])
	{
		if (Car.choque)
		{
			if (Car.frec%10==0)
			{
				al_draw_bitmap(Car.izq, Car.x, Car.y - 80, NULL);
				al_play_sample(Choque, 0.5, 0, 1.2, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
		else
			al_draw_bitmap(Car.izq, Car.x, Car.y - 80, NULL);
	}
	else
	{
		if (Car.choque)
		{
			if (Car.frec%10==0)
			{
				al_draw_bitmap(Car.imagencarro, Car.x, Car.y - 75, NULL);
				al_play_sample(Choque, 0.5, 0, 1.2, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
		else
			al_draw_bitmap(Car.imagencarro, Car.x, Car.y - 75, NULL);
	}
}
void MoveCarUp(Carro &Car)
{
	Car.y -= Car.speed;
	if (Car.y < 0)
	{
		Car.y = 0;
	}
	else
	{
		Car.distancia += 0.0006;
	}

}
void MoveCarDown(Carro &Car)
{
	Car.y += Car.speed;
	if (Car.y > HEIGHT)
	{
		Car.y = HEIGHT;
	}
	else
	{
		Car.distancia -= 0.0006;
	}

}
void MoveCarLeft(Carro &Car,Comet comets[])
{
	
	if (Automatic)
	{
		if (Car.x <= WIDTH / 2 - 203)
		{
			Car.x = WIDTH / 2 - 203;
			keys[LEFT] = false;
		}
		else
		{
			Limites(Car, comets);
			if (keys[LEFT])
				Car.x -= Car.speed;
			Limites(Car, comets);
		}
	}
	else
	{
		Car.x -= Car.speed;
		if (Car.x <= WIDTH / 2 - 200)
		{
			Car.x = WIDTH / 2 - 200;
			keys[LEFT] = false;
		}
	}
	
		
}
void MoveCarRight(Carro &Car, Comet comets[])
{
	
	if (Automatic)
	{
		if (Car.x >= WIDTH / 2 + 125)
		{
			Car.x = WIDTH / 2 + 125;
			keys[RIGHT] = false;
		}
		else
		{
			Limites(Car, comets);
			if (keys[RIGHT])
				Car.x += Car.speed;
			Limites(Car, comets);
		}
	}
	else
	{
		Car.x += Car.speed;
		if (Car.x >= WIDTH / 2 + 125)
		{
			Car.x = WIDTH / 2 + 125;
			keys[RIGHT] = false;
		}
	}
	
}


void SubirVelocidad(Comet comets[], int sizec, Carro &Car)
{
	if (speed <= 25)
	{
		for (int i = 0; i < sizec; i++)
		{
			comets[i].speed += 2;
		}
		speed += 2;
		Car.speed += 0.5;
		if (R > 100)
		{
			R -= 50;
		}
	}


}
void BajarVelocidad(Comet comets[], int sizec, Carro &Car)
{
	if (speed > 0 && Car.minima<speed)
	{
		for (int i = 0; i < sizec; i++)
		{
			if (Car.minima < speed)
			{
				comets[i].speed -= 2;
			}
			
		}
		speed -= 2;
		Car.speed -= 0.5;
		if (R < 500)
			R += 50;

	}

}


void InitBullet(Bullet bullet[], int size)
{
	for (int i = 0; i < size; i++)
	{
		bullet[i].ID = BULLET;
		bullet[i].speed = 12;
		bullet[i].boundx = 3;
		bullet[i].boundy = 2;
		bullet[i].live = false;
		bullet[i].imagenbala = al_load_bitmap("balas/bala1.png");
	}
}
void DrawBullet(Bullet bullet[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (bullet[i].live)
			al_draw_bitmap(bullet[i].imagenbala, bullet[i].x, bullet[i].y, NULL);
	}
}
void FireBullet(Bullet bullet[], int size, Carro &Car)
{
	if (Car.Energia >= 30)
	{
		for (int i = 0; i < size; i++)
		{
			if (!bullet[i].live)
			{
				bullet[i].x = Car.x + 13;
				bullet[i].y = Car.y - 100;
				bullet[i].live = true;
				break;
			}
		}
		Car.Energia -= 30;
	}

}
void UpdateBullet(Bullet bullet[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (bullet[i].live)
		{
			bullet[i].y -= bullet[i].speed;
			if (bullet[i].y <-40)
				bullet[i].live = false;
		}
	}
}
void CollideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize, Carro &Car, ALLEGRO_SAMPLE * Explo)
{
	for (int i = 0; i < bSize; i++)
	{
		if (bullet[i].live)
		{
			for (int j = 0; j < cSize; j++)
			{
				if (comets[j].live)
				{
					if ((bullet[i].x + bullet[i].boundx)>(comets[j].x - comets[j].boundx) &&
						(bullet[i].x - 30)< (comets[j].x + comets[j].boundx + 2) &&
						(bullet[i].y + bullet[i].boundy)>(comets[j].y - comets[j].boundy) &&
						(bullet[i].y - bullet[i].boundy - 25)< (comets[j].y + comets[j].boundy))
					{
						bullet[i].live = false;
						comets[j].choca = false;
						comets[j].live = false;
						comets[j].bullet = true;

						al_play_sample(Explo, 0.5, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);

						Car.score += 10;
						Car.kills++;
					}
				}
			}
		}
	}
}


void InitComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		comets[i].ID = ENEMY;
		comets[i].choca = true;
		comets[i].live = false;
		comets[i].bullet = false;
		comets[i].speed = 4;
		comets[i].boundx = 36;
		comets[i].boundy = 32;
		comets[i].frec = 0;


		if (Escenario == 1)
		{
			comets[i].imagen000 = al_load_bitmap("enemigo/floating-s0000.png");
			comets[i].imagen001 = al_load_bitmap("enemigo/floating-s0001.png");
			comets[i].imagen002 = al_load_bitmap("enemigo/floating-s0002.png");
			comets[i].imagen003 = al_load_bitmap("enemigo/floating-s0003.png");
			comets[i].imagen004 = al_load_bitmap("enemigo/floating-s0004.png");
			comets[i].imagen005 = al_load_bitmap("enemigo/floating-s0005.png");
			comets[i].imagen006 = al_load_bitmap("enemigo/floating-s0006.png");
			comets[i].imagen007 = al_load_bitmap("enemigo/floating-s0007.png");
			comets[i].imagen008 = al_load_bitmap("enemigo/floating-s0008.png");
			comets[i].imagen009 = al_load_bitmap("enemigo/floating-s0009.png");
		}
		else if (Escenario == 2)
		{
			comets[i].imagen000 = al_load_bitmap("enemigo/blinking-red-s0000.png");
			comets[i].imagen001 = al_load_bitmap("enemigo/blinking-red-s0001.png");
			comets[i].imagen002 = al_load_bitmap("enemigo/blinking-red-s0002.png");
			comets[i].imagen003 = al_load_bitmap("enemigo/blinking-red-s0003.png");
			comets[i].imagen004 = al_load_bitmap("enemigo/blinking-red-s0004.png");
			comets[i].imagen005 = al_load_bitmap("enemigo/blinking-red-s0005.png");
			comets[i].imagen006 = al_load_bitmap("enemigo/blinking-red-s0006.png");
			comets[i].imagen007 = al_load_bitmap("enemigo/blinking-red-s0007.png");
			comets[i].imagen008 = al_load_bitmap("enemigo/blinking-red-s0008.png");
			comets[i].imagen009 = al_load_bitmap("enemigo/blinking-red-s0009.png");
			comets[i].imagen010 = al_load_bitmap("enemigo/blinking-red-s0010.png");
			comets[i].imagen011 = al_load_bitmap("enemigo/blinking-red-s0011.png");
			comets[i].imagen012 = al_load_bitmap("enemigo/blinking-red-s0012.png");
			comets[i].imagen013 = al_load_bitmap("enemigo/blinking-red-s0013.png");
			comets[i].imagen014 = al_load_bitmap("enemigo/blinking-red-s0014.png");
			comets[i].imagen015 = al_load_bitmap("enemigo/blinking-red-s0015.png");
		}
		else if (Escenario == 3)
		{
			comets[i].imagen000 = al_load_bitmap("enemigo/blinking-green-s0000.png");
			comets[i].imagen001 = al_load_bitmap("enemigo/blinking-green-s0001.png");
			comets[i].imagen002 = al_load_bitmap("enemigo/blinking-green-s0002.png");
			comets[i].imagen003 = al_load_bitmap("enemigo/blinking-green-s0003.png");
			comets[i].imagen004 = al_load_bitmap("enemigo/blinking-green-s0004.png");
			comets[i].imagen005 = al_load_bitmap("enemigo/blinking-green-s0005.png");
			comets[i].imagen006 = al_load_bitmap("enemigo/blinking-green-s0006.png");
			comets[i].imagen007 = al_load_bitmap("enemigo/blinking-green-s0007.png");
			comets[i].imagen008 = al_load_bitmap("enemigo/blinking-green-s0008.png");
			comets[i].imagen009 = al_load_bitmap("enemigo/blinking-green-s0009.png");
			comets[i].imagen010 = al_load_bitmap("enemigo/blinking-green-s0010.png");
			comets[i].imagen011 = al_load_bitmap("enemigo/blinking-green-s0011.png");
			comets[i].imagen012 = al_load_bitmap("enemigo/blinking-green-s0012.png");
			comets[i].imagen013 = al_load_bitmap("enemigo/blinking-green-s0013.png");
			comets[i].imagen014 = al_load_bitmap("enemigo/blinking-green-s0014.png");
			comets[i].imagen015 = al_load_bitmap("enemigo/blinking-green-s0015.png");
		}

	}
} 
void DrawComet(Comet comets[], int size, Carro car)
{
	if (car.minima >= speed)
	{
		for (int i = 0; i < size; i++)
		{
			comets[i].speed = car.minima + 2;
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			comets[i].frec += comets[i].speed + 50;
			if (Escenario == 1)
			{
				if (0 < comets[i].frec && 300 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen000, comets[i].x, comets[i].y, NULL);
				if (300 < comets[i].frec && 600 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen001, comets[i].x, comets[i].y, NULL);
				if (600 < comets[i].frec && 900 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen002, comets[i].x, comets[i].y, NULL);
				if (900 < comets[i].frec && 1200 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen003, comets[i].x, comets[i].y, NULL);
				if (1200 < comets[i].frec && 1500 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen004, comets[i].x, comets[i].y, NULL);
				if (1500 < comets[i].frec && 1800 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen005, comets[i].x, comets[i].y, NULL);
				if (1800 < comets[i].frec && 2100 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen006, comets[i].x, comets[i].y, NULL);
				if (2100 < comets[i].frec && 2400 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen007, comets[i].x, comets[i].y, NULL);
				if (2400 < comets[i].frec && 2700 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen008, comets[i].x, comets[i].y, NULL);
				if (2700 < comets[i].frec)
					al_draw_bitmap(comets[i].imagen009, comets[i].x, comets[i].y, NULL);
				if (comets[i].frec >= 3000)
				{
					comets[i].frec = 0;
				}
			}
			else if (Escenario == 2||Escenario==3)
			{
				
				if (0<comets[i].frec && 300 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen000, comets[i].x, comets[i].y, NULL);
				if (300<comets[i].frec && 600 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen001, comets[i].x, comets[i].y, NULL);
				if (600<comets[i].frec && 900 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen002, comets[i].x, comets[i].y, NULL);
				if (900<comets[i].frec && 1200 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen003, comets[i].x, comets[i].y, NULL);
				if (1200<comets[i].frec && 1500 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen004, comets[i].x, comets[i].y, NULL);
				if (1500<comets[i].frec && 1800 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen005, comets[i].x, comets[i].y, NULL);
				if (1800<comets[i].frec && 2100 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen006, comets[i].x, comets[i].y, NULL);
				if (2100<comets[i].frec && 2400 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen007, comets[i].x, comets[i].y, NULL);
				if (2400<comets[i].frec && 2700 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen008, comets[i].x, comets[i].y, NULL);
				if (2700<comets[i].frec && 3000 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen009, comets[i].x, comets[i].y, NULL);
				if (3000<comets[i].frec && 3300 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen010, comets[i].x, comets[i].y, NULL);
				if (3300<comets[i].frec && 3600 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen011, comets[i].x, comets[i].y, NULL);
				if (3600<comets[i].frec && 3900 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen012, comets[i].x, comets[i].y, NULL);
				if (3900<comets[i].frec && 4200 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen013, comets[i].x, comets[i].y, NULL);
				if (4200<comets[i].frec && 4500 >= comets[i].frec)
					al_draw_bitmap(comets[i].imagen014, comets[i].x, comets[i].y, NULL);
				if (4500<comets[i].frec)
					al_draw_bitmap(comets[i].imagen015, comets[i].x, comets[i].y, NULL);
				if (comets[i].frec >= 4800)
				{
					comets[i].frec = 0;
				}

			}

		}
		else if (comets[i].bullet)
		{
			comets[i].frec2 += 50;
			if (0<comets[i].frec2 && 300 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl2, comets[i].x-33, comets[i].y-33, NULL);
			if (300<comets[i].frec2 && 600 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl3, comets[i].x-33, comets[i].y-33, NULL);
			if (600<comets[i].frec2 && 900 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl4, comets[i].x-33, comets[i].y-33, NULL);
			if (900<comets[i].frec2 && 1200 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl5, comets[i].x-33, comets[i].y-33, NULL);
			if (1200<comets[i].frec2 && 1500 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl6, comets[i].x-33, comets[i].y-33, NULL);
			if (1500<comets[i].frec2 && 1800 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl7, comets[i].x-33, comets[i].y-33, NULL);
			if (1800<comets[i].frec2 && 2100 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl8, comets[i].x-33, comets[i].y-33, NULL);
			if (2100<comets[i].frec2 && 2400 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl9, comets[i].x-33, comets[i].y-33, NULL);
			if (2400<comets[i].frec2 && 2700 >= comets[i].frec2)
				al_draw_bitmap(Exp.expl10, comets[i].x-33, comets[i].y-33, NULL);
			if (comets[i].frec2 >= 2700)
			{
				comets[i].frec2 = 0;
			}
		}
	}
}
void StartComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!comets[i].live)
		{
			if (rand() % R == 0)
			{
				comets[i].live = true;
				comets[i].bullet = false;
				comets[i].x = rand() % 317 + (WIDTH / 2 - 195);
				comets[i].y = -80;
				comets[i].frec2 = 0;

				break;
			}
		}
	}
}
void UpdateComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{

		if (comets[i].live)
		{
			comets[i].y += comets[i].speed;
		}
		else if (comets[i].bullet)
		{
			comets[i].y += speed;
		}
	}
}
void CollideComet(Comet comets[], int cSize, Carro &Car, ALLEGRO_SAMPLE *Explo)
{
	for (int i = 0; i < cSize; i++)
	{
		if (comets[i].live)
		{
			if (comets[i].x - comets[i].boundx < Car.x + Car.boundx &&
				comets[i].x + comets[i].boundx > Car.x - Car.boundx &&
				comets[i].y - comets[i].boundy + 20 < Car.y + Car.boundy - 20 &&
				comets[i].y + comets[i].boundy > Car.y - Car.boundy)
			{
				Car.lives--;
				comets[i].live = false;
				comets[i].bullet = true;
				comets[i].choca = false;
				Car.choque = true;
				al_play_sample(Explo, 0.5, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (comets[i].y > HEIGHT)
			{
				comets[i].live = false;
				comets[i].bullet = true;
				comets[i].choca = false; 
				comets[i].frec2 = 0;

			}
		}
	}
}

void DrawStatic(Comet comets[], int &frece)
{
	frece += comets[0].speed + 50;
	if (Escenario == 1)
	{
		if (0 < frece && 300 >= frece)
			al_draw_bitmap(comets[0].imagen000, 230, 290, NULL);
		if (300 < frece && 600 >= frece)
			al_draw_bitmap(comets[0].imagen001, 230, 290, NULL);
		if (600 < frece && 900 >= frece)
			al_draw_bitmap(comets[0].imagen002, 230, 290, NULL);
		if (900 < frece && 1200 >= frece)
			al_draw_bitmap(comets[0].imagen003, 230, 290, NULL);
		if (1200 < frece && 1500 >= frece)
			al_draw_bitmap(comets[0].imagen004, 230, 290, NULL);
		if (1500 < frece && 1800 >= frece)
			al_draw_bitmap(comets[0].imagen005, 230, 290, NULL);
		if (1800 < frece && 2100 >= frece)
			al_draw_bitmap(comets[0].imagen006, 230, 290, NULL);
		if (2100 < frece && 2400 >= frece)
			al_draw_bitmap(comets[0].imagen007, 230, 290, NULL);
		if (2400 < frece && 2700 >= frece)
			al_draw_bitmap(comets[0].imagen008, 230, 290, NULL);
		if (2700 < frece)
			al_draw_bitmap(comets[0].imagen009, 230, 290, NULL);
		if (frece >= 3000)
		{
			frece = 0;
		}
	}
	else if (Escenario == 2 || Escenario == 3)
	{

		if (0 < frece && 300 >= frece)
			al_draw_bitmap(comets[0].imagen000, 230, 290, NULL);
		if (300 < frece && 600 >= frece)
			al_draw_bitmap(comets[0].imagen001, 230, 290, NULL);
		if (600 < frece && 900 >= frece)
			al_draw_bitmap(comets[0].imagen002, 230, 290, NULL);
		if (900 < frece && 1200 >= frece)
			al_draw_bitmap(comets[0].imagen003, 230, 290, NULL);
		if (1200 < frece && 1500 >= frece)
			al_draw_bitmap(comets[0].imagen004, 230, 290, NULL);
		if (1500 < frece && 1800 >= frece)
			al_draw_bitmap(comets[0].imagen005, 230, 290, NULL);
		if (1800 < frece && 2100 >= frece)
			al_draw_bitmap(comets[0].imagen006, 230, 290, NULL);
		if (2100 < frece && 2400 >= frece)
			al_draw_bitmap(comets[0].imagen007, 230, 290, NULL);
		if (2400 < frece && 2700 >= frece)
			al_draw_bitmap(comets[0].imagen008, 230, 290, NULL);
		if (2700 < frece && 3000 >= frece)
			al_draw_bitmap(comets[0].imagen009, 230, 290, NULL);
		if (3000 < frece && 3300 >= frece)
			al_draw_bitmap(comets[0].imagen010, 230, 290, NULL);
		if (3300 < frece && 3600 >= frece)
			al_draw_bitmap(comets[0].imagen011, 230, 290, NULL);
		if (3600 < frece && 3900 >= frece)
			al_draw_bitmap(comets[0].imagen012, 230, 290, NULL);
		if (3900 < frece && 4200 >= frece)
			al_draw_bitmap(comets[0].imagen013, 230, 290, NULL);
		if (4200 < frece && 4500 >= frece)
			al_draw_bitmap(comets[0].imagen014, 230, 290, NULL);
		if (4500 < frece)
			al_draw_bitmap(comets[0].imagen015, 230, 290, NULL);
		if (frece >= 4800)
		{
			frece = 0;
		}

	}


}
   
void InitArbol(Arbol arboles[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arboles[i].ID = ARBOL;
		arboles[i].live = false;
		arboles[i].imagenarbol = al_load_bitmap("arbol/arbol1.png");
	}
}
void DrawArbol(Arbol arboles[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arboles[i].live)
		{
			al_draw_bitmap(arboles[i].imagenarbol, arboles[i].x, arboles[i].y, NULL);
		}
	}
}
void StartArbol(Arbol arboles[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!arboles[i].live)
		{
			if (i == 0 || i == 1)
			{
				if (i == 0)
				{
					arboles[i].x = (WIDTH / 2 - 282) - rand() % 120;
				}
				else
				{
					arboles[i].x = (WIDTH / 2 + 133) + rand() % 100;
				}
				if (vueltas <= 6)
					arboles[i].y = HEIGHT;
				else
					arboles[i].y = -600;
			}
			else if (i % 2 == 0)
			{
				arboles[i].x = (WIDTH / 2 - 282) - rand() % 120;
				arboles[i].y = arboles[i - 2].y - 100;
			}
			else
			{
				arboles[i].x = (WIDTH / 2 + 133) + rand() % 100;
				arboles[i].y = arboles[i - 2].y - 100;
			}

			arboles[i].live = true;
			break;
		}
	}
}
void UpdateArbol(Arbol arboles[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arboles[i].live)
		{
			arboles[i].y += speed;
			if (arboles[i].y - 10>HEIGHT)
				arboles[i].live = false;
		}

	}
}


void InitGrass(Grass grass[], int size)
{
	for (int i = 0; i < size; i++)
	{
		grass[i].ID = GRASS;
		grass[i].live = false;
		grass[i].grass = al_load_bitmap("grass/grass.png");
	}
}
void DrawGrass(Grass grass[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (grass[i].live)
		{
			al_draw_bitmap(grass[i].grass, grass[i].x, grass[i].y, NULL);
		}
	}
}
void StartGrass(Grass grass[], int size)
{

	for (int i = 0; i < size; i++)
	{

		if (!grass[i].live)
		{
			if (i == 0 || i == 1)
			{
				if (i == 0)
				{
					grass[i].x = (WIDTH / 2 - 350);
				}
				else
				{
					grass[i].x = (WIDTH / 2 + 180);
				}
				if (vueltas <= 6)
				{
					grass[i].y = HEIGHT;
				}
				else
				{
					grass[i].y = -600;
				}
				
			}
			else if (i % 2 == 0)
			{
				grass[i].x = (WIDTH / 2 - 350);
				grass[i].y = grass[i - 2].y - 200;
			}
			else
			{
				grass[i].x = (WIDTH / 2 + 200);
				grass[i].y = grass[i - 2].y - 200;
			}

			grass[i].live = true;
			break;
		}
	}
}
void UpdateGrass(Grass grass[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (grass[i].live)
		{
			grass[i].y += speed;
			if (grass[i].y - 100 > HEIGHT)
			{
				grass[i].live = false;
			}
		}
	}
}


void InitAgua(Agua agua[], int size)
{
	for (int i = 0; i < size; i++)
	{
		agua[i].live = false;
		agua[i].frec = 0;
		agua[i].a1 = al_load_bitmap("MapaAgua/ani-water-0000.png");
		agua[i].a2 = al_load_bitmap("MapaAgua/ani-water-0001.png");
		agua[i].a3 = al_load_bitmap("MapaAgua/ani-water-0002.png");
		agua[i].a4 = al_load_bitmap("MapaAgua/ani-water-0003.png");
		agua[i].a5 = al_load_bitmap("MapaAgua/ani-water-0004.png");
		agua[i].a6 = al_load_bitmap("MapaAgua/ani-water-0005.png");
		agua[i].a7 = al_load_bitmap("MapaAgua/ani-water-0006.png");
		agua[i].a8 = al_load_bitmap("MapaAgua/ani-water-0007.png");

	}
}
void DrawAgua(Agua agua[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (agua[i].live)
		{
			agua[i].frec += 50;
			if (0<agua[i].frec && 300 >= agua[i].frec)
				al_draw_bitmap(agua[i].a1, agua[i].x + 100, agua[i].y - 33, NULL);
			if (300<agua[i].frec && 600 >= agua[i].frec)
				al_draw_bitmap(agua[i].a2, agua[i].x + 100, agua[i].y - 33, NULL);
			if (600<agua[i].frec && 900 >= agua[i].frec)
				al_draw_bitmap(agua[i].a3, agua[i].x + 100, agua[i].y - 33, NULL);
			if (900<agua[i].frec && 1200 >= agua[i].frec)
				al_draw_bitmap(agua[i].a4, agua[i].x + 100, agua[i].y - 33, NULL);
			if (1200<agua[i].frec && 1500 >= agua[i].frec)
				al_draw_bitmap(agua[i].a5, agua[i].x + 100, agua[i].y - 33, NULL);
			if (1500<agua[i].frec && 1800 >= agua[i].frec)
				al_draw_bitmap(agua[i].a6, agua[i].x + 100, agua[i].y - 33, NULL);
			if (1800<agua[i].frec && 2100 >= agua[i].frec)
				al_draw_bitmap(agua[i].a7, agua[i].x + 100, agua[i].y - 33, NULL);
			if (2100<agua[i].frec)
				al_draw_bitmap(agua[i].a8, agua[i].x + 100, agua[i].y - 33, NULL);
			if (agua[i].frec >= 2400)
			{
				agua[i].frec = 0;
			}
		}
	}
}
void StartAgua(Agua agua[], int size)
{

	for (int i = 0; i < size; i++)
	{

		if (!agua[i].live)
		{
			if (i == 0 || i == 1)
			{
				if (i == 0)
				{
					agua[i].x = (WIDTH / 2 - 450);
				}
				else
				{
					agua[i].x = (WIDTH / 2 +60);
				}
				if (vueltas <= 6)
				{
					agua[i].y = HEIGHT;
				}
				else
				{
					agua[i].y = -540;
				}

			}
			else if (i % 2 == 0)
			{
				agua[i].x = (WIDTH / 2 - 450);
				agua[i].y = agua[i - 2].y - 188;
			}
			else
			{
				agua[i].x = (WIDTH / 2 + 60);
				agua[i].y = agua[i - 2].y - 188;
			}

			agua[i].live = true;
			break;
		}
	}
}
void UpdateAgua(Agua agua[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (agua[i].live)
		{
			agua[i].y += speed;
			if (agua[i].y - 100 > HEIGHT)
			{
				agua[i].live = false;
			}
		}
	}
}


void InitLava(Lava lava[], int size)
{
	for (int i = 0; i < size; i++)
	{
		lava[i].live = false;
		lava[i].lava = al_load_bitmap("MapaLava/Lava.png");

	}
}
void DrawLava(Lava lava[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (lava[i].live)
		{
			al_draw_bitmap(lava[i].lava, lava[i].x, lava[i].y, NULL);
		}
	}
}
void StartLava(Lava lava[], int size)
{

	for (int i = 0; i < size; i++)
	{

		if (!lava[i].live)
		{
			if (i == 0 || i == 1)
			{
				if (i == 0)
				{
					lava[i].x = (WIDTH / 2 - 450);
				}
				else
				{
					lava[i].x = (WIDTH / 2 + 100);
				}
				if (vueltas <= 6)
				{
					lava[i].y = HEIGHT;
				}
				else
				{
					lava[i].y = -490;
				}

			}
			else if (i % 2 == 0)
			{
				lava[i].x = (WIDTH / 2 - 450);
				lava[i].y = lava[i - 2].y - 250;
			}
			else
			{
				lava[i].x = (WIDTH / 2 + 100);
				lava[i].y = lava[i - 2].y - 250;
			}

			lava[i].live = true;
			break;
		}
	}
}
void UpdateLava(Lava lava[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (lava[i].live)
		{
			lava[i].y += speed;
			if (lava[i].y - 100 > HEIGHT)
			{
				lava[i].live = false;
			}
		}
	}
}


void InitSand(Sand sand[], int size)
{
	for (int i = 0; i < size; i++)
	{
		sand[i].ID = SAND;
		sand[i].live = false;
		sand[i].frec = 0;
		sand[i].sandd = al_load_bitmap("MapaAgua/Der.png");
		sand[i].sandi = al_load_bitmap("MapaAgua/Izq.png");
	}
}
void DrawSand(Sand sand[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (sand[i].live)
		{
			if (sand[i].x >WIDTH/ 2)
			{
				al_draw_bitmap(sand[i].sandd, sand[i].x, sand[i].y, NULL);
			}
			else 
			{
				al_draw_bitmap(sand[i].sandi, sand[i].x, sand[i].y, NULL);
				
			}
			
			
		}
	}
}
void StartSand(Sand sand[], int size)
{

	for (int i = 0; i < size; i++)
	{

		if (!sand[i].live)
		{
			if (i == 0 || i == 1)
			{
				if (i == 0)
				{
					sand[i].x = (WIDTH / 2 - 265);
				}
				else
				{
					sand[i].x = (WIDTH / 2 + 183);
				}
				if (vueltas <= 6)
				{
					sand[i].y = HEIGHT;
				}
				else
				{
					sand[i].y = -600;
				}

			}
			else if (i % 2 == 0)
			{
				sand[i].x = (WIDTH / 2 - 265);
				sand[i].y = sand[i - 2].y - 285;
			}
			else
			{
				sand[i].x = (WIDTH / 2 + 183);
				sand[i].y = sand[i - 2].y - 283;
			}

			sand[i].live = true;
			break;
		}
	}
}
void UpdateSand(Sand sand[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (sand[i].live)
		{
			sand[i].y += speed;
			if (sand[i].y - 100 > HEIGHT)
			{
				sand[i].live = false;
			}
		}
	}
}


void InitLinea(Linea lineas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		lineas[i].ID = LINEA;
		lineas[i].live = false;
		lineas[i].gato = al_load_bitmap("camino/gato.png");
	}
}
void DrawLinea(Linea lineas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (lineas[i].live)
		{
			if (i == 6)
			{
				al_draw_bitmap(lineas[i].gato, lineas[i].x + 67, lineas[i].y - 8 + 70, NULL);
			}

			else if (i == 15)
			{
				al_draw_bitmap(lineas[i].gato, lineas[i].x + 67, lineas[i].y - 8, NULL);
			}
			else if (i == 8)
			{
				al_draw_bitmap(lineas[i].gato, lineas[i].x + 60, lineas[i].y - 8 + 70, NULL);
			}
			else if (i == 17)
			{
				al_draw_bitmap(lineas[i].gato, lineas[i].x + 60, lineas[i].y - 8, NULL);
			}
			else if (i == 7)
			{
				al_draw_bitmap(lineas[i].gato, lineas[i].x + 68, lineas[i].y - 8 + 70, NULL);
				al_draw_bitmap(lineas[i].gato, lineas[i].x - 65, lineas[i].y - 8 + 70, NULL);
			}
			else if (i == 16)
			{
				al_draw_bitmap(lineas[i].gato, lineas[i].x + 68, lineas[i].y - 8, NULL);
				al_draw_bitmap(lineas[i].gato, lineas[i].x - 65, lineas[i].y - 8, NULL);
			}
			al_draw_filled_rectangle(lineas[i].x, lineas[i].y + 18, lineas[i].x + 3, lineas[i].y - 30, al_map_rgb(181, 185, 2));

		}
	}
}
void StartLinea(Linea lineas[], int size)
{

	for (int i = 0; i < size; i++)
	{

		if (!lineas[i].live)
		{
			if (i == 0 || i == 1 || i == 2)
			{
				if (i == 0)
				{
					lineas[i].x = (WIDTH / 2 + 1);
				}
				else if (i == 1)
				{
					lineas[i].x = (WIDTH / 2 + 1) + 132;
				}
				else
				{
					lineas[i].x = (WIDTH / 2 + 1) - 140;
				}
				if (vueltas <= 6)
				{
					lineas[i].y=HEIGHT;
				}
				else
				{
					lineas[i].y = -100;
				}
			}
			else if (i % 3 == 0)
			{
				lineas[i].x = (WIDTH / 2 + 1);
				lineas[i].y = lineas[i - 3].y - 110;
			}
			else if ((i - 1) % 3)
			{
				lineas[i].x = (WIDTH / 2 + 1) + 132;
				lineas[i].y = lineas[i - 3].y - 110;
			}
			else
			{
				lineas[i].x = (WIDTH / 2 + 1) - 140;
				lineas[i].y = lineas[i - 3].y - 110;
			}
			lineas[i].live = true;
		}
	}
}
void UpdateLinea(Linea lineas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (lineas[i].live)
		{
			lineas[i].y += speed;
			if (lineas[i].y - 10 > HEIGHT)
			{
				lineas[i].live = false;
			}
		}
	}
}


void InitMoney(Money dinero[], int size)
{
	for (int i = 0; i < size; i++)
	{
		dinero[i].ID = MONEY;
		dinero[i].live = false;
		dinero[i].boundx = 45;
		dinero[i].boundy = 20;
		dinero[i].imagendinero = al_load_bitmap("bateria/bateria.png");
	}
}
void DrawMoney(Money dinero[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (dinero[i].live)
		{
			al_draw_bitmap(dinero[i].imagendinero, dinero[i].x, dinero[i].y, NULL);
		}
	}
}
void StartMoney(Money dinero[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!dinero[i].live)
		{
			if (rand() % R == 0)
			{
				dinero[i].live = true;
				dinero[i].x = (WIDTH / 2 - 196) + rand() % 308;
				dinero[i].y = -100;

				break;
			}
		}
	}
}
void UpdateMoney(Money dinero[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (dinero[i].live)
		{
			dinero[i].y += speed;
		}
	}
}
void CollideMoney(Money dinero[], int cSize, Carro &Car, ALLEGRO_SAMPLE *Pick)
{
	for (int i = 0; i < cSize; i++)
	{
		if (dinero[i].live)
		{
			if (dinero[i].x - dinero[i].boundx < Car.x + Car.boundx &&
				dinero[i].x + dinero[i].boundx > Car.x - Car.boundx &&
				dinero[i].y - dinero[i].boundy < Car.y + Car.boundy &&
				dinero[i].y + dinero[i].boundy > Car.y - Car.boundy)
			{
				Car.Energia += 50;
				if (Car.Energia >= 1000)
				{
					Car.Energia = 1000;
				}

				Car.score += 5;
				dinero[i].live = false;
				al_play_sample(Pick, 0.4, 0, 0.9, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (dinero[i].y - 5 > HEIGHT)
			{
				dinero[i].live = false;
			}
		}
	}
}


void InitRoad(Road &street)
{
	if (Escenario == 2)
	{
		street.imagencamino = al_load_bitmap("camino/camino4.png");
	}
	else
	{
		street.imagencamino = al_load_bitmap("camino/camino2.png");
	}
	
}
void DrawRoad(Road &street)
{
	al_draw_bitmap(street.imagencamino, WIDTH / 2 - 203, 0, NULL);

}

void InitBat(Bateria &bat)
{
	bat.bateria1 = al_load_bitmap("bateria/1.png");
	bat.bateria2 = al_load_bitmap("bateria/2.png");
	bat.bateria3 = al_load_bitmap("bateria/3.png");
	bat.bateria4 = al_load_bitmap("bateria/4.png");
	bat.bateria5 = al_load_bitmap("bateria/5.png");
}
void DrawBat(Bateria &bat, Carro &Car)
{
	if (int(Car.Energia) >= 800)
	{
		al_draw_bitmap(bat.bateria5, 1050, 575, NULL);
	}
	else if (int(Car.Energia) >= 600 && int(Car.Energia)<800)
	{
		al_draw_bitmap(bat.bateria4, 1050, 575, NULL);
	}
	else if (int(Car.Energia) >= 400 && int(Car.Energia)<600)
	{
		al_draw_bitmap(bat.bateria3, 1050, 575, NULL);
	}
	else if (int(Car.Energia) >= 200 && int(Car.Energia)<400)
	{
		al_draw_bitmap(bat.bateria2, 1050, 575, NULL);
	}
	else if (int(Car.Energia) < 200 )
	{
		al_draw_bitmap(bat.bateria1, 1050, 575, NULL);
	}
}

void InitLuz(Luz &luz)
{
	luz.luz = al_load_bitmap("Luz/Luz.png");
}
void DrawLuz(Carro &Car, Luz luz, ALLEGRO_SAMPLE*Low)
{
	Car.luz += 15;
	if (Car.luz >= 1000)
	{
		Car.luz = 0;
	}
	if (Car.luz < 500)
	{

		al_draw_bitmap(luz.luz, 1055, 405, NULL);
	}
	if (Car.luz==195)
	{
		Car.low = 0;
		al_play_sample(Low, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}

}

void InitExplosion(Explotion &Exp)
{
	Exp.expl2 = al_load_bitmap("Explosion/explostrip-01-0.png");
	Exp.expl3 = al_load_bitmap("Explosion/explostrip-02.png");
	Exp.expl4 = al_load_bitmap("Explosion/explostrip-03.png");
	Exp.expl5 = al_load_bitmap("Explosion/explostrip-04.png");
	Exp.expl6 = al_load_bitmap("Explosion/explostrip-05.png");
	Exp.expl7 = al_load_bitmap("Explosion/explostrip-06.png");
	Exp.expl8 = al_load_bitmap("Explosion/explostrip-07.png");
	Exp.expl9 = al_load_bitmap("Explosion/explostrip-08.png");
	Exp.expl10 = al_load_bitmap("Explosion/explostrip-09.png");
}

void Choca(Comet comets[], int size, Carro Car)
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			if (comets[i].x - comets[i].boundx<Car.x + Car.boundx&&
				comets[i].x + comets[i].boundx>Car.x - Car.boundx)
			{
				comets[i].choca = true;
			}
			else
				comets[i].choca = false;
		}
		else
		{
			comets[i].choca = false;
		}

	}
}

void Limites(Carro &Car, Comet comets[])
{
	if (comets[0].live)
	{
		if (Car.y - comets[0].y < 350 && comets[0].y - Car.y < 75 && comets[0].live)
		{

			if ((Car.x - Car.boundx - (comets[0].x + comets[0].boundx)) < 15
				&& (Car.x - Car.boundx - (comets[0].x + comets[0].boundx)) > -3)
			{
				keys[LEFT] = false;
				keys[RIGHT] = true;
			}
			if ((comets[0].x - comets[0].boundx - (Car.x + Car.boundx)) < 15
				&& (comets[0].x - comets[0].boundx - (Car.x + Car.boundx)) > -3)
			{
				keys[RIGHT] = false;
				keys[LEFT] = true;
			}

		}

	}
	if (comets[1].live)
	{

		if (Car.y - comets[1].y < 350 && comets[1].y - Car.y < 75 && comets[1].live)
		{

			if ((Car.x - Car.boundx - (comets[1].x + comets[1].boundx)) < 15
				&& (Car.x - Car.boundx - (comets[1].x + comets[1].boundx)) > -3)
			{
				keys[LEFT] = false;
				keys[RIGHT] = true;
			}
			if ((comets[1].x - comets[1].boundx - (Car.x + Car.boundx)) < 15
				&& (comets[1].x - comets[1].boundx - (Car.x + Car.boundx)) > -3)
			{
				keys[RIGHT] = false;
				keys[LEFT] = true;
			}

		}

	}
	if (comets[2].live)
	{

		if (Car.y - comets[2].y < 350 && comets[2].y - Car.y < 75 && comets[2].live)
		{

			if ((Car.x - Car.boundx - (comets[2].x + comets[2].boundx)) < 15
				&& (Car.x - Car.boundx - (comets[2].x + comets[2].boundx)) > -3)
			{
				keys[LEFT] = false;
				keys[RIGHT] = true;
			}
			if ((comets[2].x - comets[2].boundx - (Car.x + Car.boundx)) < 15
				&& (comets[2].x - comets[2].boundx - (Car.x + Car.boundx)) > -3)
			{
				keys[RIGHT] = false;
				keys[LEFT] = true;
			}

		}

	}
	if (comets[3].live)
	{

		if (Car.y - comets[3].y < 350 && comets[3].y - Car.y < 75 && comets[3].live)
		{

			if ((Car.x - Car.boundx - (comets[3].x + comets[3].boundx)) < 15
				&& (Car.x - Car.boundx - (comets[3].x + comets[3].boundx)) > -3)
			{
				keys[LEFT] = false;
				keys[RIGHT] = true;
			}
			if ((comets[3].x - comets[3].boundx - (Car.x + Car.boundx)) < 15
				&& (comets[3].x - comets[3].boundx - (Car.x + Car.boundx)) > -3)
			{
				keys[RIGHT] = false;
				keys[LEFT] = true;
			}

		}

	}
	if (comets[4].live)
	{

		if (Car.y - comets[4].y < 350 && comets[4].y - Car.y < 75 && comets[4].live)
		{

			if ((Car.x - Car.boundx - (comets[4].x + comets[4].boundx)) < 15
				&& (Car.x - Car.boundx - (comets[4].x + comets[4].boundx)) > -3)
			{
				keys[LEFT] = false;
				keys[RIGHT] = true;
			}
			if ((comets[4].x - comets[4].boundx - (Car.x + Car.boundx)) < 15
				&& (comets[4].x - comets[4].boundx - (Car.x + Car.boundx)) > -3)
			{
				keys[RIGHT] = false;
				keys[LEFT] = true;
			}

		}

	}
}
void AutomaticE(Carro &Car, Comet comets[], int size, Bullet bullets[], int NUM_BULLETS, Money dinero[], int sized)
{

	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			if (comets[i].x - comets[i].boundx<Car.x + Car.boundx&&
				comets[i].x + comets[i].boundx>Car.x - Car.boundx)
			{
				comets[i].choca = true;
			}
			else
				comets[i].choca = false;
		}
		else
		{
			comets[i].choca = false;
		}

	}

	for (int i = 0; i < sized; i++)
	{
		if (dinero[i].live)
		{
			if (dinero[i].x - dinero[i].boundx<Car.x + Car.boundx&&
				dinero[i].x + dinero[i].boundx>Car.x - Car.boundx)
			{
				dinero[i].atrapa = true;
			}
			else
				dinero[i].atrapa = false;
		}
		else
		{
			dinero[i].atrapa = false;
		}

	}

	if (comets[0].choca || comets[1].choca || comets[2].choca || comets[3].choca || comets[4].choca)
	{

		for (int i = 0; i < size; i++)
		{

			if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
				(Car.x + 15 > comets[i].x - comets[i].boundx) &&
				(Car.x - 15 < comets[i].x + comets[i].boundx) &&
				Car.Energia >= 50 && comets[i].live && (comets[i].y - Car.y<30))
			{
				if (comets[i].live)
				{
					for (int i = 0; i < size; i++)
					{
						if (comets[i].live)
						{
							if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
								(Car.x + 15 > comets[i].x - comets[i].boundx) && (Car.x - 15 < comets[i].x + comets[i].boundx)
								&& comets[i].choca && Car.Energia >= 50 && (comets[i].y - Car.y<30))
							{
								comets[i].choca = false;
								keys[RIGHT] = false;
								keys[LEFT] = false;
								FireBullet(bullets, NUM_BULLETS, Car);
								comets[i].bullet = true;
							}
						}

					}
				}


			}
			else
			{
				if (comets[i].live)
				{
					if (comets[i].x - comets[i].boundx > Car.x - Car.boundx&&comets[i].choca)
					{
						if (!keys[RIGHT])
							keys[LEFT] = true;
					}
					else if (comets[i].choca)
					{
						if (!keys[LEFT])
							keys[RIGHT] = true;
					}
					for (int i = 0; i < size; i++)
					{
						if (comets[i].live)
						{
							if (comets[i].x - comets[i].boundx<Car.x + Car.boundx&&
								comets[i].x + comets[i].boundx>Car.x - Car.boundx)
							{
								comets[i].choca = true;
							}
							else
								comets[i].choca = false;
						}
						else
						{
							comets[i].choca = false;
						}

					}
					if (comets[0].choca || comets[1].choca || comets[2].choca || comets[3].choca || comets[4].choca)
					{
						if (Car.x > WIDTH / 2 + 2)
						{
							if (!keys[RIGHT])
							{
								keys[LEFT] = true;
							}
							else
							{
								keys[RIGHT] = true;
							}
						}
						else

						{
							if (!keys[LEFT])
							{
								keys[RIGHT] = true;
							}
							else
							{

								keys[LEFT] = true;
							}
						}
					}



					if (dinero[0].live || dinero[1].live&&Car.Energia >= 50)
					{
						if (!dinero[0].atrapa && !dinero[1].atrapa)
						{
							for (int i = 0; i < sized; i++)
							{
								if (dinero[i].live)
								{
									if (dinero[i].x - dinero[i].boundx + 10>Car.x + Car.boundx&&dinero[i].live)
									{
										if (!keys[LEFT])
										{
											keys[RIGHT] = true;
										}

									}
									else if (dinero[i].x + dinero[i].boundx - 10 < Car.x - Car.boundx&&dinero[i].live)
									{
										if (!keys[RIGHT])
										{
											keys[LEFT] = true;
										}
									}

								}

							}
						}

						else
						{
							bool ninguno = true;
							for (int i = 0; i < size; i++)
							{
								if (comets[i].choca)
								{
									ninguno = false;
								}
							}
							if (ninguno)
							{
								keys[LEFT] = false;
								keys[RIGHT] = false;
							}
							else
							{
								for (int i = 0; i < size; i++)
								{

									if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
										(Car.x + 15 > comets[i].x - comets[i].boundx) &&
										(Car.x - 15 < comets[i].x + comets[i].boundx) &&
										Car.Energia >= 50 && comets[i].live && (comets[i].y - Car.y<30))
									{
										if (comets[i].live)
										{
											for (int i = 0; i < size; i++)
											{
												if (comets[i].live)
												{
													if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
														(Car.x + 15 > comets[i].x - comets[i].boundx) && (Car.x - 15 < comets[i].x + comets[i].boundx)
														&& comets[i].choca && Car.Energia >= 50 && (comets[i].y - Car.y<30))
													{
														comets[i].choca = false;
														keys[RIGHT] = false;
														keys[LEFT] = false;
														FireBullet(bullets, NUM_BULLETS, Car);
														comets[i].bullet = true;
													}
												}

											}
										}


									}
									else
									{
										if (comets[i].live)
										{
											if (comets[i].x - comets[i].boundx > Car.x - Car.boundx&&comets[i].choca)
											{
												if (!keys[RIGHT])
													keys[LEFT] = true;
											}
											else if (comets[i].choca)
											{
												if (!keys[LEFT])
													keys[RIGHT] = true;
											}
											for (int i = 0; i < size; i++)
											{
												if (comets[i].live)
												{
													if (comets[i].x - comets[i].boundx<Car.x + Car.boundx&&
														comets[i].x + comets[i].boundx>Car.x - Car.boundx)
													{
														comets[i].choca = true;
													}
													else
														comets[i].choca = false;
												}
												else
												{
													comets[i].choca = false;
												}

											}
											if (comets[0].choca || comets[1].choca || comets[2].choca || comets[3].choca || comets[4].choca)
											{
												if (Car.x > WIDTH / 2 + 2)
												{
													if (!keys[RIGHT])
													{
														keys[LEFT] = true;
													}
													else
													{
														keys[RIGHT] = true;
													}
												}
												else

												{
													if (!keys[LEFT])
													{
														keys[RIGHT] = true;
													}
													else
													{

														keys[LEFT] = true;
													}
												}
											}
										}

									}
								}

							}

						}

					}

				}

			}

			if (Car.x > WIDTH / 2 + 2)
			{
				if (!keys[RIGHT])
				{
					keys[LEFT] = true;
				}
				else
				{
					keys[RIGHT] = true;
				}
			}
			else

			{
				if (!keys[LEFT])
				{
					keys[RIGHT] = true;
				}
				else
				{

					keys[LEFT] = true;
				}

			}
		}
	}
	else if (dinero[0].live || dinero[1].live&&Car.Energia >= 50)

	{

		if (!dinero[0].atrapa && !dinero[1].atrapa)
		{
			for (int i = 0; i < sized; i++)
			{
				if (dinero[i].live)
				{
					if (dinero[i].x - dinero[i].boundx + 10>Car.x + Car.boundx&&dinero[i].live)
					{
						if (!keys[LEFT])
						{
							keys[RIGHT] = true;
							keys[LEFT] = false;
						}

					}
					else if (dinero[i].x + dinero[i].boundx - 10 < Car.x - Car.boundx&&dinero[i].live)
					{
						if (!keys[RIGHT])
						{
							keys[LEFT] = true;
							keys[RIGHT] = false;
						}
					}

				}


			}
		}

		else
		{
			bool ninguno = true;
			for (int i = 0; i < size; i++)
			{
				if (comets[i].choca)
				{
					ninguno = false;
				}
				if (ninguno)
				{
					keys[LEFT] = false;
					keys[RIGHT] = false;
				}
				else
				{

					for (int i = 0; i < size; i++)
					{

						if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
							(Car.x + 15 > comets[i].x - comets[i].boundx) &&
							(Car.x - 15 < comets[i].x + comets[i].boundx) &&
							Car.Energia >= 50 && comets[i].live && (comets[i].y - Car.y<30))
						{
							if (comets[i].live)
							{
								for (int i = 0; i < size; i++)
								{
									if (comets[i].live)
									{
										if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
											(Car.x + 15 > comets[i].x - comets[i].boundx) && (Car.x - 15 < comets[i].x + comets[i].boundx)
											&& comets[i].choca && Car.Energia >= 200 && (comets[i].y - Car.y<30))
										{
											comets[i].choca = false;
											keys[RIGHT] = false;
											keys[LEFT] = false;
											FireBullet(bullets, NUM_BULLETS, Car);
											comets[i].bullet = true;
										}
									}

								}
							}


						}
						else
						{
							if (comets[i].live)
							{
								if (comets[i].x - comets[i].boundx > Car.x - Car.boundx&&comets[i].choca)
								{
									if (!keys[RIGHT])
										keys[LEFT] = true;
								}
								else if (comets[i].choca)
								{
									if (!keys[LEFT])
										keys[RIGHT] = true;
								}
								for (int i = 0; i < size; i++)
								{
									if (comets[i].live)
									{
										if (comets[i].x - comets[i].boundx<Car.x + Car.boundx&&
											comets[i].x + comets[i].boundx>Car.x - Car.boundx)
										{
											comets[i].choca = true;
										}
										else
											comets[i].choca = false;
									}
									else
									{
										comets[i].choca = false;
									}

								}
								if (comets[0].choca || comets[1].choca || comets[2].choca || comets[3].choca || comets[4].choca)
								{
									if (Car.x > WIDTH / 2 + 2)
									{
										if (!keys[RIGHT])
										{
											keys[LEFT] = true;
										}
										else
										{
											keys[RIGHT] = true;
										}
									}
									else

									{
										if (!keys[LEFT])
										{
											keys[RIGHT] = true;
										}
										else
										{

											keys[LEFT] = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}

	}

	else
	{

		bool ninguno = true;
		for (int i = 0; i < size; i++)
		{
			if (comets[i].choca)
			{
				ninguno = false;
			}
		}
		if (ninguno)
		{
			keys[LEFT] = false;
			keys[RIGHT] = false;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{

				if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
					(Car.x + 15 > comets[i].x - comets[i].boundx) &&
					(Car.x - 15 < comets[i].x + comets[i].boundx) &&
					Car.Energia >= 200 && comets[i].live && (comets[i].y - Car.y<30))
				{
					if (comets[i].live)
					{
						for (int i = 0; i < size; i++)
						{
							if (comets[i].live)
							{
								if ((Car.y - comets[i].y) < 500 && !comets[i].bullet &&
									(Car.x + 15 > comets[i].x - comets[i].boundx) && (Car.x - 15 < comets[i].x + comets[i].boundx)
									&& comets[i].choca && Car.Energia >= 200 && (comets[i].y - Car.y < 0))
								{
									comets[i].choca = false;
									keys[RIGHT] = false;
									keys[LEFT] = false;
									FireBullet(bullets, NUM_BULLETS, Car);
									comets[i].bullet = true;
								}
							}

						}
					}


				}
				else
				{
					if (comets[i].live)
					{
						if (comets[i].x - comets[i].boundx > Car.x - Car.boundx&&comets[i].choca)
						{
							if (!keys[RIGHT])
								keys[LEFT] = true;
						}
						else if (comets[i].choca)
						{
							if (!keys[LEFT])
								keys[RIGHT] = true;
						}
						for (int i = 0; i < size; i++)
						{
							if (comets[i].live)
							{
								if (comets[i].x - comets[i].boundx<Car.x + Car.boundx&&
									comets[i].x + comets[i].boundx>Car.x - Car.boundx)
								{
									comets[i].choca = true;
								}
								else
									comets[i].choca = false;
							}
							else
							{
								comets[i].choca = false;
							}

						}
						if (comets[0].choca || comets[1].choca || comets[2].choca || comets[3].choca || comets[4].choca)
						{
							if (Car.x > WIDTH / 2 + 2)
							{
								if (!keys[RIGHT])
								{
									keys[LEFT] = true;
								}
								else
								{
									keys[RIGHT] = true;
								}
							}
							else

							{
								if (!keys[LEFT])
								{
									keys[RIGHT] = true;
								}
								else
								{

									keys[LEFT] = true;
								}
							}
						}

					}

				}
			}

		}

	}
}

void Boost(Carro &Car, Comet comets[])
{
	if (Car.Boost)
	{
		Car.boost -= 5;
		if (Car.boost == 900 || Car.boost == 800 || Car.boost == 700 || Car.boost == 600 || Car.boost == 500)
		{
			speed += 4;
		}
		else if (Car.boost == 500 || Car.boost == 400 || Car.boost == 300 || Car.boost == 200 || Car.boost == 100)
		{
			speed -= 4;
		}
		if (Car.boost <= 0)
		{
			Car.Boost = false;
			keys[B] = false;
			for (int i = 0; i < 5; i++)
			{
				comets[i].speed += 2;
			}
		}
	}

}

/*
void guardar(Jugador CajaNegra[], int cont)
{
	FILE* archCajaNegra;
	fopen_s(&archCajaNegra, "Puntuaciones.txt", "w+");

	for (int y = 0; y < cont; y++)
	{
		fprintf_s(archCajaNegra, "%s", CajaNegra[y].nombre);
		if (y == (cont - 1))
		{
			fprintf_s(archCajaNegra, "\n%i", CajaNegra[y].puntuacion); 
		}
		else fprintf_s(archCajaNegra, "\n%i\n\n", CajaNegra[y].puntuacion);
	}
	fclose(archCajaNegra);
}

void cargar(Jugador CajaNegra[], int &cont)
{
	FILE*archCajaNegra;
	fopen_s(&archCajaNegra, "Puntuaciones.txt", "r");
		while (!feof(archCajaNegra))
		{
			fscanf_s(archCajaNegra, "%s", CajaNegra[cont].nombre,10);
			fscanf_s(archCajaNegra, "%i", &CajaNegra[cont].puntuacion);
			cont++;
		}
		fclose(archCajaNegra);
}

void insertar(Jugador CajaNegra[], int &cont){
	cin >> CajaNegra[cont].nombre;
	cin >> CajaNegra[cont].puntuacion;
	cont++;
}

void listarcedulas(Jugador CajaNegra[], int cont){
	int numerador = 1;
	if (cont == 0)
	{
	//no hay 
	}
	else
	{
		for (int i = 0; i < cont; i++)
		{
			cout << "	" << numerador << "	" << CajaNegra[i].puntuacion << "		" << CajaNegra[i].nombre << endl;
			numerador++;
		}
	}

}t
*/
