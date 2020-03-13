#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

struct Book {
  gchar *title;
  gchar *author;
  gchar *edition;
  gchar *total_pages;

  gchar *start_page;
  gchar *end_page;

  struct Book *next;
};

struct WidgetList {
  GtkWidget *widget;

  struct WidgetList *next;
};

/* forward declaration(s) */
static void save_books(GtkWindow *, gpointer);
static void read_books(gpointer);
static int calc_string_size(char *, int);
void parse_book(char *, gchar *, gchar *, gchar *, gchar *, gchar *, gchar *);

#endif
