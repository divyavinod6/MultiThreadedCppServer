/*
proxy_parse.h --a HTTP request parsing library
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

#ifndef PROXY_PARSE
#define PROXY_PARSE

#define DEBUG 1

struct ParsedRequest {
    char *method;
    char *protocol;
    char *host;
    char *port;
    char *path;
    char *version;
    char *buf;
    size_t buflen;
    struct ParsedHeader *headers;
    size_t headersused;
    size_t headerslen;
};


struct ParsedHeader {
    char * key;
    size_t keylen;
    char * value;
    size_t valuelen;
};

// empty parsing object to be used once for single request buffer
struct ParsedRequest* ParsedRequest_create();

// parsing req buffer in buf
int ParsedRequest_parse(struct ParsedRequest * parse, const char * buf,int buflen);

// destroy parsing object
void ParsedRequest_destroy(struct ParsedRequest * pr);

// retrieve entire buffer from parsed req obj
int ParsedRequest_unparse(struct ParsedRequest *pr,char *buf,size_t buflen);

// retrieve entire buffer from parsed req obj, but not request line
int ParsedRquest_unparse_headers(struct ParsedRequest *pr, char *buf,size_t buflen);

// total length including request line, headers and trailing \r\n
size_t ParsedRequest_totalLen(struct ParsedRequest *pr);

// length including headers and trailing /r/n but excluding request line
size_t ParsedHeader_headersLen(struct ParsedRequest *pr);

// set, get and remove null-terminated header keys and values
int ParsedHeader_set(struct ParsedRequest *pr,const char * key, const char * value);
struct ParsedHeader* ParsedHeader_get(struct ParsedRequest *pr,const char * key);
int ParsedHeader_remove (struct ParsedRequest *pr,const char * key);

// prints out debugging if DEBUG set to 1
void debug(const char * format, ...);


#endif
