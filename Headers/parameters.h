/*********************************************************************
 * parameters.h
 *
 *  Working on: 10/09/2021
 *
 *      Author: EL BAKRAOUI Salim
 *
 ********************************************************************/

#define APP_WINDOW_WIDTH			(960)	//In pixels
#define APP_WINDOW_HEIGHT			(544)	//In pixels
#define APP_WINDOW_PADDING			(48)	//In pixels
#define APP_WINDOW_COLOR_BKGND		(SDL_Color){190,190,190,255}
#define APP_WINDOW_COLOR_LIMITS		(SDL_Color){80,80,80,255}
#define APP_TIMER_TICK_MS			(80)

#define APP_MAIN_FONT_FILE_NAME		"./Resources/Fonts/LCDPHONE.ttf"

#define	SNAKE_INITIAL_LENGTH		(5)		//Initial number of snake sections
#define SNAKE_SECTION_SIZE			(22)	//In pixels
#define SNAKE_SECTION_SPACING		(2)		//In pixels
#define SNAKE_POS_INITIAL_X			(20)	//In tabular coordinates
#define SNAKE_POS_INITIAL_Y			(15)	//In tabular coordinates
#define SNAKE_POS_MIN_X				(0)		//In tabular coordinates
#define SNAKE_POS_MAX_X				((int)((APP_WINDOW_WIDTH-2*APP_WINDOW_PADDING)/(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING))) 	//In tabular coordinates
#define SNAKE_POS_MIN_Y				(0)		//In tabular coordinates
#define SNAKE_POS_MAX_Y				((int)((APP_WINDOW_HEIGHT-2*APP_WINDOW_PADDING)/(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)))	//In tabular coordinates

#define SNAKE_BODY_COLOR			(SDL_Color){150,50,50,255}
#define SNAKE_HEAD_COLOR			(SDL_Color){200,50,50,255}
#define SNAKE_TAIL_COLOR			(SDL_Color){100,50,50,255}

#define SNAKE_FOOD_SIZE				((int)(SNAKE_SECTION_SIZE*.9))				//In pixels
#define SNAKE_FOOD_PADDING			((SNAKE_SECTION_SIZE-SNAKE_FOOD_SIZE)/2)	//In pixels



