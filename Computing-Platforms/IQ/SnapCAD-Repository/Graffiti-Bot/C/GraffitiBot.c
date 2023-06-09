#pragma config(Motor,  motor6,          MotorL,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,         MotorPen,      tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor12,         MotorR,        tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//---------------------------------------------------------------------------------------------------------------------
//  Graffiti.Writer1.c                     (C) Andreas Dreier
//                                             11.05.2016
//                                             andreas@dreier-privat.de
//
//  Program for the GraffitiBot with remote control.
//
//  Motor6   : Left Motor
//  Motor11  : Motor Pen
//  Motor12  : Right Motor
//
//  Remote-Control:
//
//  Left joystick  : Control position on the wall (left/right & update/down)
//  Button L down  : Pen down
//  Button L up    : Pen up
//
//  Right joystick : left/right select the pattern of the selected group
//                   up/down select the group of pattern
//  Button R down  : Decrease the size of the pattern
//  Button R up    : Increase the size of the pattern
//  Button F down  : Draw the selected pattern
//---------------------------------------------------------------------------------------------------------------------

#define WHITE false
#define BLACK true

//---------------------------------------------------------------------------------------------------------------------
//  Define variables for actual position
//---------------------------------------------------------------------------------------------------------------------

int mypos_x;
int mypos_y;


//---------------------------------------------------------------------------------------------------------------------
//  Define the available patterns and groups
//---------------------------------------------------------------------------------------------------------------------

char  dialog_patterns[4][26] =
      {
      	 { ' ','_','+','-','*','/',',',';',':','@','!','?','$','�','%','&','(',')','{','}','[',']','^','~','"','#' },
         { '1','2','3','4','5','6','7','8','9','0', 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
         { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' },
         { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' }
      };

int   dialog_length[4] =
      {
      	 26,10,26,26
      };

int   dialog_select[4] =
      {
      	 0, 0, 0, 0
      };

int   dialog_group = 3;


//---------------------------------------------------------------------------------------------------------------------
//  Move relative to actual position with an offset of dx and dy
//---------------------------------------------------------------------------------------------------------------------

void MoveRel( int dx, int dy )
{
	   moveMotorTarget( MotorL, dx-dy, 30 );
	   moveMotorTarget( MotorR, dx+dy, 30 );

	   waitUntilMotorStop( MotorL );
     waitUntilMotorStop( MotorR );

     mypos_x += dx;
     mypos_y += dy;
}


//---------------------------------------------------------------------------------------------------------------------
//  Move to position x and y
//---------------------------------------------------------------------------------------------------------------------

void plotMoveTo( int x, int y )
{
	   MoveRel( x - mypos_x, y - mypos_y );
}


//---------------------------------------------------------------------------------------------------------------------
//  Move the pen down
//---------------------------------------------------------------------------------------------------------------------

void plotPenDown()
{
	   moveMotorTarget( MotorPen, -300,100 );
	   waitUntilMotorStop( MotorPen );
};


//---------------------------------------------------------------------------------------------------------------------
//  Move pen up
//---------------------------------------------------------------------------------------------------------------------

void plotPenUp()
{
	   moveMotorTarget( MotorPen, 300,100 );
	   waitUntilMotorStop( MotorPen );
};


//---------------------------------------------------------------------------------------------------------------------
//  Include basic functions for pattern management
//---------------------------------------------------------------------------------------------------------------------

#include "GraffitiText.inc"


//---------------------------------------------------------------------------------------------------------------------
//  Display a pattern
//---------------------------------------------------------------------------------------------------------------------

void displayPattern( char ascii, int size, int bx, int by, bool col=WHITE )
{
     int c;
     int x1;
     int x2;
     int y1;
     int y2;
     int z;

     x1=2*size;
     y1=2*size;
     z=0;

     GetPattern( ascii );
          c=0;
          while( c < pattern_length )
          {
          	   x2=x1;
          	   y2=y1;
               switch( pattern[c] )
               {
                  case '1' : while( pattern[c] == '1' )
                             {
                                    x2=x2-size;
                                    y2=y2-size;
                                    c++;
                             }
                             break;

                  case '2' : while( pattern[c] == '2' )
                             {
                                    y2=y2-size;
                                    c++;
                             }
                             break;

                  case '3' : while( pattern[c] == '3' )
                             {
                                    x2=x2+size;
                                    y2=y2-size;
                                    c++;
                             }
                             break;

                  case '4' : while( pattern[c] == '4' )
                             {
                                    x2=x2-size;
                                    c++;
                             }
                             break;

                  case '6' : while( pattern[c] == '6' )
                             {
                                    x2=x2+size;
                                    c++;
                             }
                             break;

                  case '7' : while( pattern[c] == '7' )
                             {
                                    x2=x2-size;
                                    y2=y2+size;
                                    c++;
                             }
                             break;

                  case '8' : while( pattern[c] == '8' )
                             {
                                    y2=y2+size;
                                    c++;
                             }
                             break;

                  case '9' : while( pattern[c] == '9' )
                             {
                                    x2=x2+size;
                                    y2=y2+size;
                                    c++;
                             }
                             break;

                  case 'U' : z=0;
                             c++;
                             break;

                  case 'D' : z=1;
                             c++;
                             break;

                  default  : c++;
               }

               if( z )
               {
                   if( col == BLACK )
                   {
                      drawLine(bx+y1,  by+size*10-7-x1,  bx+y2,  by+size*10-7-x2  );
                      drawLine(bx+y1-1,by+size*10-7-x1,  bx+y2-1,by+size*10-7-x2  );
                      drawLine(bx+y1,  by+size*10-7-x1-1,bx+y2,  by+size*10-7-x2-1);
                      drawLine(bx+y1+1,by+size*10-7-x1,  bx+y2+1,by+size*10-7-x2  );
                      drawLine(bx+y1,  by+size*10-7-x1+1,bx+y2,  by+size*10-7-x2+1);
                   }
                   else
                   {
                      eraseLine(bx+y1,  by+size*10-7-x1,  bx+y2,  by+size*10-7-x2  );
                      eraseLine(bx+y1-1,by+size*10-7-x1,  bx+y2-1,by+size*10-7-x2  );
                      eraseLine(bx+y1,  by+size*10-7-x1-1,bx+y2,  by+size*10-7-x2-1);
                      eraseLine(bx+y1+1,by+size*10-7-x1,  bx+y2+1,by+size*10-7-x2  );
                      eraseLine(bx+y1,  by+size*10-7-x1+1,bx+y2,  by+size*10-7-x2+1);
                   }
               }

               x1=x2;
               y1=y2;
          }

}

//---------------------------------------------------------------------------------------------------------------------
//  Initialize the GraffitiBot
//---------------------------------------------------------------------------------------------------------------------

void GrafittiBotInitialize()
{
	   plotPenUp();

	   eraseDisplay();

	   setMotorSpeed( MotorL, 0 );
	   setMotorSpeed( MotorR, 0 );

	   resetMotorEncoder( MotorL );
	   resetMotorEncoder( MotorR );

	   mypos_x = 0;
	   mypos_y = 0;


	   // Show user dialog context

     eraseDisplay();
     fillRect( 111,0,127,39 );
     displayPattern( 'A', 2, 109,27 );
     displayPattern( 'B', 2, 109,14 );
     displayPattern( 'C', 2, 109, 1 );

     fillRect( 93,0,109,39 );
     displayPattern( 'a', 2, 91,27 );
     displayPattern( 'b', 2, 91,14 );
     displayPattern( 'c', 2, 91, 1 );

     fillRect( 75,0,91,39 );
     displayPattern( '1', 2, 73,27 );
     displayPattern( '2', 2, 73,14 );
     displayPattern( '3', 2, 73, 1 );

     fillRect( 57,0,73,39 );
     displayPattern( ' ', 2, 55,27 );
     displayPattern( '_', 2, 55,14 );
     displayPattern( '+', 2, 55, 1 );
}

//---------------------------------------------------------------------------------------------------------------------
//  Main program
//---------------------------------------------------------------------------------------------------------------------

task main()
{
	   int    ascii;
	   char   ascii_text[2]    = { 0,0 };
	   string plot_ascii       = "_";
	   int    ascii_size       = 10;
	   int    control_pattern;
	   int    control_group;
	   int    control_xpos;
	   int    control_ypos;
	   bool   update_pattern = true;
	   bool   update_size    = true;
	   bool   update_group   = true;

     GrafittiBotInitialize();

     while( 1 )
     {
          //---------------------------------------------------------------------------
          // Direcdt control position

          control_ypos = vexRT[ ChA ];
	        control_xpos = vexRT[ ChB ];

	        if( control_ypos >  50 ) control_ypos =  50;
	        if( control_ypos < -50 ) control_ypos = -50;
	        if( control_xpos >  50 ) control_xpos =  50;
	        if( control_xpos < -50 ) control_xpos = -50;

	        setMotorSpeed( MotorL, control_xpos - control_ypos );
	        setMotorSpeed( MotorR, control_xpos + control_ypos );

          //---------------------------------------------------------------------------
	        // Direcdt control pen

	        if( vexRT( BtnLDown ) ) plotPenDown();
	        if( vexRT( BtnLUp   ) ) plotPenUp();

          //---------------------------------------------------------------------------
	        // Control size of pattern

	        if( vexRT( BtnRDown ) )
	        {
	        	  if( ascii_size > 5 )
	        	  	  ascii_size = ascii_size - 5;

	        	  update_size = true;
	        }

	        if( vexRT( BtnRUp ) )
	        {
	         	  if( ascii_size < 45 )
	        	  	  ascii_size = ascii_size + 5;

	        	  update_size = true;
	        }

          //---------------------------------------------------------------------------
	        // Control group of patterns

          control_group   = vexRT[ ChD ];

          if( control_group > 30 )
          {
          	  if( dialog_group < 3 )
          	  	  dialog_group++;
          	  else
          	  	  dialog_group=0;

          	  update_group = true;
          	  update_pattern = true;
          }

          if( control_group < -30 )
          {
          	  if( dialog_group > 0 )
          	  	  dialog_group--;
          	  else
          	  	  dialog_group=3;

          	  update_group = true;
          	  update_pattern = true;
          }

          //---------------------------------------------------------------------------
          // Control pattern selection

          control_pattern = vexRT[ ChC ];

          if( control_pattern < -30 )
          {
          	  if( dialog_select[ dialog_group ] > 0 )
          	  	  dialog_select[ dialog_group ]--;
          	  else
          	  	  dialog_select[ dialog_group ] = dialog_length[ dialog_group ]-1;

          	  update_pattern = true;
          }

          if( control_pattern > 30 )
          {
              if( dialog_select[ dialog_group ] < dialog_length[ dialog_group ]-1 )
              	  dialog_select[ dialog_group ]++;
              else
              	  dialog_select[ dialog_group ] = 0;

              update_pattern = true;
          }

          //---------------------------------------------------------------------------
          // update screen for selection group

          if( update_group )
          {
          	  eraseRect( 56,44, 127,43 );
          	  eraseRect( 56,42, 127,41 );
          	  fillRect( 57+18*dialog_group,44, 73+18*dialog_group,41 );
          	  update_group = false;

          	  sleep( 200 );
          }

          //---------------------------------------------------------------------------
          // update screen for seleciton size

          if( update_size )
          {
              eraseRect( 52,0,54,47 );
              fillRect( 52,47,54,47-ascii_size );
              update_size = false;

              sleep( 200 );
          }

          //---------------------------------------------------------------------------
          // update screen for selection pattern

          if( update_pattern )
          {
              ascii = dialog_patterns[ dialog_group ][ dialog_select[dialog_group] ];
              ascii_text[0] = ascii;
              stringFromChars( plot_ascii,ascii_text );

              fillRect(0,0,50,47 );
              displayPattern( ascii,5,0,0 );
              update_pattern = false;

              sleep( 200 );
          }

          //---------------------------------------------------------------------------
          // Plot the selected pattern in given size

          if( vexRT( BtnFDown ) )
	            plotText( mypos_x, mypos_y, ascii_size,FONT_DIRECTION_LR, plot_ascii );

          //---------------------------------------------------------------------------
	        // Short sleep

          sleep( 20 );
     }

}

//---------------------------------------------------------------------------------------------------------------------
//  Graffiti.Writer1.c --- End of program
//---------------------------------------------------------------------------------------------------------------------
