#ifndef MAIN_H
#define MAIN_H

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

#endif
