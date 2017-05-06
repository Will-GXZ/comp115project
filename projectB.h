
/*Use reord.h to define your record struct
 */
#include "record.h"
#include "my_queue.h"

#ifndef PROJECTB_H
#define PROJECTB_H

// assume we can have at most 100 scanDesc, this can be changed
#define MAXSDNUM 100

/* Representation of a record ID. */
typedef int recordID;

/* Representation of a scan operation for a given file (details below). */
typedef int scanDesc;

typedef struct _scanner {
    fileDesc fd;
    int currentRid;
} scanner;

extern scanner *scannerTable;

/*  The operations below call the Buffer Manager API to retrieve pages of a file.
 *  You can use the same fileDesc representation as the Buffer Manager or a different one. 
 */

/* Initialize state used by the Heap File Layer. */
void HFL_init();

/* Create a file with the given filename. err = -2*/
errCode HFL_create_file(char* filename);

/* Open an existing file with the given filename and return a file descriptor.  */
fileDesc HFL_open_file(char* filename);

/* Close an open file with the given filename. err = -4 */
errCode HFL_close_file(fileDesc fd);

/* Insert a record into the file identified by fd. */
recordID HFL_insert_rec(fileDesc fd, record* rec);

/* Delete the record with the given ID from the file identified by fd. err = -6 */
errCode HFL_delete_rec(fileDesc fd, recordID rid);

/* Make rec point to the first record in file fd. err = -7 */
errCode HFL_get_first_rec(fileDesc fd, record** rec);

/* Advance rec to the next record in fd. err = -8 */
errCode HFL_get_next_rec(fileDesc fd, record** rec);

/* Make rec point to the record in fd with ID rec_id. err = -9 */
errCode HFL_get_this_rec(fileDesc fd, recordID rid, record** rec);

 // Return a scanDesc for file fd. This is the primary operation of the Heap File Layer. At any given point in 
 // * time, there could be one or more scans of the same relation in progress, so you need to have multiple
 // * scanDescs to keep track of multiple scan iterators. 
scanDesc HFL_open_file_scan(fileDesc fd);

/* Make rec point to the next record in the scan identified by scanDesc. err = -11 */
errCode HFL_find_next_rec(scanDesc sd, record** rec);

/* Close the file scan abstraction identified by scanDesc. err = -12 */
errCode HFL_close_file_scan(scanDesc sd);

/* Print an error message.*/
void HFL_print_error(errCode ec);

///////////////////////
// helper functions////
///////////////////////

// get map array of a block
void get_mapArray(char ** map, const block *);

// release all memory allocated in heap, include HFL and BML and queue
void free_heap_memory(void); 

#endif  
