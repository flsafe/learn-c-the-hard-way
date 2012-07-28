#ifndef _db_h
#define _db_h

#define DB_FILE "/usr/local/devpkg/db"
#define DB_DIR "/usr/local/devpkg/"

int DB_init();
int DB_list();
int DB_update();
int DB_find();

#endif
