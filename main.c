#include <gtk/gtk.h>

static void
close_window(GtkButton *add,
             gpointer   data)
{
  GtkWindow *window = GTK_WINDOW(data);

  gtk_widget_destroy(GTK_WIDGET(window));
}

static void
add_book(GtkButton *add_book_button,
         gpointer   user_data)
{
  // create window
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // main widget(s)
  GtkWidget *grid;

  // Label(s)
  GtkWidget *title;
  GtkWidget *author;
  GtkWidget *pages;

  // Entries
  GtkWidget *title_entry;
  GtkWidget *author_entry;
  GtkWidget *pages_entry;

  // Button(s)
  GtkWidget *add_button;

  // Box(s)
  GtkWidget *box;

  gtk_window_set_title(GTK_WINDOW(window), "Add Book");
  gtk_window_set_default_size(GTK_WINDOW(window), 320, 240);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  grid = gtk_grid_new();

  // set grid properties
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

  // create label widget(s)
  title = gtk_label_new("Book Title:");
  gtk_label_set_xalign(GTK_LABEL(title), 0);

  author = gtk_label_new("Book Author:");
  gtk_label_set_xalign(GTK_LABEL(author), 0);

  pages = gtk_label_new("Page Count:");
  gtk_label_set_xalign(GTK_LABEL(pages), 0);

  // create entry widget(s)
  title_entry = gtk_entry_new();
  author_entry = gtk_entry_new();
  pages_entry = gtk_entry_new();

  // create box
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  // attach widget(s) to grid
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(title), 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(author), 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(pages), 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(title_entry), 1, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(author_entry), 1, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(pages_entry), 1, 2, 2, 1);

  // create button widget(s)
  add_button = gtk_button_new_with_label("Add");

  // pack box
  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(grid), FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(add_button), FALSE, FALSE, 0);

  // pack window
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(box));

  // connect buttons
  g_signal_connect(GTK_BUTTON(add_button), "clicked",
                   G_CALLBACK(close_window), window);

  // display window
  gtk_widget_show_all(window);
}

static void
activate(GtkApplication *app,
         gpointer        user_data)
{
  // main widget(s)
  GtkWidget *window;
  GtkWidget *header;

  // header widget(s)
  GtkWidget *stack_switch;
  GtkWidget *book_list;

  // stack widget(s)
  GtkWidget *stack;
  GtkWidget *stack_books_grid;
  GtkWidget *stack_logs_grid;

  // books tab widget(s)
  GtkWidget *add_book_button;
  GtkWidget *book_title;
  GtkWidget *book_author;
  GtkWidget *book_total_pages;

  // stack widget(s)
  stack = gtk_stack_new();

  stack_books_grid = gtk_grid_new();
  stack_logs_grid = gtk_grid_new();

  gtk_stack_add_titled(GTK_STACK(stack), GTK_WIDGET(stack_books_grid), "books-name", "Books");
  gtk_stack_add_titled(GTK_STACK(stack), GTK_WIDGET(stack_logs_grid), "logs-name", "Logs");

  // widget(s) to add to books grid
  add_book_button = gtk_button_new_with_label("Add Book");

  book_title = gtk_label_new("Title:");
  gtk_label_set_xalign(GTK_LABEL(book_title), 0);

  book_author = gtk_label_new("Author:");
  gtk_label_set_xalign(GTK_LABEL(book_author), 0);

  book_total_pages = gtk_label_new("Total Pages:");
  gtk_label_set_xalign(GTK_LABEL(book_total_pages), 0);

  // set grid properties
  gtk_grid_set_row_spacing(GTK_GRID(stack_books_grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(stack_books_grid), 5);

  // pack grid(s)
  gtk_grid_attach(GTK_GRID(stack_books_grid), GTK_WIDGET(book_title), 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(stack_books_grid), GTK_WIDGET(book_author), 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(stack_books_grid), GTK_WIDGET(book_total_pages), 0, 3, 1, 1);

  gtk_grid_attach(GTK_GRID(stack_books_grid), GTK_WIDGET(add_book_button), 0, 4, 1, 1);

  // stack switch widget(s)
  stack_switch = gtk_stack_switcher_new();
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switch), GTK_STACK(stack));

  // create combo box(s)
  book_list = gtk_combo_box_text_new_with_entry();

  // example book(s)
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(book_list), NULL, "Basics of Web Design");

  // header widget(s)
  header = gtk_header_bar_new();

  // set header bar properties
  gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Reading Log");
  gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header), "v0.1");
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);

  // add widget(s) to header bar
  gtk_header_bar_pack_start(GTK_HEADER_BAR(header), GTK_WIDGET(stack_switch));
  gtk_header_bar_pack_end(GTK_HEADER_BAR(header), GTK_WIDGET(book_list));

  // create window widget(s)
  window = gtk_application_window_new(app);

  // set window properties
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_window_set_titlebar(GTK_WINDOW(window), GTK_WIDGET(header));
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  // pack window
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(stack));

  // connect widget(s) to function(s)
  g_signal_connect(GTK_BUTTON(add_book_button), "clicked",
                   G_CALLBACK(add_book), NULL);

  // show widget(s)
  gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.reading-log", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
