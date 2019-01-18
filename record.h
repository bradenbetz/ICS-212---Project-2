struct record
{
    int              accountno;
    char             name[25];
    char             address[80];
    struct record*   next;
};
