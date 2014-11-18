// ***************     Simulador de movimentação do telescópio   ***************
// Auto: Lucas Petto

// A T E N C A O !
        // Pra funcionar o Graphics.h
        // Tem que comecar o projeto como C++
        // Tem que incluir no Project -> Build Options -> Linker Settings:
                // -bgi
                // -gdi32
                // -comdlg32
                // -uuid
                // -oleaut32
                // -ole32

//Funcoes principais da Graphics.h:
//      void line (int x1, int y1, int x2, int y2);
//
//      void linerel (int dx, int dy);
//
//      void lineto (int x, int y);
//
//      void outtext (char *textstring);
//
//      void outtextxy (int x, int y, char *textstring);
//
//      void pieslice (int x, int y, int stangle, int endangle, int radius);
//
//      void putpixel (int x, int y, int color);
//
//      void rectangle (int left, int top, int right, int bottom);
//
//      setcolor(BLUE);             // Change drawing color to BLUE.
//      setcolor(COLOR(255,100,0)); // Change drawing color to reddish-green.
//      void setbkcolor (int color);

//Color Name	Value
    //BLACK 	0
    //BLUE	1
    //GREEN	2
    //CYAN	3
    //RED	4
    //MAGENTA	5
    //BROWN	6
    //LIGHTGRAY	7
    //DARKGRAY	8
    //LIGHTBLUE	9
    //LIGHTGREEN	10
    //LIGHTCYAN	11
    //LIGHTRED	12
    //LIGHTMAGENTA	13
    //YELLOW	14
    //WHITE	15

#include <graphics.h>
#include <stdio.h>  // Printf, sprintf
#include <stdlib.h> // Rand
#include <math.h>
#include <time.h>  // Inicializa a Semente do Rand

#define HALF_PI (1.570796326794897)

void start_window()  // Liga Tela Grafica
{
    initwindow(800,600);                    //open a 800x600 graphics window
    setactivepage(1); setvisualpage(1);     // Liga a Tela 1! A graphics tem 2 Telas!!
    setcolor(WHITE);                          // Define a cor
    setbkcolor(BLACK);    // Seleciona cor de fundo da tela: preta
    cleardevice();        // Limpa tela (deixa toda tela preta)
}

/*Desenhando estrelas aleatoreas no espaço*/
void draw_stars()
{
  int i,x,y;
  
  for(i=0;i<=1000;i++)
  {
    x=rand()%800;
    y=rand()%600;
    putpixel(x,y,15);
  }
}

void draw_circle(int x, int y, int radius, int color){
     setcolor(color);
     circle(x, y, radius);
}

void draw_line(int a, int b, int c, int d, int color){
    setcolor(color);
    line(a, b, c, d); 
}

void draw_ellipse(int a, int b, int c, int d, int e, int f, int color){
    setcolor(color);
    ellipse(a, b, c, d, e, f);
}

void paint_ellipse(int color){
     
     for (int i=0; i< 100;i++)
     draw_ellipse(400 , 590 +i, 0, 180, 400, 70, color);
}

double calculate_R(double hour,double minute,double second){
       double R = 0.0, Rrad = 0.0;
       R = ((second + 60.00*minute + 3600.00*hour)/21600.00)*90.00;
       Rrad = (R * HALF_PI)/90.0;
       
       return Rrad;
}

double calculate_i(double graus,double minute,double second){
       double i = 0.0, irad = 0.0;
       i = 90 - (graus + minute/60 + second/3600);
       irad = (i * HALF_PI)/90.0;
       return irad;
}

double calculate_I(double i){
       double I = 0.0;
       I = sin(i)*300;
       return I;
}

double calculate_dx(double I, double R){
       double dx = 0.0;
       dx = I*cos(HALF_PI-R);
       return dx;
}

double calculate_dy(double I, double R){
       double dy = 0.0;
       dy = I*sin(HALF_PI-R);
       return dy;
}

double calculate_xe(double xp, double dx){
       double xe = 0.0;
       xe = xp + dx;
       return xe;
}

double calculate_ye(double yp, double dy){
       double ye = 0.0;
       ye = yp - dy;
       return ye;
}

int read_file(char fileName[50], float *hour, float *minute, float *second, float *graus, float *minuteDe, float *secondDe){
    FILE *file;
    
    file = fopen(fileName,"r");
    if (file == NULL)
       return 1;
    
    fscanf (file, "%f", &*hour);
    fscanf (file, "%f", &*minute);
    fscanf (file, "%f", &*second);
    fscanf (file, "%f", &*graus);
    fscanf (file, "%f", &*minuteDe);
    fscanf (file, "%f", &*secondDe);
    
    fclose(file);
    return 0;
}

void scenario_initiation(){
    start_window();
    draw_line(0,300,800,300,1);
    draw_stars();
    draw_circle(400,300,5,4);

    paint_ellipse(1);  
    draw_ellipse(400, 590, 0, 180, 400, 70, 6);
    
    settextstyle(10, HORIZ_DIR, 1);
    setcolor(RED);
    outtextxy(385, 310, "PC");
    
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy(385, 490, "S");
}

int main()
{   
    int key;
    
    while (key != 'q'){
        scenario_initiation();
        
        // Hour Angle
        float hour = 0.00, minute = 0.0, second = 0.0;
        // Angle hour declination
        float graus = 0.0, minuteDe = 0.0, secondDe = 0.0;
        
        if (read_file("coordenadas.txt", &hour, &minute, &second, &graus, &minuteDe, &secondDe)){
           settextstyle(10, HORIZ_DIR, 1);
           outtextxy(1, 1, "Ocorreu algum problema na leitura do arquivo de leitura");
           getch();
           return 1;
        }
                
        float R = 0.0, i = 0.0, I = 0.0, dx = 0.0, dy = 0.0, xe = 0.0, ye = 0.0;
           
        // Realizando os calculos
        R = calculate_R (hour, minute, second);
        i = calculate_i(graus, minuteDe, secondDe);
        I = calculate_I(i);
        dx = calculate_dx(I, R);
        dy = calculate_dy(I, R);
        xe = calculate_xe(400, dx);
        ye = calculate_ye(300, dy);
        
        int posX,posY; 
        posX = (int)xe;
        posY = (int)ye;
        
        char input[200];
        setcolor(WHITE);
        sprintf(input, "Coordenadas: H = %.2f Min = %.2f Seg = %.2f Graus = %.2f MinDe = %.2f SegDe = %.2f",hour,minute,second,graus,minuteDe,secondDe);
        settextstyle(3, HORIZ_DIR, 1);
        outtextxy(1, 1, input);
        
        char output[200];
        setcolor(WHITE);
        sprintf(output, "Localizacao R = %.2f   i = %.2f   I = %.2f   dx = %.2f   dy = %.2f   xe = %d   ye = %d",R,i,I,dx,dy,posX,posY);
        settextstyle(3, HORIZ_DIR, 1);
        outtextxy(1, 25, output);
                
        draw_circle(posX,posY,5,4);
        draw_line(400,300,posX,posY,4);
        putpixel(posX,posY,3);
        //  if (kbhit())    // So faz as comparacoes de teclas se uma tecla for realmente precionada para ganhar tempo
        key = getch();
        closegraph();        //close graphics window                                        
    }
    return 0;
}
