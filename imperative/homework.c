#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Entry {
    char name[30];
    char ph_num[30];
}Entry;

typedef struct Book{
    Entry* ptr;
    int inserted;
    int actual_size;

}Book;


void init(Book* book, int size){
    
    
    (*book).ptr = malloc(sizeof(Entry)*(size));
    
    (*book).actual_size = size;
    
    if((*book).ptr == NULL){
        printf("No Memory");
        exit(1);
    }
    (*book).inserted = 0;
}

void destroy(Book* book){
    free((*book).ptr);
    (*book).ptr = NULL;
}

bool insert(Book* book, char* person_name, char* person_number){
    if((*book).inserted < (*book).actual_size){

        int cnt = 0;
        for(int i=0; i<(*book).inserted; i++){
            if(strcmp(person_name, (*book).ptr[i].name)==0){
                strcpy((*book).ptr[i].ph_num, person_number);
                cnt++;
            }
        }
        if(cnt == 0)
        {
            strcpy((*book).ptr[(*book).inserted].name, person_name);
            strcpy((*book).ptr[(*book).inserted].ph_num, person_number);
            
            (*book).inserted++;
            return true;


        }

    }
    return false;

}

char* get(char* person_name, Book* book){
    for(int i=0; i<(*book).inserted; i++)
    {
        if(strcmp(person_name, (*book).ptr[i].name)==0)
        {
            return (*book).ptr[i].ph_num;
        }
    }
    return NULL;
}

void print(Book* book){
    for(int i=0; i<(*book).inserted; i++){
       printf("%s %s\n", (*book).ptr[i].name, (*book).ptr[i].ph_num);
      
    }
    return ;
}

void dump(Book* book, char *myfile){
    FILE *fptr;
    fptr = fopen(myfile, "w");

    for(int i=0; i<(*book).inserted; i++){
       fprintf(fptr, "%s %s\n", (*book).ptr[i].name, (*book).ptr[i].ph_num);
      
    }

    fclose(fptr);
    return ;
}


int main() {
    Book book;
    init(&book, 5);
    insert(&book, "Igor", "597500050");
    insert(&book, "Pati", "599176085");
    insert(&book, "Maro", "599906084");
    insert(&book, "Anachka", "595187798");

    //update a number
    insert(&book, "Maro", "222333444");

    //insert more that memory can handle
    insert(&book, "ZZZZZZZ", "00000000");
    insert(&book, "ZZZZZZZ", "00000000");
    insert(&book, "ZZZZZZZ", "00000000");
    print(&book);

    //check get function
    char* test_name = "Pati";
    char* test_number = get(test_name, &book);
    printf("%s if number of %s", test_number, test_name);

    //check dump function
    dump(&book, "Test_FIle.txt");
    
    //destroy:
    destroy(&book);
    

    return 0;
}