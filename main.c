#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "main.h"

struct Book *start = NULL;
bool loaded = false;

struct Book *
get_book(const gchar *book_name)
{
  struct Book *curr_book = start;

  while(curr_book != NULL) {
    if(strcmp(curr_book->title, book_name) == 0) {
      return curr_book;
    }

    curr_book = curr_book->next;
  }

  return NULL;
}

static void
select_book(GtkComboBoxText *combo,
            gpointer         user_data)
{
  GtkComboBoxText *curr_box = combo;
  struct WidgetList *data = (struct WidgetList *) user_data;

  GtkEntry *title_entry = GTK_ENTRY(data->widget);
  GtkEntry *author_entry = GTK_ENTRY(data->next->widget);
  GtkEntry *edition_entry = GTK_ENTRY(data->next->next->widget);
  GtkEntry *pages_entry = GTK_ENTRY(data->next->next->next->widget);

  const gchar *selection = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(curr_box));

  struct Book *book = get_book(selection);

  gtk_entry_set_text(GTK_ENTRY(title_entry), book->title);
  gtk_entry_set_text(GTK_ENTRY(author_entry), book->author);
  gtk_entry_set_text(GTK_ENTRY(edition_entry), book->edition);
  gtk_entry_set_text(GTK_ENTRY(pages_entry), book->total_pages);
}

static void
confirm_book(GtkButton *add,
             gpointer   data)
{
  struct WidgetList *curr_entry;
  GtkWindow *window;
  const char *title, *author, *pages, *edition;
  GtkComboBoxText *combo;

  // set values
  curr_entry = data;

  combo = GTK_COMBO_BOX_TEXT(curr_entry->widget);
  title = gtk_entry_get_text(GTK_ENTRY(curr_entry->next->widget));
  author = gtk_entry_get_text(GTK_ENTRY(curr_entry->next->next->widget));
  edition = gtk_entry_get_text(GTK_ENTRY(curr_entry->next->next->next->widget));
  pages = gtk_entry_get_text(GTK_ENTRY(curr_entry->next->next->next->next->widget));
  window = GTK_WINDOW(curr_entry->next->next->next->next->next->widget);

  struct Book *new_book = (struct Book *) malloc(sizeof(struct Book));

  new_book->title = (gchar *) malloc((sizeof(gchar) * strlen(title)) + 1);
  new_book->author = (gchar *) malloc((sizeof(gchar) * strlen(author)) + 1);
  new_book->edition = (gchar *) malloc((sizeof(gchar) * strlen(edition)) + 1);
  new_book->total_pages = (gchar *) malloc((sizeof(gchar) * strlen(pages)) + 1);

  // copy data to new book
  strcpy(new_book->title, title);
  strcpy(new_book->author, author);
  strcpy(new_book->edition, edition);
  strcpy(new_book->total_pages, pages);

  // default(s)
  new_book->start_page = "0";
  new_book->end_page = "0";
  new_book->next = NULL;

  // add to book list
  if(start == NULL) {
    printf("Set Head\n");
    start = new_book;
  }
  else {
    printf("Appended Tail\n");
    struct Book *curr_book = start;

    while(curr_book->next != NULL) {
      curr_book = curr_book->next;
    }

    curr_book->next = new_book;
  }

  // update combo box
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, new_book->title);

  // destroy window
  gtk_widget_destroy(GTK_WIDGET(window));
}

static void
add_book(GtkButton *add_book_button,
         gpointer   data)
{
  // parameter widget(s)
  GtkWidget *combo = data;

  // create window
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // main widget(s)
  GtkWidget *grid;

  // Label(s)
  GtkWidget *title;
  GtkWidget *author;
  GtkWidget *edition;
  GtkWidget *pages;

  // Entries
  struct WidgetList *widgets;
  GtkWidget *title_entry;
  GtkWidget *author_entry;
  GtkWidget *edition_entry;
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

  edition = gtk_label_new("Book Edition:");
  gtk_label_set_xalign(GTK_LABEL(edition), 0);

  pages = gtk_label_new("Page Count:");
  gtk_label_set_xalign(GTK_LABEL(pages), 0);

  // create entry widget(s)
  widgets = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  widgets->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  widgets->next->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  widgets->next->next->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  widgets->next->next->next->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  widgets->next->next->next->next->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));

  title_entry = gtk_entry_new();
  author_entry = gtk_entry_new();
  edition_entry = gtk_entry_new();
  pages_entry = gtk_entry_new();

  // create widget list
  widgets->widget = combo;
  widgets->next->widget = title_entry;
  widgets->next->next->widget = author_entry;
  widgets->next->next->next->widget = edition_entry;
  widgets->next->next->next->next->widget = pages_entry;
  widgets->next->next->next->next->next->widget = window;

  // create box
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  // attach widget(s) to grid
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(title), 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(author), 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(edition), 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(pages), 0, 3, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(title_entry), 1, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(author_entry), 1, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(edition_entry), 1, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(pages_entry), 1, 3, 2, 1);

  // create button widget(s)
  add_button = gtk_button_new_with_label("Add");

  // pack box
  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(grid), FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(add_button), FALSE, FALSE, 0);

  // pack window
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(box));

  // connect buttons
  g_signal_connect(GTK_BUTTON(add_button), "clicked",
                   G_CALLBACK(confirm_book), widgets);

  // display window
  gtk_widget_show_all(window);
}

static void
activate(GtkApplication *app,
         gpointer        data)
{
  // main widget(s)
  GtkWidget *window;
  GtkWidget *header;

  // header widget(s)
  GtkWidget *stack_switch;
  GtkWidget *book_list;

  // stack widget(s)
  GtkWidget *stack;
  GtkWidget *stack_books_box;

  GtkWidget *book_info_box;
  GtkWidget *book_labels_box;
  GtkWidget *book_entries_box;
  GtkWidget *stack_logs_box;

  // books tab widget(s)
  GtkWidget *add_book_button;
  GtkWidget *book_title;
  GtkWidget *book_author;
  GtkWidget *book_edition;
  GtkWidget *book_pages;

  struct WidgetList *book_info_entry;

  GtkWidget *book_title_entry;
  GtkWidget *book_author_entry;
  GtkWidget *book_edition_entry;
  GtkWidget *book_pages_entry;

  // stack widget(s)
  stack = gtk_stack_new();

  stack_books_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  stack_logs_box = gtk_grid_new();

  gtk_stack_add_titled(GTK_STACK(stack), GTK_WIDGET(stack_books_box), "books-name", "Books");
  gtk_stack_add_titled(GTK_STACK(stack), GTK_WIDGET(stack_logs_box), "logs-name", "Logs");

  // widget(s) to add to books box
  book_info_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  book_labels_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  book_entries_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  add_book_button = gtk_button_new_with_label("Add Book");

  book_title = gtk_label_new("Title:");
  gtk_label_set_xalign(GTK_LABEL(book_title), 0);

  book_author = gtk_label_new("Author:");
  gtk_label_set_xalign(GTK_LABEL(book_author), 0);

  book_edition = gtk_label_new("Edition:");
  gtk_label_set_xalign(GTK_LABEL(book_edition), 0);

  book_pages = gtk_label_new("Total Pages:");
  gtk_label_set_xalign(GTK_LABEL(book_pages), 0);

  book_title_entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(book_title_entry), FALSE);

  book_author_entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(book_author_entry), FALSE);

  book_edition_entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(book_edition_entry), FALSE);

  book_pages_entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(book_pages_entry), FALSE);

  book_info_entry = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  book_info_entry->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  book_info_entry->next->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));
  book_info_entry->next->next->next = (struct WidgetList *) malloc(sizeof(struct WidgetList));

  book_info_entry->widget = book_title_entry;
  book_info_entry->next->widget = book_author_entry;
  book_info_entry->next->next->widget = book_edition_entry;
  book_info_entry->next->next->next->widget = book_pages_entry;

  // pack labels box
  gtk_box_pack_start(GTK_BOX(book_labels_box), GTK_WIDGET(book_title), TRUE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(book_labels_box), GTK_WIDGET(book_author), TRUE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(book_labels_box), GTK_WIDGET(book_edition), TRUE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(book_labels_box), GTK_WIDGET(book_pages), TRUE, FALSE, 0);

  // pack entries box
  gtk_box_pack_start(GTK_BOX(book_entries_box), GTK_WIDGET(book_title_entry), TRUE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(book_entries_box), GTK_WIDGET(book_author_entry), TRUE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(book_entries_box), GTK_WIDGET(book_edition_entry), TRUE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(book_entries_box), GTK_WIDGET(book_pages_entry), TRUE, FALSE, 0);

  // pack info box
  gtk_box_pack_start(GTK_BOX(book_info_box), GTK_WIDGET(book_labels_box), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(book_info_box), GTK_WIDGET(book_entries_box), TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(stack_books_box), GTK_WIDGET(book_info_box), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(stack_books_box), GTK_WIDGET(add_book_button), FALSE, FALSE, 0);

  // stack switch widget(s)
  stack_switch = gtk_stack_switcher_new();
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switch), GTK_STACK(stack));

  // create combo box(s)
  book_list = gtk_combo_box_text_new_with_entry();

  // combo box property(s)
  //   gtk_combo_box_set_popup_fixed_width(GTK_COMBO_BOX(book_list), TRUE);

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
                   G_CALLBACK(add_book), book_list);
  g_signal_connect(GTK_COMBO_BOX_TEXT(book_list), "changed",
                   G_CALLBACK(select_book), book_info_entry);

  // end task(s)
  g_signal_connect(GTK_WINDOW(window), "delete_event", G_CALLBACK(save_books), NULL);

  // startup task(s)
  read_books(GTK_COMBO_BOX_TEXT(book_list));

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

static void
save_books(GtkWindow *window,
           gpointer   data)
{
  struct Book *curr_book = start;

  if(curr_book != NULL) {
    // create file
    FILE *output_file;

    // open file
    if((output_file = fopen("book-list.txt", "w")) == NULL) {
      fprintf(stderr, "Unable to open '%s'\n", "book-list.txt");
      exit(1);
    }

    // write data to file
    while(curr_book != NULL) {
      // write book information
      fprintf(output_file, "%s", curr_book->title);
      fprintf(output_file, "#"); // delimeter

      fprintf(output_file, "%s", curr_book->author);
      fprintf(output_file, "#");

      fprintf(output_file, "%s", curr_book->edition);
      fprintf(output_file, "#");

      fprintf(output_file, "%s", curr_book->total_pages);
      fprintf(output_file, "#");

      fprintf(output_file, "%s", curr_book->start_page);
      fprintf(output_file, "#");

      fprintf(output_file, "%s", curr_book->end_page);
      fprintf(output_file, "#");

      // end of book information
      fprintf(output_file, "##\n");

      // next book
      curr_book = curr_book->next;
    }

    // close file
    fclose(output_file);
  }
}

static void
read_books(gpointer data) {

  if(!loaded) {
    loaded = true;

    GtkComboBoxText *combo;
    combo = GTK_COMBO_BOX_TEXT(data);

    // create file
    FILE *input_file;

    // open file
    if((input_file = fopen("book-list.txt", "r")) == NULL) {
      fprintf(stderr, "Unable to open '%s'.\n", "book-list.txt");
      exit(2);
    }

    // read data into buffer
    char character, *buffer;
    int i;

    do {
      // new buffer to allocate
      buffer = (char *) malloc(sizeof(char) * 250);
      i = 0;

      do {
        // read character
        character = getc(input_file);

        if(character == '\n') {
          // append null character to buffer
          *(buffer + i) = '\0';
        }
        else {
          // append character to buffer
          *(buffer + i) = character;
        }

        // test for line completed
        if(*(buffer + i) == '\0') {
          // create Book with information within line

          struct Book *new_book = (struct Book *) malloc(sizeof(struct Book));

          // allocate variable memory
          new_book->title = (gchar *) malloc(sizeof(gchar) * calc_string_size(buffer, 1));
          new_book->author = (gchar *) malloc(sizeof(gchar) * calc_string_size(buffer, 2));
          new_book->edition = (gchar *) malloc(sizeof(gchar) * calc_string_size(buffer, 3));
          new_book->total_pages = (gchar *) malloc(sizeof(gchar) * calc_string_size(buffer, 4));
          new_book->start_page = (gchar *) malloc(sizeof(gchar) * calc_string_size(buffer, 5));
          new_book->end_page = (gchar *) malloc(sizeof(gchar) * calc_string_size(buffer, 6));

          new_book->next = NULL;

          parse_book(buffer, new_book->title, new_book->author, new_book->edition,
                     new_book->total_pages, new_book->start_page, new_book->end_page);

          // append Book to List
          if(start == NULL) {
            start = new_book;
          }
          else {
            struct Book *temp_book = start;

            while(temp_book->next != NULL) {
              temp_book = temp_book->next;
            }

            temp_book->next = new_book;
          }

          // append to combobox
          gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, new_book->title);
        }

        // move to next character
        ++i;
      }
      while(character != '\n' && character != EOF);

      // free current buffer
      free(buffer);
    }
    while(character != EOF);

    // close file
    fclose(input_file);
  }
}

static int
calc_string_size(char *buffer, int hash)
{
  int size = 0;
  int hash_count = 0;
  char character;
  int i = 0;

  do {
    character = *(buffer + i);

    if(character == '#') {
      ++hash_count;
    }
    else if(hash_count == (hash - 1)) {
      ++size;
    }

    ++i;
  }
  while(hash_count < hash);

  return size + 1;
}

void parse_book(char *buffer, gchar *title, gchar *author, gchar *edition,
                gchar *total_pages, gchar *start, gchar *end)
{
  char character;
  int i = 0, ii = 0, iii = 0, iv = 0, v = 0, vi = 0, vii = 0;
  int delimeter_count = 0;

  do {
    character = *(buffer + i);

    if(character == '#') {
      ++delimeter_count;
    }

    switch(delimeter_count) {
    case 0: {
      // reading book title
      if(character != '#') {
        *(title + ii) = character;
        ++ii;
      }
    }
      break;
    case 1: {
      // reading book author
      if(character != '#') {
        *(author + iii) = character;
        ++iii;
      }
    }
      break;
    case 2: {
      // reading book edition
      if(character != '#') {
        *(edition + iv) = character;
        ++iv;
      }
    }
      break;
    case 3: {
      // reading book page count
      if(character != '#') {
        *(total_pages + v) = character;
        ++v;
      }
    }
      break;
    case 4: {
      // reading book start
      if(character != '#') {
        *(start + vi) = character;
        ++vi;
      }
    }
      break;
    case 5: {
      if(character != '#') {
        *(end + vii) = character;
        ++vii;
      }
    }
      break;
    }

    // increment to next character in buffer
    ++i;
  }
  while(character != '\0');

  // append null character(s)
  *(title + ii) = '\0';
  *(author + iii) = '\0';
  *(edition + iv) = '\0';
  *(total_pages + v) = '\0';
  *(start + vi) = '\0';
  *(end + vii) = '\0';
}
