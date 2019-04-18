#include <kipr/botball.h>
void lift();
void forward();
//void open();

int right_servo=1539;				//servo 0 open 1539
int left_servo=403;					//servo 1 open 403
int rise=129;						//servo 3 down 129



int main()
{
    int iteration_count = 0;			// copy camera code from botball docs
    int update_errors = 0; 
    int see_fire = 2;
    create_connect();

    set_servo_position(0,right_servo); 				 //set servo to open position
    set_servo_position(1,left_servo);
    set_servo_position(3,134);
    enable_servos();

    create_drive_direct(200,200);
    msleep(2500);									//drive out of the starting box and stop to reset GCD
    create_stop();

    while((analog(1)<=3500)||(analog(0)<=3400))		//analog 0: white <250 black >3450
    {     						 					//analog 1: white <250 black >3600
        if((analog(1)>=3500)&&(analog(0)<=3400))	//localize
        {create_drive_direct(0,30);}

        else if ((analog(0)>=3400)&&(analog(1)<=3500))

        {create_drive_direct(30,0);}
        else

        { create_drive_direct(200,200);}
    }
    create_stop();

    set_create_distance(0);
    while(get_create_distance() <= 190) 				//pivot about left motor 200 mm
    {
        create_drive_direct(0,70);
    }
    set_create_distance(0);
    create_stop();

    while((analog(1)<=3500)||(analog(0)<=3400))		//analog 0: white <250 black >3450
    {     											//analog 1: white <250 black >3600
        if((analog(1)>=3500)&&(analog(0)<=3400))
        {create_drive_direct(-30,30);}
        else if ((analog(0)>=3400)&&(analog(1)<=3500))
        {create_drive_direct(30,-30);}
        else
        {create_drive_direct(50,50);}
    }
    create_stop();
    create_drive_direct(0,100);
    msleep(750);

    while(analog(0)<=3400)

    {create_drive_direct(0,100);}

    create_stop();
    create_drive_direct(50,50);
    msleep(1000);
    create_stop();

    while(right_servo>191||left_servo<1751)			//while right servo is less than int,while left more than 403

    {set_servo_position(0,right_servo);			//set position to closed value same for left
     set_servo_position(1,left_servo);
     msleep(30);									// timeframe for function
     left_servo=left_servo+20;					// value=value+value, if value does'nt = value +value, add value
     right_servo=right_servo-20;}				// closes servo at a value of 100 each time

    lift();
    forward();

    while(right_servo>191||left_servo<1751)		//while right servo is less than int,while left more than 403
    {
        set_servo_position(0,right_servo);		//set position to closed value same for left
        set_servo_position(1,left_servo);
        msleep(30);								// timeframe for function
        left_servo=left_servo+20;				// value=value+value, if value does'nt = value +value, add value
        right_servo=right_servo-20;				// closes servo at a value of 100 each time
    }

    lift();
    forward();

    while(get_create_distance()<360)			//drive forward a little bit to get over the bump in the middle
    {
        if(analog(0)>3000)
        {
            create_drive_direct(80,40);
        }

        else
        {
            create_drive_direct(40,80);  
        }

    }
    create_stop();


    while(right_servo>191||left_servo<1751)		//while right servo is less than int,while left more than 403
    {
        set_servo_position(0,right_servo);		//set position to closed value same for left
        set_servo_position(1,left_servo);
        msleep(30);								// timeframe for function
        left_servo=left_servo+20;				// value=value+value, if value does'nt = value +value, add value
        right_servo=right_servo-20;				// closes servo at a value of 100 each time
    }

    lift();
    forward();

    while(right_servo>191||left_servo<1751)		//while right servo is less than int,while left more than 403
    {
        set_servo_position(0,right_servo);		//set position to closed value same for left
        set_servo_position(1,left_servo);
        msleep(30);								// timeframe for function
        left_servo=left_servo+20;				// value=value+value, if value does'nt = value +value, add value
        right_servo=right_servo-20;				// closes servo at a value of 100 each time
    }
    lift();

    while(analog(1)<=3000)						//linefollow until the left servo sees black which means it has reached the end of the black and silver tape			
    {
        if(analog(0)>3000)
        {
            create_drive_direct(80,40);
        }

        else
        {
            create_drive_direct(40,80);  
        }

    }
    create_stop();

    camera_open_black(); 
    msleep(2000);
    						//activate camera to see if the building is on fire
    while (see_fire == 2) 
    {
        if(!camera_update()) 
        {
            update_errors++;
            continue; 
        }
        if (iteration_count > 1000) 		//code copied from botball slides
        {
            iteration_count = 0; 
            camera_close(); 
            camera_open_black();
        }

        if (get_object_count(0) >0)
        {
            see_fire = 1;					// variable named see _fire is 1 if the building in front of the robot is on fire
            printf("fire!\n");
        }
        else 
        {
            see_fire = 0;	
            printf("all clear!\n");
        }
        iteration_count++;
    } 
    camera_close(); 



    if (see_fire == 0)						// if fire isnt in front, see_fire is 0
    {
        while(rise<896)
        {
            set_servo_position(3,rise);			//lift servo slowly before driving forward and placing cubes

            msleep(30);
            rise = rise + 30;
        }											//get_create_rbump();
        while(get_create_rbump()==0&&get_create_lbump()==0)
        {
            create_drive_direct(50,50);
        }
        create_stop();

        set_create_distance(0);
        while(get_create_distance()>=-60)
        { create_drive_direct(-50,-50); }							// back up after bumping burning building 
        create_stop();

        while(right_servo<800||left_servo>1000)
        {
            set_servo_position(1,left_servo);
            set_servo_position(0,right_servo); 						// slowly open servos halfway to dump the cubes
            msleep(30);
            right_servo = right_servo+10;
            left_servo = left_servo-10;
        }
        set_create_distance(0);
        while(get_create_distance()<=30)
        {  create_drive_direct(60,60);}
        create_stop();
    }

    else															// if there was a fire in front, go to the other building
    {
        while(analog(0)>=2900)
        {
            create_drive_direct(70,0);
        }
        create_stop();
        while(rise<896)
        {
            set_servo_position(3,rise);			//lift servo slowly before driving forward and placing cubes

            msleep(30);
            rise = rise + 30;
        }						
        while(get_create_rbump()==0&&get_create_lbump()==0)
        {
            create_drive_direct(50,50);
        }
        create_stop();

        set_create_distance(0);
        while(get_create_distance()>=-60)
        { create_drive_direct(-50,-50); }							// back up after bumping burning building 
        create_stop();

        while(right_servo<800||left_servo>1000)
        {
            set_servo_position(1,left_servo);
            set_servo_position(0,right_servo); 						// slowly open servos halfway to dump the cubes
            msleep(30);
            right_servo = right_servo+10;
            left_servo = left_servo-10;
        }
    }

    disable_servos();

    create_disconnect();

    return 0;
}




void lift()
{
    int up_servo= 129;
    while(up_servo<1243)
    {
        set_servo_position(3,up_servo);			//lift servo slowly
        msleep(30);
        up_servo = up_servo + 30;
    }
    while(up_servo>129)
    {
        set_servo_position(3,up_servo);
        msleep(30);
        up_servo = up_servo - 30;				//lower servo slowly 
    }
}


void forward()
{
    set_create_distance(0);
    while(get_create_distance()<210)
    {
        if(analog(0)>3000)
        {
            create_drive_direct(80,40);
        }

        else
        {
            create_drive_direct(40,80);  
        }

    }
    create_stop();

    while(right_servo<800||left_servo>1000)
    {
        set_servo_position(1,left_servo);
        set_servo_position(0,right_servo); 						// slowly open servos halfway
        msleep(30);
        right_servo = right_servo+20;
        left_servo = left_servo-20;
    }
    while(get_create_distance()<330)
    {
        if(analog(0)>3000)
        {
            create_drive_direct(80,40);
        }

        else
        {
            create_drive_direct(40,80);  
        }

    }
    create_stop();

}





