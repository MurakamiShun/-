# ifndef OBJECT_H
# define OBJECT_H
# define ZUKUNULL -1
# define AREA_SENT 7

typedef struct{
	int x;
	int y;
	int turn;
} MAX_SPOT;

typedef struct{
	int x;
	int y;
} Pos;

typedef struct{
	Pos Zuku[17];//”Ô•º‚P
	MAX_SPOT Max_Spot;
	int Count;
} STONE;


typedef struct{
	int Zuku[46][46];//”Ô•º‚P‚S
	int Point;
}AREA;


# endif