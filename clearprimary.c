// This was initially taken from:
// https://github.com/bstpierre/gtk-examples/blob/master/c/clipboard_watch.c

#include <gdk/gdk.h>
#include <gtk/gtk.h>

// This callback is invoked when the clipboard owner changes.
void handle_owner_change(GtkClipboard *clipboard,
                         GdkEvent *event,
                         gpointer data)
{
    // Avoid 'unused arg' warnings.
    (void)event;
    (void)data;

    // Get the selected text from the clipboard; note that we could
    // get back NULL if the clipboard is empty or does not contain
    // text.
    char* text = gtk_clipboard_wait_for_text(clipboard);
    if(text != NULL && strlen(text) != 0)
    {
        gtk_clipboard_set_text(clipboard, "", 0);
    }
}

int main(int argc, char** argv)
{
    gdk_set_allowed_backends("x11");

    // Standard boilerplate: initialize the toolkit.
    gtk_init(&argc, &argv);

    // Get a handle to the given clipboard. You can also ask for
    // GDK_SELECTION_PRIMARY (the X "primary selection") or
    // GDK_SELECTION_SECONDARY.
    GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);

    gtk_clipboard_set_text(clipboard, "", 0);

    // Connect to the "owner-change" signal which means that ownership
    // of the X clipboard has changed.
    g_signal_connect(clipboard, "owner-change",
                     G_CALLBACK(handle_owner_change), NULL);

    // Run the GTK main loop so that we get the owner-change signal
    // until the user kills the program (^C).
    gtk_main();

    return 0;
}
