#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct words {
    char word[15];
    int c;
    struct words *next;
    struct words *prev;
} node;

node *head = NULL;
node *tail = NULL;

int min=0,max=0,lenght=0;
void insert_end(int value, char word[]) {

    node *new, *temp;
    lenght++;
    new = (node *) malloc(sizeof(node));
    new->c = value;
    new->next = NULL;
    strcpy(new->word, word);

    if (head == NULL) {
        head = new;
        tail = new;
        head->prev =NULL;
        head->next = NULL;
        return;
    }

    temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new;
    new->next = NULL;
    new->prev = temp;
    tail = new;

}

void insert_head(int value, char word[]) {
    node *t;
    lenght++;
    t = (node *) malloc(sizeof(node));   //bos node yaratilir
    t->c = value;                       // deger atamasi
    strcpy(t->word, word);               // deger atamasi

    if (head == NULL) {     //eger head yoksa head olarak atanır
        head = t;
        head->next = NULL;
        head->prev = NULL;
        tail = t;
        return;
    }

    t->next = head;     // yeni node basa eklenir
    head->prev = t;
    head = t;           // yeni node head olarak atanir
    head->prev = NULL;
}

void insert(int value, char word[]) {
    node *new, *temp;
    temp = head;

    new = (node *) malloc(sizeof(node));   //bos node yaratilir
    new->c = value;     // deger atamasi
    strcpy(new->word, word);               // deger atamasi

    if (head == NULL) {     //eger head yoksa head olarak atanır
        head = new;
        head->next = NULL;
        head->prev = NULL;
        return;
    }


    for(int i = 0; i < lenght; i++){

        if(temp->c-1 >= value && temp->next->c+1 <= value){
            node *t = temp->next;
            new->prev = temp;
            new->next = temp->next;
            temp->next = new;
            t->prev = new;
            return;
        }
        if(temp->c == value){
            node *t = temp->next;
            new->next = t;
            new->prev = temp;
            temp->next = new;
            t->prev = new;
            return;
        }
        else
            temp = temp->next;

    }


}

void printList(node *temp) {
    FILE *cikti=fopen("cikti.txt","w");
    int a = 1;
    if (temp == NULL)
        printf("Liste bos");
    while (temp != NULL) {
        printf("%d -): %s : %d \n", a, temp->word, temp->c);
        fprintf(cikti,"%d -): %s : %d \n", a, temp->word, temp->c);
        a++;
        temp = temp->next;
    }
    fclose(cikti);
}

bool searchList(char *ptr) {
    node *temp;
    temp = head;
    if (temp == NULL)
        return true;
    else {
        while (temp != NULL) {
            if (strcmp(temp->word, ptr) == 0)
                return false;
            else
                temp = temp->next;
        }
    }
    return true;

}
void order(int rep, char word[]){
    node *temp;
    temp = head;
    if(temp==NULL){
        insert_head(rep,word);
        min=rep;
        max=rep;
        return;
    }
    else if(min>=rep){
        insert_end(rep,word);
        min=rep;
        return;
    }
    else if(max<=rep){
        insert_head(rep,word);
        max=rep;
        return;
    }
    else{
        insert(rep,word);
    }

}
int main() {
    FILE *f, *f2;
    char *search, *p;
    int rep,ar=0;
    search = malloc(20 * sizeof(char));
    p = malloc(20 * sizeof(char));
    f = fopen("metin.txt", "r");
    f2 = fopen("metin.txt", "r");
    while (fscanf(f, "%s", p) != EOF) {
        rep = 0;
        if(searchList(p)){
            ar++;
            while (fscanf(f2, "%s", search) != EOF) {
            if (strcmp(p, search) == 0) {
                rep++;
                }
            }
            order(rep,p);
            rewind(f2);
        }
    }
    fclose(f);
    fclose(f2);
    printList(head);
    return 0;
}
