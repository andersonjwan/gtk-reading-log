#ifndef MAIN_H
#define MAIN_H

struct Book {
  const gchar *title;
  const gchar *author;
  const gint total_pages;

  gint start_page;
  gint end_page;

  struct Book *next;
}

#endif
