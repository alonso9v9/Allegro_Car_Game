enum IDS{ PLAYER, BULLET, ENEMY, MONEY, LINEA, ARBOL, GRASS,SAND};


struct Jugador
{
	char nombre[25];
	float puntuacion;
};

struct Carro
{
	int ID;
	int luz;
	int x;
	int y;
	int lives;
	int C;
	int V;
	int boundx;
	int boundy;
	int score;
	int frec;
	int low;
	int kills;
	int minima;
	int Bos;
	int Bos2;
	bool choque;
	bool Boost;
	float Energia;
	float Temp;
	int boost;
	float speed;
	float distancia;
	ALLEGRO_BITMAP *imagencarro;
	ALLEGRO_BITMAP *izq;
	ALLEGRO_BITMAP *der;
};

struct Bullet
{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP *imagenbala;
};

struct Comet
{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
	bool choca;
	bool bullet;
	int frec;
	int frec2;
	ALLEGRO_BITMAP *imagen000;
	ALLEGRO_BITMAP *imagen001;
	ALLEGRO_BITMAP *imagen002;
	ALLEGRO_BITMAP *imagen003;
	ALLEGRO_BITMAP *imagen004;
	ALLEGRO_BITMAP *imagen005;
	ALLEGRO_BITMAP *imagen006;
	ALLEGRO_BITMAP *imagen007;
	ALLEGRO_BITMAP *imagen008;
	ALLEGRO_BITMAP *imagen009;
	ALLEGRO_BITMAP *imagen010;
	ALLEGRO_BITMAP *imagen011;
	ALLEGRO_BITMAP *imagen012;
	ALLEGRO_BITMAP *imagen013;
	ALLEGRO_BITMAP *imagen014;
	ALLEGRO_BITMAP *imagen015;
};

struct Money
{
	int ID;
	int x;
	int y;
	bool atrapa;
	bool live;
	int boundx;
	int boundy;

	ALLEGRO_BITMAP *imagendinero;
};

struct Road
{
	ALLEGRO_BITMAP *imagencamino;
};

struct Linea
{
	int ID;
	int x;
	int y;
	bool live;
	ALLEGRO_BITMAP *gato;
};

struct Grass
{
	int ID;
	int x;
	int y;
	bool live;
	ALLEGRO_BITMAP *grass;
};

struct Agua
{
	int x;
	int y;
	int frec;
	bool live;
	ALLEGRO_BITMAP* a1;
	ALLEGRO_BITMAP* a2;
	ALLEGRO_BITMAP* a3;
	ALLEGRO_BITMAP* a4;
	ALLEGRO_BITMAP* a5;
	ALLEGRO_BITMAP* a6;
	ALLEGRO_BITMAP* a7;
	ALLEGRO_BITMAP* a8;
};

struct Lava
{
	int x;
	int y;
	bool live;
	ALLEGRO_BITMAP* lava;
};

struct Sand
{
	int ID;
	int x;
	int y;
	bool live;
	int frec;
	ALLEGRO_BITMAP *sandi;
	ALLEGRO_BITMAP *sandd;
};

struct Arbol
{
	int ID;
	int x;
	int y;
	bool live;
	ALLEGRO_BITMAP *imagenarbol;
};

struct Bateria
{
	ALLEGRO_BITMAP* bateria1;
	ALLEGRO_BITMAP* bateria2;
	ALLEGRO_BITMAP* bateria3;
	ALLEGRO_BITMAP* bateria4;
	ALLEGRO_BITMAP* bateria5;
};

struct Explotion
{
	ALLEGRO_BITMAP* expl2;
	ALLEGRO_BITMAP* expl3;
	ALLEGRO_BITMAP* expl4;
	ALLEGRO_BITMAP* expl5;
	ALLEGRO_BITMAP* expl6;
	ALLEGRO_BITMAP* expl7;
	ALLEGRO_BITMAP* expl8;
	ALLEGRO_BITMAP* expl9;
	ALLEGRO_BITMAP* expl10;
};

struct Luz
{
	ALLEGRO_BITMAP* luz;
};