/* 
	gcc `pkg-config gtk+-3.0 --cflags` wallpaperSelect.c -O2 -s -o wallpaperSelect `pkg-config gtk+-3.0 --libs`
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	
	GtkWidget *fileDialog = gtk_file_chooser_dialog_new(
		"Open Wallpaper",
		NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
		"Cancel", GTK_RESPONSE_CANCEL,
		"Open", GTK_RESPONSE_OK,
		NULL
	);
	
	GtkWidget *tileDialog = gtk_message_dialog_new(
		NULL,
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_QUESTION,
		GTK_BUTTONS_YES_NO,
		"Do you want the wallpaper to be tiled?"
	);
	
	if (gtk_dialog_run(GTK_DIALOG(fileDialog)) == GTK_RESPONSE_OK) {
		char *fehFlag;
		char *fehBackground = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileDialog));
		char command[255];
		
		if (gtk_dialog_run(GTK_DIALOG(tileDialog)) == GTK_RESPONSE_YES) {
			fehFlag = "bg-tile";
		} else {
			fehFlag = "bg-fill";
		}
		
		sprintf(command, "feh --%s \"%s\"\n", fehFlag, fehBackground);
		
		system(command);
		return 0;
	}
	return 1;
}