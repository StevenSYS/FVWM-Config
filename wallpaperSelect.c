#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
	char *fehFlag = "bg-fill";
	char *fehBackground;
	char command[255];
	
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
	
	if (gtk_dialog_run(GTK_DIALOG(fileDialog)) != GTK_RESPONSE_OK) {
		return 1;
	}
	
	fehBackground = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileDialog));
	
	if (gtk_dialog_run(GTK_DIALOG(tileDialog)) == GTK_RESPONSE_YES) {
		fehFlag = "bg-tile";
	}
	
	sprintf(command, "feh --%s \"%s\"\n", fehFlag, fehBackground);
	system(command);
	return 0;
}