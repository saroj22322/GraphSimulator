/*Bar Graph Simulator for Windows*/
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "htc.h"
#include <string.h>
#include <math.h>

int xbase = 50;
int ybase = 30;

int randomVal[500] = {4,3,2,7,8,4,7,2,1,6,8,8,8,5,10,7,10,3,5,1,7,4,5,10,4,7,6,1,2,9,0,4,9,5,8,5,7,9,1,1,0,4,0,5,6,6,6,5,7,7,2,10,10,3,3,7,2,4,3,1,2,4,0,0,6,3,9,3,4,6,8,3,9,9,8,0,7,1,0,8,1,10,5,8,9,6,8,8,4,7,8,0,4,10,8,6,5,0,6,6,4,2,7,9,5,2,6,7,10,5,5,3,5,7,2,1,8,10,9,3,1,6,0,9,6,9,6,0,9,8,3,8,2,9,7,5,9,6,1,7,10,3,9,4,6,9,1,8,6,7,2,1,10,2,6,9,2,1,0,2,3,2,3,4,3,9,9,2,2,6,3,6,6,3,4,2,1,6,10,6,10,5,6,7,1,8,9,6,3,3,6,10,7,2,6,6,5,5,10,3,10,8,5,1,8,7,1,5,10,10,6,8,2,5,7,2,10,4,0,5,2,0,8,7,6,10,1,3,1,9,3,3,9,1,0,1,5,9,10,8,0,3,1,6,5,3,4,8,1,10,5,8,0,10,4,2,8,2,5,9,5,7,7,9,0,5,7,3,1,8,8,8,2,5,5,2,7,3,0,7,1,7,5,4,6,8,3,5,2,6,4,8,7,0,2,8,2,5,0,3,4,6,6,2,0,2,10,5,3,4,5,0,5,5,6,6,5,3,1,3,1,0,4,2,1,7,4,7,8,9,9,6,4,10,6,0,2,3,4,2,10,0,6,3,0,8,2,5,10,0,8,6,1,3,9,0,3,8,3,7,2,8,4,6,1,9,8,10,6,10,1,6,7,8,4,9,2,2,9,10,3,10,7,0,4,4,3,4,8,3,6,5,4,10,4,1,2,7,5,1,7,3,4,3,10,10,10,4,2,6,7,7,6,6,4,8,0,2,3,5,0,8,10,4,9,7,1,9,10,4,3,10,1,8,4,7,7,1,8,4,2,0,4,8,8,2,0,3,5,9,9,6,2,2,6,8,6,3,4,10,2,10,5,5,4,6,2,6,2,7,10,0,3,0,6,7,9,6,0,8,1,6,4,4,1,6,7,10,10,8,1,9,9,0,2,6,10,2,4,7};
double randomDVal[500];
double val[100] = {[0 ... 99] = 0.0f};

void loadBar(int x, int ybase, int pointer) {
	for (int i = 0; i < 10; ++i)
	{
		pointer = (pointer >= 100) ? 0 : pointer;
		pointer = (pointer < 0) ? 99 : pointer;
		int height = (int) ceil(val[pointer] * 2);

		if(height == 0) {
			gotoxy(x - (i*2), ybase);
			printf("_");
		}else {
			for (int j = 0; j < height; ++j)
			{
				gotoxy(x - (i*2), ybase - j);
				printf("%c", 219);
			}
		}
		pointer--;
	}
}

void loadGraph(){
	system("cls");
	for (int m = 0; m < 500; ++m)
	{
		randomDVal[m] = (double) randomVal[m] / 2; 
	}
	int i = 0;
	int j = 0;
	while(1) {
		i = (i >= 100) ? 0 : i;
		j = (j >= 500) ? 0 : j;
		val[i] = randomDVal[j];
		gotoxy(xbase + 3, ybase);
		printf("%1.1f\n", val[i]);
		gotoxy(xbase - 18 , ybase + 3);
		printf("S:9");
		gotoxy(xbase + 3 , ybase + 3);
		printf("%03d",i);
		loadBar(xbase, ybase, i);
		i++;
		j++;
		Sleep(500);
		htc_fieldclr(30,55,20,35);
	}
}


void loadMenu() {
	system("cls");
	char* menus[] = {"Welcome to Graph","Graph","Exit"};
	int a = htc_menumaker(menus, 3 , 20, 20);
	switch(a) {
		case 1:
			loadGraph();
			break;
	}
}

int main() {
	fullscreen();
	loadMenu();
}
 