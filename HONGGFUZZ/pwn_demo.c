
int foo()
{
    char buf[10]={};
    read(0, buf, 20);
    return 1;
}

int main(void)
{
    foo();
    return 0;
}