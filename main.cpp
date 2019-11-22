#include <stdio.h>
#include <queue>

using namespace std;

int convert(char car) {
    if(car >= '0' and car <= '9')
        return car-'0';
    else if(car == 'A'){
        return 1;}
    else if(car == 'T'){
        return 10;}
    else if(car == 'J'){
        return 11;}
    else if(car == 'Q'){
        return 12;}
    else if(car == 'K'){
        return 13;}
}
int main() {
    char input[50];
    int card[52];
    int it;
    while(true) {
        for(it = 0; it < 52; it++) {
            scanf("%s", input);
            if(input[0] == '#') return 0;
            card[it] = convert(input[1]);
        }
        queue<int> A, B;
        for(it = 51; it >= 0; it--) {
            if(it%2) A.push(card[it]);
            else    B.push(card[it]);
        }
        int turn = 1;//0 A, 1 B
        int judge = -1;
        queue<int> H;//heap
        while(true) {
            if(turn == 0 && A.empty()) {
                judge = 0;
                break;
            }
            if(turn == 1 && B.empty()) {
                judge = 1;
                break;
            }
            int card_temp;
            if(turn == 0)
                card_temp = A.front(), A.pop();
            else
                card_temp = B.front(), B.pop();
            //printf("%d - %c %d %d\n", CARD, turn+'A', A.size(), B.size());
            H.push(card_temp);
            turn = 1-turn;
            int ended = 1;
            while(card_temp >= 11 || card_temp == 1) {
                ended = 0;
                int paid;
                if(card_temp == 1)
                    paid = 4;
                else if(card_temp == 11)
                    paid = 1;
                else if(card_temp == 12)
                    paid = 2;
                else if(card_temp == 13)
                    paid = 3;
                for(it = 0; it < paid; it++) {
                    if(turn == 0 && A.empty()) {
                        judge = 0;
                        break;
                    }
                    if(turn == 1 && B.empty()) {
                        judge = 1;
                        break;
                    }
                    if(turn == 0)
                        card_temp = A.front(), A.pop();
                    else
                        card_temp = B.front(), B.pop();
                    H.push(card_temp);
                    //printf("%d - %c\n", CARD, turn+'A');
                    if(card_temp == 1 || card_temp >= 11)//change
                        break;
                }
                if(judge >= 0)  break;
                turn = 1-turn;
            }
            if(judge >= 0)  break;
            if(ended == 0) {
                if(turn == 0) {
                    while(!H.empty()) {
                        A.push(H.front());
                        H.pop();
                    }
                } else {
                    while(!H.empty()) {
                        B.push(H.front());
                        H.pop();
                    }
                }
            }
        }
        int a;
        if(judge){
            a= A.size();
        }else
           a = B.size();
        printf("%d%3d\n", 2-judge,  a);
    }
    return 0;
}