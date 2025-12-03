// fast read using getchar()
inline unsigned long long readULL()
{
    int c = getchar();
    while (c != EOF && (c < '0' || c > '9'))
        c = getchar();
    unsigned long long x = 0;
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + (unsigned long long)(c - '0');
        c = getchar();
    }
    return x;
}
inline unsigned int readUInt()
{
    int c = getchar();
    while (c != EOF && (c < '0' || c > '9'))
        c = getchar();
    unsigned int x = 0;
    while (c >= '0' && c <= '9')
    {
        x = x * 10u + (unsigned int)(c - '0');
        c = getchar();
    }
    return x;
}