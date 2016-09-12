#ifndef MESSAGE_H
#define MESSAGE_H 1

struct Message {
    char *event;
    void *data;
    unsigned int messageId;
    char mt;
    char dt;
};

#endif
