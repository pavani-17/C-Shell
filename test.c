
#include "header.h"
#define ll long long int

int takeMeOut(ll n){
    struct timeval tv;
    tv.tv_usec = 0;
    tv.tv_sec = n;

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    int ret = select(1,&rfds, NULL, NULL, &tv);
    if(ret > 0){
        char c;
        scanf("%c",&c);
        if (c == 'q'){
            printf("Bye Bye\n");
            exit(0);
        }
    }
    return 0;
}

int main(){
    ll n;
    scanf("%lld",&n);
    while(1){
        printf("Hey here i go after every %lld secs\n",n);
        takeMeOut(n);
    }
}