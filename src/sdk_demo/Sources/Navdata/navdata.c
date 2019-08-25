#include <ardrone_tool/Navdata/ardrone_navdata_client.h>

#include <Navdata/navdata.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define OUT_FIFO "/tmp/drone_pub_fifo"

int fd, fd_client, bytes_read, i;
char buf [4096];
char buf2 [128];

/* Initialization local variables before event loop  */
inline C_RESULT demo_navdata_client_init( void* data )
{

	return C_OK;
}

/* Receving navdata during the event loop */
inline C_RESULT demo_navdata_client_process( const navdata_unpacked_t* const navdata )
{
	vp_os_memset (buf, '\0', sizeof (buf));
	const navdata_demo_t*nd = &navdata->navdata_demo;

	sprintf(buf, "=====================\nNavdata for flight demonstrations =====================\n\n");
	strcat(buf, buf2);
	sprintf(buf, "Control state : %i\n",nd->ctrl_state);
	strcat(buf, buf2);	
	sprintf(buf, "Battery level : %i mV\n",nd->vbat_flying_percentage);
	strcat(buf, buf2);
	sprintf(buf, "Orientation   : [Theta] %4.3f  [Phi] %4.3f  [Psi] %4.3f\n",nd->theta,nd->phi,nd->psi);
	strcat(buf, buf2);
	sprintf(buf, "Altitude      : %i\n",nd->altitude);
	strcat(buf, buf2);
	sprintf(buf, "Speed         : [vX] %4.3f  [vY] %4.3f  [vZPsi] %4.3f\n",nd->theta,nd->phi,nd->psi);
	strcat(buf, buf2);

	sleep(2);

     if ((fd_client = open (OUT_FIFO, O_WRONLY)) == -1) {
         perror ("open: client fifo");
     }

     if (write (fd, buf, strlen (buf)) != strlen (buf))
         perror ("write");

     if (close (fd) == -1)
         perror ("close");

	return C_OK;
}

/* Relinquish the local resources after the event loop exit */
inline C_RESULT demo_navdata_client_release( void )
{
  return C_OK;
}

/* Registering to navdata client */
BEGIN_NAVDATA_HANDLER_TABLE
  NAVDATA_HANDLER_TABLE_ENTRY(demo_navdata_client_init, demo_navdata_client_process, demo_navdata_client_release, NULL)
END_NAVDATA_HANDLER_TABLE

